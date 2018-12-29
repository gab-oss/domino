#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL.h>
#include <iostream>

#include "Shader.h"

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

const GLuint WIDTH = 800, HEIGHT = 600;

const float d = 0.2, hw = 0.25f, hh = 0.5f;
const float hd = d / 2;


glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

float deltaTime = 0.0f;	// Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame

float yaw = -90.0f, pitch = 0.0f;

//simple triangle

int main()
{

		float vertices[] = {

		//front lower half
		-hw,  -hh,  hd,  0.0f, 0.0f,
		hw,  0,		hd,  1.0f, 0.0f,
		hw,  -hh,   hd,  1.0f, 1.0f,
		hw,  0,		hd,  1.0f, 1.0f,
		-hw,  0,	hd,  0.0f, 1.0f,
		-hw,  -hh,  hd,  0.0f, 0.0f,

		//front upper half
		-hw,  0,  hd,  0.0f, 0.0f,
		hw,  hh,  hd,  1.0f, 0.0f,
		hw,  0,   hd,  1.0f, 1.0f,
		hw,  hh,  hd,  1.0f, 1.0f,
		-hw,  hh, hd,  0.0f, 1.0f,
		-hw,  0,  hd,  0.0f, 0.0f,

		//back
		-hw, -hh, -hd,  1.0f, 0.0f,
		hw, -hh,  -hd,   1.0f, 1.0f,
		hw,  hh,  -hd,   0.0f, 1.0f,
		hw,  hh,  -hd,  0.0f, 1.0f,
		-hw,  hh, -hd,  0.0f, 0.0f,
		-hw, -hh, -hd,  1.0f, 0.0f,

		//left side
		-hw,  hh,  hd,  1.0f, 0.0f,
		-hw,  hh, -hd,  1.0f, 1.0f,
		-hw, -hh, -hd,  0.0f, 1.0f,
		-hw, -hh, -hd,  0.0f, 1.0f,
		-hw, -hh,  hd,  0.0f, 0.0f,
		-hw,  hh,  hd,  1.0f, 0.0f,

		//right side
		hw,  hh,  hd,  1.0f, 0.0f,
		hw,  hh, -hd,  1.0f, 1.0f,
		hw, -hh, -hd,  0.0f, 1.0f,
		hw, -hh, -hd,  0.0f, 1.0f,
		hw, -hh,  hd,  0.0f, 0.0f,
		hw,  hh,  hd,  1.0f, 0.0f,

		//bottom
		-hw, -hh, -hd,  0.0f, 1.0f,
		hw, -hh, -hd,  1.0f, 1.0f,
		hw, -hh,  hd,  1.0f, 0.0f,
		hw, -hh,  hd,  1.0f, 0.0f,
		-hw, -hh,  hd,  0.0f, 0.0f,
		-hw, -hh, -hd,  0.0f, 1.0f,

		//top
		-hw,  hh, -hd,  0.0f, 1.0f,
		hw,  hh, -hd,  1.0f, 1.0f,
		hw,  hh,  hd,  1.0f, 0.0f,
		hw,  hh,  hd,  1.0f, 0.0f,
		-hw,  hh,  hd,  0.0f, 0.0f,
		-hw,  hh, -hd,  0.0f, 1.0f

		};

/*	float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	}; */


	/*	glm::vec3 cubePositions[] = {
			glm::vec3(0.0f,  0.0f,  0.0f),
			glm::vec3(2.0f,  5.0f, -15.0f),
			glm::vec3(-1.5f, -2.2f, -2.5f),
			glm::vec3(-3.8f, -2.0f, -12.3f),
			glm::vec3(2.4f, -0.4f, -3.5f),
			glm::vec3(-1.7f,  3.0f, -7.5f),
			glm::vec3(1.3f, -2.0f, -2.5f),
			glm::vec3(1.5f,  2.0f, -2.5f),
			glm::vec3(1.5f,  0.2f, -1.5f),
			glm::vec3(-1.3f,  1.0f, -1.5f)
		}; */


	glm::vec3 tilePositions[8];

	for (int i = 0; i < 8; ++i) {

		tilePositions[i] = glm::vec3(0.0f, 0.0f, -0.7f * i);
	}

	if (glfwInit() != GL_TRUE)
	{
		cout << "GLFW initialization failed" << endl;
		return -1;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	try
	{
		GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Domino", nullptr, nullptr);

		if (window == nullptr) {
			throw exception("GLFW window not created");
			glfwTerminate();
			return -1;
		}

		glfwMakeContextCurrent(window);

		glewExperimental = GL_TRUE;
		if (glewInit() != GLEW_OK){
			throw exception("GLEW Initialization failed");
			return -1;
		}

		glViewport(0, 0, WIDTH, HEIGHT);
		glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

		Shader ourShader("vertexSHader.vert", "fragmentShader.frag"); 

		glEnable(GL_DEPTH_TEST);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// prepare textures
		int tex_width, tex_height;
		unsigned char* image = SOIL_load_image("domino_tex.png", &tex_width, &tex_height, 0, SOIL_LOAD_RGB);
		if (image == nullptr)
			throw exception("Failed to load texture file");

		unsigned int VBO, VAO;
		//create VAO and bind it
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		//create VBO and bind it
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		//From that point on any buffer calls we make (on the GL_ARRAY_BUFFER target) will be used 
		//to configure the currently bound buffer, which is VBO. 
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //GL_DYNAMIC_DRAW, GL_STREAM_DRAW


		//Each vertex attribute takes its data from memory managed by a VBO and which VBO it takes its data from 
		//(you can have multiple VBOs) is determined by the VBO currently bound to GL_ARRAY_BUFFER when 
		//calling glVertexAttribPointer.

		// position attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		// texture coord attribute
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		unsigned int texture;
		glGenTextures(1, &texture);

		glBindTexture(GL_TEXTURE_2D, texture);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex_width, tex_height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);

		SOIL_free_image_data(image);

		// main event loop
		while (!glfwWindowShouldClose(window))
		{
			//Process input from keyboard
			processInput(window);

			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			glBindTexture(GL_TEXTURE_2D, texture);

			// activate shader
			ourShader.use();

			// create transformations
			glm::mat4 model;
			glm::mat4 projection;
			glm::mat4 view;
			float radius = 10.0f;
			float camX = sin(glfwGetTime()) * radius;
			float camZ = cos(glfwGetTime()) * radius;
			view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

			model = glm::mat4(1.0);
	//		model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.5f));
			projection = glm::perspective(glm::radians(45.0f), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
			// retrieve the matrix uniform locations
			unsigned int modelLoc = glGetUniformLocation(ourShader.ID, "model");
			unsigned int viewLoc = glGetUniformLocation(ourShader.ID, "view");
			// pass them to the shaders (3 different ways)
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
			// note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
			ourShader.setMat4("projection", projection);

			//draw vertexes from VAO
			glBindVertexArray(VAO);
			for (unsigned int i = 0; i < 8; i++)
			{
				glm::mat4 model;
				model = glm::translate(model, tilePositions[i]);
				float angle = 0.0f;
				model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			//	model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
				ourShader.setMat4("model", model);

				glDrawArrays(GL_TRIANGLES, 0, 42);
			}
			// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
			glBindVertexArray(0);
			glfwPollEvents();

			float currentFrame = glfwGetTime();
			deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;

			// Swap the screen buffers
			glfwSwapBuffers(window);
		}

		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glfwTerminate();
	}

	catch (exception ex)
	{
		cout << ex.what() << endl;
	}

	return 0;
}

void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	float cameraSpeed = 0.03f;
	float rotationSpeed = 0.2f;


	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {

		cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
		cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
		cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

		yaw = -89.0f;
		pitch = 0.0f;

	}

	else {
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			cameraPos += cameraSpeed * cameraFront;
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			cameraPos -= cameraSpeed * cameraFront;
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;

		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
			yaw += rotationSpeed;
		if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
			yaw -= rotationSpeed;
		if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
			pitch -= rotationSpeed;
		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
			pitch += rotationSpeed;

		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;

		glm::vec3 front;
		front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		front.y = sin(glm::radians(pitch));
		front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		cameraFront = glm::normalize(front);
	}
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}