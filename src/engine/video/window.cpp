#include <iostream>
#include <GL/glew.h>
#include "window.h"

namespace engine
{
namespace video
{

Window::Window()
{
	 
}

Window::~Window()
{
	
}

void Window::open(geometry::Vector2 size, std::string name, bool fullScreen, bool vsync)
{
	int windowFlags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;
	
	if (fullScreen)
		windowFlags |= SDL_WINDOW_FULLSCREEN;
	
	m_window = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, size.getX(), size.getY(), windowFlags);
	
	int rendererFlags = 0;
	
	if (vsync)
		rendererFlags |= SDL_RENDERER_PRESENTVSYNC;
	
	m_renderer = SDL_CreateRenderer(m_window, -1, rendererFlags);
	
	int err = glewInit();
	if (err != GLEW_OK)
	{
		std::cerr << "Fatal: glewInit failed: " << glewGetErrorString(err) << std::endl;
		exit(1);
	}
	
	SDL_WarpMouseInWindow(m_window, size.getX() / 2, size.getY() / 2);

	m_fullScreen = fullScreen;
	m_vsync = vsync;

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	initSize(size);
}

void Window::toggleFullScreen()
{
	m_fullScreen = !m_fullScreen;
	geometry::Vector2 desktopSize = getDesktopSize();
	if (m_fullScreen)
	{
		SDL_SetWindowSize(m_window, desktopSize.getX(), desktopSize.getY());
		SDL_SetWindowFullscreen(m_window, SDL_WINDOW_FULLSCREEN);
	}
	else
	{
		SDL_SetWindowSize(m_window, desktopSize.getX() / 2, desktopSize.getY() / 2);
		SDL_SetWindowFullscreen(m_window, 0);
	}
}

void Window::resized(const geometry::Vector2& size)
{
	m_size = size;
	glViewport(0, 0, m_size.getX(), m_size.getY());
	setView(m_view);
}

geometry::Vector2 Window::getDesktopSize()
{
	SDL_DisplayMode desktopDisplayMode;
	SDL_GetDesktopDisplayMode(0, &desktopDisplayMode);
	return geometry::Vector2(desktopDisplayMode.w, desktopDisplayMode.h);
}

void Window::setView(View view)
{
	m_view = view;
	m_view.updateProjectionMatrix(m_size);
}

void Window::setInterfaceView()
{
	setView(View());
}

void Window::beginFrame()
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void Window::endFrame()
{
	glFlush();
	SDL_RenderPresent(m_renderer);
}

void Window::initSize(const geometry::Vector2& size)
{
	resized(size);
}

} // video
} // engine


