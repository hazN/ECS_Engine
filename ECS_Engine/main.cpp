//---------------------- ECS ENGINE ----------------------
/*
*						Group Project
* ------------------------------------------------------
*			Student's name			:	Student number	
* ------------------------------------------------------
*	->	Krupesh Parmar				:	1124374
*   ->	Hassan Assaf				:	0929917
*	->	Siraphong Chinsaengchai		:	1103475
* 
* 
*	Student mail :		k_parmar180076@fanshaweonline.ca
* 
*	Program name :		GAME DEVELOPMENT ADVANCED PROGRAMMING
*	Course name  :		Game Component Integration
*	
*			Sprint 1 : Milestone I ( Rendering )
*	
*	a) How to build this project:
*	- Select x64 platform
*	- Select Release configuration for best performance
*	- Right click on "ECS_Engine" from Solution Explorer and hit build
*	- The build is now created for selected platform
*	
*	b) How to run this project:
*	- You can run project only from Visual Studio using key "F5" or "Ctrl + F5"
*	
*	c) User inputs :
*	- Hold right click to interact with camera
*	- While right click is held down use WASD keys to move camera
*	- Hold down shift key to move faster
*	- Use Arrow keys to move the character
* 
*/

#include "thrift_src/LeaderboardClient.h"
#include <Application.h>

int main(int argc, char* argv[])
{
	// Create our application
	sas::Application* app = new sas::Application();

	LeaderboardClientCall();
	// Start the game loop
	app->Run();
	return 0;
}