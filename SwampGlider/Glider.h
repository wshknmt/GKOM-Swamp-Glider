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
			// sciana boczna z tylu
			-4.0f,  0.0f,  -2.0f,	color[0], color[1],  color[2], color[3],	0.0f,  0.0f,	-1.0f, 0.0f, 0.0f,	//0		0
			-4.0f,  0.0f,  2.0f,	color[0], color[1],  color[2], color[3],	0.0f,  0.0f,	-1.0f, 0.0f, 0.0f,	//1		1
			-4.0f,  1.0f,  2.0f,	color[0], color[1],  color[2], color[3],	0.0f,  0.0f,	-1.0f, 0.0f, 0.0f,	//2		2
			-4.0f,  1.0f,  -2.0f,	color[0], color[1],  color[2], color[3],	0.0f,  0.0f,	-1.0f, 0.0f, 0.0f,	//3		3
			// sciana boczna z prawej
			-4.0f,  0.0f,  2.0f,	color[0], color[1],  color[2], color[3],	0.0f,  0.0f,	0.0f, 0.0f, 1.0f,	//1		4
			3.0f,  0.0f,  2.0f,		color[0], color[1],  color[2], color[3],	0.0f,  0.0f,	0.0f, 0.0f, 1.0f,	//5		5
			3.0f,  1.0f,  2.0f,		color[0], color[1],  color[2], color[3],	0.0f,  0.0f,	0.0f, 0.0f, 1.0f,	//6		6
			-4.0f,  1.0f,  2.0f,	color[0], color[1],  color[2], color[3],	0.0f,  0.0f,	0.0f, 0.0f, 1.0f,	//2		7
			// sciana boczna przednia prawa
			3.0f,  0.0f,  2.0f,		color[0], color[1],  color[2], color[3],	0.0f,  0.0f,	1.0f, 0.0f, 1.0f,	//5		8
			4.0f,  0.0f,  1.0f,		color[0], color[1],  color[2], color[3],	0.0f,  0.0f,	1.0f, 0.0f, 1.0f,	//9		9
			4.0f,  1.0f,  1.0f,		color[0], color[1],  color[2], color[3],	0.0f,  0.0f,	1.0f, 0.0f, 1.0f,	//10	10
			3.0f,  1.0f,  2.0f,		color[0], color[1],  color[2], color[3],	0.0f,  0.0f,	1.0f, 0.0f, 1.0f,	//6		11
			// sciana boczna przednia
			4.0f,  0.0f,  1.0f,		color[0], color[1],  color[2], color[3],	0.0f,  0.0f,	1.0f, 0.0f, 0.0f,	//9		12
			4.0f,  0.0f,  -1.0f,	color[0], color[1],  color[2], color[3],	0.0f,  0.0f,	1.0f, 0.0f, 0.0f,	//8		13
			4.0f,  1.0f,  -1.0f,	color[0], color[1],  color[2], color[3],	0.0f,  0.0f,	1.0f, 0.0f, 0.0f,	//11	14
			4.0f,  1.0f,  1.0f,		color[0], color[1],  color[2], color[3],	0.0f,  0.0f,	1.0f, 0.0f, 0.0f,	//10	15
			// sciana boczna przednia lewa
			4.0f,  0.0f,  -1.0f,	color[0], color[1],  color[2], color[3],	0.0f,  0.0f,	1.0f, 0.0f, -1.0f,	//8		16
			3.0f,  0.0f,  -2.0f,	color[0], color[1],  color[2], color[3],	0.0f,  0.0f,	1.0f, 0.0f, -1.0f,	//4		17
			3.0f,  1.0f,  -2.0f,	color[0], color[1],  color[2], color[3],	0.0f,  0.0f,	1.0f, 0.0f, -1.0f,	//7		18
			4.0f,  1.0f,  -1.0f,	color[0], color[1],  color[2], color[3],	0.0f,  0.0f,	1.0f, 0.0f, -1.0f,	//11	19
			// sciana boczna lewa
			3.0f,  0.0f,  -2.0f,	color[0], color[1],  color[2], color[3],	0.0f,  0.0f,	0.0f, 0.0f, -1.0f,	//4		20
			-4.0f,  0.0f,  -2.0f,	color[0], color[1],  color[2], color[3],	0.0f,  0.0f,	0.0f, 0.0f, -1.0f,	//0		21
			-4.0f,  1.0f,  -2.0f,	color[0], color[1],  color[2], color[3],	0.0f,  0.0f,	0.0f, 0.0f, -1.0f,	//3		22
			3.0f,  1.0f,  -2.0f,	color[0], color[1],  color[2], color[3],	0.0f,  0.0f,	0.0f, 0.0f, -1.0f,	//7		23
			// sciana dolna
			-4.0f,  0.0f,  -2.0f,	color[0], color[1],  color[2], color[3],	0.0f,  0.0f,	0.0f, -1.0f, 0.0f,	//0		24
			-4.0f,  0.0f,  2.0f,	color[0], color[1],  color[2], color[3],	0.0f,  0.0f,	0.0f, -1.0f, 0.0f,	//1		25
			3.0f,  0.0f,  2.0f,		color[0], color[1],  color[2], color[3],	0.0f,  0.0f,	0.0f, -1.0f, 0.0f,	//5		26
			4.0f,  0.0f,  1.0f,		color[0], color[1],  color[2], color[3],	0.0f,  0.0f,	0.0f, -1.0f, 0.0f,	//9		27
			4.0f,  0.0f,  -1.0f,	color[0], color[1],  color[2], color[3],	0.0f,  0.0f,	0.0f, -1.0f, 0.0f,	//8		28
			3.0f,  0.0f,  -2.0f,	color[0], color[1],  color[2], color[3],	0.0f,  0.0f,	0.0f, -1.0f, 0.0f,	//4		29
			// sciana gorna z lewej
			-4.0f,  1.0f,  -2.0f,	color[0], color[1],  color[2], color[3],	0.0f,  0.0f,	0.0f, 1.0f, 0.0f,	//3		30
			-3.5f,  1.0f,  -1.0f,	color[0], color[1],  color[2], color[3],	0.0f,  0.0f,	0.0f, 1.0f, 0.0f,	//15	31
			0.0f,  1.0f,  -1.0f,	color[0], color[1],  color[2], color[3],	0.0f,  0.0f,	0.0f, 1.0f, 0.0f,	//19	32
			3.0f,  1.0f,  -2.0f,	color[0], color[1],  color[2], color[3],	0.0f,  0.0f,	0.0f, 1.0f, 0.0f,	//7		33
			// sciana gorna z przodu
			0.0f,  1.0f,  -1.0f,	color[0], color[1],  color[2], color[3],	0.0f,  0.0f,	0.0f, 1.0f, 0.0f,	//19	34
			0.0f,  1.0f,  1.0f,		color[0], color[1],  color[2], color[3],	0.0f,  0.0f,	0.0f, 1.0f, 0.0f,	//18	35
			3.0f,  1.0f,  2.0f,		color[0], color[1],  color[2], color[3],	0.0f,  0.0f,	0.0f, 1.0f, 0.0f,	//6		36
			4.0f,  1.0f,  1.0f,		color[0], color[1],  color[2], color[3],	0.0f,  0.0f,	0.0f, 1.0f, 0.0f,	//10	37
			4.0f,  1.0f,  -1.0f,	color[0], color[1],  color[2], color[3],	0.0f,  0.0f,	0.0f, 1.0f, 0.0f,	//11	38
			3.0f,  1.0f,  -2.0f,	color[0], color[1],  color[2], color[3],	0.0f,  0.0f,	0.0f, 1.0f, 0.0f,	//7		39
			// sciana gorna z prawej
			-4.0f,  1.0f,  2.0f,	color[0], color[1],  color[2], color[3],	0.0f,  0.0f,	0.0f, 1.0f, 0.0f,	//2		40
			3.0f,  1.0f,  2.0f,		color[0], color[1],  color[2], color[3],	0.0f,  0.0f,	0.0f, 1.0f, 0.0f,	//6		41
			0.0f,  1.0f,  1.0f,		color[0], color[1],  color[2], color[3],	0.0f,  0.0f,	0.0f, 1.0f, 0.0f,	//18	42
			-3.5f,  1.0f,  1.0f,	color[0], color[1],  color[2], color[3],	0.0f,  0.0f,	0.0f, 1.0f, 0.0f,	//14	43
			// sciana gorna z tylu
			-4.0f,  1.0f,  -2.0f,	color[0], color[1],  color[2], color[3],	0.0f,  0.0f,	0.0f, 1.0f, 0.0f,	//3		44
			-4.0f,  1.0f,  2.0f,	color[0], color[1],  color[2], color[3],	0.0f,  0.0f,	0.0f, 1.0f, 0.0f,	//2		45
			-3.5f,  1.0f,  1.0f,	color[0], color[1],  color[2], color[3],	0.0f,  0.0f,	0.0f, 1.0f, 0.0f,	//14	46
			-3.5f,  1.0f,  -1.0f,	color[0], color[1],  color[2], color[3],	0.0f,  0.0f,	0.0f, 1.0f, 0.0f,	//15	47
			// siedzenie - boczna z tylu
			-3.5f,  0.25f, -1.0f,	0.0f,	  1.0f,			0.0f,	0.0f,		0.0f,  0.0f,	1.0f, 0.0f, 0.0f,	//12	48
			-3.5f,  0.25f, 1.0f,	0.0f,	  1.0f,			0.0f,	0.0f,		0.0f,  0.0f,	1.0f, 0.0f, 0.0f,	//13	49
			-3.5f,  1.0f,  1.0f,	color[0], color[1],  color[2], color[3],	0.0f,  0.0f,	1.0f, 0.0f, 0.0f,	//14	50
			-3.5f,  1.0f,  -1.0f,	color[0], color[1],  color[2], color[3],	0.0f,  0.0f,	1.0f, 0.0f, 0.0f,	//15	51
			// siedzenie - boczna z przodu
			0.0f,  0.25f, -1.0f,	0.0f,	  1.0f,			0.0f,	0.0f,		0.0f,  0.0f,	-1.0f, 0.0f, 0.0f,	//16	52
			0.0f,  0.25f, 1.0f,		0.0f,	  1.0f,			0.0f,	0.0f,		0.0f,  0.0f,	-1.0f, 0.0f, 0.0f,	//17	53
			0.0f,  1.0f,  1.0f,		color[0], color[1],  color[2], color[3],	0.0f,  0.0f,	-1.0f, 0.0f, 0.0f,	//18	54
			0.0f,  1.0f,  -1.0f,	color[0], color[1],  color[2], color[3],	0.0f,  0.0f,	-1.0f, 0.0f, 0.0f,	//19	55
			// siedzenie - boczna z prawej
			-3.5f,  0.25f, 1.0f,	0.0f,	  1.0f,			0.0f,	0.0f,		0.0f,  0.0f,	0.0f, 0.0f, -1.0f,	//13	56
			0.0f,  0.25f, 1.0f,		0.0f,	  1.0f,			0.0f,	0.0f,		0.0f,  0.0f,	0.0f, 0.0f, -1.0f,	//17	57
			0.0f,  1.0f,  1.0f,		color[0], color[1],  color[2], color[3],	0.0f,  0.0f,	0.0f, 0.0f, -1.0f,	//18	58
			-3.5f,  1.0f,  1.0f,	color[0], color[1],  color[2], color[3],	0.0f,  0.0f,	0.0f, 0.0f, -1.0f,	//14	59
			// siedzenie - boczna z lewej
			-3.5f,  0.25f, -1.0f,	0.0f,	  1.0f,			0.0f,	0.0f,		0.0f,  0.0f,	0.0f, 0.0f, 1.0f,	//12	60
			0.0f,  0.25f, -1.0f,	0.0f,	  1.0f,			0.0f,	0.0f,		0.0f,  0.0f,	0.0f, 0.0f, 1.0f,	//16	61
			0.0f,  1.0f,  -1.0f,	color[0], color[1],  color[2], color[3],	0.0f,  0.0f,	0.0f, 0.0f, 1.0f,	//19	62
			-3.5f,  1.0f,  -1.0f,	color[0], color[1],  color[2], color[3],	0.0f,  0.0f,	0.0f, 0.0f, 1.0f,	//15	63
			// siedzenie - dolna
			-3.5f,  0.25f, -1.0f,	0.0f,	  1.0f,			0.0f,	0.0f,		0.0f,  0.0f,	0.0f, 1.0f, 0.0f,	//12	64
			-3.5f,  0.25f, 1.0f,	0.0f,	  1.0f,			0.0f,	0.0f,		0.0f,  0.0f,	0.0f, 1.0f, 0.0f,	//13	65
			0.0f,  0.25f, 1.0f,		0.0f,	  1.0f,			0.0f,	0.0f,		0.0f,  0.0f,	0.0f, 1.0f, 0.0f,	//17	66
			0.0f,  0.25f, -1.0f,	0.0f,	  1.0f,			0.0f,	0.0f,		0.0f,  0.0f,	0.0f, 1.0f, 0.0f,	//16	67
		};
	}

	void setIndices() override {
		this->indices = {
			0,1,3,
			1,3,2,
			0,17,18,
			0,3,18,
			17,13,14,
			17,18,14,
			13,9,10,
			13,14,10,
			9,5,6,
			9,10,6,
			6,1,2,
			5,6,1,
			17,13,9,
			17,9,5,
			0,17,5,
			0,1,5,
			18,14,10,
			18,10,6,
			3,31,18,
			3,31,2,
			31,2,43,
			43,2,6,
			43,35,6,
			32,35,6,
			6,32,18,
			31,32,18,
			48,52,32,
			48,31,32,
			52,53,35,
			52,32,35,
			53,49,43,
			53,35,43,
			48,49,43,
			48,31,49,
			48,52,53,
			48,49,53
		};
	}
};