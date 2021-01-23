#define GLEW_STATIC
#include <GL/glew.h>
#include "shprogram.h"
#include <GLFW/glfw3.h>
#include <SOIL.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <cstdlib>
#include <cstdio>
#include <ctime>

#include "Camera.h"
#include "Glider.h"
#include "Water.h"
#include "Rudder.h"
#include "Cylinder.h"
#include "Pipe.h"
#include "Cone.h"

using namespace std;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

ostream& operator<<(ostream& os, const glm::mat4& mx) {
	for (int row = 0; row < 4; ++row)
	{
		for (int col = 0; col < 4; ++col)
			cout << mx[row][col] << ' ';
		cout << endl;
	}
	return os;
}

int main() {
	srand(time(NULL));
	if (glfwInit() != GL_TRUE) {
		cout << "GLFW initialization failed" << endl;
		return -1;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	try	{
		GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Swamp Glider", nullptr, nullptr);
		if (window == nullptr)
			throw exception("GLFW window not created");
		glfwMakeContextCurrent(window);
		glfwSetKeyCallback(window, key_callback);
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

		glewExperimental = GL_TRUE;
		if (glewInit() != GLEW_OK)
			throw exception("GLEW Initialization failed");

		glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

		glEnable(GL_DEPTH_TEST);

		// Setup camera object
		glm::vec3 positionVector = glm::vec3(-10, 2, -10);
		GLfloat hAngle = 0.785f;
		GLfloat vAngle = 0.0f;
		GLfloat initialFoV = 45.0f;
		GLfloat movementSpeed = 0.09f;
		GLfloat mouseSpeed = 0.005f;
		Camera camera = Camera(window, positionVector, hAngle, vAngle, movementSpeed, mouseSpeed);

		// Let's check what are maximum parameters counts
		/*GLint nrAttributes;
		glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
		cout << "Max vertex attributes allowed: " << nrAttributes << std::endl;
		glGetIntegerv(GL_MAX_TEXTURE_COORDS, &nrAttributes);
		cout << "Max texture coords allowed: " << nrAttributes << std::endl;*/

		// Build, compile and link shader programs
		ShaderProgram textureShaders("swampGliderTexture.vert", "swampGliderTexture.frag");
		ShaderProgram colorShaders("swampGliderColor.vert", "swampGliderColor.frag");

		// water
		Water water("water.jpg");
		water.scale(glm::vec3(200.0f, 3.0f, 200.0f));
		water.move(glm::vec3(0.0f, -1.0f, 0.0f));

		// glider, duuh
		Glider glider(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
		glider.scale(glm::vec3(1.0f, 2.0f, 1.0f));
		glider.move(glm::vec3(0.0f, 0.01f, 0.0f));
		//glider.rotate(glm::vec3(0.0f, 90.0f, 0.0f));

		//rudder
		Rudder rudder(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
		rudder.move(glm::vec3(0.15f, -0.06f, 0.0f));
		rudder.rotate(glm::vec3(0.0f, 180.0f, 0.0f));
		rudder.scale(glm::vec3(1.75f, 2.0f, 1.0f));
		

		//cylinder
		Cylinder cylinder(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
		cylinder.scale(glm::vec3(0.2f, 0.5f, 0.2f));
		cylinder.rotate(glm::vec3(0.0f, 0.0f, 0.0f));
		cylinder.move(glm::vec3(0.24f, 2.0f, 0.0f));

		//cylinder2
		Cylinder cylinder2(glm::vec4(0.0f, 0.5f, 0.5f, 1.0f));
		cylinder2.scale(glm::vec3(0.07f, 1.5f, 0.07f));
		cylinder2.rotate(glm::vec3(0.0f, 0.0f, 0.0f));
		cylinder2.move(glm::vec3(0.24f, 3.85f, 0.0f));

		//pipe
		Pipe pipe(glm::vec4(1.0f, 215.0f/255.0f, 0.0f, 1.0f), 0.9f);
		pipe.scale(glm::vec3(1.5f, 0.27f, 1.5f));
		pipe.rotate(glm::vec3(0.0f, 0.0f, 90.0f));
		pipe.move(glm::vec3(0.22f, 3.9f, 0.0f));

		float numberOfSmiglo = 9;
		vector <Cone> wiatrak;
		for (int i = 0; i < numberOfSmiglo; i++) {
			Cone cone(glm::vec4(0.0f, 1.0f, 1.0f, 1.0f));
			cone.scale(glm::vec3(0.05f, 1.3f, 0.2f));
			cone.move(glm::vec3(0.1f, 3.9f, 0.0f));
			cone.rotate(glm::vec3(i * (360.0f/numberOfSmiglo), 0.0f, 0.0f));
			wiatrak.push_back(cone);
		}

		//wulkan
		Cone wulkan(glm::vec4(120.0f/255.0f, 60.0f/255.0f, 0.0f, 1.0f));
		wulkan.scale(glm::vec3(10.0f, 20.0f, 10.0f));
		wulkan.rotate(glm::vec3(0.0f, 0.0f, 0.0f));
		wulkan.move(glm::vec3(80.0f, 0.0f, 0.0f));



		// main event loop
		while (!glfwWindowShouldClose(window)) {
			wulkan.move(glm::vec3(-0.05f, 0.0f, 0.0f));
			water.move(glm::vec3(-0.05f, 0.0f, 0.0f));

			glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			camera.refresh();
			glm::mat4 view = camera.getViewMatrix();
			glm::mat4 projection = PROJECTION_MATRIX;

			textureShaders.Use();
			glUniformMatrix4fv(glGetUniformLocation(textureShaders.get_programID(), "view"), 1, GL_FALSE, &view[0][0]);
			glUniformMatrix4fv(glGetUniformLocation(textureShaders.get_programID(), "projection"), 1, GL_FALSE, &projection[0][0]);
			water.draw(textureShaders.get_programID());

			colorShaders.Use();
			glUniformMatrix4fv(glGetUniformLocation(colorShaders.get_programID(), "view"), 1, GL_FALSE, &view[0][0]);
			glUniformMatrix4fv(glGetUniformLocation(colorShaders.get_programID(), "projection"), 1, GL_FALSE, &projection[0][0]);
			glider.draw(colorShaders.get_programID());
			rudder.draw(colorShaders.get_programID());
			cylinder.draw(colorShaders.get_programID());
			cylinder2.draw(colorShaders.get_programID());
			wulkan.draw(colorShaders.get_programID());
			pipe.draw(colorShaders.get_programID());

			for (int i = 0; i < numberOfSmiglo; i++) {
				wiatrak[i].draw(colorShaders.get_programID());
				wiatrak[i].rotate(glm::vec3(0.5f, 0.0f, 0.0f));
			}

			glfwPollEvents();
			glfwSwapBuffers(window);
		}
	} catch (exception ex) {
		cout << ex.what() << endl;
	}
	glfwTerminate();

	return 0;
}
