#include "window.h"
#include "../video/window.h"

namespace engine
{
namespace input
{
namespace window
{

static bool windowClosed;
static bool windowResized;

bool closed()
{
	return windowClosed;
}

bool resized()
{
	return windowResized;
}

/* private */

void clearEvents()
{
	windowClosed = false;
	windowResized = false;
}

void addEvent(const SDL_Event& e)
{
	switch (e.type)
	{
		case SDL_QUIT:
		windowClosed = true;
		break;

		case SDL_VIDEORESIZE:
		windowResized = true;
		video::window::setWidth(e.resize.w);
		video::window::setHeight(e.resize.h);
		break;
	}
}

void open()
{
	clearEvents();
}

void close()
{

}

} // window
} // input
} // engine


