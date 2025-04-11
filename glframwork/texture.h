#pragma once
#include "core.h"

class Texture
{
public:
	Texture(const char* path, unsigned int unit);
	~Texture();  // ɾ������

	void bind(unsigned int unit) const; //�л�����Ԫ

	int getWidth();
	int getHeight();

private:
	GLuint mTexture{ 0 };
	int mWidth{ 0 };
	int mHeight{ 0 };
	//unsigned int textureUnit{ 0 };
};
