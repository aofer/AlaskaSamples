
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "common/Camera.h"
#include "SimpleMeshDemo.h"
#include "common/ResourceManager.h"

static void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}


int main(int argc, char *argv[])
{
	GLFWwindow* window;

	glfwSetErrorCallback(error_callback);

	if (!glfwInit())
		exit(EXIT_FAILURE);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

	window = glfwCreateWindow(640, 480, "Simple example", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwSetKeyCallback(window, key_callback);

	glfwMakeContextCurrent(window);

	//Init glew
	glewExperimental = true;

	if (glewInit() == GLEW_OK)
	{
		std::cout << "GLEW: Initialized" << std::endl;
	}

	if (glewIsSupported("GL_VERSION_4_5"))
	{
		std::cout << "GLEW GL_VERSION_4_5 is 4.5\n ";
	}
	else
	{
		std::cout << " GLEW GL_VERSION_4_5 not supported\n ";
	}

	Camera* camera = new Camera();
	camera->SetPosition(glm::vec3(-1.0, 2.0, -1.0));
	camera->SetLookAt(glm::vec3(0.0, 1.0, 0.0));
	ResourceManager* manager = new ResourceManager();
	IDemo* demo = new SimpleMeshDemo();
	demo->InitializeScene(manager);
	glfwSwapInterval(1);

	// NOTE: OpenGL error checks have been omitted for brevity

	while (!glfwWindowShouldClose(window))
	{
		float ratio;
		int width, height;


		glfwGetFramebufferSize(window, &width, &height);
		ratio = width / (float)height;

		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.0, 0.0, 0.0, 1.0);
		demo->Update(0.0);
		demo->Render(camera);



		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);

	glfwTerminate();
	exit(EXIT_SUCCESS);
}