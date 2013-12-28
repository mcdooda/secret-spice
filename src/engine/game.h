#ifndef ENGINE_GAME_H
#define ENGINE_GAME_H

#include "engine.h"

// input
#include "input/input.h"
#include "input/keyboard.h"
#include "input/mouse.h"
#include "input/window.h"

// time
#include "time/time.h"

// video
#include "video/video.h"
#include "video/window.h"

// audio
#include "audio/audio.h"

// random
#include "random/random.h"

// geometry
#include "geometry/rectangle.h"
#include "geometry/circle.h"

namespace engine
{

class Game
{
	public:
		Game(std::string name);
		virtual ~Game();
		
		void loop();
		virtual void begin() {}
		virtual bool frame() = 0;
		virtual void end() {}
		
		template <class T> static int run()
		{
			T* game = new T();
			game->begin();
			game->loop();
			game->end();
			delete game;
			return 0;
		}
};

} // engine

using namespace engine;

#endif // ENGINE_GAME_H


