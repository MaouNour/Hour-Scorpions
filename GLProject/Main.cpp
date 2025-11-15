// GLProject.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <glad/glad_loader_docs.h>
#include <GLFW/glfw3.h>
#include <learnopengl/shader_m.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "MyPoly.cpp"
#include "Polygon.cpp"
#include <math.h>
#include "Shapes.cpp"
#include <stb_image.h>
#include "PolygonTex.cpp"
#include "Helper.cpp"


using namespace glm;

int width = 800;
int height = 600;

vec3 cameraPos = vec3(0.0f, 0.0f, 4.0f);
vec3 cameraFront = vec3(0.0f, 0.0f, -1.0f);
vec3 cameraUp = vec3(0.0f, 1.0f, 0.0f);



static int seconds = 0;
static int minutes = 0;
static int hours = 0;
bool checkSeconds();
bool checkMinutes();
bool checkHours();
static std::vector<MyPoly> makeArrow(float length,float rectWidth= 0.02f,float triangleEdge= 0.03f,float depth=0.02f) {
	MyPoly ArrowBody = MyPoly(Shapes::makeRect(rectWidth, length), depth);
	ArrowBody.translate(vec3(0.0f, 0.0f, 0.34f));
	ArrowBody.translate(vec3(0.0f, length / 2.0f, 0.0f));
	ArrowBody.setCenter(vec3(0.0f, -length/2.0f, 0.0f));
	MyPoly ArrowHead = MyPoly(Shapes::makeTriangle(triangleEdge), depth);
	ArrowHead.translate(vec3(0.0f, 0.0f, 0.34f));
	ArrowHead.translate(vec3(0.0f, length, 0.0f));
	ArrowHead.setCenter(vec3(0.0f, -length, 0.0f));
	return {ArrowBody,ArrowHead};
}
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	const float cameraSpeed = 0.02f;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cameraPos += cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cameraPos -= cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cameraPos -= normalize(cross(cameraFront, cameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cameraPos += normalize(cross(cameraFront, cameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		cameraPos += cross(cameraFront, normalize(cross(cameraFront, cameraUp))) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		cameraPos -= cross(cameraFront, normalize(cross(cameraFront, cameraUp))) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		mat4 rotationMatrix = glm::rotate(mat4(1.0f), 0.001f, vec3(0.0f, 1.0f, 0.0f));
		vec4 rotatedVectorHomogeneous = rotationMatrix * vec4(cameraFront, 1.0f);
		cameraFront = vec3(rotatedVectorHomogeneous);
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		mat4 rotationMatrix = glm::rotate(mat4(1.0f), 0.001f, vec3(0.0f, -1.0f, 0.0f));
		vec4 rotatedVectorHomogeneous = rotationMatrix * vec4(cameraFront, 1.0f);
		cameraFront = vec3(rotatedVectorHomogeneous);
	}
}

int main()
{
	glfwInit();
	GLFWwindow* window = glfwCreateWindow(width, height, "Lecture 3", NULL, NULL);
	glfwMakeContextCurrent(window);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	glfwSwapInterval(1);

	glEnable(GL_DEPTH_TEST);
	Shader ourShader("./shaders/vs/L3.vs", "./shaders/fs/L3.fs");
	Shader texShader("./shaders/vs/texture.vs", "./shaders/fs/texture.fs");

	mat4 projection = mat4(1.0f);
	projection = perspective(radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
	ourShader.setMat4("projection", projection);
	
	//INIT
	MyPoly box = MyPoly(Shapes::makeRect(1.0f, 1.0f), 0.5f, TEXTURE, Shapes::squareTexture(), {"./container.jpg"});
	MyPoly UpperClockShape = MyPoly(Shapes::makeCircle(30, 0.5f), 0.5);
	PolygonTex clock = PolygonTex(Shapes::makeRect(0.7, 0.7), "./ccc.png", Shapes::squareTexture());
	std::vector<MyPoly> temp= makeArrow(0.20f,0.01);
	MyPoly secArrowBody = temp.at(0);
	MyPoly secArrowHead = temp.at(1);
	temp = makeArrow(0.15f,0.01);
	MyPoly minArrowBody = temp.at(0);
	MyPoly minArrowHead = temp.at(1);
	temp = makeArrow(0.10f,0.015f,0.03f);
	MyPoly hoursArrowBody = temp.at(0);
	MyPoly hoursArrowHead = temp.at(1);
	MyPoly centerCircle = MyPoly(Shapes::makeCircle(10, 0.015f), 0.02f);
	centerCircle.translate(vec3(0.0f, 0.0f, 0.34f));
	MyPoly pendulumBody = MyPoly(Shapes::makeRect(0.02f,0.7f),0.02f);
	pendulumBody.setCenter(vec3(0.0f,0.35f,0.0f));
	MyPoly pendulumHead = MyPoly(Shapes::makeCircle(30,0.1),0.02f);
	pendulumHead.setCenter(vec3(0.0f, 0.7f, 0.0f));
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		mat4 view = mat4(1.0f);
		//view = translate(view, vec3(0.0f, 0.0f, -4.0f));
		view = lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
		
		//##Textured Objects
		texShader.use();
		texShader.setMat4("projection", projection);
		texShader.setMat4("view", view);
		box.resetTransformation();
		box.scale(vec3(0.6f,1.0f,0.5f));
		box.translate(vec3(0.0f, -0.75f, 0.0f));
		box.draw(texShader);
		mat4 transform = mat4(1.0);
		transform = translate(transform,vec3(0.0f,0.0f,0.35f));
		clock.transformation(transform);
		clock.draw(texShader);



		//##Colored Objects
		ourShader.use();
		ourShader.setMat4("projection", projection);
		ourShader.setMat4("view", view);
		UpperClockShape.resetTransformation();
		UpperClockShape.scale(vec3(0.7,0.7,0.6));
		UpperClockShape.translate(vec3(0.0f,0.0f,-0.15f));
		UpperClockShape.setColor(vec3(0.5,0.5,0.5));
		UpperClockShape.draw(ourShader);
		centerCircle.draw(ourShader);
		if(checkSeconds())
		{
			secArrowBody.rotate(6.0f, vec3(0.0f, 0.0f, -1.0f));
			secArrowHead.rotate(6.0f, vec3(0.0f, 0.0f, -1.0f));
		}
		secArrowBody.draw(ourShader);
		secArrowHead.draw(ourShader);
		if (checkMinutes())
		{
			minArrowBody.rotate(6.0f, vec3(0.0f, 0.0f, -1.0f));
			minArrowHead.rotate(6.0f, vec3(0.0f, 0.0f, -1.0f));
		}
		minArrowBody.draw(ourShader);
		minArrowHead.draw(ourShader);
		if (checkHours())
		{
			hoursArrowBody.rotate(30.0f, vec3(0.0f, 0.0f, -1.0f));
			hoursArrowHead.rotate(30.0f, vec3(0.0f, 0.0f, -1.0f));
		}
		hoursArrowBody.draw(ourShader);
		hoursArrowHead.draw(ourShader);
		float rotationSpeed = glm::radians(180.0f);
		pendulumBody.resetTransformation();
		pendulumBody.translate(vec3(0.0f, -0.6f, 0.28f));
		pendulumBody.rotateRad(cos((float)glfwGetTime() * rotationSpeed) / 2, vec3(0.0f, 0.0f, 1.0f));
		pendulumBody.draw(ourShader);

		pendulumHead.resetTransformation();
		pendulumHead.translate(vec3(0.0f,-0.9f,0.28f));
		pendulumHead.rotateRad(cos((float)glfwGetTime() * rotationSpeed) / 2, vec3(0.0f, 0.0f, 1.0f));
		pendulumHead.draw(ourShader);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
bool checkSeconds() {
	if ((int)glfwGetTime() > seconds)
	{
		seconds = (int)glfwGetTime();
		return true;
	}
	return false;
}
bool checkMinutes() {
	if ((int)glfwGetTime()/60 > minutes)
	{
		minutes = (int)glfwGetTime() / 60;
		return true;
	}
	return false;
}
bool checkHours() {
	if ((int)glfwGetTime() / 3600 > hours)
	{
		hours = (int)glfwGetTime() / 3600;
		return true;
	}
	return false;
}