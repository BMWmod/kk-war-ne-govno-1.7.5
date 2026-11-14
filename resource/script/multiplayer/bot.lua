require([[/script/multiplayer/bot.data]])

-- If something is wrong in here, feel free to tell me about it.

local Context = {
	Purchase = nil,
	SpawnInfo = nil,
	SquadTimers = {},
	TimedUnits = {},
	CandidateUnits = {},
	CandidateRates = {},
	FlagCounts = {},
	Running = false,
	Generation = 0
}

function addTimedUnit(unit)
	Context.TimedUnits[unit] = Quants + unit.charge * 100
end

function updateTimedUnits(unit_to_search)
	local expires = Context.TimedUnits[unit_to_search]
	if expires and Quants <= expires then
		return 0
	end
	Context.TimedUnits[unit_to_search] = nil
	return 1
end

local function clearBotState()
	Context.Running = false
	Context.Generation = Context.Generation + 1
	for squad, timer in pairs(Context.SquadTimers) do
		BotApi.Events:KillQuantTimer(timer)
	end
	Context.SquadTimers = {}
	Context.TimedUnits = {}
	Context.CandidateUnits = {}
	Context.CandidateRates = {}
	Context.FlagCounts = {}
	Context.Purchase = nil
	Context.SpawnInfo = nil
end

