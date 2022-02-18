# ASCII-Game-Engine

Made by Tate Donnelly

January - February 2022

Platform: Windows

--------------------------------------------------------------------
## Code structure:
The proj2-Donnelly folder contains:
	- .cpp files and .h files (including a test files)
	- Visual Studio solution files (Microsoft Windows)
		- including proj2-Donnelly.sln
	- This incredible README.txt file
  - Sound folder
    - Holds music and sounds  
  - Sprite folder
    - Holds sprites and their frames  
	- A logfile (dragonfly)
--------------------------------------------------------------------

## How to compile:
To compile and run:

0) Extract contents of the folder

1) Build proj2-Donnelly.sln on Visual Studio (F7)

2) Compile (Ctrl+F7) and run the solution (F5)
	- Tests will run in the same solution

--------------------------------------------------------------------
## Additional notes:

Due to the nature of some tests and my engine, certain tests could not be run in doTests(). Instead, to run those tests, you will need to
set a test's corresponding boolean to true in the game.cpp file and compile the program as described in "How to compile". Only one 
boolean may be set to true at a time. Descriptions of the tests are next to the corresponding booleans.
