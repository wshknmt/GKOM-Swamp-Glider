#include "Object.h"
Object::Object() : model(glm::mat4(1.0f)), scaling(glm::mat4(1.0f)), parent(nullptr) {}

Object::Object(string textureName) : Object() {
	this->textureFileName = textureName;
	this->textured = true;
}

Object::Object(glm::vec4 color) : Object() {
	this->color = color;
	this->textured = false;
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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 12 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// vertex color data 
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 12 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// vertex texture coordinates
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 12 * sizeof(GLfloat), (GLvoid*)(7 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	// vertex normal coordinates
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 12 * sizeof(GLfloat), (GLvoid*)(9 * sizeof(GLfloat)));
	glEnableVertexAttribArray(3);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	if (textured) {
		// Set the texture wrapping parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Set texture wrapping to GL_REPEAT (usually basic wrapping method)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		// Set texture filtering parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

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
	glm::mat4 drawnModel;
	if (parent != nullptr) {
		drawnModel = parent->getModel() * model * scaling;
	} else {
		drawnModel = model * scaling;
	}
	glUniformMatrix4fv(glGetUniformLocation(shaderId, "model"), 1, GL_FALSE, &drawnModel[0][0]);

	if (textured) {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureId);
		glUniform1i(glGetUniformLocation(shaderId, "Texture"), 0);
	}

	glBindVertexArray(VAO);

	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Object::move(const glm::vec3& vector) {
	model = glm::translate(model, vector);

}

void Object::scale(const glm::vec3& vector) {
	scaling = glm::scale(scaling, vector);
}

void Object::rotate(const glm::vec3& vector) {
	model = glm::rotate(model, glm::radians(vector.x), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(vector.y), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(vector.z), glm::vec3(0.0f, 0.0f, 1.0f));
}

glm::mat4 Object::getModel() {
	if (parent != nullptr)
		return parent->getModel() * model;
	else
		return model;
}

void Object::setParent(Object* parent) {
	this->parent = parent;
}

bool Object::isTextured() {
	return textured;
}