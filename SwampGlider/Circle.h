#pragma once

#include "Object.h"
#include "consts.h"
#include <vector>

class Circle : public Object {

public:

	Circle(glm::vec4 color) : Object(color) {
		initialize();
	}

private:
	void setVertices() override {

		const GLfloat R = 1.0f;

		for (int i = 0; i < CIRCLE_VERTS; ++i) {
			// wspolrzedne x, y, z
			vertices.push_back(R * cos(glm::radians(360.0f / CIRCLE_VERTS * i)));
			vertices.push_back(0);
			vertices.push_back(R * sin(glm::radians(360.0f / CIRCLE_VERTS * i)));
			// kolory
			for (int i = 0; i < 4; ++i)
				vertices.push_back(color[i]);
			// tekstura
			vertices.push_back(0.0f);
			vertices.push_back(0.0f);
		}
	}

	void setIndices() override {

		for (int i = 0; i < CIRCLE_VERTS - 2; ++i) {
			// podstawa gorna
			indices.push_back(0);
			indices.push_back(i + 1);
			indices.push_back(i + 2);
		}
	}
};