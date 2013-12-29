#include <GL/gl.h>
#include <GL/glu.h>
#include "window.h"

namespace engine
{
namespace video
{

Window::Window() :
	m_view(geometry::Vector2d(0, 0), 1)
{
	 
}

Window::~Window()
{
	
}

void Window::open(geometry::Vector2d size, std::string name, bool fullScreen)
{
	int flags = SDL_OPENGL | SDL_GL_DOUBLEBUFFER | SDL_RESIZABLE;

	if (fullScreen)
		flags |= SDL_FULLSCREEN;

	m_screen = SDL_SetVideoMode(size.getX(), size.getY(), 32, flags);
	SDL_WM_SetCaption(name.c_str(), name.c_str());
	SDL_WarpMouse(size.getX() / 2, size.getY() / 2);

	m_size = size;
	m_oldSize = size;

	m_fullScreen = fullScreen;

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	resize();
}

void Window::toggleFullScreen()
{
	SDL_WM_ToggleFullScreen(m_screen);
	/*
	fullScreen = !fullScreen;

	int flags = SDL_OPENGL | SDL_GL_DOUBLEBUFFER | SDL_RESIZABLE;

	int width;
	int height;

	if (fullScreen)
	{
		flags |= SDL_FULLSCREEN;
		oldWindowWidth = windowWidth;
		oldWindowHeight = windowHeight;
		width = getDesktopWidth();
		height = getDesktopHeight();
	}
	else
	{
		width = oldWindowWidth;
		height = oldWindowHeight;
	}

	SDL_FreeSurface(screen);
	screen = SDL_SetVideoMode(width, height, 32, flags);

	resize();
	*/
}

geometry::Vector2d Window::getDesktopSize()
{
	const SDL_VideoInfo* videoInfo = SDL_GetVideoInfo();
	return geometry::Vector2d(videoInfo->current_w, videoInfo->current_h);
}

void Window::setView(View view)
{
	m_view = view;
	m_view.updateBorders(m_size);
	glLoadIdentity();
	gluOrtho2D(m_view.getLeft(), m_view.getRight(), m_view.getBottom(), m_view.getTop());
}

void Window::setInterfaceView()
{
	m_view = View(geometry::Vector2d(m_size.getX() / 2, m_size.getY() / 2), 1);
	glLoadIdentity();
	gluOrtho2D(0, m_size.getX(), 0, m_size.getY());
}

void Window::resize()
{
	glViewport(0, 0, m_size.getX(), m_size.getY());
	setView(m_view);
}

} // video
} // engine


