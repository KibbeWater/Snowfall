# Snowfall Mod Menu

Mod menu for [Crab Game](https://store.steampowered.com/app/1782210/Crab_Game/), dani's gamified version of Crab Game.
This is not in as much active development as it used to be, game has largely died down and is now filled with bots. I have therefore lost interest and releasing my private mod menu written fully in C++ with an integrated Lua engine

## Features

### Lua Engine

The menu has an integrated Lua API to interact with the game. See the [docs](https://github.com/KibbeWater/Snowfall/wiki/Snowfall-Lua-API) here:
https://github.com/KibbeWater/Snowfall/wiki/Snowfall-Lua-API

### General
* Disable pre-game freeze
* Lagswitch (keybind is Q, cannot toggle in menu)
* Auto-Clicker - i.e auto-fire with guns
* Command Handler - enable chat commands, very WIP but allows you to use commands like "profile" and "give"
* Complete Daily - allows you to claim daily without doing the quest

### Combat
* God Mode
* Fast Swing - swing bats and other melees without cooldown
* No Throw Cooldown - removes cooldown on throwing snowballs
* Auto Snowball Refill - when throwing a snowball, will try to automatically replenish if close to a snowpile
* Infinite Ammo
* No Recoil
* Rapid Fire - Fast Swing but for some guns 

### Movement
* Speedhack
* AirJump - jump in the air
* Anti-Knockback - removes most game KB
* Advanced Anti-Knockback - WIP: intended to mitigate some flinging exploits to prevent you from being flung into the void

### Gamemodes

#### Red Light Green Light
* Red Light freeze - prevents movement packets from being sent during red light

#### Dorms
* Lights always on - prevents lights from going out

#### Glass Break
* Break Glass - if clicked before game start, will break all glass. If clicked during game, will show the correct path to win

### Item Giver
Give yourself a weapon of choice, does not work in normal play, players can only see that you are holding it, not shooting it.
