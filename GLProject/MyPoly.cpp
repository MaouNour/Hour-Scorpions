#include "Polygon3d.cpp"
#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class MyPoly:Polygon3d {
private:
	float depth;
	void calDepth(float z1, float z2) {
		this->depth = abs(z1 - z2);
	}
	void calDepth(float scale) {
		this->depth = depth * scale;
	}
	float getDepth() { return depth; }
public:
	MyPoly(std::vector<glm::vec3> vertices,float depth){
		this->vertices = vertices;
		int currsize = vertices.size();
		std::vector<int> faces = {};
		std::vector<int> numberOfVerticesInFace = {};

		for (int i = 0; i < currsize; i++)
		{
			vertices.push_back(glm::vec3(vertices.at(i).x, vertices.at(i).y,depth));
		}
		calDepth(vertices.at(0).z, vertices.at(currsize).z);
		//make front and back faces
		for (int i = 0; i < vertices.size(); i++)
		{
			faces.push_back(i);
		}
		numberOfVerticesInFace.push_back(currsize);
		numberOfVerticesInFace.push_back(currsize);
		//make all through faces
		int size = vertices.size();
		for (int i = 0; i < currsize; i++)
		{
			faces.push_back(i % size);
			faces.push_back((i+1) % size);
			faces.push_back((i+currsize+1) % size);
			faces.push_back((i+currsize) % size);
			numberOfVerticesInFace.push_back(4);
		}
		Polygon3d::init(vertices,numberOfVerticesInFace,faces);
	}
public:
	void draw(Shader& shader) {

		Polygon3d::draw(shader);
	}
	void deleteBuffers() {
		Polygon3d::deleteBuffers();
	}
	void transformation(glm::mat4 t) {
		Polygon3d::transformation(t);
	}
	//TESTING
	void Zscale(float value) {
		glm::mat4 scaling = glm::mat4(1.0);
		//scaling side polygons
		scaling = glm::scale(scaling,glm::vec3(1.0f,1.0f,value));
		float curdepth = getDepth();
		calDepth(value);
		float trans = abs(curdepth - getDepth())/2;
		//std::cout << trans;
		for (int i = 2; i < polygons.size(); i++)
		{
			polygons.at(i).transformation(scaling);
		}
		// translation of the fron tand back polygon
		glm::mat4 translation = glm::mat4(1.0f);
		polygons.at(0).transformation(glm::translate(translation, glm::vec3(0.0f, 0.0f, trans)));
		polygons.at(1).transformation(glm::translate(translation, glm::vec3(0.0f, 0.0f, -trans)));
	}
};