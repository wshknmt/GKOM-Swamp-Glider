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
			// sciana gorna
			0.0f,  0.7f,  0.1f,		color[0], color[1],  color[2], color[3],	0.0f,  0.0f,	0.0f,  1.0f,  0.0f,	//2		0
			0.0f,  0.7f,  -0.1f,	color[0], color[1],  color[2], color[3],	0.0f,  0.0f,	0.0f,  1.0f,  0.0f,	//3		1
			1.0f,  1.0f, -0.1f,		color[0], color[1],  color[2], color[3],	0.0f,  0.0f,	0.0f,  1.0f,  0.0f,	//7		2
			1.0f,  1.0f,  0.1f,		color[0], color[1],  color[2], color[3],	0.0f,  0.0f,	0.0f,  1.0f,  0.0f,	//6		3
			// sciana dolna
			0.0f,  0.1f,  -0.1f,	color[0], color[1],  color[2], color[3],	0.0f,  0.0f,	0.0f,  -1.0f,  0.0f,//0		4
			0.0f,  0.1f,  0.1f,		color[0], color[1],  color[2], color[3],	0.0f,  0.0f,	0.0f,  -1.0f,  0.0f,//1		5
			1.0f, -0.25f, -0.1f,	color[0], color[1],  color[2], color[3],	0.0f,  0.0f,	0.0f,  -1.0f,  1.0f,//4		6
			1.0f, -0.25f, 0.1f,		color[0], color[1],  color[2], color[3],	0.0f,  0.0f,	0.0f,  -1.0f,  1.0f,//5		7
			// sciana boczna lewa
			0.0f,  0.1f,  0.1f,		color[0], color[1],  color[2], color[3],	0.0f,  0.0f,	0.0f,  0.0f,  1.0f,	//1		8
			0.0f,  0.7f,  0.1f,		color[0], color[1],  color[2], color[3],	0.0f,  0.0f,	0.0f,  0.0f,  1.0f,	//2		9
			1.0f,  1.0f,  0.1f,		color[0], color[1],  color[2], color[3],	0.0f,  0.0f,	0.0f,  0.0f,  1.0f,	//6		10
			1.0f, -0.25f, 0.1f,		color[0], color[1],  color[2], color[3],	0.0f,  0.0f,	0.0f,  0.0f,  1.0f,	//5		11
			// sciana boczna prawa
			0.0f,  0.1f,  -0.1f,	color[0], color[1],  color[2], color[3],	0.0f,  0.0f,	0.0f,  0.0f,  -1.0f,//0		12
			1.0f, -0.25f, -0.1f,	color[0], color[1],  color[2], color[3],	0.0f,  0.0f,	0.0f,  0.0f,  -1.0f,//4		13
			1.0f,  1.0f, -0.1f,		color[0], color[1],  color[2], color[3],	0.0f,  0.0f,	0.0f,  0.0f,  -1.0f,//7		14
			0.0f,  0.7f,  -0.1f,	color[0], color[1],  color[2], color[3],	0.0f,  0.0f,	0.0f,  0.0f,  -1.0f,//3		15
			// sciana boczna przednia
			0.0f,  0.1f,  -0.1f,	color[0], color[1],  color[2], color[3],	0.0f,  0.0f,	-1.0f,  0.0f,  0.0f,//0		16
			0.0f,  0.1f,  0.1f,		color[0], color[1],  color[2], color[3],	0.0f,  0.0f,	-1.0f,  0.0f,  0.0f,//1		17
			0.0f,  0.7f,  0.1f,		color[0], color[1],  color[2], color[3],	0.0f,  0.0f,	-1.0f,  0.0f,  0.0f,//2		18
			0.0f,  0.7f,  -0.1f,	color[0], color[1],  color[2], color[3],	0.0f,  0.0f,	-1.0f,  0.0f,  0.0f,//3		19
			// sciana boczna tylna
			1.0f, -0.25f, -0.1f,	color[0], color[1],  color[2], color[3],	0.0f,  0.0f,	1.0f,  0.0f,  0.0f,	//4		20
			1.0f, -0.25f, 0.1f,		color[0], color[1],  color[2], color[3],	0.0f,  0.0f,	1.0f,  0.0f,  0.0f,	//5		21
			1.0f,  1.0f,  0.1f,		color[0], color[1],  color[2], color[3],	0.0f,  0.0f,	1.0f,  0.0f,  0.0f,	//6		22
			1.0f,  1.0f, - 0.1f,	color[0], color[1],  color[2], color[3],	0.0f,  0.0f,	1.0f,  0.0f,  0.0f	//7		23
		};
	}

	void setIndices() override {
		this->indices = {
			16,17,18,
			16,19,18,
			12,15,14,
			12,13,14,
			20,23,22,
			20,21,22,
			11,8,9,
			11,10,9,
			4,6,7,
			4,5,7,
			1,0,3,
			1,2,3
		};
	}

};