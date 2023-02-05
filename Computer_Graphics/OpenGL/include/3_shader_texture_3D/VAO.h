#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include <glad.h>
#include "3_shader_texture_3D/VBO.h"

class VAO{
	public:
		GLuint ID;
		VAO();

		void LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offest);
		void Bind();
		void Unbind();
		void Delete();
};

#endif