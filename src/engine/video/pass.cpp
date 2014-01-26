#include <GL/glew.h>
#include "pass.h"

namespace engine
{
namespace video
{

Pass::Pass() : Program()
{
	
}

Pass::~Pass()
{
	glDeleteFramebuffers(1, &m_fbo);
}

void Pass::init(const geometry::Vector2& size)
{
	m_size = size;
	glGenFramebuffers(1, &m_fbo);
}

void Pass::use()
{
	Program::use();
	
	
}

RenderTexture Pass::newDepthTexture(std::string name)
{
	m_outputDepthTexture = newOutputTexture(name, GL_DEPTH_COMPONENT24, GL_DEPTH_COMPONENT, GL_DEPTH_ATTACHMENT);
	return m_outputDepthTexture;
}

RenderTexture Pass::newColorTexture(std::string name)
{
	RenderTexture outputTexture = newOutputTexture(name, GL_RGBA, GL_RGBA, GL_COLOR_ATTACHMENT0 + m_outputTextures.size());
	m_outputTextures.push_back(outputTexture);
	return outputTexture;
}

RenderTexture Pass::newFloatTexture(std::string name)
{
	RenderTexture outputTexture = newOutputTexture(name, GL_RED, GL_RED, GL_COLOR_ATTACHMENT0 + m_outputTextures.size());
	m_outputTextures.push_back(outputTexture);
	return outputTexture;
}

RenderTexture Pass::newOutputTexture(std::string name, int internalFormat, int format, int attachment)
{
	unsigned int outputTextureId;
	glGenTextures(1, &outputTextureId);
	
	glBindTexture(GL_TEXTURE_2D, outputTextureId);
	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_size.getX(), m_size.getY(), 0, format, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
	glBindTexture(GL_TEXTURE_2D, outputTextureId);
	glFramebufferTexture2D(GL_FRAMEBUFFER, attachment, GL_TEXTURE_2D, outputTextureId, 0);
	
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	
	glUseProgram(m_programId);
	unsigned int fragDataLocation = glGetFragDataLocation(m_programId, name.c_str());
	glUseProgram(0);
	
	RenderTexture outputTexture;
	outputTexture.init(name, fragDataLocation, outputTextureId, m_size);
	return outputTexture;
}

} // video
} // engine


