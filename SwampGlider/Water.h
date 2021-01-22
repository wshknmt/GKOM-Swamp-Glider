#pragma once

#include <vector>
#include "Object.h"
#include "consts.h"

class Water : public Object {

public:
	Water(string textureFileName) : Object(textureFileName) {
		initialize();
	}

private:
	void setVertices() override {
		this->vertices = {
			-0.5f, -0.5f,  0.5f,	0.0f, 0.0f, 0.0f, 1.0f,	WATER_TEX_REPS,  0.0f,	          //0
			 0.5f, -0.5f,  0.5f,	0.0f, 0.0f, 0.0f, 1.0f,	0.0f,  0.0f,	                  //1
			 0.5f, -0.5f, -0.5f,	0.0f, 0.0f, 0.0f, 1.0f,	0.0f,  WATER_TEX_REPS,	          //2
			-0.5f, -0.5f, -0.5f,	0.0f, 0.0f, 0.0f, 1.0f,	WATER_TEX_REPS,  WATER_TEX_REPS,  //3
			-0.5f,  0.5f,  0.5f,	0.0f, 0.0f, 0.0f, 1.0f,	0.0f,  WATER_TEX_REPS,	          //4
			 0.5f,  0.5f,  0.5f,	0.0f, 0.0f, 0.0f, 1.0f,	WATER_TEX_REPS,  WATER_TEX_REPS,  //5
			 0.5f,  0.5f, -0.5f,	0.0f, 0.0f, 0.0f, 1.0f,	WATER_TEX_REPS,  0.0f,            //6
			-0.5f,  0.5f, -0.5f,	0.0f, 0.0f, 0.0f, 1.0f,	0.0f,  0.0f	                      //7
		};
	}

	void setIndices() override {
		this->indices = {
			0, 1, 4,
			1, 5, 4,
			1, 2, 6,
			1, 6, 5,
			2, 3, 7,
			7, 6, 2,
			0, 3, 7,
			0, 7, 4,
			0, 1, 2,
			0, 2, 3,
			4, 5, 6,
			4, 6, 7
		};
	}
};