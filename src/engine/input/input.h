#ifndef ENGINE_INPUT_INPUT_H
#define ENGINE_INPUT_INPUT_H

#include "keyboard.h"
#include "mouse.h"
#include "window.h"
#include "../video/video.h"

namespace engine
{
namespace input
{

class Input
{
	public:
		Input(video::Video* video);
		~Input();
		
		void poll();
		void clearAll();
		
	public:
		Keyboard* keyboard;
		Mouse* mouse;
		Window* window;
};

} // input
} // engine

#endif // ENGINE_INPUT_INPUT_H


