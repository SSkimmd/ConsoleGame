# C++ Based Console Game
# Build Instructions
Open the build.bat file in the project directory
# Dependencies
The only dependency the project relies on is json.h used to parse the level files: found at - https://github.com/nlohmann/json \
The project also utilises some of the 
# Development Patterns Utilised
The prototype follows the basic pattern of having a main game loop and a level manager. \
The level manager contains references to all objects in the scene through the level struct, while also keeping track of the game state, player state and enemy state. \
The level manager is also responsible for loading each level from their respective level.json file and generating the scene. 
# Sprites And Objects
Each object/sprite on the screen contains an update and draw function called by the level manager.
