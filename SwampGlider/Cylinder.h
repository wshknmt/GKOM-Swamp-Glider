#pragma once

#include "Object.h"
#include "consts.h"
#include <vector>

class Cylinder : public Object {

public:

	Cylinder(glm::vec4 color) : Object(color) {
		initialize();
	}

private:
	void setVertices() override {

		const GLfloat R = 1.0f;

		for (int i = 0; i < CIRCLE_VERTS; ++i) {
			// wspolrzedne x, y, z gornej podstawy
			vertices.push_back(R * cos(glm::radians(360.0f / CIRCLE_VERTS * i)));
			vertices.push_back(R);
			vertices.push_back(R * sin(glm::radians(360.0f / CIRCLE_VERTS * i)));
			// kolory
			for (int i = 0; i < 4; ++i)
				vertices.push_back(color[i]);
			// tekstura
			vertices.push_back(0.0f);
			vertices.push_back(0.0f);
		}

		for (int i = 0; i < CIRCLE_VERTS; ++i) {
			// wspolrzedne x, y, z gornej podstawy
			vertices.push_back(R * cos(glm::radians(360.0f / CIRCLE_VERTS * i)));
			vertices.push_back(-R);
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

		for (int i = 0; i < CIRCLE_VERTS; ++i) {
			// powierzchnia boczna
			indices.push_back(i % CIRCLE_VERTS);
			indices.push_back((i + 1) % CIRCLE_VERTS);
			indices.push_back(CIRCLE_VERTS + ((i + 1) % CIRCLE_VERTS));

			indices.push_back(i % CIRCLE_VERTS);
			indices.push_back(CIRCLE_VERTS + (i % CIRCLE_VERTS));
			indices.push_back(CIRCLE_VERTS + ((i + 1) % CIRCLE_VERTS));
		}

		for (int i = 0; i < CIRCLE_VERTS - 2; ++i) {
			// podstawa dolna
			indices.push_back(CIRCLE_VERTS);
			indices.push_back(i + 1 + CIRCLE_VERTS);
			indices.push_back(i + 2 + CIRCLE_VERTS);
		}

	}
};