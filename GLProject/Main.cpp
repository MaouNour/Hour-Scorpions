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
//#include "Polygon.cpp"
#include <math.h>

using namespace glm;

int width = 800;
int height = 600;

vec3 cameraPos = vec3(0.0f, 0.0f, 4.0f);
vec3 cameraFront = vec3(0.0f, 0.0f, -1.0f);
vec3 cameraUp = vec3(0.0f, 1.0f, 0.0f);

void processInput(GLFWwindow *window)
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
		cameraPos += cross(cameraFront,normalize(cross(cameraFront, cameraUp))) * cameraSpeed;
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

	glEnable(GL_DEPTH_TEST);

	Shader ourShader("./shaders/vs/L3.vs", "./shaders/fs/L3.fs");
	std::vector<vec3> vertices0 = {};

	/*vertices0.push_back(vec3(0.01f, -3.0f, 0.0f));
	vertices0.push_back(vec3(-0.01f, -3.0f, 0.0f));
	vertices0.push_back(vec3(-0.01f, 3.0f, 0.0f));
	vertices0.push_back(vec3(0.01f, 3.0f, 0.0f));
	Polygon axis = Polygon(vertices0, vec3(0.0f, 0.0f, 0.0f));*/

	std::vector<vec3> vertices1 = {};
	vertices1.push_back(vec3(0.5f, -0.5f, 0.0f));//down right
	vertices1.push_back(vec3(-0.5f, -0.5f, 0.0f));//down left
	vertices1.push_back(vec3(-0.5f, 0.5f, 0.0f));//top left
	vertices1.push_back(vec3(0.5f, 0.5f, 0.0f));//top right
	Polygon Polygon1 = Polygon(vertices1, vec3(1.0f, 0.0f, 0.0f));
	/////////////////////////////////////////////////////
	std::vector<vec3> arrow1 = {};
	arrow1.push_back(vec3(0.01f, 0.0f, 0.0f));///
	arrow1.push_back(vec3(0.01f, 0.4f, 0.0f));//
	arrow1.push_back(vec3(-0.01f, 0.4f, 0.0f));//
	arrow1.push_back(vec3(-0.01f, 0.0f, 0.0f));//
	Polygon Arrow1 = Polygon(arrow1, vec3(0.0f, 1.0f, 0.0f));

	std::vector<vec3> arrow11 = {};
	arrow11.push_back(vec3(0.05f, 0.4f, 0.0f));//
	arrow11.push_back(vec3(0.0f, 0.45f, 0.0f));//
	arrow11.push_back(vec3(-0.05f, 0.4f, 0.0f));//
	Polygon Arrow11 = Polygon(arrow11, vec3(0.0f, 1.0f, 0.0f));
	////////////////////////////////////////////////////
	std::vector<vec3> arrow2 = {};
	arrow2.push_back(vec3(0.01f, 0.0f, 0.01f));///
	arrow2.push_back(vec3(0.01f, 0.2f, 0.01f));//
	arrow2.push_back(vec3(-0.01f, 0.2f, 0.01f));//
	arrow2.push_back(vec3(-0.01f, 0.0f, 0.01f));//
	Polygon Arrow2 = Polygon(arrow2, vec3(1.0f, 1.0f, 0.0f));

	std::vector<vec3> arrow22 = {};
	arrow22.push_back(vec3(0.05f, 0.2f, 0.001f));//
	arrow22.push_back(vec3(0.0f, 0.25f, 0.001f));//
	arrow22.push_back(vec3(-0.05f, 0.2f, 0.001f));//
	Polygon Arrow22 = Polygon(arrow22, vec3(1.0f, 1.0f, 0.0f));
	//////////////////////////////////////////////////////
	std::vector<vec3> arrow3 = {};
	arrow3.push_back(vec3(0.01f, 0.0f, 0.001f));///
	arrow3.push_back(vec3(0.01f, 0.3f, 0.001f));//
	arrow3.push_back(vec3(-0.01f, 0.3f, 0.001f));//
	arrow3.push_back(vec3(-0.01f, 0.0f, 0.001f));//
	Polygon Arrow3 = Polygon(arrow3, vec3(0.0f, 1.0f, 1.0f));

	std::vector<vec3> arrow33 = {};
	arrow33.push_back(vec3(0.05f, 0.3f, 0.01f));//
	arrow33.push_back(vec3(0.0f, 0.35f, 0.01f));//
	arrow33.push_back(vec3(-0.05f, 0.3f, 0.01f));//
	Polygon Arrow33 = Polygon(arrow33, vec3(0.0f, 1.0f, 1.0f));
	//////////////////////////////////////////////////////


	std::vector<vec3> vertices2 = {};
	vertices2.push_back(vec3(-0.01f, -0.2f, 0.0f));
	vertices2.push_back(vec3(-0.01f, 0.2f, 0.0f));
	vertices2.push_back(vec3(0.01f, 0.2f, 0.0f));
	vertices2.push_back(vec3(0.01f, -0.2f, 0.0f));
	Polygon Polygon2 = Polygon(vertices2, vec3(0.0f, 1.0f, 0.0f));

	std::vector<vec3> vertices3 = {};
	vertices3.push_back(vec3(0.5f, -0.5f, 0.0f));//right
	vertices3.push_back(vec3(-0.5f, -0.5f, 0.0f));//left
	vertices3.push_back(vec3(-0.5f, 0.5f, 0.0f));//top
	vertices3.push_back(vec3(0.5f, 0.5f, 0.0f));//top
	Polygon Polygon3 = Polygon(vertices3, vec3(0.0f, 0.0f, 1.0f));

	//std::vector<vec3> vertices4 = {};
	//vertices4.push_back(vec3(-0.5f, -0.5f, 0.0f));
	//vertices4.push_back(vec3(-0.5f, -0.5f, 1.0f));
	//vertices4.push_back(vec3(0.0f, 0.366f, 1.0f));
	//vertices4.push_back(vec3(0.0f, 0.366f, 0.0f));
	//Polygon Polygon4 = Polygon(vertices4, vec3(1.0f, 1.0f, 0.0f));

	//std::vector<vec3> vertices5 = {};
	//vertices5.push_back(vec3(0.5f, -0.5f, 0.0f));
	//vertices5.push_back(vec3(0.5f, -0.5f, 1.0f));
	//vertices5.push_back(vec3(0.0f, 0.366f, 1.0f));
	//vertices5.push_back(vec3(0.0f, 0.366f, 0.0f));
	//Polygon Polygon5 = Polygon(vertices5, vec3(1.0f, 1.0f, 0.0f));

	ourShader.use();
	
	mat4 projection = mat4(1.0f);
	projection = perspective(radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
	//projection = ortho(-(float)width, (float)width, -(float)height, (float)height, 0.01f, 100.0f);;
	ourShader.setMat4("projection", projection);

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		mat4 view = mat4(1.0f);
		//view = translate(view, vec3(0.0f, 0.0f, -4.0f));
		view = lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
		ourShader.setMat4("view", view);
		
		mat4 transformation = mat4(1.0f);
		//transformation = translate(transformation, vec3(0.0f, -0.5f, 0.0f));
		//axis.transformation(transformation);
		//axis.draw(ourShader);
		//transformation = rotate(transformation, (float)glfwGetTime(), vec3(0.0f, 1.0f, 1.0f));

		//////////////////////////////////////////////////////
		transformation = mat4(1.0f);
		float rotationSpeed = glm::radians(6.0f);
		float time = glfwGetTime();
		float angle = rotationSpeed * time;
		transformation = rotate(transformation, angle, vec3(0.0f, 0.0f, -1.0f));

		Arrow1.transformation(transformation);
        Arrow11.transformation(transformation);
		
		Arrow1.draw(ourShader);
		Arrow11.draw(ourShader);
		///////////////////////////////////////////////////////////////////
		transformation = mat4(1.0f);
		float timeInMin = glfwGetTime()/ 60;
		float MinAngle = rotationSpeed * timeInMin;
		transformation = rotate(transformation, MinAngle, vec3(0.0f, 0.0f, -1.0f));
		transformation = rotate(transformation, (float)3.14 / 2, vec3(0.0f, 0.0f, -1.0f));
		
		Arrow2.transformation(transformation);
		Arrow22.transformation(transformation);

		Arrow2.draw(ourShader);
		Arrow22.draw(ourShader);
		////////////////////////////////////////////////////////////////////////
		transformation = mat4(1.0f);
		float timeInHours = glfwGetTime() / 3600;
		rotationSpeed = glm::radians(30.0f);
		float HourAngle = rotationSpeed * timeInHours;
		transformation = rotate(transformation, HourAngle, vec3(0.0f, 0.0f, -1.0f));
		transformation = rotate(transformation, (float)3.14 / 4, vec3(0.0f, 0.0f, -1.0f));

		Arrow3.transformation(transformation);
		Arrow33.transformation(transformation);

		Arrow3.draw(ourShader);
		Arrow33.draw(ourShader);
		/////////////////////////////////////////////////////
		transformation = mat4(1.0f);
		transformation = translate(transformation, vec3(0.0f, 0.1f, 0.0f));
		transformation = scale(transformation, vec3(0.8f, 0.8f, 1.0f));
		Polygon1.transformation(transformation);
		Polygon1.draw(ourShader);

		float speed = 0.5f;
		transformation = mat4(1.0f);
		transformation = rotate(transformation, cos((float)glfwGetTime())/2, vec3(0.0f, 0.0f, 1.0f*speed));
		transformation = translate(transformation, vec3(0.0f, -0.5f, 0.0f));
		Polygon2.transformation(transformation);
		Polygon2.draw(ourShader);

		transformation = mat4(1.0f);
		transformation = rotate(transformation, cos((float)glfwGetTime())/2, vec3(0.0f, 0.0f, 1.0f*speed));
		transformation = translate(transformation, vec3(0.0f, -0.5f - 0.1f * 2.0f, 0.1f));
		transformation = scale(transformation, vec3(0.12,0.12,1.0));
		Polygon3.transformation(transformation);
		Polygon3.draw(ourShader);
		
		
		////Polygon4.transformation(transformation);
		//Polygon4.draw(ourShader);

		////Polygon5.transformation(transformation);
		//Polygon5.draw(ourShader);

		//Test::
		std::vector<vec3> ve = {};
		ve.push_back(vec3(0.5f, -0.5f, 0.0f));//down right
		ve.push_back(vec3(-0.5f, -0.5f, 0.0f));//down left
		ve.push_back(vec3(-0.5f, 0.5f, 0.0f));//top left
		ve.push_back(vec3(0.5f, 0.5f, 0.0f));//top right
		//MyPoly m = MyPoly(ve,0.5f);
		//glm::mat4 t = mat4(1.0f);
		//t = glm::rotate(t,30.0f,vec3(0.0f,1.0f,0.0f));
		//m.transformation(t);
		//m.Zscale(0.5);
		//m.draw(ourShader);
		


		//
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
