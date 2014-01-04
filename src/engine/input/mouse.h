#ifndef ENGINE_INPUT_MOUSE_H
#define ENGINE_INPUT_MOUSE_H

#include <SDL/SDL.h>
#include "../geometry/vector2d.h"
#include "../video/video.h"
#include "../video/view.h"

#define M(m) SDL_BUTTON_##m
#define NUM_BUTTONS 8

namespace engine
{
namespace input
{

class Mouse
{
	public:
		Mouse(video::Video* video);
		~Mouse();
		
		bool isPressed(int button);
		bool isJustPressed(int button);
		bool isJustReleased(int button);

		inline bool justMoved() const { return m_moved; }

		inline geometry::Vector2d getPosition() const { return m_position; }

		void clearEvents();
		void addEvent(const SDL_Event& e);
		
	private:
		bool m_justPressedButtons[NUM_BUTTONS];
		bool m_justReleasedButtons[NUM_BUTTONS];

		bool m_moved;
		geometry::Vector2d m_position;
		
		video::Video* video;

};

} // input
} // engine

#endif // ENGINE_INPUT_MOUSE_H


