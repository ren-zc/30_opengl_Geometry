#include "shader.h"
#include "../wrapper/checkError.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
	// ------  第一部分 从文件读取shader --------

	// shader字符串用于保存shader代码
	std::string vertexCode, fragmentCode;

	// shader文件流
	std::ifstream vertexFS, fragmentFS;

	vertexFS.exceptions(std::fstream::failbit | std::fstream::badbit);
	fragmentFS.exceptions(std::fstream::failbit | std::fstream::badbit);

	// 读取文件流, 并转换为C风格字符串
	try
	{
		std::stringstream vertexSS, fragmentSS;
		vertexFS.open(vertexFile);
		fragmentFS.open(fragmentFile);
		vertexSS << vertexFS.rdbuf();
		fragmentSS << fragmentFS.rdbuf();

		vertexFS.close();
		fragmentFS.close();

		vertexCode = vertexSS.str();
		fragmentCode = fragmentSS.str();
	}
	catch (const std::fstream::failure& e)
	{
		std::cout << "Error: shader file error, " << e.what() << std::endl;
	}

	// ------  第二部分 创建 链接 program 完成vs, fs的链接工作 --------

	// 创建vs和fs程序
	GLuint vertex = 0, fragment = 0;
	vertex = glCreateShader(GL_VERTEX_SHADER);
	fragment = glCreateShader(GL_FRAGMENT_SHADER);

	// 为shader程序输入shader代码
	const char* vertexShader = vertexCode.c_str();
	const char* fragmentShader = fragmentCode.c_str();
	glShaderSource(vertex, 1, &vertexShader, NULL);
	glShaderSource(fragment, 1, &fragmentShader, NULL);

	// 编译vertex shader并检查编译结果
	glCompileShader(vertex);
	checkShaderError(COMPILE, vertex);

	// 编译fragment shader并检查编译结果
	glCompileShader(fragment);
	checkShaderError(COMPILE, fragment);

	//GLuint program; 使用全局program
	mProgram = glCreateProgram();

	// 把vertex fragment装入program
	glAttachShader(mProgram, vertex);
	glAttachShader(mProgram, fragment);

	// 链接program
	glLinkProgram(mProgram);

	// 检查link错误
	checkShaderError(LINK, 0);

	// 此时vertex, fragment已经没有用处了, 可以删除
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

Shader::~Shader()
{
}

void Shader::begin()
{
	GL_CALL(glUseProgram(mProgram));
}

void Shader::end()
{
	GL_CALL(glUseProgram(0));
}

void Shader::setUniformFloat(const char* name, const float value)
{
	GLuint location = glGetUniformLocation(mProgram, name);
	GL_CALL(glUniform1f(location, value));
}

void Shader::setUniform3Float(const char* name, const float v0, const float v1, const float v2)
{
	GLuint location = glGetUniformLocation(mProgram, name);
	GL_CALL(glUniform3f(location, v0, v1, v2));
}

void Shader::setUniform3Float(const char* name, const float* vector3)
{
	GLuint location = glGetUniformLocation(mProgram, name);
	// 第二个参数意思是vector3数组中有几个vec3, vector3长度为3, 则其为1, 若长度为6, 则其为2
	glUniform3fv(location, 1, vector3); 
}

void Shader::setUniform1i(const char* name, int i)
{
	GLuint location = glGetUniformLocation(mProgram, name);
	glUniform1i(location, i);
}

void Shader::setMetrix4(const char* name, glm::mat4 value)
{
	GLuint location = glGetUniformLocation(mProgram, name);
	// glUniformMatrix4fv 用于向shader传输4x4类型的, 元素类型是float, 以数组形式传递数据的函数
	// 第二个参数表示: 传输的数组数据中有几个4x4矩阵
	// 第三个参数表示: 是否需要转置, opengl使用的是列式存储的数组, glm碰巧也是, 所以此处不需要转置,
	// 如果使用了其他数学库, 且是行式存储的数组, 此处是需要转置的
	// 最后一个参数使用glm内置的函数提取矩阵的指针
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::checkShaderError(CHECK_TYPE checkType, GLuint shaderType)
{
	int success;
	char infoLog[1024];

	if (checkType == COMPILE)
	{
		glGetShaderiv(shaderType, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shaderType, 1024, NULL, infoLog);
			std::cout << "Error: vertex shader compile error: \n" << infoLog << std::endl;
		}

	}
	else if (checkType == LINK)
	{
		glGetProgramiv(mProgram, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(mProgram, 1024, NULL, infoLog);
			std::cout << "Error: link program\n" << infoLog << std::endl;
		}
	}
	else
	{
		std::cout << "Error: unknown check type.\n" << std::endl;
	}
}
