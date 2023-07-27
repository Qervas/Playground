#ifndef MESH_H
#define MESH_H

#include <string>
#include <vector>

#include "9_stencil_culling/VAO.h"
#include "9_stencil_culling/Camera.h"
#include "9_stencil_culling/EBO.h"
#include "9_stencil_culling/Texture.h"

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