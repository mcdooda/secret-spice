#include <GL/glew.h>
#include "rendertexture.h"

namespace engine
{
namespace video
{

RenderTexture::RenderTexture() :
	m_textureId(0)
{
	
}

RenderTexture::~RenderTexture()
{
	if (glIsTexture(m_textureId))
		glDeleteTextures(1, &m_textureId);
}

void RenderTexture::init(std::string name, unsigned int fragDataLocation, unsigned int textureId, const geometry::Vector2& size)
{
	m_name = name;
	m_fragDataLocation = fragDataLocation;
	m_textureId = textureId;
	m_size = size;
}

} // video
} // engine


