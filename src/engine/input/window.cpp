#include "window.h"
#include "../video/video.h"

namespace engine
{
namespace input
{

Window::Window(video::Video* video)
{
	this->video = video;
	clearEvents();
}

Window::~Window()
{
	
}

void Window::clearEvents()
{
	m_closed = false;
	m_resized = false;
}

void Window::addEvent(const SDL_Event& e)
{
	switch (e.type)
	{
		case SDL_QUIT:
		m_closed = true;
		break;

		case SDL_VIDEORESIZE:
		m_resized = true;
		video->window->setSize(geometry::Vector2d(e.resize.w, e.resize.h));
		break;
	}
}

} // input
} // engine


