#pragma once

#include <GL\glew.h>
#include <glm/gtc/matrix_transform.hpp>

const GLuint WINDOW_WIDTH = 800, WINDOW_HEIGHT = 600;

// camera parameters
const GLfloat FIELD_OF_VIEW = 45.0f;
const glm::mat4 PROJECTION_MATRIX = glm::perspective(glm::radians(FIELD_OF_VIEW), (GLfloat)WINDOW_WIDTH / (GLfloat)WINDOW_HEIGHT, 0.1f, 100.0f);

// water
const GLfloat WATER_TEX_REPS = 100.0f;

const GLuint CIRCLE_VERTS = 6;
