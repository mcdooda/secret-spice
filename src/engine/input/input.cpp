#include "input.h"

#include "keyboard.h"
#include "mouse.h"
#include "window.h"

namespace engine
{
namespace input
{

Input::Input(video::Video* video)
{
	keyboard = new Keyboard;
	mouse = new Mouse(video);
	window = new Window(video);
}

Input::~Input()
{
	delete keyboard;
	delete mouse;
	delete window;
}

void Input::poll()
{
	SDL_Event e;
	keyboard->clearEvents();
	mouse->clearEvents();
	window->clearEvents();
	while (SDL_PollEvent(&e))
	{
		keyboard->addEvent(e);
		mouse->addEvent(e);
		window->addEvent(e);
	}
}

void Input::clearAll()
{
	SDL_Event e;
	while (SDL_PollEvent(&e));
	keyboard->clearEvents();
	mouse->clearEvents();
	window->clearEvents();
}

} // input
} // engine


