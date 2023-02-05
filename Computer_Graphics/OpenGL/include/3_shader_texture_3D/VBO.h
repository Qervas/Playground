#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include <glad.h>

class VBO{
	public:
	GLuint ID;
	VBO(GLfloat* vertices, GLsizeiptr size);

	void Bind();
	void Unbind();
	void Delete();
};

#endif