#pragma once
#include <string>
#include <glm/glm.hpp>
class ShaderProgram
{
	GLuint program_id; 	// The program ID
public:
	// Constructor reads and builds the shader
	ShaderProgram(const GLchar* vertexPath, const GLchar* fragmentPath);
	ShaderProgram(const GLchar* vertexPath, const GLchar* fragmentPath, const GLchar* geometryPath);
	// Use the program
	void Use() const
	{
		glUseProgram(get_programID());
	}
	void setMat4(const std::string& name, const glm::mat4& mat)
	{
		glUniformMatrix4fv(glGetUniformLocation(program_id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}

	void setFloat(const std::string& name, float value)
	{
		glUniform1f(glGetUniformLocation(program_id, name.c_str()), value);
	}

	void setVec3(const std::string& name, const glm::vec3& value)
	{
		glUniform3fv(glGetUniformLocation(program_id, name.c_str()), 1, &value[0]);
	}

	void setInt(const std::string& name, int value) const
	{
		glUniform1i(glGetUniformLocation(program_id, name.c_str()), value);
	}
	// returns program ID
	GLuint get_programID() const
	{
		return program_id;
	}
};