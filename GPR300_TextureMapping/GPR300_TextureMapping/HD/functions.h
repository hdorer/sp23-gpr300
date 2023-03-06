#pragma once

#define STB_IMAGE_IMPLEMENTATION

#include "GL/glew.h"
#include "stb_image.h"

namespace hd {
	GLuint createTexture(const char* filePath) {
		GLuint texture;
		glActiveTexture(GL_TEXTURE0);
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);

		stbi_set_flip_vertically_on_load(true);
		int width, height, numComponents;
		unsigned char* textureData = stbi_load(filePath, &width, &height, &numComponents, 0);
		if(!textureData) {
			printf("Texture data did not work");
		}

		GLuint format;

		switch(numComponents) {
			case 1:
				format = GL_RED;
			case 2:
				format = GL_RG;
			case 3:
				format = GL_RGB;
			case 4:
				format = GL_RGBA;
			default:
				format = NULL;
		}

		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, textureData);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		// stbi_image_free(textureData);

		return texture;
	}
}