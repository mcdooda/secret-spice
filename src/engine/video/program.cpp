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
	
	loadAttributes();
	loadUniforms();
}

void Program::use()
{
	if (!m_valid)
	{
		std::cerr << "Fatal error: using invalid shader program" << std::endl;
		exit(1);
	}
	
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(m_programId);
}

Attribute Program::getAttribute(std::string attributeName)
{
	std::map<std::string, Attribute>::iterator it = m_attributes.find(attributeName);
	
	if (it != m_attributes.end())
		return it->second;
		
	else
		return -1;
}

Uniform Program::getUniform(std::string uniformName)
{
	std::map<std::string, Uniform>::iterator it = m_uniforms.find(uniformName);
	
	if (it != m_uniforms.end())
		return it->second;
		
	else
		return Uniform(-1);
}

int Program::compileProgram(unsigned int fragmentShaderId, unsigned int vertexShaderId)
{
	int programId = glCreateProgram();
	glAttachShader(programId, vertexShaderId);
	glAttachShader(programId, fragmentShaderId);
	glLinkProgram(programId);
	return programId;
}

int Program::compileShader(std::string shader, unsigned int shaderType)
{
	const char* shaderCode = readCode(shader);
	int shaderId = glCreateShader(shaderType);
	glShaderSource(shaderId, 1, &shaderCode, NULL);
	delete shaderCode;
	glCompileShader(shaderId);
	return shaderId;
}

void Program::checkProgram(unsigned int programId)
{
	GLint result = GL_FALSE;
	glGetProgramiv(programId, GL_LINK_STATUS, &result);

	if (!result)
	{
		int infoLogLength;
		glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &infoLogLength);
		char message[infoLogLength];
		glGetProgramInfoLog(programId, infoLogLength, NULL, message);
		std::cerr << "Warning: " << message << std::endl;
		m_valid = false;
	}
}

void Program::checkShader(std::string shaderFile, unsigned int shaderId)
{
	GLint result = GL_FALSE;
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &result);

	if (!result)
	{
		int infoLogLength;
		glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &infoLogLength);
		char message[infoLogLength];
		glGetShaderInfoLog(shaderId, infoLogLength, NULL, message);
		std::cerr << "Warning while loading shader file '" << shaderFile << "' :" << std::endl << message << std::endl;
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

void Program::loadAttributes()
{
	int total = -1;
	glGetProgramiv(m_programId, GL_ACTIVE_ATTRIBUTES, &total); 
	for(int i = 0; i < total; i++) {
		int nameLength;
		int size;
		GLenum type = GL_ZERO;
		char name[100];
		glGetActiveAttrib(m_programId, i, sizeof(name) - 1, &nameLength, &size, &type, name);
		name[nameLength] = '\0';
		int location = glGetAttribLocation(m_programId, name);
		m_attributes[name] = location;
	}
}

void Program::loadUniforms()
{
	int total = -1;
	glGetProgramiv(m_programId, GL_ACTIVE_UNIFORMS, &total); 
	for(int i = 0; i < total; i++) {
		int nameLength;
		int size;
		GLenum type = GL_ZERO;
		char name[100];
		glGetActiveUniform(m_programId, i, sizeof(name) - 1, &nameLength, &size, &type, name);
		name[nameLength] = '\0';
		int location = glGetUniformLocation(m_programId, name);
		m_uniforms[name] = Uniform(location);
	}
}

} // video
} // engine


