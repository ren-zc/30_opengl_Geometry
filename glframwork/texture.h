#pragma once
#include "core.h"

class Texture
{
public:
	Texture(const char* path, unsigned int unit);
	~Texture();  // 删除纹理

	void bind(unsigned int unit) const; //切换纹理单元

	int getWidth();
	int getHeight();

private:
	GLuint mTexture{ 0 };
	int mWidth{ 0 };
	int mHeight{ 0 };
	//unsigned int textureUnit{ 0 };
};
