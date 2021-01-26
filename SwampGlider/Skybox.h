#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "shprogram.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <SOIL.h>
#include <iostream>

class Skybox {
private:

	unsigned int skyboxVAO, skyboxVBO;
	unsigned int cubemapTexture;
	ShaderProgram shader;
	std::vector<float> skyboxVertices;

	std::vector<std::string> faces {
		"test1.png",
		"test1.png",
		"test1.png",
		"test1.png",
		"test1.png",
		"test1.png"
	};

	unsigned int loadCubemap(std::vector<std::string> faces);

	void setupBuffers();

public:
	Skybox();

	~Skybox();

	void draw(glm::mat4 projection, glm::mat4 view);
};