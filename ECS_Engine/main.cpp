// ECS ENGINE

#include <Application.h>

int main(int argc, char* argv[])
{
	// Create our application
	sas::Application* app = new sas::Application();

	// Start the game loop
	app->Run();
	return 0;
}