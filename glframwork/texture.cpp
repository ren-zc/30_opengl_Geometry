#include "texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../application/stb_image.h"


Texture::Texture(const char* path, unsigned int unit)
{
	// 使用stb读取纹理数据
	int channels;

	// --- 反转y轴 ---
	stbi_set_flip_vertically_on_load(true);

	unsigned char* data = stbi_load(path, &mWidth, &mHeight, &channels, STBI_rgb_alpha);

	// 生成纹理
	glGenTextures(1, &mTexture);

	// --- 激活纹理单元 ---
	glActiveTexture(GL_TEXTURE0 + unit);
	// --- 绑定纹理 ---
	glBindTexture(GL_TEXTURE_2D, mTexture);  // 把纹理绑定到GL_TEXTURE_2D插槽

	// 传输纹理数据(会开辟显存)
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mWidth, mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	// 生成mipmap
	glGenerateMipmap(GL_TEXTURE_2D);  // 在GL_TEXTURE_2D这个插槽上生成mipmap

	// 释放纹理数据
	stbi_image_free(data);

	// 设置纹理过滤方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// GL_NEAREST_MIPMAP_LINEAR:
	//	- GL_NEAREST: 在单个mipmap上采用最邻近采样, 此外还有GL_LINEAR, 前半段指的是单张图片如何去采样
	//	- MIPMAP_LINEAR: 在两层mipmap直接使用线性插值, 此外还有MIPMAP_NEAREST, 后半段指的是不同mipmap之间如何去选择
	//	- 2 * 2共两种组合方式, 只有采用这4种方式, 才有mipmap效果
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);  // 改为mipmap, 如果在FS中指定使用哪个level, 需要注释此行
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	// 设置纹理的包裹方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // u
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // v

}

Texture::~Texture()
{
	if (mTexture != 0)
	{
		glDeleteTextures(1, &mTexture);
	}
}

void Texture::bind(unsigned int unit) const
{
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, mTexture);
}

int Texture::getWidth()
{
	return mWidth;
}

int Texture::getHeight()
{
	return mHeight;
}
