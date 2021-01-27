#pragma once

#include <vector>
#include "Object.h"
#include "consts.h"

class Cuboid : public Object {

public:
	Cuboid(string textureFileName) : Object(textureFileName) {
		initialize();
	}
	Cuboid(glm::vec4 color) : Object(color) {
		//this->textureRepetitions = 0.0f; // to i tak jest nieuzywane
		initialize();
	}

private:
	void setVertices() override {
		this->vertices = {
			// sciana dolna
			-0.5f, -0.5f,  0.5f,	color[0], color[1],  color[2], color[3],	WATER_TEX_REPS,	0.0f,			0.0f, -1.0f, 0.0f,	//0		0
			 0.5f, -0.5f,  0.5f,	color[0], color[1],  color[2], color[3],	0.0f,			0.0f,			0.0f, -1.0f, 0.0f,	//1		1
			 0.5f, -0.5f, -0.5f,	color[0], color[1],  color[2], color[3],	0.0f,			WATER_TEX_REPS,	0.0f, -1.0f, 0.0f,	//2		2
			-0.5f, -0.5f, -0.5f,	color[0], color[1],  color[2], color[3],	WATER_TEX_REPS,	WATER_TEX_REPS,	0.0f, -1.0f, 0.0f,	//3		3
			// sciana gorna
			-0.5f,  0.5f,  0.5f,	color[0], color[1],  color[2], color[3],	0.0f,			WATER_TEX_REPS,	0.0f, 1.0f, 0.0f,	//4		4
			 0.5f,  0.5f,  0.5f,	color[0], color[1],  color[2], color[3],	WATER_TEX_REPS,	WATER_TEX_REPS,	0.0f, 1.0f, 0.0f,	//5		5
			 0.5f,  0.5f, -0.5f,	color[0], color[1],  color[2], color[3],	WATER_TEX_REPS,	0.0f,			0.0f, 1.0f, 0.0f,	//6		6
			-0.5f,  0.5f, -0.5f,	color[0], color[1],  color[2], color[3],	0.0f,			0.0f,			0.0f, 1.0f, 0.0f,	//7		7
			// sciana boczna lewa
			0.5f, -0.5f, -0.5f,		color[0], color[1],  color[2], color[3],	0.0f,			WATER_TEX_REPS,	0.0f, 0.0f, -1.0f,	//2		8
			-0.5f, -0.5f, -0.5f,	color[0], color[1],  color[2], color[3],	WATER_TEX_REPS,	WATER_TEX_REPS,	0.0f, 0.0f, -1.0f,	//3		9
			-0.5f,  0.5f, -0.5f,	color[0], color[1],  color[2], color[3],	0.0f,			0.0f,			0.0f, 0.0f, -1.0f,	//7		10
			0.5f,  0.5f, -0.5f,		color[0], color[1],  color[2], color[3],	WATER_TEX_REPS,	0.0f,			0.0f, 0.0f, -1.0f,	//6		11
			// sciana boczna przednia
			0.5f, -0.5f,  0.5f,		color[0], color[1],  color[2], color[3],	0.0f,			0.0f,			1.0f, 0.0f, 0.0f,	//1		12
			0.5f, -0.5f, -0.5f,		color[0], color[1],  color[2], color[3],	0.0f,			WATER_TEX_REPS,	1.0f, 0.0f, 0.0f,	//2		13
			0.5f,  0.5f, -0.5f,		color[0], color[1],  color[2], color[3],	WATER_TEX_REPS,	0.0f,			1.0f, 0.0f, 0.0f,	//6		14
			0.5f,  0.5f,  0.5f,		color[0], color[1],  color[2], color[3],	WATER_TEX_REPS,	WATER_TEX_REPS,	1.0f, 0.0f, 0.0f,	//5		15
			// sciana boczna prawa
			-0.5f, -0.5f,  0.5f,	color[0], color[1],  color[2], color[3],	WATER_TEX_REPS,	0.0f,			0.0f, 0.0f, 1.0f,	//0		16
			 0.5f, -0.5f,  0.5f,	color[0], color[1],  color[2], color[3],	0.0f,			0.0f,			0.0f, 0.0f, 1.0f,	//1		17
			 0.5f,  0.5f,  0.5f,	color[0], color[1],  color[2], color[3],	WATER_TEX_REPS,	WATER_TEX_REPS,	0.0f, 0.0f, 1.0f,	//5		18
			-0.5f,  0.5f,  0.5f,	color[0], color[1],  color[2], color[3],	0.0f,			WATER_TEX_REPS,	0.0f, 0.0f, 1.0f,	//4		19
			// sciana boczna tylna
			-0.5f, -0.5f,  0.5f,	color[0], color[1],  color[2], color[3],	WATER_TEX_REPS,	0.0f,			-1.0f, 0.0f, 0.0f,	//0		20
			-0.5f,  0.5f,  0.5f,	color[0], color[1],  color[2], color[3],	0.0f,			WATER_TEX_REPS,	-1.0f, 0.0f, 0.0f,	//4		21
			-0.5f, -0.5f, -0.5f,	color[0], color[1],  color[2], color[3],	WATER_TEX_REPS,	WATER_TEX_REPS,	-1.0f, 0.0f, 0.0f,	//3		22
			-0.5f,  0.5f, -0.5f,	color[0], color[1],  color[2], color[3],	0.0f,			0.0f,			-1.0f, 0.0f, 0.0f	//7		23
		};
	}

	void setIndices() override {
		this->indices = {
			16, 17, 19,
			17, 18, 19,
			12, 13, 14,
			12, 14, 15,
			8, 9, 10,
			10, 11, 8,
			20, 22, 23,
			20, 23, 21,
			0, 1, 2,
			0, 2, 3,
			4, 5, 6,
			4, 6, 7
		};
	}
};