// ECS ENGINE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

int main(int argc, char* argv[])
{
	glfwInit();
	GLFWwindow* m_Window = glfwCreateWindow(1920, 1080, "test", nullptr, nullptr);

	glfwMakeContextCurrent(m_Window);
	int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	while (true)
	{
		glClearColor(0.8f, 0.1f, 0.8f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}
	return 0;
}