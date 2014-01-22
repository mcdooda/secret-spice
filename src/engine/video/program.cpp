#include <GL/glew.h>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>
#include "program.h"

namespace engine
{
namespace video
{

Program::Program() :
	m_programId(0),
	m_valid(false)
{
	
}

Program::~Program()
{
	if (glIsProgram(m_programId))
		glDeleteProgram(m_programId);
}

void Program::load(std::string fragmentShader, std::string vertexShader)
{
	m_valid = true;
	
	int fragmentShaderId = compileShader(fragmentShader, GL_FRAGMENT_SHADER);
	checkShader(fragmentShader, fragmentShaderId);
	
	int vertexShaderId = compileShader(vertexShader, GL_VERTEX_SHADER);
	checkShader(vertexShader, vertexShaderId);
	
	m_programId = compileProgram(fragmentShaderId, vertexShaderId);
	checkProgram(m_programId);
}

void Program::use()
{
	if (!m_valid)
	{
		std::cerr << "Fatal error: using invalid shader program" << std::endl;
		exit(1);
	}
		
	glUseProgram(m_programId);
}

int Program::getAttribLocation(std::string attribName)
{
	return glGetAttribLocation(m_programId, attribName.c_str());
}

Uniform Program::getUniform(std::string uniformName)
{
	int uniformLocation = glGetUniformLocation(m_programId, uniformName.c_str());
	return Uniform(uniformLocation);
}

int Program::compileProgram(int fragmentShaderId, int vertexShaderId)
{
	int programId = glCreateProgram();
	glAttachShader(programId, vertexShaderId);
	glAttachShader(programId, fragmentShaderId);
	glLinkProgram(programId);
	return programId;
}

int Program::compileShader(std::string shader, int shaderType)
{
	const char* shaderCode = readCode(shader);
	int shaderId = glCreateShader(shaderType);
	glShaderSource(shaderId, 1, &shaderCode, NULL);
	delete shaderCode;
	glCompileShader(shaderId);
	return shaderId;
}

void Program::checkProgram(int programId)
{
	GLint result = GL_FALSE;
	int infoLogLength;

	glGetProgramiv(programId, GL_LINK_STATUS, &result);
	glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &infoLogLength);

	if (infoLogLength > 0) {
		std::vector<char> message(infoLogLength + 1);
		glGetProgramInfoLog(programId, infoLogLength, NULL, &message[0]);
		std::cerr << "Warning: " << (const char*) &message[0] << std::endl;
		m_valid = false;
	}
}

void Program::checkShader(std::string shaderFile, int shaderId)
{
	GLint result = GL_FALSE;
	int infoLogLength;

	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &result);
	glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &infoLogLength);

	if (infoLogLength > 0) {
		std::vector<char> message(infoLogLength + 1);
		glGetShaderInfoLog(shaderId, infoLogLength, NULL, &message[0]);
		std::cerr << "Warning while loading shader file '" << shaderFile << "' :" << std::endl << (const char*) &message[0] << std::endl;
		m_valid = false;
	}
}

const char* Program::readCode(std::string shader)
{
	std::ifstream file(shader.c_str(), std::ifstream::binary);
	if (!file.is_open())
	{
		std::cerr << "Warning: unable to open shader file '" << shader << "'" << std::endl;
		m_valid = false;
		return NULL;
	}
	
	file.seekg(0, file.end);
	int length = file.tellg();
	file.seekg(0, file.beg);
	
	char* code = new char[length + 1];
	file.read(code, length);
	code[length] = '\0';
		
	file.close();
	
	return code;
}

} // video
} // engine


