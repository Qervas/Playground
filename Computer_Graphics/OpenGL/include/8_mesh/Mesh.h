#ifndef MESH_H
#define MESH_H

#include <string>
#include <vector>

#include "8_mesh/VAO.h"
#include "8_mesh/Camera.h"
#include "8_mesh/EBO.h"
#include "8_mesh/Texture.h"

class Mesh{
public:
	std::vector <Vertex> vertices;
	std::vector <GLuint> indices;
	std::vector <Texture> textures;

	VAO VAO;

	Mesh(std::vector <Vertex>& vertices, std::vector <GLuint>& indices, std::vector<Texture>& textures);

	void Draw(Shader& shader, Camera& camera, 
				glm::mat4 matrix = glm::mat4(1.0f), 
				glm::vec3 translation = glm::vec3(0.0f, 0.0f, 0.0f),
				glm::quat rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f),
				glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f)
				);

};


#endif