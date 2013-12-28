#include "mouse.h"
#include "../video/window.h"
#include "../video/view.h"

#define NUM_BUTTONS 8

namespace engine
{
namespace input
{
namespace mouse
{

static bool justPressedButtons[NUM_BUTTONS];
static bool justReleasedButtons[NUM_BUTTONS];

static bool mouseMoved;
static int mouseX;
static int mouseY;

bool isPressed(int button)
{
	Uint8 buttonState = SDL_GetMouseState(NULL, NULL);
	return buttonState & SDL_BUTTON(button);
}

bool isJustPressed(int button)
{
	if (button < NUM_BUTTONS)
		return justPressedButtons[button];

	return false;
}

bool isJustReleased(int button)
{
	if (button < NUM_BUTTONS)
		return justReleasedButtons[button];

	return false;
}

bool moved()
{
	return mouseMoved;
}

int getX()
{
	return mouseX;
}

int getY()
{
	return mouseY;
}

float getViewX()
{
	const video::View& view = video::window::getView();
	return view.getRelativeX(mouseX);
}

float getViewY()
{
	const video::View& view = video::window::getView();
	return view.getRelativeY(mouseY);
}

geometry::Vector2d getViewPosition()
{
	const video::View& view = video::window::getView();
	return view.getRelativePosition(mouseX, mouseY);
}

/* private */

void clearEvents()
{
	mouseMoved = false;
	memset(justPressedButtons, 0, NUM_BUTTONS * sizeof(bool));
	memset(justReleasedButtons, 0, NUM_BUTTONS * sizeof(bool));
}

void addEvent(const SDL_Event& e)
{
	switch (e.type)
	{
		case SDL_MOUSEBUTTONDOWN:
		mouseX = e.button.x;
		mouseY = video::window::getHeight() - e.button.y;

		if (e.button.button < NUM_BUTTONS)
			justPressedButtons[e.button.button] = true;

		break;

		case SDL_MOUSEBUTTONUP:
		mouseX = e.button.x;
		mouseY = video::window::getHeight() - e.button.y;

		if (e.button.button < NUM_BUTTONS)
			justReleasedButtons[e.button.button] = true;

		break;

		case SDL_MOUSEMOTION:
		mouseX = e.button.x;
		mouseY = video::window::getHeight() - e.button.y;
		mouseMoved = true;
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

} // mouse
} // input
} // engine


