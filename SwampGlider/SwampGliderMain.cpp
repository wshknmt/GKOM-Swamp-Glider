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
#include "Circle.h"
#include "Skybox.h"

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

void spawnLily(std::vector<Object*> &objects, glm::vec3 position) {
	Cone* stalk = new Cone(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
	stalk->move(glm::vec3(position[0], position[1], position[2]));
	stalk->rotate(glm::vec3(180.0f, 0.0f, 0.0f));
	stalk->scale(glm::vec3(0.2f, 0.6f, 0.2f));

	objects.push_back(stalk);

	Pipe* flower = new Pipe(glm::vec4((rand() % 256) / 255.0f, (rand() % 256) / 255.0f, (rand() % 256) / 255.0f, 1.0f), 0.45f);
	flower->rotate(glm::vec3(0.0f, 0.0f, 90.0f));
	flower->scale(glm::vec3(0.1f, 0.4f, 0.4f));
	flower->setParent(stalk);

	objects.push_back(flower);

	Circle* leaf = new Circle(glm::vec4(0.0f, 83.0f / 255.0f, 44.0f / 255.0f, 1.0f));
	leaf->scale(glm::vec3(0.5f, 1.0f, 0.5f));
	leaf->setParent(stalk);
	leaf->move(glm::vec3(0.0f, 0.55f, 0.0f));
	objects.push_back(leaf);
}

void generateLilies(std::vector<Object*>& objects, int numberOfLilies) {
	for (int i = 0; i < numberOfLilies; ++i)
		spawnLily(objects, glm::vec3{ rand() % (int)WATER_SIZE * 1.0f - WATER_SIZE / 2, 1.06f, rand() % (int)WATER_SIZE * 1.0f - WATER_SIZE / 2});
}

int main() {
	srand(time(NULL));
	if (glfwInit() != GL_TRUE) {
		cout << "GLFW initialization failed" << endl;
		return -1;
	}
	GLfloat turbo;
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
		glm::vec3 positionVector = glm::vec3(-20, 5, -20);
		GLfloat hAngle = 0.785f;
		GLfloat vAngle = 0.0f;
		GLfloat movementSpeed = 0.09f;
		GLfloat mouseSpeed = 0.005f;
		Camera camera = Camera(window, positionVector, hAngle, vAngle, movementSpeed, mouseSpeed);

		// lighting
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
		Cuboid* water = new Cuboid("bagno.png");
		objects.push_back(water);
		water->scale(glm::vec3(WATER_SIZE, 3.0f, WATER_SIZE));
		water->move(glm::vec3(0.0f, -1.0f, 0.0f));

		// glider, duuh
		Glider* glider = new Glider("glider.png");
		objects.push_back(glider);
		glider->move(glm::vec3(-3.0f, 0.01f, 0.0f));
		glider->scale(glm::vec3(1.0f, 2.0f, 1.0f));

		//rudder
		Rudder* rudder = new Rudder(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
		objects.push_back(rudder);
		rudder->move(glm::vec3(-3.9f, -0.05f, 0.0f));
		rudder->rotate(glm::vec3(0.0f, 180.0f, 0.0f));
		rudder->scale(glm::vec3(1.3f, 2.0f, 1.0f));
		rudder->setParent(glider);

		//bottom of propeller
		Cylinder* bottomOfPropellerCylinder = new Cylinder(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
		objects.push_back(bottomOfPropellerCylinder);
		bottomOfPropellerCylinder->move(glm::vec3(-3.76f, 2.3f, 0.0f));
		bottomOfPropellerCylinder->rotate(glm::vec3(0.0f, 0.0f, 0.0f));
		bottomOfPropellerCylinder->scale(glm::vec3(0.2f, 0.5f, 0.2f));
		bottomOfPropellerCylinder->setParent(glider);

		//propeller guard
		Pipe* propellerGuard = new Pipe(glm::vec4(1.0f, 215.0f/255.0f, 0.0f, 1.0f), 0.9f);
		objects.push_back(propellerGuard);
		propellerGuard->move(glm::vec3(-3.75f, 4.2f, 0.0f));
		propellerGuard->scale(glm::vec3(0.27f, 1.5f, 1.5f));
		propellerGuard->setParent(glider);

		//propeller long stick
		Cylinder* propellerLongStick = new Cylinder(glm::vec4(0.0f, 0.5f, 0.5f, 1.0f));
		objects.push_back(propellerLongStick);
		propellerLongStick->move(glm::vec3(0.0f, 0.0f, 0.0f));
		propellerLongStick->rotate(glm::vec3(0.0f, 0.0f, 0.0f));
		propellerLongStick->scale(glm::vec3(0.07f, 1.45f, 0.07f));
		propellerLongStick->setParent(propellerGuard);

		//thick steering wheel stand
		Cylinder* thickSteeringWheelStand = new Cylinder(glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));
		objects.push_back(thickSteeringWheelStand);
		thickSteeringWheelStand->move(glm::vec3(0.35f, 2.0f, 0.0f));
		thickSteeringWheelStand->rotate(glm::vec3(0.0f, 0.0f, 0.0f));
		thickSteeringWheelStand->scale(glm::vec3(0.2, 0.25f, 0.2f));
		thickSteeringWheelStand->setParent(glider);

		//thin steering wheel stand
		Cylinder* thinSteeringWheelStand = new Cylinder(glm::vec4(1.0f, 0.0f, 1.0f, 1.0f));
		objects.push_back(thinSteeringWheelStand);
		thinSteeringWheelStand->move(glm::vec3(0.0f, 0.5f, 0.0f));
		thinSteeringWheelStand->rotate(glm::vec3(0.0f, 0.0f, 0.0f));
		thinSteeringWheelStand->scale(glm::vec3(0.04, 0.25f, 0.04f));
		thinSteeringWheelStand->setParent(thickSteeringWheelStand);

		//steering wheel
		Pipe* steeringWheel = new Pipe(glm::vec4(1.0f, 115.0f / 255.0f, 0.2f, 1.0f), 0.7f);
		objects.push_back(steeringWheel);
		steeringWheel->move(glm::vec3(0.0f, 0.6f, 0.0f));
		steeringWheel->scale(glm::vec3(0.045f, 0.4f, 0.4f));
		steeringWheel->setParent(thinSteeringWheelStand);

		vector<Cone*> propeller;
		for (int i = 0; i < (int)WINGS_NUM; ++i) {
			Cone* cone = new Cone(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
			cone->move(glm::vec3(-0.15f, 0.0f, 0.0f));
			cone->rotate(glm::vec3(i * (360.0f/WINGS_NUM), 0.0f, 0.0f));
			cone->scale(glm::vec3(0.05f, 1.3f, 0.2f));
			cone->setParent(propellerGuard);
			propeller.push_back(cone);
			objects.push_back(cone);
		}
		GLfloat steerPosition = 0.0f;
		vector<Cone*> steeringWheelInterior;
		for (int i = 0; i < 3; ++i) {
			Cone* cone = new Cone(glm::vec4(0.0f, 1.0f, 1.0f, 1.0f));
			cone->move(glm::vec3(0.0f, 0.0f, 0.0f));
			cone->rotate(glm::vec3(i * (360.0f / 3), 0.0f, 0.0f));
			cone->scale(glm::vec3(0.05f, 0.4f, 0.07f));
			cone->setParent(steeringWheel);
			steeringWheelInterior.push_back(cone);
			objects.push_back(cone);
		}

		//bird
		vector <GLint> birds;
		vector <GLint> wings;
		vector <GLfloat> birdPositionX;
		vector <GLfloat> birdPositionZ;
		vector <GLfloat> birdRotateCounter;
		vector <GLfloat> birdSpeed;

		bool up = false;
		for (int i = 0; i < BIRD_QUANTITY; ++i) {
			birds.push_back(objects.size());
			birdPositionX.push_back(0.0f);
			birdPositionZ.push_back(0.0f);
			birdRotateCounter.push_back(0.0f);
			int speed = rand() % 100 + 30;
			birdSpeed.push_back((GLfloat)speed / 100.0f);
			int altitude = (rand() % 800) + BIRD_HIGHT_PARAM;
			
			Cuboid* birdBody = new Cuboid(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
			objects.push_back(birdBody);
			birdBody->scale(glm::vec3(2.5f, 1.0f, 0.25f));
			birdBody->move(glm::vec3(0.0f - WATER_SIZE/2.0f, (GLfloat)altitude / 100.0f, 0.0f - WATER_SIZE / 2.0f));
			
			Pipe* head = new Pipe(glm::vec4(65.0f / 255.0f, 0.0f / 255.0f, 93.0f / 255.0f, 1.0f), 0.5);
			objects.push_back(head);
			head->rotate(glm::vec3(0.0f, 90.0f, 0.0f));
			head->move(glm::vec3(0.0f, 0.85f, 1.2f));
			head->scale(glm::vec3(0.15f, 0.4f, 0.4f));
			head->setParent(birdBody);

			wings.push_back(objects.size());
			Cone* wing1 = new Cone(glm::vec4(65.0f / 255.0f, 0.0f / 255.0f, 93.0f / 255.0f, 1.0f));
			objects.push_back(wing1);
			wing1->scale(glm::vec3(0.7f, 1.4f, 0.1f));
			wing1->rotate(glm::vec3(45.0f, 0.0f, 0.0f));
			wing1->setParent(birdBody);

			wings.push_back(objects.size());
			Cone* wing2 = new Cone(glm::vec4(65.0f / 255.0f, 0.0f / 255.0f, 93.0f / 255.0f, 1.0f));
			objects.push_back(wing2);
			wing2->scale(glm::vec3(0.7f, 1.4f, 0.1f));
			wing2->rotate(glm::vec3(-45.0f, 0.0f, 0.0f));
			wing2->setParent(birdBody);
			
			Cone* tail = new Cone(glm::vec4(65.0f / 255.0f, 0.0f / 255.0f, 93.0f / 255.0f, 1.0f));
			objects.push_back(tail);
			tail->scale(glm::vec3(0.03f, 0.8f, 0.1f));
			tail->move(glm::vec3(-1.2f, 0.45f, 0.0f));
			tail->rotate(glm::vec3(0.0f, 0.0f, 45.0f));
			tail->setParent(birdBody);

			Cone* beak = new Cone(glm::vec4(230.0f / 255.0f, 198.0f / 255.0f, 25.0f / 255.0f, 1.0f));
			objects.push_back(beak);
			beak->scale(glm::vec3(0.1f, 0.7f, 0.1f));
			beak->move(glm::vec3(0.0f, 0.0f, 0.4f));
			beak->rotate(glm::vec3(90.0f, 0.0f, 0.0f));
			beak->setParent(head);
		}

		//volcano
		Cone* volcano = new Cone(glm::vec4(120.0f/255.0f, 60.0f/255.0f, 0.0f, 1.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
		objects.push_back(volcano);
		volcano->scale(glm::vec3(10.0f, 20.0f, 10.0f));
		volcano->rotate(glm::vec3(0.0f, 0.0f, 0.0f));
		volcano->move(glm::vec3(80.0f, 0.0f, 0.0f));

		//mountains
		Cone* mountain1 = new Cone(glm::vec4(144.0f / 255.0f, 123.0f / 255.0f, 90.0f/255.0f, 1.0f));
		objects.push_back(mountain1);
		mountain1->scale(glm::vec3(10.0f, 20.0f, 10.0f));
		mountain1->rotate(glm::vec3(0.0f, 0.0f, 0.0f));
		mountain1->move(glm::vec3(-80.0f, 0.0f, 0.0f));

		Cone* mountain2 = new Cone(glm::vec4(255.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f, 1.0f));
		objects.push_back(mountain2);
		mountain2->scale(glm::vec3(2.5f, 5.0f, 2.5f));
		mountain2->rotate(glm::vec3(0.0f, 0.0f, 0.0f));
		mountain2->move(glm::vec3(0.0f, 15.01f, 0.0f));
		mountain2->setParent(mountain1);

		Cone* mountain3 = new Cone(glm::vec4(144.0f / 255.0f, 123.0f / 255.0f, 90.0f / 255.0f, 1.0f));
		objects.push_back(mountain3);
		mountain3->scale(glm::vec3(5.0f, 10.0f, 5.0f));
		mountain3->rotate(glm::vec3(0.0f, 0.0f, 0.0f));
		mountain3->move(glm::vec3(0.0f,0.0f, 10.0f));
		mountain3->setParent(mountain1);

		Cone* mountain4 = new Cone(glm::vec4(144.0f / 255.0f, 123.0f / 255.0f, 90.0f / 255.0f, 1.0f));
		objects.push_back(mountain4);
		mountain4->scale(glm::vec3(5.0f, 15.0f, 5.0f));
		mountain4->rotate(glm::vec3(0.0f, 0.0f, 0.0f));
		mountain4->move(glm::vec3(0.0f, 0.0f, -8.0f));
		mountain4->setParent(mountain1);

		Cone* mountain5 = new Cone(glm::vec4(255.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f, 1.0f));
		objects.push_back(mountain5);
		mountain5->scale(glm::vec3(1.0f, 3.0f, 1.0f));
		mountain5->rotate(glm::vec3(0.0f, 0.0f, 0.0f));
		mountain5->move(glm::vec3(0.0f, 12.26f, 0.0f));
		mountain5->setParent(mountain4);

		Cone* mountain6 = new Cone(glm::vec4(125.0f / 255.0f, 98.0f / 255.0f, 72.0f / 255.0f, 1.0f));
		objects.push_back(mountain6);
		mountain6->scale(glm::vec3(2.5f, 5.0f, 2.5f));
		mountain6->rotate(glm::vec3(0.0f, 0.0f, 0.0f));
		mountain6->move(glm::vec3(11.0f, 0.0f, 0.0f));
		mountain6->setParent(mountain1);

		int numberOfLilies = rand() % 50 + 25;
		generateLilies(objects, numberOfLilies);
		
		Skybox skybox = Skybox();

		glm::vec3 lightPos = LIGHT_POS_VERT;

		glm::vec3 lightColor = LIGHT_COLOR_VEC;

		// main event loop
		while (!glfwWindowShouldClose(window)) {
			if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
				glider->move(glm::vec3(0.1f + turbo, 0.0f, 0.0f));
				for (int i = 0; i < (int)WINGS_NUM; ++i)
					propeller[i]->rotate(glm::vec3(40.0f, 0.0f, 0.0f));
			}
			if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
				glider->move(glm::vec3(-0.1f - turbo, 0.0f, 0.0f));
				for (int i = 0; i < (int)WINGS_NUM; ++i)
					propeller[i]->rotate(glm::vec3(40.0f, 0.0f, 0.0f));
			}
			if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
				if((glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS))
					glider->rotate(glm::vec3(0.0f, -1.0f, 0.0f));

				for (int i = 0; i < 3; ++i)
					steeringWheelInterior[i]->rotate(glm::vec3(5.0f, 0.0f, 0.0f));
				if (rudder->rudderCounter <= 45.0f) {
					rudder->rotate(glm::vec3(0.0f, -2.0f, 0.0f));
					rudder->rudderCounter += 2.0f;
				}
			} 
			if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS ) {
				if ((glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS))
					glider->rotate(glm::vec3(0.0f, 1.0f, 0.0f));
				for (int i = 0; i < 3; ++i)
					steeringWheelInterior[i]->rotate(glm::vec3(-5.0f, 0.0f, 0.0f));
				if (rudder->rudderCounter >= -45.0f) {
					rudder->rotate(glm::vec3(0.0f, 2.0f, 0.0f));
					rudder->rudderCounter -= 2.0f;
				}
			}
			if (glfwGetKey(window, GLFW_KEY_LEFT) != GLFW_PRESS && glfwGetKey(window, GLFW_KEY_RIGHT) != GLFW_PRESS) {
				rudder->rotate(glm::vec3(0.0f, rudder->rudderCounter, 0.0f));
				rudder->rudderCounter = 0.0f;
			}
			if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
				turbo = 1.0f;
			else
				turbo = 0.0f;

			for (int i = 0; i < birds.size(); ++i) {
				objects[birds[i]]->move(glm::vec3(birdSpeed[i], 0.0f, 0.0f));
				birdPositionX[i] += birdSpeed[i];
				if (birdPositionX[i] >= WATER_SIZE) {
					GLfloat randomizeZ = rand() % (int)WATER_SIZE;
					birdPositionZ[i] += randomizeZ;
					objects[birds[i]]->move(glm::vec3(WATER_SIZE * -1.0f, 0.0f, randomizeZ));
					birdPositionX[i] -= WATER_SIZE;
					if (birdPositionZ[i] >= WATER_SIZE) {
						objects[birds[i]]->move(glm::vec3(0.0f, 0.0f, 0.0f - WATER_SIZE));
						birdPositionZ[i] -= WATER_SIZE;
					}
				}
			}

			// poruszanie szescianem przod tyl
			if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) {
				lightPos += glm::vec3(0.1f, 0.0f, 0.0f);
			}
			if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) {
				lightPos += glm::vec3(-0.1f, 0.0f, 0.0f);
			}
			// poruszanie szescianem lewo prawo
			if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
				lightPos += glm::vec3(0.0f, 0.0f, 0.1f);
			}
			if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) {
				lightPos += glm::vec3(0.0f, 0.0f, -0.1f);
			}
			// poruszanie szescianem gora dol
			if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) {
				lightPos += glm::vec3(0.0f, 0.1f, 0.0f);
			}
			if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) {
				lightPos += glm::vec3(0.0f, -0.1f, 0.0f);
			}

			// zmiana koloru swiatla
			if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) {
				lightColor = glm::vec3(1.0f, 0.0f, 0.0f);
			}
			if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) {
				lightColor = glm::vec3(0.0f, 1.0f, 0.0f);
			}
			if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) {
				lightColor = glm::vec3(0.0f, 0.0f, 1.0f);
			}
			if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS) {
				lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
			}

			for (int i = 0; i < wings.size(); i+=2) {
				if (up) {
					objects[wings[i]]->rotate(glm::vec3(-2.0f, 0.0f, 0.0f));
					objects[wings[i+1]]->rotate(glm::vec3(2.0f, 0.0f, 0.0f));
					birdRotateCounter[i/2] -= 2;
					if (birdRotateCounter[i/2] <= 0.0f)
						up = !up;
				} else {
					objects[wings[i]]->rotate(glm::vec3(2.0f, 0.0f, 0.0f));
					objects[wings[i + 1]]->rotate(glm::vec3(-2.0f, 0.0f, 0.0f));
					birdRotateCounter[i/2] += 2;
					if (birdRotateCounter[i/2] >= 90.0f)
						up = !up;
				}

			}
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
			glUniform3fv(glGetUniformLocation(colorShaders.get_programID(), "lightColor"), 1, &lightColor[0]);
			glUniform3fv(glGetUniformLocation(colorShaders.get_programID(), "lightPos"), 1, &lightPos[0]);
			//colorShaders.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
			//colorShaders.setVec3("lightPos", LIGHT_POS_VERT);

			glUniformMatrix4fv(glGetUniformLocation(colorShaders.get_programID(), "view"), 1, GL_FALSE, &view[0][0]);
			glUniformMatrix4fv(glGetUniformLocation(colorShaders.get_programID(), "projection"), 1, GL_FALSE, &projection[0][0]);
			
			for (Object* obj : objects) {
				if (!(obj->isTextured()))
					obj->draw(colorShaders.get_programID());
			}
		
			skybox.draw(projection, view);

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
