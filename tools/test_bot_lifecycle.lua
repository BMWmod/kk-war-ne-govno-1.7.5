-- Run from the mod root with Lua 5.2+ (the game uses goto).
-- A standalone fake BotApi; this file must not be included by the game.
local timers, alive, commands = {}, {}, 0
local next_timer = 0
BotApi = {
    Instance = {hostId=1, army="rus", team=1, enemyTeam=2, teamSize=1, playerId=1},
    Scene = {Squads={}, Flags={}},
    Commands = {},
    Events = {GameStart=1, GameEnd=2, Quant=3, GameSpawn=4},
}
function BotApi.Scene:IsSquadExists(id) return alive[id] == true end
function BotApi.Commands:Spawn() return false end
function BotApi.Commands:Income() return 0 end
function BotApi.Commands:EnemyHasTanks() return false end
function BotApi.Commands:CaptureFlag() commands=commands+1 end
function BotApi.Events:Subscribe() end
function BotApi.Events:SetQuantTimer(callback, delay)
    next_timer=next_timer+1
    timers[next_timer]={callback=callback, delay=delay}
    return next_timer
end
function BotApi.Events:KillQuantTimer(id) timers[id]=nil end
package.preload["/script/multiplayer/bot.data"] = function()
    dofile("resource/script/multiplayer/bot.data.lua")
    function readAllUnits() end -- Avoid parsing real purchases in timer tests.
    return true
end
dofile("resource/script/multiplayer/bot.lua")
local function count(t)
    local n=0
    for _ in pairs(t) do n=n+1 end
    return n
end
local function only_timer()
    assert(count(timers)==1)
    return next(timers)
end
local function order() commands=commands+1 end

onGameStart()
alive[1]=true
setSquadOrder(order,1,120000)
setSquadOrder(order,1,120000)
onGameSpawn({squadId=1})
assert(count(timers)==1 and commands==1, "duplicate squad timer/order")
local id=only_timer()
local callback=timers[id].callback
timers[id]=nil
callback()
assert(count(timers)==1 and commands==2, "timer must reschedule exactly once")
callback() -- Re-delivery of an old callback cannot create a second timer.
assert(count(timers)==1 and commands==2, "stale callback was not rejected")
alive[1]=false
onGameQuant()
assert(count(timers)==0, "dead squad retained a timer")

alive[1]=true
setSquadOrder(order,1,120000)
local old_callback=timers[only_timer()].callback
onGameStop()
assert(count(timers)==0, "game end retained timers")
local old_commands=commands
old_callback()
onGameStart()
old_callback()
assert(count(timers)==0 and commands==old_commands, "previous match callback survived restart")

local a,b={charge=1},{charge=10}
Quants=0;addTimedUnit(a);addTimedUnit(b)
Quants=101
assert(updateTimedUnits(a)==1, "expired cooldown still blocked")
assert(updateTimedUnits(b)==0, "removing one cooldown lost another")
addTimedUnit(b);addTimedUnit(b)
Quants=1101
assert(updateTimedUnits(b)==0, "cooldown boundary changed")
Quants=1102
assert(updateTimedUnits(b)==1, "repeated cooldown did not expire")
addTimedUnit(b)
onGameStop();onGameStart()
assert(updateTimedUnits(b)==1, "previous match cooldown survived restart")
assert(getUnitToSpawn({count=1})==nil, "empty catalog selection failed")
onGameStop()
print("PASS: duplicate/dead/stale timers, match reset, cooldown expiry and empty catalog")
