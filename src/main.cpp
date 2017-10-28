
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>

// ImGui
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"

#include "common/FPSCamera.h"
#include "SimpleMeshDemo.h"
#include "common/ResourceManager.h"

bool activeCamera;
FPSCamera camera;
GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;
GLfloat lastX, lastY;
GLfloat mouseSensitivity = 0.5;
bool firstEntered = true;

static void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	if (key == GLFW_KEY_W && action == GLFW_PRESS)
	{
		camera.moveForward(0.3);
	}
	else if (key ==GLFW_KEY_S && action == GLFW_PRESS)
	{
		camera.moveForward(-0.3);
	}
	else if (key == GLFW_KEY_A && action == GLFW_PRESS)
	{
		camera.strafe(0.3);
	}
	else if (key == GLFW_KEY_D && action == GLFW_PRESS)
	{
		camera.strafe(-0.3);
	}
	else if (key == GLFW_KEY_Q && action == GLFW_PRESS)
	{
		camera.liftUp(0.3);
	}
	else if (key == GLFW_KEY_Z && action == GLFW_PRESS)
	{
		camera.liftUp(-0.3);
	}
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
	{
		activeCamera = true;
	}
	else
	{
		activeCamera = false;
	}
}

void mouse_move_callback(GLFWwindow *window, double xPos, double yPos)
{

	if (firstEntered)
	{
		lastX = xPos;
		lastY = yPos;
		firstEntered = false;
	}

	GLfloat xOffset = xPos - lastX;
	GLfloat yOffset = lastY - yPos;
	lastX = xPos;
	lastY = yPos;

	if (activeCamera)
	{
		//camera.MouseMovement(xOffset, yOffset);
		camera.pitch(mouseSensitivity * yOffset);
		camera.yaw(mouseSensitivity * -xOffset);
	}

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


	window = glfwCreateWindow(1024, 768, "OpenGL Tech Demos", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, mouse_move_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
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


	//FPSCamera* camera = new FPSCamera();
	camera.SetPosition(glm::vec3(-1.0, 2.0, -1.0));
	camera.SetLookAt(glm::vec3(0.0, 1.0, 0.0));
	ResourceManager* manager = new ResourceManager();
	IDemo* demo = new SimpleMeshDemo();
	demo->InitializeScene(manager);
	glfwSwapInterval(1);

	// NOTE: OpenGL error checks have been omitted for brevity

	while (!glfwWindowShouldClose(window))
	{
		float ratio;
		int width, height;
		// Set frame time
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;


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

		demo->Update(deltaTime);
		demo->Render(&camera);


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