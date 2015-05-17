# GreeneysRun
Endless Runner for Pebble / Pebble Time
![Greeney's Run Header Image](http://i.imgur.com/PR7sukm.png)


Check it out on the Pebble Store!

https://apps.getpebble.com/applications/554f9adb4e604b9ed3000071

The source code is divided as follows:
Collision.c/.h: Responsible for collision with Segments, Moving Platforms and Death zones

GameLogic.c/.h: Contains main game loop, resetting of game, inserting/patching of segments

Globals.c/.h: Contain all used global variables

GreenSquare.c: Contains the main function as well as callbacks to Pebble API (Timer, Clicks, FocusAPI,...)

Rendering.c/.h: Contains all rendering (backgrounds, segments, player, platforms, titlescreen, font...)

ResourceIO.c/.h: Contains functions used to read/write from persistent data, manipulate loaded data and some functions which are called when data is loaded

pebble-js-app.js: Contains Timeline functionality, pushing directly to the users timeline if a new highscore is achieved. Thanks to https://github.com/C-D-Lewis for the parts marked with "timeline lib"
