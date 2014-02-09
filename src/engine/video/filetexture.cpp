#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <GL/glew.h>
#include "filetexture.h"

namespace engine
{
namespace video
{

FileTexture::FileTexture(std::string filename) :
	m_path(filename)
{
	m_surface = IMG_Load(filename.c_str());
	
	if (m_surface != NULL)
		load();
		
	else
		std::cerr << "Warning: error in IMG_Load(" << filename.c_str() << ") : " << IMG_GetError() << std::endl;
}

Color FileTexture::getPixel(int x, int y)
{
	Uint32 pixel = *((Uint32*) m_surface->pixels + (m_surface->h - y) * m_surface->w + x);
	Uint8 r, g, b, a;
	SDL_GetRGBA(pixel, m_surface->format, &r, &g, &b, &a);
	return Color(r, g, b, a);
}

void FileTexture::load()
{
	m_size = geometry::Vector2(m_surface->w, m_surface->h);
	
	glGenTextures(1, &m_textureId);
	glBindTexture(GL_TEXTURE_2D, m_textureId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_surface->w, m_surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_surface->pixels);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void FileTexture::free()
{
	glDeleteTextures(1, &m_textureId);
	SDL_FreeSurface(m_surface);
}

} // video
} // engine


