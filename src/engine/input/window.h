#ifndef ENGINE_INPUT_WINDOW_H
#define ENGINE_INPUT_WINDOW_H

#include <SDL/SDL.h>
#include "../video/video.h"

namespace engine
{
namespace input
{

class Window
{
	public:
		Window(video::Video* video);
		~Window();
		
		inline bool closed() const { return m_closed; }
		inline bool resized() const { return m_resized; }

		void clearEvents();
		void addEvent(const SDL_Event& e);
		
	private:
		bool m_closed;
		bool m_resized;
		
		video::Video* video;
};

} // input
} // engine

#endif // ENGINE_INPUT_WINDOW_H


