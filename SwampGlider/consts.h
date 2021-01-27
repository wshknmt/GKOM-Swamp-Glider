#pragma once

#include <GL\glew.h>
#include <glm/gtc/matrix_transform.hpp>

const GLuint WINDOW_WIDTH = 1280, WINDOW_HEIGHT = 720;
//800 600
// camera parameters
const GLfloat FIELD_OF_VIEW = 45.0f;
const glm::mat4 PROJECTION_MATRIX = glm::perspective(glm::radians(FIELD_OF_VIEW), (GLfloat)WINDOW_WIDTH / (GLfloat)WINDOW_HEIGHT, 0.1f, 100.0f);

// water
const GLfloat WATER_TEX_REPS = 10.0f;
const GLfloat WATER_SIZE = 200.0f;

const GLuint CIRCLE_VERTS = 128;

const GLfloat WINGS_NUM = 6.0f;
const GLfloat BIRD_QUANTITY = 200;
const int BIRD_HIGHT_PARAM = 2000;

const glm::vec3 LIGHT_POS_VERT(30.0f, 25.0f, 30.0f);
const glm::vec3 LIGHT_COLOR_VEC(1.0f, 1.0f, 1.0f);

const GLuint NUMBER_OF_LILIES = 80;
