# C++ Based Console Game
# Build Instructions
Open the build.bat file in the project directory
# Dependencies
The only dependency the project relies on is json.h used to parse the level files: found at - https://github.com/nlohmann/json \
The project also utilises some of the 
# Development Patterns Utilised
For the project overall i opted to use composition over inheritance. \
The prototype follows the basic pattern of having a main game loop, a level manager and a display/screen.
# Level Manager
The level manager contains references to all objects in the scene through the level struct, while also keeping track of the game state, player state and enemy state. \
The level manager is also responsible for loading each level from their respective level.json file and generating the scene.
# Display
The display class contains all the functions used to display content. \
The display create function is called to create a new console window and prepare the buffer ready for data. 
# Sprites And Objects
Each object/sprite on the screen contains an update and draw function called by the level manager.
# Enemies
As a result of not using inheritance, the enemy doesn't inherit from the sprite class, instead, the enemy object contains and controls a sprite object. \
Each enemy has a colour associated with it when spawned, this colour comes from a random selection of the colours contained in level.json file selected \
