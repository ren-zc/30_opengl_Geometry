#include "texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../application/stb_image.h"


Texture::Texture(const char* path, unsigned int unit)
{
	// ʹ��stb��ȡ��������
	int channels;

	// --- ��תy�� ---
	stbi_set_flip_vertically_on_load(true);

	unsigned char* data = stbi_load(path, &mWidth, &mHeight, &channels, STBI_rgb_alpha);

	// ��������
	glGenTextures(1, &mTexture);

	// --- ��������Ԫ ---
	glActiveTexture(GL_TEXTURE0 + unit);
	// --- ������ ---
	glBindTexture(GL_TEXTURE_2D, mTexture);  // ������󶨵�GL_TEXTURE_2D���

	// ������������(�Ὺ���Դ�)
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mWidth, mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	// ����mipmap
	glGenerateMipmap(GL_TEXTURE_2D);  // ��GL_TEXTURE_2D������������mipmap

	// �ͷ���������
	stbi_image_free(data);

	// ����������˷�ʽ
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// GL_NEAREST_MIPMAP_LINEAR:
	//	- GL_NEAREST: �ڵ���mipmap�ϲ������ڽ�����, ���⻹��GL_LINEAR, ǰ���ָ���ǵ���ͼƬ���ȥ����
	//	- MIPMAP_LINEAR: ������mipmapֱ��ʹ�����Բ�ֵ, ���⻹��MIPMAP_NEAREST, ����ָ���ǲ�ͬmipmap֮�����ȥѡ��
	//	- 2 * 2��������Ϸ�ʽ, ֻ�в�����4�ַ�ʽ, ����mipmapЧ��
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);  // ��Ϊmipmap, �����FS��ָ��ʹ���ĸ�level, ��Ҫע�ʹ���
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	// ��������İ�����ʽ
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
