// ECS ENGINE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <Application.h>

int main(int argc, char* argv[])
{
	sas::Application* app = new sas::Application();
	app->Run();
	return 0;
}