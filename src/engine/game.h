#ifndef ENGINE_GAME_H
#define ENGINE_GAME_H

#include <string>
#include "engine.h"

// single header public API

// geometry
#include "geometry/linesegment.h"
#include "geometry/circle.h"
#include "geometry/rectangle.h"

// video
#include "video/pass.h"
#include "video/render.h"
#include "video/color.h"

namespace engine
{

class Game
{
	public:
		Game(std::string name);
		virtual ~Game();
		
		void loop();
		virtual void begin();
		virtual bool update() = 0;
		virtual void draw() = 0;
		virtual void end();
		
		template <class T> static int run()
		{
			T* game = new T();
			game->begin();
			game->loop();
			game->end();
			delete game;
			return 0;
		}
		
	protected:
		Engine* engine;
};

} // engine

using namespace engine;

#endif // ENGINE_GAME_H


