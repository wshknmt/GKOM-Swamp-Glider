#pragma once
#include "consts.h"
#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

using namespace glm;

class Camera {

private:
	GLFWwindow* window;
	glm::vec3 positionVector;
	glm::mat4 ViewMatrix;
	GLfloat hAngle;
	GLfloat vAngle;
	GLfloat movementSpeed;
	GLfloat mouseSpeed;
	bool initialRun = true;
public:
	Camera::Camera(GLFWwindow* window, glm::vec3 positionVector, GLfloat hAngle,
		GLfloat vAngle, GLfloat movementSpeed, GLfloat mouseSpeed);
		
	glm::mat4 getViewMatrix();

	void refresh();
};
