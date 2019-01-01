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
float gap = 0.7f;
const float tableW = 15.0f;
const float tableH = 0.3f;

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

float deltaTime = 0.0f;	// Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame

float yaw = -90.0f, pitch = 0.0f;

glm::vec3 lightPos = glm::vec3(-5.0f, 10.0f, 5.0f);
//simple triangle

float fingerZ = 2.0f;
float fingerSpeed = 0.02f;

float r = 0.25, h = 0.4;
float s = (1 / sqrt(2)) * r;

glm::vec3 tablePosition = glm::vec3(0.0f, -0.75f, -2.5f);
glm::vec3 tilePositions[8];

const float PI = 3.14;

GLfloat lim = asin((gap - d) / (2 * hh)) * 180 / PI;
GLfloat max = 90 - (atan(d / gap)) * 180 / PI;

bool fallSwitch = false;
GLfloat angle[8] = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };

int main()
{
	std::cout << "lim = " << lim << std::endl;
	std::cout << "max = " << max << std::endl;

	float table[] = {
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
	};


	float f = 0.143;

	float vertices[] = {

	//front lower half
	-hw,  -hh,  hd,  0.0f, 0.273f, 0.0f,  0.0f, 1.0f,
	hw,  0,		hd,  f, 0.0f, 0.0f,  0.0f, 1.0f,
	hw,  -hh,   hd,  f, 0.273f, 0.0f,  0.0f, 1.0f,
	hw,  0,		hd,  f, 0.0f, 0.0f,  0.0f, 1.0f,
	-hw,  0,	hd,  0.0f, 0.0f, 0.0f,  0.0f, 1.0f,
	-hw,  -hh,  hd,  0.0f, 0.273f, 0.0f,  0.0f, 1.0f,

	//front upper half
	-hw,  0,  hd,  1 - f, 0.273f, 0.0f,  0.0f, 1.0f,
	hw,  hh,  hd,  1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
	hw,  0,   hd,  1.0f, 0.273f, 0.0f,  0.0f, 1.0f,
	hw,  hh,  hd,  1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
	-hw,  hh, hd,  1 - f, 0.0f, 0.0f,  0.0f, 1.0f,
	-hw,  0,  hd,  1 - f, 0.273f, 0.0f,  0.0f, 1.0f,

	//back
	-hw, -hh, -hd,  0.0f, 1.0f, 0.0f,  0.0f, -1.0f,
	hw, -hh,  -hd,  0.15f, 1.0f, 0.0f,  0.0f, -1.0f,
	hw,  hh,  -hd,  0.15f, 0.4f, 0.0f,  0.0f, -1.0f,
	hw,  hh,  -hd,  0.15f, 0.4f, 0.0f,  0.0f, -1.0f,
	-hw,  hh, -hd,  0.0f, 0.4f, 0.0f,  0.0f, -1.0f,
	-hw, -hh, -hd,  0.0f, 1.0f, 0.0f,  0.0f, -1.0f,

	//left side
	-hw,  hh,  hd,  0.3f, 0.4f, -1.0f,  0.0f,  0.0f,
	-hw,  hh, -hd,  0.15f, 0.4f, -1.0f,  0.0f,  0.0f,
	-hw, -hh, -hd,  0.15f, 1.0f, -1.0f,  0.0f,  0.0f,
	-hw, -hh, -hd,  0.15f, 1.0f, -1.0f,  0.0f,  0.0f,
	-hw, -hh,  hd,  0.3f, 1.0f, -1.0f,  0.0f,  0.0f,
	-hw,  hh,  hd,  0.3f, 0.4f, -1.0f,  0.0f,  0.0f,

	//right side
	hw,  hh,  hd,  0.6f, 0.4f, 1.0f,  0.0f,  0.0f,
	hw,  hh, -hd,  0.3f, 0.4f, 1.0f,  0.0f,  0.0f,
	hw, -hh, -hd,  0.3f, 1.0f, 1.0f,  0.0f,  0.0f,
	hw, -hh, -hd,  0.3f, 1.0f, 1.0f,  0.0f,  0.0f,
	hw, -hh,  hd,  0.6f, 1.0f, 1.0f,  0.0f,  0.0f,
	hw,  hh,  hd,  0.6f, 0.4f, 1.0f,  0.0f,  0.0f,

	//bottom
	-hw, -hh, -hd,  0.9f, 1.0f, 0.0f, -1.0f,  0.0f,
	hw, -hh, -hd,  0.9f, 0.4f, 0.0f, -1.0f,  0.0f,
	hw, -hh,  hd,  0.6f, 0.4f, 0.0f, -1.0f,  0.0f,
	hw, -hh,  hd,  0.6f, 0.4f, 0.0f, -1.0f,  0.0f,
	-hw, -hh,  hd,  0.6f, 1.0f, 0.0f, -1.0f,  0.0f,
	-hw, -hh, -hd,  0.9f, 1.0f, 0.0f, -1.0f,  0.0f,

	//top
	-hw,  hh, -hd,  0.9f, 1.0f, 0.0f,  1.0f,  0.0f,
	hw,  hh, -hd,  0.9f, 0.4f, 0.0f,  1.0f,  0.0f,
	hw,  hh,  hd,  0.6f, 0.4f, 0.0f,  1.0f,  0.0f,
	hw,  hh,  hd,  0.6f, 0.4f, 0.0f,  1.0f,  0.0f,
	-hw,  hh,  hd,  0.6f, 1.0f, 0.0f,  1.0f,  0.0f,
	-hw,  hh, -hd,  0.9f, 1.0f, 0.0f,  1.0f,  0.0f

	};

	glm::vec3 bFingerNormal = -glm::cross(glm::vec3(-r, 0.0f, 0.0f), glm::vec3(-s, 0.0f, s));

	glm::vec3 fingerNormals[8];
	fingerNormals[0] = glm::cross(glm::vec3(-s, 0.0f, s) - glm::vec3(0.0f, h, 0.0f),
						glm::vec3(-r, 0.0f, 0.0f) - glm::vec3(0.0f, h, 0.0f));
	fingerNormals[1] = glm::cross(glm::vec3(0.0f, 0.0f, r) - glm::vec3(0.0f, h, 0.0f),
						glm::vec3(-s, 0.0f, s) - glm::vec3(0.0f, h, 0.0f));
	fingerNormals[2] = glm::cross(glm::vec3(s, 0.0f, s) - glm::vec3(0.0f, h, 0.0f),
						glm::vec3(0.0f, 0.0f, r) - glm::vec3(0.0f, h, 0.0f));
	fingerNormals[3] = glm::cross(glm::vec3(r, 0.0f, 0.0f) - glm::vec3(0.0f, h, 0.0f),
						glm::vec3(s, 0.0f, s) - glm::vec3(0.0f, h, 0.0f));

	fingerNormals[4] = glm::cross(glm::vec3(s, 0.0f, -s) - glm::vec3(0.0f, h, 0.0f),
						glm::vec3(r, 0.0f, 0.0f) - glm::vec3(0.0f, h, 0.0f));
	fingerNormals[5] = glm::cross(glm::vec3(0.0f, 0.0f, -r) - glm::vec3(0.0f, h, 0.0f),
						glm::vec3(s, 0.0f, -s) - glm::vec3(0.0f, h, 0.0f));
	fingerNormals[6] = glm::cross(glm::vec3(-s, 0.0f, -s) - glm::vec3(0.0f, h, 0.0f),
						glm::vec3(0.0f, 0.0f, -r) - glm::vec3(0.0f, h, 0.0f));
	fingerNormals[7] = glm::cross(glm::vec3(-r, 0.0f, 0.0f) - glm::vec3(0.0f, h, 0.0f),
						glm::vec3(-s, 0.0f, -s) - glm::vec3(0.0f, h, 0.0f));

	float finger[] = {
		-r, 0.0f, 0.0f, fingerNormals[0].x, fingerNormals[0].y, fingerNormals[0].z,
		0.0f, h, 0.0f, fingerNormals[0].x, fingerNormals[0].y, fingerNormals[0].z,
		-s, 0.0f, s, fingerNormals[0].x, fingerNormals[0].y, fingerNormals[0].z,

		-s, 0.0f, s, fingerNormals[1].x, fingerNormals[1].y, fingerNormals[1].z,
		0.0f, h, 0.0f, fingerNormals[1].x, fingerNormals[1].y, fingerNormals[1].z,
		0.0f, 0.0f, r, fingerNormals[1].x, fingerNormals[1].y, fingerNormals[1].z,

		0.0f, 0.0f, r, fingerNormals[2].x, fingerNormals[2].y, fingerNormals[2].z,
		0.0f, h, 0.0f,	fingerNormals[2].x, fingerNormals[2].y, fingerNormals[2].z,
		s, 0.0f, s, fingerNormals[2].x, fingerNormals[2].y, fingerNormals[2].z,

		s, 0.0f, s, fingerNormals[3].x, fingerNormals[3].y, fingerNormals[3].z,
		0.0f, h, 0.0f, fingerNormals[3].x, fingerNormals[3].y, fingerNormals[3].z,
		r, 0.0f, 0.0f, fingerNormals[3].x, fingerNormals[3].y, fingerNormals[3].z,

		r, 0.0f, 0.0f, fingerNormals[4].x, fingerNormals[4].y, fingerNormals[4].z,
		0.0f, h, 0.0f, fingerNormals[4].x, fingerNormals[4].y, fingerNormals[4].z,
		s, 0.0f, -s, fingerNormals[4].x, fingerNormals[4].y, fingerNormals[4].z,

		s, 0.0f, -s, fingerNormals[5].x, fingerNormals[5].y, fingerNormals[5].z,
		0.0f, h, 0.0f, fingerNormals[5].x, fingerNormals[5].y, fingerNormals[5].z,
		0.0f, 0.0f, -r, fingerNormals[5].x, fingerNormals[5].y, fingerNormals[5].z,

		0.0f, 0.0f, -r, fingerNormals[6].x, fingerNormals[6].y, fingerNormals[6].z,
		0.0f, h, 0.0f, fingerNormals[6].x, fingerNormals[6].y, fingerNormals[6].z,
		-s, 0.0f, -s, fingerNormals[6].x, fingerNormals[6].y, fingerNormals[6].z,

		-s, 0.0f, -s, fingerNormals[7].x, fingerNormals[7].y, fingerNormals[7].z,
		0.0f, h, 0.0f, fingerNormals[7].x, fingerNormals[7].y, fingerNormals[7].z,
		-r, 0.0f, 0.0f, fingerNormals[7].x, fingerNormals[7].y, fingerNormals[7].z,

		//podstawa
		- r, 0.0f, 0.0f, bFingerNormal.x, bFingerNormal.y, bFingerNormal.z,
		0.0f, 0.0f, 0.0f, bFingerNormal.x, bFingerNormal.y, bFingerNormal.z,
		-s, 0.0f, s, bFingerNormal.x, bFingerNormal.y, bFingerNormal.z,

		-s, 0.0f, s, bFingerNormal.x, bFingerNormal.y, bFingerNormal.z,
		0.0f, 0.0f, 0.0f, bFingerNormal.x, bFingerNormal.y, bFingerNormal.z,
		0.0f, 0.0f, r, bFingerNormal.x, bFingerNormal.y, bFingerNormal.z,

		0.0f, 0.0f, r, bFingerNormal.x, bFingerNormal.y, bFingerNormal.z,
		0.0f, 0.0f, 0.0f,	bFingerNormal.x, bFingerNormal.y, bFingerNormal.z,
		s, 0.0f, s, bFingerNormal.x, bFingerNormal.y, bFingerNormal.z,

		s, 0.0f, s, bFingerNormal.x, bFingerNormal.y, bFingerNormal.z,
		0.0f, 0.0f, 0.0f, bFingerNormal.x, bFingerNormal.y, bFingerNormal.z,
		r, 0.0f, 0.0f, bFingerNormal.x, bFingerNormal.y, bFingerNormal.z,

		r, 0.0f, 0.0f, bFingerNormal.x, bFingerNormal.y, bFingerNormal.z,
		0.0f, 0.0f, 0.0f, bFingerNormal.x, bFingerNormal.y, bFingerNormal.z,
		s, 0.0f, -s, bFingerNormal.x, bFingerNormal.y, bFingerNormal.z,

		s, 0.0f, -s, bFingerNormal.x, bFingerNormal.y, bFingerNormal.z,
		0.0f, 0.0f, 0.0f, bFingerNormal.x, bFingerNormal.y, bFingerNormal.z,
		0.0f, 0.0f, -r, bFingerNormal.x, bFingerNormal.y, bFingerNormal.z,

		0.0f, 0.0f, -r, bFingerNormal.x, bFingerNormal.y, bFingerNormal.z,
		0.0f, 0.0f, 0.0f, bFingerNormal.x, bFingerNormal.y, bFingerNormal.z,
		-s, 0.0f, -s, bFingerNormal.x, bFingerNormal.y, bFingerNormal.z,

		-s, 0.0f, -s, bFingerNormal.x, bFingerNormal.y, bFingerNormal.z,
		0.0f, 0.0f, 0.0f, bFingerNormal.x, bFingerNormal.y, bFingerNormal.z,
		-r, 0.0f, 0.0f, bFingerNormal.x, bFingerNormal.y, bFingerNormal.z
	};


	glm::vec2 texShifts[] = {
		glm::vec2(0.0f, 2 * f),
		glm::vec2(f, 3 * f),
		glm::vec2(4 * f, 4 * f),
		glm::vec2(5 * f, 6 * f),

		glm::vec2(3 * f, 2 * f),
		glm::vec2(f, 0.0f),
		glm::vec2(3 * f, 6 * f),
		glm::vec2(5 * f, 0.0f)
	};

	for (int i = 0; i < 8; ++i) {

		tilePositions[i] = glm::vec3(0.0f, 0.0f, -gap * i);
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

		Shader ourShader("vertexShader.vert", "fragmentShader.frag"); 
		Shader tableShader("tabVertShader.vert", "tabFragShader.frag");

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
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		// texture coord attribute
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
		//normals
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
		glEnableVertexAttribArray(2);

		unsigned int texture;
		glGenTextures(1, &texture);

		glBindTexture(GL_TEXTURE_2D, texture);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex_width, tex_height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);

		SOIL_free_image_data(image);

		//table

		unsigned int tabVBO, tabVAO;
		//create VAO and bind it
		glGenVertexArrays(1, &tabVAO);
		glBindVertexArray(tabVAO);

		//create VBO and bind it
		glGenBuffers(1, &tabVBO);
		glBindBuffer(GL_ARRAY_BUFFER, tabVBO);
		//From that point on any buffer calls we make (on the GL_ARRAY_BUFFER target) will be used 
		//to configure the currently bound buffer, which is VBO. 
		glBufferData(GL_ARRAY_BUFFER, sizeof(table), table, GL_STATIC_DRAW); //GL_DYNAMIC_DRAW, GL_STREAM_DRAW


		//Each vertex attribute takes its data from memory managed by a VBO and which VBO it takes its data from 
		//(you can have multiple VBOs) is determined by the VBO currently bound to GL_ARRAY_BUFFER when 
		//calling glVertexAttribPointer.

		// position attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
		//----------------------------------------------------------------------------

		//finger

		unsigned int fingerVBO, fingerVAO;
		//create VAO and bind it
		glGenVertexArrays(1, &fingerVAO);
		glBindVertexArray(fingerVAO);

		//create VBO and bind it
		glGenBuffers(1, &fingerVBO);
		glBindBuffer(GL_ARRAY_BUFFER, fingerVBO);
		//From that point on any buffer calls we make (on the GL_ARRAY_BUFFER target) will be used 
		//to configure the currently bound buffer, which is VBO. 
		glBufferData(GL_ARRAY_BUFFER, sizeof(finger), finger, GL_STATIC_DRAW); //GL_DYNAMIC_DRAW, GL_STREAM_DRAW

		//Each vertex attribute takes its data from memory managed by a VBO and which VBO it takes its data from 
		//(you can have multiple VBOs) is determined by the VBO currently bound to GL_ARRAY_BUFFER when 
		//calling glVertexAttribPointer.

		// position attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		ourShader.use();
		ourShader.setVec3("lightPos", lightPos);
		// Once during setup, after linking program.


		GLuint k = 0;
		GLfloat rot_speed = 0.1f;

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
			ourShader.setVec4("lightColor", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
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
		//	unsigned int modelLoc = glGetUniformLocation(ourShader.ID, "model");
		//	unsigned int viewLoc = glGetUniformLocation(ourShader.ID, "view");
			// pass them to the shaders (3 different ways)
		//	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			ourShader.setMat4("model", model);
		//	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
			ourShader.setMat4("view", view);
			// note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
			ourShader.setMat4("projection", projection);

			//draw vertexes from VAO
			glBindVertexArray(VAO);
			for (unsigned int i = 0; i < 8; i++)
			{
				glm::mat4 model;
				model = glm::translate(model, tilePositions[i]);

				if (fallSwitch) {
				
					//obracanie
					for (unsigned int i = 0; i < 8; i++)
					{

						if (i == 0 && angle[i] < max) {
							angle[i] = angle[i] + rot_speed;
							//		std::cout << "0 " << angle[i] << ", " << max << ", " << lim << std::endl;
						}

						if (i > 0 && i < 7 && angle[i - 1] > lim && angle[i] < max) {
							angle[i] = angle[i] + rot_speed;
							//		std::cout << "<4 " << angle[i] << ", " << max << ", " << lim << std::endl;
						}


						if (i == 7 && angle[i - 1] > lim && angle[i] < 90) {
							angle[i] = angle[i] + rot_speed;
							//		std::cout << "4 " << angle[i] << ", " << max << ", " << lim << std::endl;
						}

					//	if (i == 7) {
						//	break;
						//}
					}

						model = glm::translate(model, glm::vec3(0.0f, -hh, -hd));
						model = glm::rotate(model, glm::radians(-angle[i]), glm::vec3(1.0, 0.0, 0.0));
						model = glm::translate(model, glm::vec3(0.0f, hh, hd));
				}


			//	float angle = 0.0f;
			//	model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			//	model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
				ourShader.setMat4("model", model);
				
				ourShader.setVec2("TexShift", glm::vec2(texShifts[i]));

				glDrawArrays(GL_TRIANGLES, 0, 42);
			}
			// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		//	glBindVertexArray(0);

			tableShader.use();
			tableShader.setVec4("lightColor", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
			
			tableShader.setVec4("color", glm::vec4(0.0, 0.25, 0.02, 1.0));

			tableShader.setMat4("view", view);
			tableShader.setMat4("projection", projection);

			glBindVertexArray(tabVAO);
			model = glm::translate(model, tablePosition);
			model = glm::scale(model, glm::vec3(10.0f, 0.5f, 10.0f));
			tableShader.setMat4("model", model);
		 	glDrawArrays(GL_TRIANGLES, 0, 36);

			tableShader.setVec4("color", glm::vec4(0.5, 0.0, 0.0, 1.0));
			glBindVertexArray(fingerVAO);
			model = glm::mat4(1.0);

			//animation
			
			if (glfwGetKey(window, GLFW_KEY_E) != GLFW_PRESS) {
				if (fingerZ < 2.0f) {
					fingerZ = fingerZ + fingerSpeed;
				}
			}
			model = glm::translate(model, glm::vec3(0.0f, 0.4f, fingerZ) );

			model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
			tableShader.setMat4("model", model);
			glDrawArrays(GL_TRIANGLES, 0, 48);

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

		fallSwitch = false;
		for (int i = 0; i < 8; ++i) {
			angle[i] = 0.0f;
		}
	}

	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
		if (fingerZ - h - hd > tilePositions[0].z) {
			fingerZ -= fingerSpeed;
		}
		else {
			fallSwitch = true;
		}
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