function readUnitsRaw(fname, units, army) 								-- Credit for parser goes to the maker of AggroAi.
	--if verbose then print("reading ", fname , " for ", army) end		-- You can enable prints for debug purposes.
	local f=io.open(fname, "r")
	if f~=nil then 
		while true do
			local asRead = f:read("*l")
			local line = asRead
			if line == nil then break end
			
			line = line:gsub(";.*","")
			line = line:gsub("^%s*(.-)%s*$", "%1")
			if (line:lower():find("[(]"..army:lower().."[)]") and line:len() > 0  -- only things of the current army
				and line:find("nobot")==nil 		-- no ammo suppliers.
				
				) -- no things for the support menu (all carried weapon don't work).
				then 
				--if (verbose) then print("parsing ", line) end
				local unit = line
				unit = unit:gsub( ".*name[(]", "")
				unit = unit:gsub( "[)].*", "")

				local cost = line
				cost = cost:gsub( ".*[{]cost ", "")
				cost = cost:gsub( ".*cost[(]", "")
				cost = cost:gsub( "[})].*", "")
				cost = tonumber(cost)
				
				local fcost = cost
				if(cost == nil) then cost = 197 end
				if(cost == 0) then cost = 1 end
				if (fcost == nil) then fcost = 0 end

				local count = 0 
				local charge = 0
				local fore = 0
				local group = 0
				for uc in line:gmatch(" c[(]([^)]*)[)]") do charge = charge + tonumber(uc) 
				end
				for uc in line:gmatch(" f[(]([^)]*)[)]") do fore = fore + tonumber(uc) 
				end
				for uc in line:gmatch("[{]fore ([0-9]+)[}]") do fore = fore + tonumber(uc) 
				end
				for uc in line:gmatch(" g[(]([^)]*)[)]") do group = uc 
				end
				
				fore=1-fore
				wait_at_quant=charge*fore*50+1
				if line:find('squad') then 
					for uc in line:gmatch("c[0-9]+[(][^)]*:([0-9]+)") do
					count = count + tonumber(uc)
					end
					if count>0 then
						cost=cost/count
					end
				end
				if (count==0) or (count==nil) then 
					count=1
				end
				if unit:len()>0 and not unit:match("{") then
					if line:find("bazookers") or line:find("stormtroopers2") then 
						units[units.count] = {unit = unit.."("..army..")", count = count, class = UnitClass.ATInfantry, priority = 2, fcost = fcost,
											 cost = cost, charge = charge, fore = fore, group = group, wait_at_quant = wait_at_quant}
						units.count = units.count+1
					elseif line:find(" side( ") then
						units[units.count] = {unit = unit.."("..army..")", count = count, class = UnitClass.Infantry, priority = 6, fcost = fcost,
											 cost = cost, charge = charge, fore = fore, group = group, wait_at_quant = wait_at_quant}
						units.count=units.count+1
					else 
						units[units.count] = {unit = unit.."("..army..")", count = count, class = UnitClass.Infantry, priority = 6, fcost = fcost,
											 cost = cost, charge = charge, fore = fore, group = group, wait_at_quant = wait_at_quant}
						units.count=units.count+1
					end	
				else 
					unit = line
					unit = unit:gsub( "{\"", "")
					unit = unit:gsub( "\".*", "")

					if not unit:match("mp/") and unit:len()>0 then
						units[units.count] = { unit = unit, count = count, class = UnitClass.Vehicle, priority = 2, fcost = fcost,
							cost = cost, charge = charge, fore = fore, group = group, wait_at_quant = wait_at_quant}

						if asRead:find("hero") then 
							units[units.count].class = UnitClass.Hero
							units[units.count].priority = 3
							units[units.count].wait_at_quant = units[units.count].wait_at_quant + (units[units.count].charge*20) -- *20 == floor(*100/5)
						elseif line:find("heavy") then 
							units[units.count].class = UnitClass.HeavyTank
							units[units.count].priority = 1
						elseif line:find("b[(]v4[)]") then 
								-- if verbose then print(unit, " read as tank, p:",cost) end
								units[units.count].class = UnitClass.Tank
								units[units.count].priority = 1
						elseif line:find("b[(]v5[)]") or line:find("b[(]vet[)]") then 
								-- if verbose then print(unit, " read as anti-tank, p:",cost) end
								units[units.count].class = UnitClass.ATTank
								units[units.count].priority = 1
						end
						units.count=units.count+1
					end
				end
				--if verbose then print(units[units.count-1].unit, " read as ",units[units.count-1].class.className, " squad of ", count, " costs ", units[units.count-1].cost, " charge/initial ", charge, wait_at_quant) end
			end
		end
		io.close(f) 
	end
end

function getFlagPriority(flag)
	if	   flag.occupant==BotApi.Instance.team 	    then return FlagPriority.Captured
	elseif flag.occupant==BotApi.Instance.enemyTeam then return FlagPriority.Enemy
	else 							  				   	 return FlagPriority.Neutral end
end

function getFlagToCapture(flagPoints)
	local flags_and_priorities = {}
	local max=0
	local getFP = getFlagPriority								-- Optimisation thing here.

	for i, flag in pairs(flagPoints) do
		local cur=math.random(80)
		if cur>max then
			max=cur
		end
		table.insert(flags_and_priorities, {name=flag, priority=cur})
	end

	local length = #flags_and_priorities
	local lim=0
	local min=math.floor(length/3)
	for i, flag in pairs(flags_and_priorities) do
		if flag.priority==max then
			local t=math.random(lim, length)
			if t>min then
				return flag.name
			else
				lim=lim+1
			end
		end
	end
	for i, flag in pairs(flags_and_priorities) do
	    return flag.name
	end
end

function getFlagTable(flags)
	local team_my=BotApi.Instance.team
	local team_enemy=BotApi.Instance.enemyTeam

	flags = flags or {}
	flags.captured, flags.enemy, flags.neutral = 0, 0, 0
	for i, flag in pairs(BotApi.Scene.Flags) do
		if 	   flag.occupant == team_my    then flags.captured = flags.captured+1
		elseif flag.occupant == team_enemy then flags.enemy    = flags.enemy+1
		else 									flags.neutral  = flags.neutral+1 end
	end

	return flags
end

function getUnitPriority(unit, enemy_has_tanks, flags)
	if unit.class==UnitClass.Infantry  and enemy_has_tanks		   then return 5 end
	if unit.class==UnitClass.Vehicle   and flags.neutral>0 		   then return 3 end
	if unit.class==UnitClass.Tank      and enemy_has_tanks		   then return 2 end
	if unit.class==UnitClass.HeavyTank and flags.enemy==0  		   then return 2 end
	if unit.class==UnitClass.Hero 	   and unit.cost<SpecialPoints then return 2 end

	if unit.class==UnitClass.HeavyTank and flags.captured<flags.enemy then
		return 3
	end

	if unit.class==ATInfantry then
		if enemy_has_tanks then
		 	return 4
		else
			return 1
		end
	end
	if unit.class==UnitClass.ATTank then
		if enemy_has_tanks then
		 	return 2
		else
			return 1
		end
	end

	return unit.priority
end

function getUnitToSpawn(units)
	if not units or #units == 0 then
		return nil
	end
	
	-- Reuse flat buffers instead of allocating a wrapper table per candidate.
	local candidates, rates = Context.CandidateUnits, Context.CandidateRates
	local candidate_count = 0
	local team_size=BotApi.Instance.teamSize
	local income, enemy_has_tanks, current_flags = BotApi.Commands:Income(BotApi.Instance.playerId), BotApi.Commands:EnemyHasTanks(), getFlagTable(Context.FlagCounts)
	local quants, updateTU, getUP = Quants, updateTimedUnits, getUnitPriority -- Some optimisation things here.
	local formula=(374*income-31.3*income*income+1.1*income*income*income-1.3) + (354.5*team_size-23*team_size*team_size-342)

	local total_rate=1
	-- The catalog is a dense array with a separate 'count' metadata field.
	for i, unit in ipairs(units) do

		if formula >= unit.cost and quants>unit.wait_at_quant then	-- Formulas
			if unit.charge>25 then
				if updateTU(unit)==0 then
					goto continue
				end
			end

			local rate = getUP(unit, enemy_has_tanks, current_flags)
			total_rate=total_rate+rate
			if rate>0 then
				candidate_count = candidate_count + 1
				candidates[candidate_count], rates[candidate_count] = unit, rate
			end
		end
		::continue::
	end

	if candidate_count == 0 then
		return nil
	end
	
	local selected_unit
	local rnd = math.floor(math.random()*total_rate)
	for i = 1, candidate_count do
		rnd=rnd - rates[i]
		if rnd < 1 then
			selected_unit=candidates[i]
			break
		end
	end
	-- Keep buffer capacity, but retain no references to candidates between calls.
	for i = 1, candidate_count do
		candidates[i], rates[i] = nil, nil
	end
	if selected_unit.charge>25 then
		addTimedUnit(selected_unit)
	end
	if selected_unit.class==Hero then
		SpecialPoints=SpecialPoints-selected_unit.cost
	end

	return selected_unit
end

function onGameStart()
	clearBotState()
	Context.Running = true
	math.randomseed(os.time()*BotApi.Instance.hostId)
	Quants=0

	local units={}
	units.count=1

	readAllUnits(sq, units, BotApi.Instance.army)

	Context.Purchase=units
	Context.SpawnInfo=getUnitToSpawn(Context.Purchase)
end

function onGameStop()
	clearBotState()
	collectgarbage("collect")		-- Maybe gc helps a little the game engine not to run out of memory after multiple games. At least i hope so...
end

function onGameQuant()
	if not Context.Running then return end
	Quants=Quants+1
	-- Release dead squads immediately, rather than retaining their callbacks
	-- until the two-minute order timer fires.
	for squad, timer in pairs(Context.SquadTimers) do
		if not BotApi.Scene:IsSquadExists(squad) then
			BotApi.Events:KillQuantTimer(timer)
			Context.SquadTimers[squad] = nil
		end
	end
	for unit, expires in pairs(Context.TimedUnits) do
		if Quants > expires then Context.TimedUnits[unit] = nil end
	end
	if not Context.SpawnInfo or BotApi.Commands:Spawn(Context.SpawnInfo.unit, MaxSquadSize) then
		Context.SpawnInfo=getUnitToSpawn(Context.Purchase)
	end
	
	for i, squad in pairs(BotApi.Scene.Squads) do
		if not Context.SquadTimers[squad] then
			setSquadOrder(captureFlag, squad, OrderRotationPeriod)
		end
	end
end

function captureFlag(squad)
	local flag = getFlagToCapture(BotApi.Scene.Flags)
	if flag then
		BotApi.Commands:CaptureFlag(squad, flag.name)
	end
end

function setSquadOrder(order, squad, delay)
	if not Context.Running or Context.SquadTimers[squad]
		or not BotApi.Scene:IsSquadExists(squad) then return end
	local generation = Context.Generation
	order(squad)
	local function schedule()
		local timer
		timer = BotApi.Events:SetQuantTimer(function()
			if not Context.Running or Context.Generation ~= generation
				or Context.SquadTimers[squad] ~= timer then return end
			Context.SquadTimers[squad] = nil
			if BotApi.Scene:IsSquadExists(squad) then
				order(squad)
				schedule()
			end
		end, delay)
		Context.SquadTimers[squad] = timer
	end
	schedule()
end

function onGameSpawn(args)
	setSquadOrder(captureFlag, args.squadId, OrderRotationPeriod)
end

BotApi.Events:Subscribe(BotApi.Events.GameStart, onGameStart)
BotApi.Events:Subscribe(BotApi.Events.GameEnd, onGameStop)
BotApi.Events:Subscribe(BotApi.Events.Quant, onGameQuant)
BotApi.Events:Subscribe(BotApi.Events.GameSpawn, onGameSpawn)
