

#include <iostream>
#include <filesystem>
#include <string>
#include <sstream>
#include <fstream>

#include "glad\glad.h"
#include "GLFW\glfw3.h"
#include "../../mefGL/mefGL.h"

#include "glm/glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\type_ptr.hpp"

namespace conf
{
	int WIDTH = 800;
	int HEIGHT = 600;
	float aspectRatio = WIDTH / HEIGHT;

	
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	conf::WIDTH = width;
	conf::HEIGHT = height;
	conf::aspectRatio = static_cast<float>(conf::WIDTH) / conf::HEIGHT;

}

int main()
{
	GLFWwindow* window;
	
	if (!glfwInit())
	{
		std::cerr << "[ERROR] Failed initializing GLFW!\n";
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(conf::WIDTH, conf::HEIGHT, "Mefs Kreis", NULL, NULL);
	if (!window)
	{
		std::cerr << "[ERROR] Failed Creating a Window!\n";
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cerr << "[ERROR] Failed to initialize GLAD\n";
		return -1;
	}

	// GLFW Settings
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// OPENGL Settings
	glViewport(0, 0, conf::WIDTH, conf::HEIGHT);

	float width = 0.5f;
	float height = 0.5f;
	glm::vec2 pos = glm::vec2(0.0f, 0.0f);
	float radius = 0.5f;

	float vertices[] = {
		-width, -height, 0.0f,
		-width, height, 0.0f,
		width, -height, 0.0f,
		width, height, 0.0f
	};

	unsigned int indices[]{
		0, 1, 2,
		1, 2, 3
	};

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	std::string vertexStr;
	std::string fragmentStr;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		vShaderFile.open("src/Shader.vert");
		fShaderFile.open("src/Shader.frag");
		std::stringstream vShaderStream, fShaderStream;

		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		vShaderFile.close();
		fShaderFile.close();

		vertexStr = vShaderStream.str();
		fragmentStr = fShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cerr << "[ERROR] Failed Reading Shader File!\n";
	}

	const char* vShaderCode = vertexStr.c_str();
	const char* fShaderCode = fragmentStr.c_str();

	unsigned int vertexShader, fragmentShader;
	int success;
	char infoLog[512];
	
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vShaderCode, NULL);
	glCompileShader(vertexShader);

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cerr << "[ERROR] Failed Compiling Vertex Shader!\n" << infoLog << std::endl;;
	}

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fShaderCode, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cerr << "[ERROR] Failed Compiling Fragment Shader!\n" << infoLog << std::endl;;
	}

	unsigned int shader;
	shader = glCreateProgram();
	glAttachShader(shader, vertexShader);
	glAttachShader(shader, fragmentShader);
	glLinkProgram(shader);

	glGetProgramiv(shader, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shader, 512, NULL, infoLog);
		std::cerr << "[ERROR] Failed Linking Shader Program!\n" << infoLog << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	glm::mat4 model = glm::mat4(1.0f);

	glm::mat4 projection = glm::ortho(-1.0f * conf::aspectRatio, 1.0f * conf::aspectRatio, -1.0f, 1.0f, -1.0f, 1.0f);
	auto projLoc = glGetUniformLocation(shader, "u_proj");
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	while (!glfwWindowShouldClose(window))
	{
		glClearColor(1.0f, 1.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(shader);

		glm::mat4 projection = glm::ortho(-1.0f * conf::aspectRatio, 1.0f * conf::aspectRatio, -1.0f, 1.0f, -1.0f, 1.0f);
		auto projLoc = glGetUniformLocation(shader, "u_proj");
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));



		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
		glfwSwapBuffers(window);
		glfwPollEvents();

	}

	glfwTerminate();

	return 0;
}

