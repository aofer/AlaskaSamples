
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>

// ImGui
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"

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


void RenderImgui()
{

}

int main(int argc, char *argv[])
{
	GLFWwindow* window;

	glfwSetErrorCallback(error_callback);

	if (!glfwInit())
		exit(EXIT_FAILURE);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

	GLFWmonitor *monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* vidMode = glfwGetVideoMode(monitor);
	int screenWidth = vidMode->width;
	int screenHeight = vidMode->height;
	bool fullscreen = false;


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

	// Setup ImGui binding
	// Set the install_callbacks to false as i am setting up the GLFW input callbacks myself above.
	ImGui_ImplGlfwGL3_Init(window, false);
	//SetupImGuiStyle(1.0f);
	bool ImGui_WindowOpened = true;


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
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.0, 0.0, 0.0, 1.0);
		glEnable(GL_DEPTH_TEST);

		glfwPollEvents();
		ImGui_ImplGlfwGL3_NewFrame();

#pragma region ImGui
		ImGui::Begin("OpenGL Tech Demos", &ImGui_WindowOpened, ImVec2(0, 0), 0.5f, ImGuiWindowFlags_AlwaysUseWindowPadding | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoTitleBar);
		ImGui::SetWindowPos(ImVec2(10, 10));
		ImGui::SetWindowSize(ImVec2(255, screenHeight - 20));
		if (ImGui::CollapsingHeader("Demos", 0, true, true))
		{
			if (ImGui::TreeNode("Simple Mesh"))
			{
				bool clicked = ImGui::Button("Cube Mapping Demo");
				ImGui::TreePop();
			}
		}
		ImGui::End();

#pragma endregion
		demo->Update(0.0);
		demo->Render(camera);


		//render gui
		glDisable(GL_STENCIL_TEST);
		// Render the GUI pannel.
		ImGui::Render();
		glEnable(GL_STENCIL_TEST);


		glfwSwapBuffers(window);

	}

	glfwDestroyWindow(window);

	glfwTerminate();
	exit(EXIT_SUCCESS);
}