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
		const GLfloat TS = 4096.0f;
		this->vertices = {
			// sciana boczna z tylu
			-4.0f,  0.0f,  -2.0f,	color[0], color[1],  color[2], color[3],	1200/TS,  2700/TS,	-1.0f, 0.0f, 0.0f,	//0		0
			-4.0f,  0.0f,  2.0f,	color[0], color[1],  color[2], color[3],	0 / TS,  2700 / TS,	-1.0f, 0.0f, 0.0f,	//1		1
			-4.0f,  1.0f,  2.0f,	color[0], color[1],  color[2], color[3],	0 / TS,  3000 / TS,	-1.0f, 0.0f, 0.0f,	//2		2
			-4.0f,  1.0f,  -2.0f,	color[0], color[1],  color[2], color[3],	1200 / TS,  3000 / TS,	-1.0f, 0.0f, 0.0f,	//3		3
			// sciana boczna z prawej
			-4.0f,  0.0f,  2.0f,	color[0], color[1],  color[2], color[3],	1500 / TS,  2700 / TS,	0.0f, 0.0f, 1.0f,	//1		4
			3.0f,  0.0f,  2.0f,		color[0], color[1],  color[2], color[3],	1500 / TS,  600 / TS,	0.0f, 0.0f, 1.0f,	//5		5
			3.0f,  1.0f,  2.0f,		color[0], color[1],  color[2], color[3],	1200 / TS,  600 / TS,	0.0f, 0.0f, 1.0f,	//6		6
			-4.0f,  1.0f,  2.0f,	color[0], color[1],  color[2], color[3],	1200 / TS,  2700 / TS,	0.0f, 0.0f, 1.0f,	//2		7
			// sciana boczna przednia prawa
			3.0f,  0.0f,  2.0f,		color[0], color[1],  color[2], color[3],	3600 / TS,  600 / TS,	1.0f, 0.0f, 1.0f,	//5		8
			4.0f,  0.0f,  1.0f,		color[0], color[1],  color[2], color[3],	3300 / TS,  600 / TS,	1.0f, 0.0f, 1.0f,	//9		9
			4.0f,  1.0f,  1.0f,		color[0], color[1],  color[2], color[3],	3300 / TS,  900 / TS,	1.0f, 0.0f, 1.0f,	//10	10
			3.0f,  1.0f,  2.0f,		color[0], color[1],  color[2], color[3],	3600 / TS,  900 / TS,	1.0f, 0.0f, 1.0f,	//6		11
			// sciana boczna przednia
			4.0f,  0.0f,  1.0f,		color[0], color[1],  color[2], color[3],	2400 / TS,  0.0f,	1.0f, 0.0f, 0.0f,	//9		12
			4.0f,  0.0f,  -1.0f,	color[0], color[1],  color[2], color[3],	1800 / TS,  0.0f,	1.0f, 0.0f, 0.0f,	//8		13
			4.0f,  1.0f,  -1.0f,	color[0], color[1],  color[2], color[3],	1800 / TS,  300 / TS,	1.0f, 0.0f, 0.0f,	//11	14
			4.0f,  1.0f,  1.0f,		color[0], color[1],  color[2], color[3],	2400 / TS,  300 / TS,	1.0f, 0.0f, 0.0f,	//10	15
			// sciana boczna przednia lewa
			4.0f,  0.0f,  -1.0f,	color[0], color[1],  color[2], color[3],	3300 / TS,  300 / TS,	1.0f, 0.0f, -1.0f,	//8		16
			3.0f,  0.0f,  -2.0f,	color[0], color[1],  color[2], color[3],	3000 / TS,  300 / TS,	1.0f, 0.0f, -1.0f,	//4		17
			3.0f,  1.0f,  -2.0f,	color[0], color[1],  color[2], color[3],	3000 / TS,  600 / TS,	1.0f, 0.0f, -1.0f,	//7		18
			4.0f,  1.0f,  -1.0f,	color[0], color[1],  color[2], color[3],	3300 / TS,  600 / TS,	1.0f, 0.0f, -1.0f,	//11	19
			// sciana boczna lewa
			3.0f,  0.0f,  -2.0f,	color[0], color[1],  color[2], color[3],	2700/TS,  600 / TS,	0.0f, 0.0f, -1.0f,	//4		20
			-4.0f,  0.0f,  -2.0f,	color[0], color[1],  color[2], color[3],	2700 / TS,  2700 / TS,	0.0f, 0.0f, -1.0f,	//0		21
			-4.0f,  1.0f,  -2.0f,	color[0], color[1],  color[2], color[3],	3000 / TS,  2700 / TS,	0.0f, 0.0f, -1.0f,	//3		22
			3.0f,  1.0f,  -2.0f,	color[0], color[1],  color[2], color[3],	3000 / TS,  600 / TS,	0.0f, 0.0f, -1.0f,	//7		23
			// sciana dolna
			-4.0f,  0.0f,  -2.0f,	color[0], color[1],  color[2], color[3],	1500 / TS,  2700 / TS,	0.0f, -1.0f, 0.0f,	//0		24
			-4.0f,  0.0f,  2.0f,	color[0], color[1],  color[2], color[3],	2700 / TS,  2700 / TS,	0.0f, -1.0f, 0.0f,	//1		25
			3.0f,  0.0f,  2.0f,		color[0], color[1],  color[2], color[3],	2700 / TS,  600 / TS,	0.0f, -1.0f, 0.0f,	//5		26
			4.0f,  0.0f,  1.0f,		color[0], color[1],  color[2], color[3],	2400 / TS,  300 / TS,	0.0f, -1.0f, 0.0f,	//9		27
			4.0f,  0.0f,  -1.0f,	color[0], color[1],  color[2], color[3],	1800 / TS,  300 / TS,	0.0f, -1.0f, 0.0f,	//8		28
			3.0f,  0.0f,  -2.0f,	color[0], color[1],  color[2], color[3],	1500 / TS,  600 / TS,	0.0f, -1.0f, 0.0f,	//4		29
			// sciana gorna z lewej
			-4.0f,  1.0f,  -2.0f,	color[0], color[1],  color[2], color[3],	0 / TS,  2700 / TS,	0.0f, 1.0f, 0.0f,	//3		30
			-3.5f,  1.0f,  -1.0f,	color[0], color[1],  color[2], color[3],	300 / TS,  2550 / TS,	0.0f, 1.0f, 0.0f,	//15	31
			0.0f,  1.0f,  -1.0f,	color[0], color[1],  color[2], color[3],	300 / TS,  1500 / TS,	0.0f, 1.0f, 0.0f,	//19	32
			3.0f,  1.0f,  -2.0f,	color[0], color[1],  color[2], color[3],	0 / TS,  600 / TS,	0.0f, 1.0f, 0.0f,	//7		33
			// sciana gorna z przodu
			0.0f,  1.0f,  -1.0f,	color[0], color[1],  color[2], color[3],	300 / TS,  1500 / TS,	0.0f, 1.0f, 0.0f,	//19	34
			0.0f,  1.0f,  1.0f,		color[0], color[1],  color[2], color[3],	900 / TS,  1500 / TS,	0.0f, 1.0f, 0.0f,	//18	35
			3.0f,  1.0f,  2.0f,		color[0], color[1],  color[2], color[3],	1200 / TS,  600 / TS,	0.0f, 1.0f, 0.0f,	//6		36
			4.0f,  1.0f,  1.0f,		color[0], color[1],  color[2], color[3],	900 / TS,  300 / TS,	0.0f, 1.0f, 0.0f,	//10	37
			4.0f,  1.0f,  -1.0f,	color[0], color[1],  color[2], color[3],	300 / TS,  300 / TS,	0.0f, 1.0f, 0.0f,	//11	38
			3.0f,  1.0f,  -2.0f,	color[0], color[1],  color[2], color[3],	0 / TS,  600 / TS,	0.0f, 1.0f, 0.0f,	//7		39
			// sciana gorna z prawej
			-4.0f,  1.0f,  2.0f,	color[0], color[1],  color[2], color[3],	1200 / TS,  2700 / TS,	0.0f, 1.0f, 0.0f,	//2		40
			3.0f,  1.0f,  2.0f,		color[0], color[1],  color[2], color[3],	1200 / TS,  600 / TS,	0.0f, 1.0f, 0.0f,	//6		41
			0.0f,  1.0f,  1.0f,		color[0], color[1],  color[2], color[3],	900 / TS,  1500 / TS,	0.0f, 1.0f, 0.0f,	//18	42
			-3.5f,  1.0f,  1.0f,	color[0], color[1],  color[2], color[3],	900 / TS,  2550 / TS,	0.0f, 1.0f, 0.0f,	//14	43
			// sciana gorna z tylu
			-4.0f,  1.0f,  -2.0f,	color[0], color[1],  color[2], color[3],	0 / TS,  2700 / TS,	0.0f, 1.0f, 0.0f,	//3		44
			-4.0f,  1.0f,  2.0f,	color[0], color[1],  color[2], color[3],	1200 / TS,  2700 / TS,	0.0f, 1.0f, 0.0f,	//2		45
			-3.5f,  1.0f,  1.0f,	color[0], color[1],  color[2], color[3],	900 / TS,  2550 / TS,	0.0f, 1.0f, 0.0f,	//14	46
			-3.5f,  1.0f,  -1.0f,	color[0], color[1],  color[2], color[3],	300 / TS,  2550 / TS,	0.0f, 1.0f, 0.0f,	//15	47
			// siedzenie - boczna z tylu
			-3.5f,  0.25f, -1.0f,	0.0f,	  1.0f,			0.0f,	0.0f,		3271 / TS,  3871 / TS,	1.0f, 0.0f, 0.0f,	//12	48
			-3.5f,  0.25f, 1.0f,	0.0f,	  1.0f,			0.0f,	0.0f,		3871 / TS,  3871 / TS,	1.0f, 0.0f, 0.0f,	//13	49
			-3.5f,  1.0f,  1.0f,	color[0], color[1],  color[2], color[3],	3871 / TS,  4096 / TS,	1.0f, 0.0f, 0.0f,	//14	50
			-3.5f,  1.0f,  -1.0f,	color[0], color[1],  color[2], color[3],	3271 / TS,  4096 / TS,	1.0f, 0.0f, 0.0f,	//15	51
			// siedzenie - boczna z przodu
			0.0f,  0.25f, -1.0f,	0.0f,	  1.0f,			0.0f,	0.0f,		3271 / TS,  2821 / TS,	-1.0f, 0.0f, 0.0f,	//16	52
			0.0f,  0.25f, 1.0f,		0.0f,	  1.0f,			0.0f,	0.0f,		3871 / TS,  2821 / TS,	-1.0f, 0.0f, 0.0f,	//17	53
			0.0f,  1.0f,  1.0f,		color[0], color[1],  color[2], color[3],	3871 / TS,  2596 / TS,	-1.0f, 0.0f, 0.0f,	//18	54
			0.0f,  1.0f,  -1.0f,	color[0], color[1],  color[2], color[3],	3271 / TS,  2596 / TS,	-1.0f, 0.0f, 0.0f,	//19	55
			// siedzenie - boczna z prawej
			-3.5f,  0.25f, 1.0f,	0.0f,	  1.0f,			0.0f,	0.0f,		3871 / TS,  3871 / TS,	0.0f, 0.0f, -1.0f,	//13	56
			0.0f,  0.25f, 1.0f,		0.0f,	  1.0f,			0.0f,	0.0f,		3871 / TS,  2821 / TS,	0.0f, 0.0f, -1.0f,	//17	57
			0.0f,  1.0f,  1.0f,		color[0], color[1],  color[2], color[3],	4096 / TS,  2821 / TS,	0.0f, 0.0f, -1.0f,	//18	58
			-3.5f,  1.0f,  1.0f,	color[0], color[1],  color[2], color[3],	4096 / TS,  3871 / TS,	0.0f, 0.0f, -1.0f,	//14	59
			// siedzenie - boczna z lewej
			-3.5f,  0.25f, -1.0f,	0.0f,	  1.0f,			0.0f,	0.0f,		3271 / TS,  3871 / TS,	0.0f, 0.0f, 1.0f,	//12	60
			0.0f,  0.25f, -1.0f,	0.0f,	  1.0f,			0.0f,	0.0f,		3271 / TS,  2821 / TS,	0.0f, 0.0f, 1.0f,	//16	61
			0.0f,  1.0f,  -1.0f,	color[0], color[1],  color[2], color[3],	3046 / TS,  2821 / TS,	0.0f, 0.0f, 1.0f,	//19	62
			-3.5f,  1.0f,  -1.0f,	color[0], color[1],  color[2], color[3],	3046 / TS,  3871 / TS,	0.0f, 0.0f, 1.0f,	//15	63
			// siedzenie - dolna
			-3.5f,  0.25f, -1.0f,	0.0f,	  1.0f,			0.0f,	0.0f,		3271 / TS,  3871 / TS,	0.0f, 1.0f, 0.0f,	//12	64
			-3.5f,  0.25f, 1.0f,	0.0f,	  1.0f,			0.0f,	0.0f,		3871 / TS,  3871 / TS,	0.0f, 1.0f, 0.0f,	//13	65
			0.0f,  0.25f, 1.0f,		0.0f,	  1.0f,			0.0f,	0.0f,		3871 / TS,  2821 / TS,	0.0f, 1.0f, 0.0f,	//17	66
			0.0f,  0.25f, -1.0f,	0.0f,	  1.0f,			0.0f,	0.0f,		3271 / TS,  2821 / TS,	0.0f, 1.0f, 0.0f,	//16	67
		};
	}

	void setIndices() override {
		this->indices = {
			0,1,3,
			1,3,2,
			21,20,23,
			21,22,23,
			17,16,19,
			17,18,19,
			13,12,15,
			13,14,15,
			9,8,11,
			9,10,11,
			6,4,7,
			5,6,4,
			29,28,27,
			29,27,26,
			24,29,26,
			24,25,26,
			39,38,37,
			39,37,36,
			30,31,33,
			44,47,45,
			47,45,46,
			43,40,41,
			43,42,41,
			34,35,36,
			36,34,39,
			31,32,33,
			60,61,62,
			60,63,62,
			52,53,54,
			52,55,54,
			57,56,59,
			57,58,59,
			48,49,50,
			48,51,50,
			64,67,66,
			64,65,66
		};
	}
};