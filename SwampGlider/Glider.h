#pragma once

#include "Object.h"
#include <vector>

class Glider : public Object {

public:
	Glider(string textureFileName) : Object(textureFileName) {
		initialize();
	}

	Glider(glm::vec4 color) : Object(color) {
		//this->textureRepetitions = 0.0f; // to i tak jest nieuzywane
		initialize();
	}

private:
	void setVertices() override {

		this->vertices = {
			-4.0f,  0.0f,  -2.0f,	color[0], color[1],  color[2], color[3],	0.0f,  0.0f,	//0
			-4.0f,  0.0f,  2.0f,	color[0], color[1],  color[2], color[3],	0.0f,  0.0f,	//1
			-4.0f,  1.0f,  2.0f,	color[0], color[1],  color[2], color[3],	0.0f,  0.0f,	//2
			-4.0f,  1.0f,  -2.0f,	color[0], color[1],  color[2], color[3],	0.0f,  0.0f,	//3
			3.0f,  0.0f,  -2.0f,	color[0], color[1],  color[2], color[3],	0.0f,  0.0f,	//4
			3.0f,  0.0f,  2.0f,		color[0], color[1],  color[2], color[3],	0.0f,  0.0f,	//5
			3.0f,  1.0f,  2.0f,		color[0], color[1],  color[2], color[3],	0.0f,  0.0f,	//6
			3.0f,  1.0f,  -2.0f,	color[0], color[1],  color[2], color[3],	0.0f,  0.0f,	//7
			4.0f,  0.0f,  -1.0f,	color[0], color[1],  color[2], color[3],	0.0f,  0.0f,	//8
			4.0f,  0.0f,  1.0f,		color[0], color[1],  color[2], color[3],	0.0f,  0.0f,	//9
			4.0f,  1.0f,  1.0f,		color[0], color[1],  color[2], color[3],	0.0f,  0.0f,	//10
			4.0f,  1.0f,  -1.0f,	color[0], color[1],  color[2], color[3],	0.0f,  0.0f,	//11
			-3.5f,  0.25f, -1.0f,	0.0f,	  1.0f,	 0.0f, 0.0f,				0.0f,  0.0f,	//12
			-3.5f,  0.25f, 1.0f,	0.0f,	  1.0f,	 0.0f, 0.0f,				0.0f,  0.0f,	//13
			-3.5f,  1.0f,  1.0f,	color[0], color[1],  color[2], color[3],	0.0f,  0.0f,	//14
			-3.5f,  1.0f,  -1.0f,	color[0], color[1],  color[2], color[3],	0.0f,  0.0f,	//15
			0.0f,  0.25f, -1.0f,	0.0f, 1.0f,  0.0f, 0.0f,					0.0f,  0.0f,	//16
			0.0f,  0.25f, 1.0f,		0.0f, 1.0f,  0.0f, 0.0f,				    0.0f,  0.0f,	//17
			0.0f,  1.0f,  1.0f,		color[0], color[1],  color[2], color[3],	0.0f,  0.0f,	//18
			0.0f,  1.0f,  -1.0f,	color[0], color[1],  color[2], color[3],	0.0f,  0.0f,	//19
		};
	}

	void setIndices() override {
		this->indices = {
			0,1,3,
			1,3,2,
			0,4,7,
			0,3,7,
			4,8,11,
			4,7,11,
			8,9,10,
			8,11,10,
			9,5,6,
			9,10,6,
			6,1,2,
			5,6,1,
			4,8,9,
			4,9,5,
			0,4,5,
			0,1,5,
			7,11,10,
			7,10,6,
			3,15,7,
			3,15,2,
			15,2,14,
			14,2,6,
			14,18,6,
			19,18,6,
			6,19,7,
			15,19,7,
			12,16,19,
			12,15,19,
			16,17,18,
			16,19,18,
			17,13,14,
			17,18,14,
			12,13,14,
			12,15,14,
			12,16,17,
			12,13,17
		};
	}
};