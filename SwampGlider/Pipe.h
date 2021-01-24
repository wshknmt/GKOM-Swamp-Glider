#pragma once

#include "Object.h"
#include "consts.h"
#include <vector>

class Pipe : public Object {

public:

	Pipe(glm::vec4 color, GLfloat minorRadiusRatio = 1.0f) : Object(color) {
		if (minorRadiusRatio <= 0.0f || minorRadiusRatio > 1.0f)
			this->minorRadiusRatio = 1.0f;
		else
			this->minorRadiusRatio = minorRadiusRatio;
		initialize();
	}

private:
	GLfloat minorRadiusRatio;

	void setVertices() override {

		const GLfloat R = 1.0f;

		for (int i = 0; i < CIRCLE_VERTS; ++i) {
			// wspolrzedne x, y, z gornej podstawy
			vertices.push_back(R);
			vertices.push_back(R * cos(glm::radians(360.0f / CIRCLE_VERTS * i)));			
			vertices.push_back(R * sin(glm::radians(360.0f / CIRCLE_VERTS * i)));
			// kolory
			vertices.push_back(color[0]);
			vertices.push_back(color[1]);
			vertices.push_back(color[2]);
			vertices.push_back(color[3]);
			// tekstura
			vertices.push_back(0.0f);
			vertices.push_back(0.0f);
		}

		for (int i = 0; i < CIRCLE_VERTS; ++i) {
			// wspolrzedne x, y, z gornej podstawy
			vertices.push_back(R);
			vertices.push_back(R * minorRadiusRatio * cos(glm::radians(360.0f / CIRCLE_VERTS * i)));
			vertices.push_back(R * minorRadiusRatio * sin(glm::radians(360.0f / CIRCLE_VERTS * i)));
			// kolory
			vertices.push_back(color[0]);
			vertices.push_back(color[1]);
			vertices.push_back(color[2]);
			vertices.push_back(color[3]);
			// tekstura
			vertices.push_back(0.0f);
			vertices.push_back(0.0f);
		}

		for (int i = 0; i < CIRCLE_VERTS; ++i) {
			// wspolrzedne x, y, z gornej podstawy
			vertices.push_back(-R);
			vertices.push_back(R * cos(glm::radians(360.0f / CIRCLE_VERTS * i)));
			vertices.push_back(R * sin(glm::radians(360.0f / CIRCLE_VERTS * i)));
			// kolory
			vertices.push_back(color[0]);
			vertices.push_back(color[1]);
			vertices.push_back(color[2]);
			vertices.push_back(color[3]);
			// tekstura
			vertices.push_back(0.0f);
			vertices.push_back(0.0f);
		}

		for (int i = 0; i < CIRCLE_VERTS; ++i) {
			// wspolrzedne x, y, z gornej podstawy
			vertices.push_back(-R);
			vertices.push_back(R * minorRadiusRatio * cos(glm::radians(360.0f / CIRCLE_VERTS * i)));
			vertices.push_back(R * minorRadiusRatio * sin(glm::radians(360.0f / CIRCLE_VERTS * i)));
			// kolory
			vertices.push_back(color[0]);
			vertices.push_back(color[1]);
			vertices.push_back(color[2]);
			vertices.push_back(color[3]);
			// tekstura
			vertices.push_back(0.0f);
			vertices.push_back(0.0f);
		}
	}

	void setIndices() override {

		/*for (int i = 0; i < CIRCLE_VERTS - 2; ++i) {
			// podstawa gorna
			indices.push_back(0);
			indices.push_back(i + 1);
			indices.push_back(i + 2);
		}*/

		for (int i = 0; i < CIRCLE_VERTS; ++i) {
			// podstawa gorna
			indices.push_back(i % CIRCLE_VERTS);
			indices.push_back((i + 1) % CIRCLE_VERTS);
			indices.push_back(CIRCLE_VERTS + ((i + 1) % CIRCLE_VERTS));

			indices.push_back(i % CIRCLE_VERTS);
			indices.push_back(CIRCLE_VERTS + (i % CIRCLE_VERTS));
			indices.push_back(CIRCLE_VERTS + ((i + 1) % CIRCLE_VERTS));
		}

		for (int i = 0; i < CIRCLE_VERTS; ++i) {
			// bok zewnetrzny
			indices.push_back(0 * CIRCLE_VERTS + (i % CIRCLE_VERTS));
			indices.push_back(0 * CIRCLE_VERTS + (i + 1) % CIRCLE_VERTS);
			indices.push_back(2 * CIRCLE_VERTS + ((i + 1) % CIRCLE_VERTS));

			indices.push_back(0 * CIRCLE_VERTS + (i % CIRCLE_VERTS));
			indices.push_back(2 * CIRCLE_VERTS + (i % CIRCLE_VERTS));
			indices.push_back(2 * CIRCLE_VERTS + ((i + 1) % CIRCLE_VERTS));
		}

		for (int i = 0; i < CIRCLE_VERTS; ++i) {
			// bok wewnetrzny
			indices.push_back(1 * CIRCLE_VERTS + (i % CIRCLE_VERTS));
			indices.push_back(1 * CIRCLE_VERTS + (i + 1) % CIRCLE_VERTS);
			indices.push_back(3 * CIRCLE_VERTS + ((i + 1) % CIRCLE_VERTS));

			indices.push_back(1 * CIRCLE_VERTS + (i % CIRCLE_VERTS));
			indices.push_back(3 * CIRCLE_VERTS + (i % CIRCLE_VERTS));
			indices.push_back(3 * CIRCLE_VERTS + ((i + 1) % CIRCLE_VERTS));
		}

		for (int i = 0; i < CIRCLE_VERTS; ++i) {
			// podstawa dolna
			indices.push_back(2 * CIRCLE_VERTS + (i % CIRCLE_VERTS));
			indices.push_back(2 * CIRCLE_VERTS + (i + 1) % CIRCLE_VERTS);
			indices.push_back(3 * CIRCLE_VERTS + ((i + 1) % CIRCLE_VERTS));

			indices.push_back(2 * CIRCLE_VERTS + (i % CIRCLE_VERTS));
			indices.push_back(3 * CIRCLE_VERTS + (i % CIRCLE_VERTS));
			indices.push_back(3 * CIRCLE_VERTS + ((i + 1) % CIRCLE_VERTS));
		}

	}
};