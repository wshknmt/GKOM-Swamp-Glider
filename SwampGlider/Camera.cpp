#include "Camera.h"

Camera::Camera(GLFWwindow* window, glm::vec3 positionVector, GLfloat hAngle,
	GLfloat vAngle, GLfloat movementSpeed, GLfloat mouseSpeed) :
	window(window), positionVector(positionVector), hAngle(hAngle), 
	vAngle(vAngle), movementSpeed(movementSpeed), mouseSpeed(mouseSpeed){};

glm::mat4 Camera::getViewMatrix() {
	return ViewMatrix;
}

void Camera::refresh() {
	double mouseX, mouseY;
	glfwGetCursorPos(window, &mouseX, &mouseY);

	glfwSetCursorPos(window, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);

	if (!initialRun) {
		hAngle += mouseSpeed * GLfloat(WINDOW_WIDTH / 2 - mouseX);
		vAngle += mouseSpeed * GLfloat(WINDOW_HEIGHT / 2 - mouseY);
	} else 
		initialRun = false;

	if (vAngle > glm::radians(90.0f))
		vAngle = glm::radians(90.0f);
	if (vAngle < -glm::radians(90.0f))
		vAngle = -glm::radians(90.0f);

	glm::vec3 direction(cos(vAngle) * sin(hAngle), sin(vAngle), cos(vAngle) * cos(hAngle));
	glm::vec3 right = glm::vec3(sin(hAngle - glm::radians(90.0f)), 0, cos(hAngle - glm::radians(90.0f)));
	glm::vec3 up = glm::cross(right, direction);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) 
		positionVector += direction * movementSpeed;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		positionVector -= direction * movementSpeed;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		positionVector -= right * movementSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) 
		positionVector += right * movementSpeed;
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		positionVector += up * movementSpeed;
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		positionVector -= up * movementSpeed;

	ViewMatrix = glm::lookAt(positionVector, positionVector + direction, up);
}