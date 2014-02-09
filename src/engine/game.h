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
#include "video/program.h"
#include "video/color.h"

namespace engine
{

class Game
{
	public:
		Game(std::vector<std::string> args);
		virtual ~Game();
		
		void loop();
		virtual void begin();
		virtual bool update() = 0;
		virtual void draw() = 0;
		virtual void end();
		
		template <class T> static int run(std::vector<std::string> args)
		{
			T* game = new T(args);
			game->begin();
			game->loop();
			game->end();
			delete game;
			return 0;
		}
		
	protected:
		Engine* engine;
		std::vector<std::string> args;
};

} // engine

using namespace engine;

#endif // ENGINE_GAME_H


