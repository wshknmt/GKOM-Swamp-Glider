#pragma once

#include "Object.h"
#include <vector>

class Rudder : public Object {

public:
	GLfloat reps;
	Rudder(string textureName, GLfloat texture_repeats) : Object(textureName) {
		this->reps = texture_repeats * 1.0f;
		initialize();
	}

	Rudder(glm::vec4 color) : Object(color) {
		this->reps = 0.0f; // to i tak jest nieuzywane
		initialize();
	}


private:
	void setVertices() override {
		this->vertices = {
			0.0f,  0.1f,  0.0f,		0.0f, 0.0f,  0.0f,	0.0f,  0.0f,	//0
			0.0f,  0.1f,  0.2f,		0.0f, 0.0f,  0.0f,	0.0f,  0.0f,	//1
			0.0f,  1.0f,  0.2f,		0.0f, 0.0f,  0.0f,	0.0f,  0.0f,	//2
			0.0f,  1.0f,  0.0f,		0.0f, 0.0f,  0.0f,	0.0f,  0.0f,	//3
			1.0f, -0.25f, 0.0f,		0.0f, 0.0f, -1.0f,	0.0f,  0.0f,	//4
			1.0f, -0.25f, 0.2f,		0.0f, 0.0f, -1.0f,	0.0f,  0.0f,	//5
			1.0f,  1.3f,  0.2f,		0.0f, 0.0f, -1.0f,	0.0f,  0.0f,	//6
			1.0f,  1.3f,  0.0f,		0.0f, 1.0f,  0.0f,	0.0f,  0.0f,	//7
		};
	}

	void setIndices() override {
		this->indices = {
			0,1,2,
			0,3,2,
			0,3,7,
			0,4,7,
			4,7,6,
			4,5,6,
			5,1,2,
			5,6,2,
			0,4,5,
			0,1,5,
			3,2,6,
			3,7,6
		};
	}

};