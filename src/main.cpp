
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
#include "SphericalHarmonicsDemo.h"
#include "TerrainTesselationDemo.h"
#include "common/ResourceManager.h"
#include "common/Logger.h"

bool camMouseMove;
FPSCamera defaultCamera;
FPSCamera* activeCamera;
GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;
GLfloat lastX, lastY;
GLfloat mouseSensitivity = 0.5;
bool firstEntered = true;

#define REPEAT_OR_PRESS(action) (action == GLFW_PRESS || action == GLFW_REPEAT)

static void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	if (key == GLFW_KEY_W && REPEAT_OR_PRESS(action))
	{
		activeCamera->moveForward(0.3);
	}
	else if (key ==GLFW_KEY_S && REPEAT_OR_PRESS(action))
	{
		activeCamera->moveForward(-0.3);
	}
	else if (key == GLFW_KEY_A && REPEAT_OR_PRESS(action))
	{
		activeCamera->strafe(0.3);
	}
	else if (key == GLFW_KEY_D && REPEAT_OR_PRESS(action))
	{
		activeCamera->strafe(-0.3);
	}
	else if (key == GLFW_KEY_Q && REPEAT_OR_PRESS(action))
	{
		activeCamera->liftUp(0.3);
	}
	else if (key == GLFW_KEY_Z && REPEAT_OR_PRESS(action))
	{
		activeCamera->liftUp(-0.3);
	}
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
	{
		camMouseMove = true;
	}
	else
	{
		camMouseMove = false;
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

	if (camMouseMove)
	{
		//camera.MouseMovement(xOffset, yOffset);
		activeCamera->pitch(mouseSensitivity * yOffset);
		activeCamera->yaw(mouseSensitivity * -xOffset);
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

	glm::ivec2 windowSize = glm::ivec2(1024, 768);
	window = glfwCreateWindow(windowSize.x, windowSize.y, "OpenGL Tech Demos", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	//Init logger
	Common::Logger::GetInstance().Init();

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
	defaultCamera.SetPosition(glm::vec3(0.0, 1.0, -1.0));
	defaultCamera.SetLookAt(glm::vec3(0.0, 1.0, 1.0));
	activeCamera = &defaultCamera;
	ResourceManager* manager = new ResourceManager();
	SimpleMeshDemo* simpleMeshDemo = new SimpleMeshDemo();
	SphericalHarmonicsDemo* shDemo = new SphericalHarmonicsDemo();
	TerrainTesselationDemo* terrainDemo = new TerrainTesselationDemo();
	shDemo->InitializeScene(manager);
	simpleMeshDemo->InitializeScene(manager);
	terrainDemo->InitializeScene(manager);
	terrainDemo->SetWindowSize(windowSize);
	glfwSwapInterval(1);


	IDemo* currentDemo = terrainDemo;

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
		ImGui::SetWindowSize(ImVec2(300, screenHeight - 20));
		if (ImGui::CollapsingHeader("Demos", 0, true, true))
		{
			if (ImGui::TreeNode("Simple Mesh"))
			{
				bool clicked = ImGui::Button("Simple Mesh Demo");
				if (clicked)
				{
					currentDemo = simpleMeshDemo;
					activeCamera = &defaultCamera;
				}
				float colorA[4];
				ImGui::ColorPicker4("colorA", colorA, 0);
				glm::vec4 colorVec(colorA[0],colorA[1], colorA[2], colorA[3] );
				float colorB[4];
				ImGui::ColorPicker4("colorB", colorB, 0);
				glm::vec4 colorVecB(colorB[0], colorB[1], colorB[2], colorB[3]);
				float colorC[4];
				ImGui::ColorPicker4("colorC", colorC, 0);
				glm::vec4 colorVecC(colorC[0], colorC[1], colorC[2], colorC[3]);
				simpleMeshDemo->SetColors(colorVec, colorVecB, colorVecC);
				ImGui::TreePop();
			}
			if (ImGui::TreeNode("Spherical Harmonics"))
			{
				bool clicked = ImGui::Button("Spherical Harmonics Demo");
				if (clicked)
				{
					currentDemo = shDemo;
					activeCamera = shDemo->GetDemoCamera();
				}
				static int numBounces = 1;
				if (ImGui::SliderInt("Bounces", &numBounces, 0, 3, nullptr))
				{
					shDemo->SetBounces(numBounces);
				}
				//ImGui::InputText("Cubemap center",)


				ImGui::TreePop();
			}
			if (ImGui::TreeNode("Terrain Tessellation"))
			{
				bool clicked = ImGui::Button("Terrain Tessellation Demo");
				if (clicked)
				{
					currentDemo = terrainDemo;
					//activeCamera = terrainDemo->GetDemoCamera();
				}
				static int terrainSize = 10;
				static float displacementScale = 1.0;
				static int gridSize = 64;
				static bool enableWireframe = false;
				if (ImGui::SliderInt("Terrain Size", &terrainSize, 10, 1000, nullptr))
				{
					terrainDemo->SetTerrainSize(terrainSize);
				}
				if (ImGui::SliderFloat("Disp Scale", &displacementScale, 1.0, 200.0, nullptr))
				{
					terrainDemo->SetDisplacementScale(displacementScale);
				}
				if (ImGui::SliderInt("Grid Size", &gridSize, 64, 512, nullptr))
				{
					//terrainDemo->SetGridSize(gridSize);
				}
				if (ImGui::Checkbox("Enable Wireframe", &enableWireframe))
				{
					terrainDemo->SetWireframe(enableWireframe);
				}
				ImGui::TreePop();
			}


		}
		ImGui::End();

#pragma endregion

		currentDemo->Update(deltaTime);
		currentDemo->Render(activeCamera);


		//render gui
		glDisable(GL_STENCIL_TEST);
		// Render the GUI pannel.
		ImGui::Render();
		glEnable(GL_STENCIL_TEST);


		glfwSwapBuffers(window);

	}

	//Add cleanup code
	ImGui_ImplGlfwGL3_Shutdown();
	delete simpleMeshDemo;
	delete shDemo;

	glfwDestroyWindow(window);

	glfwTerminate();
	exit(EXIT_SUCCESS);
}