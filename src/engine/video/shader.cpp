#include <GL/glew.h>
#include <fstream>
#include <iostream>
#include <vector>
#include "shader.h"

namespace engine
{
namespace video
{

Shader::Shader() :
	m_programId(0)
{
	
}

Shader::~Shader()
{
	if (glIsProgram(m_programId))
		glDeleteProgram(m_programId);
}

void Shader::load(std::string fragmentShader, std::string vertexShader)
{
	int fragmentShaderId = compileShader(fragmentShader, GL_FRAGMENT_SHADER);
	checkShader(fragmentShaderId);
	
	int vertexShaderId = compileShader(fragmentShader, GL_VERTEX_SHADER);
	checkShader(vertexShaderId);
	
	m_programId = compileProgram(fragmentShaderId, vertexShaderId);
	checkProgram(m_programId);
}

void Shader::use()
{
	glUseProgram(m_programId);
}

int Shader::getAttribLocation(std::string attribName)
{
	return glGetAttribLocation(m_programId, attribName.c_str());
}

int Shader::getUniformLocation(std::string uniformName)
{
	return glGetAttribLocation(m_programId, uniformName.c_str());
}

int Shader::compileProgram(int fragmentShaderId, int vertexShaderId)
{
  int programId = glCreateProgram();
  glAttachShader(programId, vertexShaderId);
  glAttachShader(programId, fragmentShaderId);
  glLinkProgram(programId);
  return programId;
}

int Shader::compileShader(std::string shader, int shaderType)
{
	const char* shaderCode = readCode(shader).c_str();
	int shaderId = glCreateShader(shaderType);
	glShaderSource(shaderId, 1, &shaderCode, NULL);
	glCompileShader(shaderId);
	return shaderId;
}

void Shader::checkProgram(int programId)
{
	GLint result = GL_FALSE;
	int infoLogLength;

	glGetProgramiv(programId, GL_LINK_STATUS, &result);
	glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &infoLogLength);

	if (infoLogLength > 0) {
		std::vector<char> message(infoLogLength + 1);
		glGetProgramInfoLog(programId, infoLogLength, NULL, &message[0]);
		std::cerr << "Warning: " << (const char*) &message[0] << std::endl;
	}
}

void Shader::checkShader(int shaderId)
{
	GLint result = GL_FALSE;
	int infoLogLength;

	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &result);
	glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &infoLogLength);

	if (infoLogLength > 0) {
		std::vector<char> message(infoLogLength + 1);
		glGetShaderInfoLog(shaderId, infoLogLength, NULL, &message[0]);
		std::cerr << "Warning: " << (const char*) &message[0] << std::endl;
	}
}

std::string Shader::readCode(std::string shader)
{
	std::ifstream file(shader.c_str(), std::ios::in);
	if (!file.is_open())
	{
		std::cerr << "Warning: unable to open shader file '" << shader << "'" << std::endl;
		return "";
	}
	
	std::string code;
	std::string line;
	while (getline(file, line))
		code += line + "\n";
		
	file.close();
	
	return code;
}

} // video
} // engine


