#include "checkError.h"
#include <glad/glad.h>
#include <string>
#include <iostream>
#include <assert.h>

void checkError() {
	std::string error = "";
	GLenum errorCode = glGetError();
	if (errorCode != GL_NO_ERROR)
	{
		switch (errorCode)
		{
		case GL_INVALID_ENUM: 
			error = "INVALID_ENUM"; 
			break;
		case GL_INVALID_VALUE: 
			error = "INVALID_VALUE"; 
			break;
		case GL_INVALID_OPERATION: 
			error = "INVALID_OPERATION"; 
			break;
		case GL_OUT_OF_MEMORY : 
			error = "OUT OF MEMORY"; 
			break;
		default:
			error = "UNKNOWN";
			break;
		}
		std::cout << error << std::endl;
		assert(false); // assert会根据传入的bool决定是否继续运行
	}
}