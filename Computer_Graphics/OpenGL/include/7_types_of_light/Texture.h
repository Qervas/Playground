#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include <glad.h>
#include <stb/stb_image.h>

#include "7_types_of_light/shaderClass.h"

class Texture{
	public:
		GLuint ID;
		GLenum type;
		GLuint unit;
		Texture(const char* image, GLenum texType, GLuint slot, GLenum format, GLenum pixelType);

		void texUnit(Shader& shader, const char* uniform, GLuint unit);
		void Bind();
		void Unbind();
		void Delete();

};

#endif