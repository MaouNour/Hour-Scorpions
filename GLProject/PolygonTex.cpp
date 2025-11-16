#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <learnopengl/shader_m.h>
#include <stb_image.h>
#include <iostream>
#include "Polygon.cpp"


class PolygonTex: public Polygon{
    struct Vertex
    {
        glm::vec3 position;
        glm::vec2 textureCoords;
    };
public:
    // Constructor: vertices + texture coordinates + texture path
	PolygonTex(std::vector<glm::vec3> v, const char* tex, std::vector<glm::vec2> TexCoords) :Polygon(){
		this->vertices.clear();
		this->vertices.reserve(v.size());

		for (int i = 0; i < v.size(); i++)
		{
			this->vertices.push_back(Vertex{ v[i], TexCoords[i] });
		}
		this->image = tex;
		this->TexCoords = TexCoords;
		this->vertices = vertices;
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, textureCoords));
		glEnableVertexAttribArray(1);

		glGenTextures(1, &texture);
		glBindVertexArray(0);
		initTexture(tex);
	}
	void initTexture(const char* tex) {
		glBindVertexArray(VAO);
		glBindTexture(GL_TEXTURE_2D, texture);
		int width, height, nrChannels;
		//unsigned char* data = stbi_load(tex, &width, &height, &nrChannels, STBI_rgb_alpha);
		unsigned char* data = stbi_load(tex, &width, &height, &nrChannels, 0);

		if (!data) {
			std::cout << "Failed to load texture: " << tex << std::endl;
		}

		GLenum format;
		if (nrChannels == 1)
			format = GL_RED;
		else if (nrChannels == 3)
			format = GL_RGB;
		else if (nrChannels == 4)
			format = GL_RGBA;

		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		stbi_image_free(data);
	}
    void transformation(const glm::mat4& t) {
        model = t;
    }

    void draw(Shader& shader) override{
		shader.use();
		shader.setMat4("model", model);
		glBindTexture(GL_TEXTURE_2D, texture);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLE_FAN, 0, vertices.size());
    }
	void drawc(Shader& shader) override {
		glBindTexture(GL_TEXTURE_2D, texture);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLE_FAN, 0, vertices.size());
	}

private:
	unsigned int texture;
	unsigned int VBO, VAO;
	const char* image;
	glm::vec3 head;
	std::vector<Vertex> vertices;
	glm::vec3 color;
	glm::mat4 model = glm::mat4(1.0);
    std::vector<glm::vec2> TexCoords;
};
