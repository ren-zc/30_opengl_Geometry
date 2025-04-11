#pragma once

#include "core.h"

class Shader
{
public:
	Shader(const char* vertexFile, const char* fragmentFile);
	~Shader();

	void begin();  // 开始使用program
	void end();  // 结束使用program

	void setUniformFloat(const char* name, const float value);
	void setUniform3Float(const char* name, const float v0, const float v1, const float v2);
	void setUniform3Float(const char* name, const float* vector3);
	void setUniform1i(const char* name, int i);
	void setMetrix4(const char* name, glm::mat4 value);

private:
	enum CHECK_TYPE
	{
		COMPILE,
		LINK
	};
	GLuint mProgram{ 0 };
	void checkShaderError(CHECK_TYPE checkType, GLuint shaderType);
};
