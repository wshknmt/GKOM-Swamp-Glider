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
#include <vector>

#include "Camera.h"
#include "Glider.h"
#include "Water.h"
#include "Rudder.h"
#include "Cylinder.h"
#include "Pipe.h"
#include "Cone.h"

#include "shader.h"

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
	std::vector<Object*> objects;
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


		// lighting
		glm::vec3 lightPos(0.0f, 10.0f, 0.0f);
		glm::vec3 cubePos(5.0f, 2.0f, -3.0f);
		Shader lightingShader("lighting.vert", "lighting.frag");
		Shader lightSourceShader("lightSource.vert", "lightSource.frag");

		float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
		};

		// first, configure the cube's VAO (and VBO)
		unsigned int VBO, cubeVAO;
		glGenVertexArrays(1, &cubeVAO);
		glGenBuffers(1, &VBO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindVertexArray(cubeVAO);

		// position attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		// normal attribute
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		// second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
		unsigned int lightCubeVAO;
		glGenVertexArrays(1, &lightCubeVAO);
		glBindVertexArray(lightCubeVAO);

		// we only need to bind to the VBO (to link it with glVertexAttribPointer), no need to fill it; the VBO's data already contains all we need (it's already bound, but we do it again for educational purposes)
		glBindBuffer(GL_ARRAY_BUFFER, VBO);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		
		
		// Build, compile and link shader programs
		ShaderProgram textureShaders("swampGliderTexture.vert", "swampGliderTexture.frag");
		ShaderProgram colorShaders("swampGliderColor.vert", "swampGliderColor.frag");		

		// water
		Water* water = new Water("water.jpg");
		objects.push_back(water);
		water->scale(glm::vec3(200.0f, 3.0f, 200.0f));
		water->move(glm::vec3(0.0f, -1.0f, 0.0f));

		// glider, duuh
		Glider* glider = new Glider(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
		objects.push_back(glider);
		glider->move(glm::vec3(-3.0f, 0.01f, 0.0f));
		glider->scale(glm::vec3(1.0f, 2.0f, 1.0f));
		//glider.rotate(glm::vec3(0.0f, 90.0f, 0.0f));

		//rudder
		Rudder* rudder = new Rudder(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
		objects.push_back(rudder);
		rudder->move(glm::vec3(-3.9f, -0.05f, 0.0f));
		rudder->rotate(glm::vec3(0.0f, 180.0f, 0.0f));
		rudder->scale(glm::vec3(1.3f, 2.0f, 1.0f));
		rudder->setParent(glider);
		//rudder->move(glm::vec3(0.15f, -0.06f, 0.0f));
		//rudder->rotate(glm::vec3(0.0f, 180.0f, 0.0f));
		//rudder->scale(glm::vec3(1.75f, 2.0f, 1.0f));
		

		//cylinder
		Cylinder* cylinder = new Cylinder(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
		objects.push_back(cylinder);
		cylinder->move(glm::vec3(-3.76f, 2.3f, 0.0f));
		cylinder->rotate(glm::vec3(0.0f, 0.0f, 0.0f));
		cylinder->scale(glm::vec3(0.2f, 0.5f, 0.2f));
		cylinder->setParent(glider);

		//pipe
		Pipe* pipe = new Pipe(glm::vec4(1.0f, 215.0f/255.0f, 0.0f, 1.0f), 0.9f);
		objects.push_back(pipe);
		pipe->move(glm::vec3(-3.75f, 4.2f, 0.0f));
		pipe->scale(glm::vec3(0.27f, 1.5f, 1.5f));
		pipe->setParent(glider);

		//cylinder2
		Cylinder* cylinder2 = new Cylinder(glm::vec4(0.0f, 0.5f, 0.5f, 1.0f));
		objects.push_back(cylinder2);
		cylinder2->move(glm::vec3(0.0f, 0.0f, 0.0f));
		cylinder2->rotate(glm::vec3(0.0f, 0.0f, 0.0f));
		cylinder2->scale(glm::vec3(0.07f, 1.45f, 0.07f));
		cylinder2->setParent(pipe);

		vector<Cone*> propeller;
		for (int i = 0; i < (int)WINGS_NUM; i++) {
			Cone* cone = new Cone(glm::vec4(0.0f, 1.0f, 1.0f, 1.0f));
			cone->move(glm::vec3(-0.15f, 0.0f, 0.0f));
			cone->rotate(glm::vec3(i * (360.0f/WINGS_NUM), 0.0f, 0.0f));
			cone->scale(glm::vec3(0.05f, 1.3f, 0.2f));
			cone->setParent(pipe);
			propeller.push_back(cone);
			objects.push_back(cone);

		}

		//volcano
		Cone* volcano = new Cone(glm::vec4(120.0f/255.0f, 60.0f/255.0f, 0.0f, 1.0f));
		objects.push_back(volcano);
		volcano->scale(glm::vec3(10.0f, 20.0f, 10.0f));
		volcano->rotate(glm::vec3(0.0f, 0.0f, 0.0f));
		volcano->move(glm::vec3(80.0f, 0.0f, 0.0f));

		// main event loop
		while (!glfwWindowShouldClose(window)) {
			if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
				glider->move(glm::vec3(0.1f, 0.0f, 0.0f));
			}
			if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
				glider->move(glm::vec3(-0.1f, 0.0f, 0.0f));
			}
			if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
				glider->rotate(glm::vec3(0.0f, -1.0f, 0.0f));
			}
			if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
				glider->rotate(glm::vec3(0.0f, 1.0f, 0.0f));
			}

			// poruszanie szescianem przod tyl
			if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) {
				cubePos += glm::vec3(0.01f, 0.0f, 0.0f);
			}
			if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) {
				cubePos += glm::vec3(-0.01f, 0.0f, 0.0f);
			}
			// poruszanie szescianem lewo prawo
			if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
				cubePos += glm::vec3(0.0f, 0.0f, 0.01f);
			}
			if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) {
				cubePos += glm::vec3(0.0f, 0.0f, -0.01f);
			}
			// poruszanie szescianem gora dol
			if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) {
				cubePos += glm::vec3(0.0f, 0.01f, 0.0f);
			}
			if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) {
				cubePos += glm::vec3(0.0f, -0.01f, 0.0f);
			}


			for (int i = 0; i < (int)WINGS_NUM; i++) {
				propeller[i]->rotate(glm::vec3(0.5f, 0.0f, 0.0f));
			}

			glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			camera.refresh();
			glm::mat4 view = camera.getViewMatrix();
			glm::mat4 projection = PROJECTION_MATRIX;

			textureShaders.Use();
			glUniformMatrix4fv(glGetUniformLocation(textureShaders.get_programID(), "view"), 1, GL_FALSE, &view[0][0]);
			glUniformMatrix4fv(glGetUniformLocation(textureShaders.get_programID(), "projection"), 1, GL_FALSE, &projection[0][0]);
			
			for (Object* obj : objects) {
				if (obj->isTextured())
					obj->draw(textureShaders.get_programID());
			}
			
			colorShaders.Use();
			glUniformMatrix4fv(glGetUniformLocation(colorShaders.get_programID(), "view"), 1, GL_FALSE, &view[0][0]);
			glUniformMatrix4fv(glGetUniformLocation(colorShaders.get_programID(), "projection"), 1, GL_FALSE, &projection[0][0]);
			
			for (Object* obj : objects) {
				if (!(obj->isTextured()))
					obj->draw(colorShaders.get_programID());
			}

			// be sure to activate shader when setting uniforms/drawing objects
			lightingShader.use();
			lightingShader.setVec3("objectColor", 0.0f, 0.9f, 0.9f);
			lightingShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
			lightingShader.setVec3("lightPos", lightPos);

			// world transformation
			glm::mat4 model = glm::mat4(1.0f);
			lightingShader.setMat4("model", model);

			// view/projection transformations
			lightingShader.use();
			lightingShader.setMat4("projection", projection);
			lightingShader.setMat4("view", view);
			
			// draw the cube
			model = glm::mat4(1.0f);
			model = glm::translate(model, cubePos);
			model = glm::scale(model, glm::vec3(2.0f)); // a bigger cube
			lightingShader.setMat4("model", model);
			glBindVertexArray(cubeVAO);
			glDrawArrays(GL_TRIANGLES, 0, 72);

			// also draw the lamp object
			lightSourceShader.use();
			lightSourceShader.setMat4("projection", projection);
			lightSourceShader.setMat4("view", view);
			model = glm::mat4(1.0f);
			model = glm::translate(model, lightPos);
			model = glm::scale(model, glm::vec3(1.0f)); // a smaller cube
			lightSourceShader.setMat4("model", model);

			glBindVertexArray(lightCubeVAO);
			glDrawArrays(GL_TRIANGLES, 0, 36);
			
			
			glfwPollEvents();
			glfwSwapBuffers(window);
		}
	} catch (exception ex) {
		cout << ex.what() << endl;
	}
	glfwTerminate();

	for (Object* obj : objects)
		delete obj;
	return 0;
}
