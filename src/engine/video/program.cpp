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
	
	loadCommonAttribsUniforms();
}

void Program::use()
{
	if (!m_valid)
	{
		std::cerr << "Fatal error: using invalid shader program" << std::endl;
		exit(1);
	}
		
	glUseProgram(m_programId);
	
	if (m_inputTextures.size() > 0)
	{
		std::vector<Uniform>::iterator it1 = m_inputTexturesUniforms.begin();
		std::vector<RenderTexture>::iterator it2 = m_inputTextures.begin();
		const std::vector<Uniform>::iterator it1_end = m_inputTexturesUniforms.end();
		for (int i = 0; it1 != it1_end; i++, it1++, it2++)
			it1->setTexture(*it2, i);
	}
}

Attrib Program::getAttrib(std::string attribName)
{
	return glGetAttribLocation(m_programId, attribName.c_str());
}

Uniform Program::getUniform(std::string uniformName)
{
	int uniformLocation = glGetUniformLocation(m_programId, uniformName.c_str());
	return Uniform(uniformLocation);
}

void Program::addInputTexture(RenderTexture texture)
{
	m_inputTextures.push_back(texture);
	
	Uniform inputTextureUniform = getUniform(texture.getName());
	m_inputTexturesUniforms.push_back(inputTextureUniform);
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

	if (!result) {
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

	if (!result) {
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

void Program::loadCommonAttribsUniforms()
{
	// attributes
	m_positionAttrib = getAttrib("position");
	
	// uniforms
	m_vpMatrixUniform = getUniform("vpMatrix");
}

} // video
} // engine


