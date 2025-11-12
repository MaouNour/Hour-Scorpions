#include "Polygon.cpp"
#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Polygon3d {
private:
protected:
	std::vector<glm::vec3> vertices;
	std::vector<Polygon> polygons;
	glm::vec3 color = glm::vec3(1.0f, 0.0f, 0.0f);
	glm::mat4 model;
	Polygon3d() {};
	void init(std::vector<glm::vec3> vertices, std::vector<int> numberOfVerticesInFace, std::vector<int> faces) {
		int f = 0;
		for (int i = 0; i < numberOfVerticesInFace.size(); i++)
		{
			std::vector<glm::vec3> p = {};
			for (int j = 0; j < numberOfVerticesInFace.at(i); j++)
			{
				//error here (nvm i fixed it)
				p.push_back(vertices.at(faces.at(f++)));
			}
			polygons.push_back(Polygon(p, color));
		}
	}
public:
	Polygon3d(std::vector<glm::vec3> vertices , std::vector<int> numberOfVerticesInFace,std::vector<int> faces) {
		this->vertices = vertices;
		init(vertices, numberOfVerticesInFace, faces);
	}
	void draw(Shader& shader) {
		for (int i = 0; i < polygons.size(); i++)
		{
			polygons.at(i).draw(shader);
		}
	}
	void deleteBuffers() {
		for (int i = 0; i < polygons.size(); i++)
		{
			polygons.at(i).deleteBuffers();
		}
	}
	void transformation(glm::mat4 t) {
		//TODO
		//error in rotation and scaling 
		for (int i = 0; i < polygons.size(); i++)
		{
			polygons.at(i).transformation(t);
		}
	}
	
};