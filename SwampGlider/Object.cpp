#include "Object.h"
Object::Object() :
	positionVector(glm::vec3(0.0f, 0.0f, 0.0f)),
	rotationVector(glm::vec3(0.0f, 0.0f, 0.0f)),
	scaleVector(glm::vec3(1.0f, 1.0f, 1.0f))
{}

Object::Object(string textureName) : Object() {
	this->textureFileName = textureName;
	this->isTextured = true;
}

Object::Object(glm::vec4 color) : Object() {
	this->color = color;
	this->isTextured = false;
}

Object::~Object() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}


void Object::initialize() {
	setVertices();
	setIndices();
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices[0]), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(indices[0]), &indices[0], GL_STATIC_DRAW);

	// vertex geometry data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// vertex color data 
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// vertex texture coordinates
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	if (isTextured) {
		// Set the texture wrapping parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Set texture wrapping to GL_REPEAT (usually basic wrapping method)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		// Set texture filtering parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		//prepare texture
		//GLuint texture;
		glGenTextures(1, &textureId);

		// Load texture and generate mipmaps
		int width, height;
		unsigned char* image = SOIL_load_image(textureFileName.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
		if (image == nullptr) 
			throw exception("Error. Texture cannot be loaded.");

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureId);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);

		glGenerateMipmap(GL_TEXTURE_2D);

		SOIL_free_image_data(image);

		glBindTexture(GL_TEXTURE_2D, 0);
	}
}

void Object::draw(GLint shaderId) {
	glm::mat4 model = glm::mat4(1.0f);
	model = translate(model, positionVector);
	model = glm::rotate(model, glm::radians(rotationVector.x), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(rotationVector.y), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(rotationVector.z), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::scale(model, scaleVector);
	glUniformMatrix4fv(glGetUniformLocation(shaderId, "Model"), 1, GL_FALSE, &model[0][0]);

	if (isTextured) {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureId);
		glUniform1i(glGetUniformLocation(shaderId, "Texture"), 0);
	} else 
		glUniform4fv(glGetUniformLocation(shaderId, "Color"), 1, &color[0]);


	glBindVertexArray(VAO);

	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Object::move(const glm::vec3& vector) {
	this->positionVector += vector;
}

void Object::scale(const glm::vec3& vector) {
	this->scaleVector += vector;
}

void Object::rotate(const glm::vec3& vector) {
	this->rotationVector += vector;
}