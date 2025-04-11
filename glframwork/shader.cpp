#include "shader.h"
#include "../wrapper/checkError.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
	// ------  ��һ���� ���ļ���ȡshader --------

	// shader�ַ������ڱ���shader����
	std::string vertexCode, fragmentCode;

	// shader�ļ���
	std::ifstream vertexFS, fragmentFS;

	vertexFS.exceptions(std::fstream::failbit | std::fstream::badbit);
	fragmentFS.exceptions(std::fstream::failbit | std::fstream::badbit);

	// ��ȡ�ļ���, ��ת��ΪC����ַ���
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

	// ------  �ڶ����� ���� ���� program ���vs, fs�����ӹ��� --------

	// ����vs��fs����
	GLuint vertex = 0, fragment = 0;
	vertex = glCreateShader(GL_VERTEX_SHADER);
	fragment = glCreateShader(GL_FRAGMENT_SHADER);

	// Ϊshader��������shader����
	const char* vertexShader = vertexCode.c_str();
	const char* fragmentShader = fragmentCode.c_str();
	glShaderSource(vertex, 1, &vertexShader, NULL);
	glShaderSource(fragment, 1, &fragmentShader, NULL);

	// ����vertex shader����������
	glCompileShader(vertex);
	checkShaderError(COMPILE, vertex);

	// ����fragment shader����������
	glCompileShader(fragment);
	checkShaderError(COMPILE, fragment);

	//GLuint program; ʹ��ȫ��program
	mProgram = glCreateProgram();

	// ��vertex fragmentװ��program
	glAttachShader(mProgram, vertex);
	glAttachShader(mProgram, fragment);

	// ����program
	glLinkProgram(mProgram);

	// ���link����
	checkShaderError(LINK, 0);

	// ��ʱvertex, fragment�Ѿ�û���ô���, ����ɾ��
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
	// �ڶ���������˼��vector3�������м���vec3, vector3����Ϊ3, ����Ϊ1, ������Ϊ6, ����Ϊ2
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
	// glUniformMatrix4fv ������shader����4x4���͵�, Ԫ��������float, ��������ʽ�������ݵĺ���
	// �ڶ���������ʾ: ����������������м���4x4����
	// ������������ʾ: �Ƿ���Ҫת��, openglʹ�õ�����ʽ�洢������, glm����Ҳ��, ���Դ˴�����Ҫת��,
	// ���ʹ����������ѧ��, ������ʽ�洢������, �˴�����Ҫת�õ�
	// ���һ������ʹ��glm���õĺ�����ȡ�����ָ��
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
