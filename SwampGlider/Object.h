#pragma once
#include <GL/glew.h>
#include <string>
#include <SOIL.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <vector>

using namespace std;

class Object {
	virtual void setVertices() = 0;
	virtual void setIndices() = 0;

	glm::vec3 positionVector;
	glm::vec3 rotationVector;
	glm::vec3 scaleVector;
	GLuint VAO, VBO, EBO;

	bool isTextured;
	GLuint textureId;
	

protected:
	glm::vec4 color;
	vector<GLfloat> vertices;
	vector<GLuint> indices;
	string textureFileName;
public:

	Object();
	Object(string textureName);
	Object(glm::vec4 color);
	~Object();

	void initialize();
	void draw(GLint shaderId);
	void move(const glm::vec3& vector);
	void scale(const glm::vec3& vector);
	void rotate(const glm::vec3& vector);
};
