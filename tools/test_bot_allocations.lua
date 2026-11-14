-- Standalone Lua 5.3 test. The runner supplies BASELINE_BOT_SOURCE from git HEAD.
dofile('tools/test_bot_lifecycle.lua')
local start_at = assert(BASELINE_BOT_SOURCE:find('function getUnitToSpawn(units)', 1, true))
local end_at = assert(BASELINE_BOT_SOURCE:find('function onGameStart()', start_at, true))
local env = setmetatable({}, {__index = _G})
assert(load(BASELINE_BOT_SOURCE:sub(start_at, end_at - 1), 'baseline-selection', 't', env))()
local reference = env.getUnitToSpawn
function BotApi.Commands:Income() return 10 end
local units = {}
for i = 1, 200 do
    units[i] = {unit='test'..i, cost=10, charge=0, wait_at_quant=0,
                class=UnitClass.Infantry, priority=i % 7 + 1}
end
onGameStart()
Quants = 1
for seed = 1, 1000 do
    math.randomseed(seed)
    local expected = reference(units)
    math.randomseed(seed)
    assert(getUnitToSpawn(units) == expected, 'weighted choice changed at seed '..seed)
end
-- Metadata is not a catalog entry and must not terminate candidate iteration.
units.count = 201
assert(getUnitToSpawn(units), 'metadata prevented purchase selection')
units.count = nil
local counts = {}
BotApi.Scene.Flags = {{occupant=1}, {occupant=2}, {occupant=0}}
assert(getFlagTable(counts) == counts)
assert(counts.captured == 1 and counts.enemy == 1 and counts.neutral == 1)
BotApi.Scene.Flags = {}
getFlagTable(counts)
assert(counts.captured == 0 and counts.enemy == 0 and counts.neutral == 0)
local function allocation_kib(fn)
    collectgarbage('collect')
    collectgarbage('stop')
    local before = collectgarbage('count')
    for i = 1, 1000 do assert(fn(units)) end
    local allocated = collectgarbage('count') - before
    collectgarbage('restart')
    collectgarbage('collect')
    return allocated
end
local old_kib, new_kib = allocation_kib(reference), allocation_kib(getUnitToSpawn)
assert(new_kib < old_kib * 0.1, 'temporary allocation reduction below 90%')
local context
for i = 1, 10 do
    local name, value = debug.getupvalue(getUnitToSpawn, i)
    if name == 'Context' then context = value end
end
assert(context and next(context.CandidateUnits) == nil and next(context.CandidateRates) == nil,
       'candidate buffers retained references')
Quants = 0
assert(getUnitToSpawn(units) == nil, 'early purchase allowed')
onGameStop()
assert(next(context.CandidateUnits) == nil and next(context.CandidateRates) == nil)
print(string.format('PASS: 1000 seeded choices, metadata, flags, buffer cleanup; '
    ..'1000 selections / 200 candidates allocated %.1f -> %.1f KiB (standalone Lua)', old_kib, new_kib))
