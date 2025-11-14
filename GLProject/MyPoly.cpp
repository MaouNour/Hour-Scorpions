#include "Polygon3d.cpp"
#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class MyPoly:public Polygon3d {
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
	
};