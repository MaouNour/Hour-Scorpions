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
	glm::mat4 model = glm::mat4(1.0f);
	glm::vec3 center = { 0, 0, 0 };
	Polygon3d() {};
	void init(std::vector<glm::vec3> vertices, std::vector<int> numberOfVerticesInFace, std::vector<int> faces) {
		int f = 0;
		for (int i = 0; i < numberOfVerticesInFace.size(); i++)
		{
			std::vector<glm::vec3> p = {};
			for (int j = 0; j < numberOfVerticesInFace.at(i); j++)
			{
				p.push_back(vertices.at(faces.at(f++)));
			}
			polygons.push_back(Polygon(p, color));
		}
		setCenter(computeCenter());
	}
	void setCenter(const glm::vec3& c) {
		center = c;
	}
	glm::vec3 computeCenter() {
		glm::vec3 min(FLT_MAX);
		glm::vec3 max(-FLT_MAX);

		for (auto& poly : polygons) {
			for (auto& v : poly.getVertices()) {
				min = glm::min(min, v);
				max = glm::max(max, v);
			}
		}
		return (min + max) * 0.5f;
	}
public:
	Polygon3d(std::vector<glm::vec3> vertices , std::vector<int> numberOfVerticesInFace,std::vector<int> faces) {
		this->vertices = vertices;
		init(vertices, numberOfVerticesInFace, faces);
	}
	void draw(Shader& shader) {
		shader.use();
		shader.setMat4("model", model);
		shader.setVec3("objectColor", color);

		for (auto& p : polygons)
			p.drawc(shader); 
	}
	void deleteBuffers() {
		for (int i = 0; i < polygons.size(); i++)
		{
			polygons.at(i).deleteBuffers();
		}
	}
	void translate(const glm::vec3& t) {
		model = glm::translate(model, t);
	}
	void scale(float s) {
		model = glm::translate(model, center);
		model = glm::scale(model, glm::vec3(s));
		model = glm::translate(model, -center);
	}
	void scale(const glm::vec3& s) {
		model = glm::translate(model, center);
		model = glm::scale(model, s);
		model = glm::translate(model, -center);
	}
	void rotate(float angleDeg, const glm::vec3& axis) {
		float angleRad = glm::radians(angleDeg);

		model = glm::translate(model, center);
		model = glm::rotate(model, angleRad, axis);
		model = glm::translate(model, -center);
	}
};