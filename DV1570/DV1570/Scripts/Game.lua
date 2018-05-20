--LEVEL_PATH is a set global that contains the path of the level the player wants to play
print(LEVEL_PATH)

--have a collection of global tables for all defined types

PLAYERS = {}

levelFile = io.open(LEVEL_PATH, "r")
--[[When we are parsing the level, we first get the type 
of the defined object - then we know how many values to get
from the line to create an instance of the described object]]
if levelFile then
	print("Loading: " .. LEVEL_PATH)
	for line in levelFile:lines() do
		local type = line:match("(%a+)")
		print(type)
		if type == "Player" then
			local name, hp, x, y = line:match("(%a+) (%d+) (%d+) (%d+)")
			print(name .. " " .. hp .. " " ..  x .. " " ..  y)
			local newPlayer =  Player(name, hp, x, y)
			table.insert(PLAYERS, newPlayer)
		end
<<<<<<< HEAD
		if "Spawn" == type then
		
		end
		if "Boulder" == type then
		
		end
		if "Ground" == type then
		
=======
		if type == "Spawn" then
		 --create a spawnpoint and insert to spawnppoint table
		end
		if type == "Boulder" then
		--create a TileObject with boolean TRUE for indestructable
		end
		if type == "Ground" then
		--cretae TileObject with boolean FALSE for indestructable
>>>>>>> master
		end
	end
else
	error("BAD PATH - LEVEL NOT LOADED\n")
end
--in case of bad path return an error - make sure to check for it (!= EXIT_SUCCESS)

print("Number of Players: " .. #PLAYERS)

CAN_SHOOT = true