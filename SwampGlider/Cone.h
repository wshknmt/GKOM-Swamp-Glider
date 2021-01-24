#pragma once

#include "Object.h"
#include "consts.h"
#include <vector>

class Cone : public Object {

public:

	Cone(glm::vec4 color) : Object(color) {
		initialize();
	}

private:
	glm::vec4 secondColor;

	void setVertices() override {

		const GLfloat R = 1.0f;

		for (int i = 0; i < CIRCLE_VERTS; ++i) {
			// wspolrzedne x, y, z gornej podstawy
			vertices.push_back(-R * cos(glm::radians(360.0f / CIRCLE_VERTS * i)));
			vertices.push_back(0.0f);
			vertices.push_back(-R * sin(glm::radians(360.0f / CIRCLE_VERTS * i)));
			// kolory
			vertices.push_back(color[0]);
			vertices.push_back(color[1]);
			vertices.push_back(color[2]);
			vertices.push_back(color[3]);
			// tekstura
			vertices.push_back(0.0f);
			vertices.push_back(0.0f);
		}

		//czubek
		vertices.push_back(0.0f);
		vertices.push_back(1.0f);
		vertices.push_back(0.0f);
		// kolory
		vertices.push_back(1.0f);
		vertices.push_back(0.0f);
		vertices.push_back(0.0f);
		vertices.push_back(color[3]);
		// tekstura
		vertices.push_back(0.0f);
		vertices.push_back(0.0f);
	}

	void setIndices() override {

		for (int i = 0; i < CIRCLE_VERTS - 2; ++i) {
			// podstawa gorna
			indices.push_back(0);
			indices.push_back(i + 1);
			indices.push_back(i + 2);
		}

		for (int i = 0; i < CIRCLE_VERTS; ++i) {
			// powierzchnia boczna
			indices.push_back(i % CIRCLE_VERTS);
			indices.push_back((i + 1) % CIRCLE_VERTS);
			indices.push_back(CIRCLE_VERTS);
		}
	}
};