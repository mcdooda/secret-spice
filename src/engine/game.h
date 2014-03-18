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

// state
#include "state/state.h"

namespace engine
{

class Game : public Engine
{
	public:
		Game();
		virtual ~Game();
		
		/* arguments */
		void setArgs(std::vector<std::string> args);
		virtual void checkArgs();
		
		void argCheckString(int index);
		std::string argGetString(int index);
		
		void argCheckInt(int index);
		int argGetInt(int index);
		
		/* game logic */
		void loop();
		virtual void begin();
		virtual bool update() = 0;
		virtual void draw() = 0;
		virtual void end();
		
		/* game launcher */
		template <class T> static int run(std::vector<std::string> args)
		{
			T* game = new T();
			game->setArgs(args);
			game->begin();
			game->loop();
			game->end();
			delete game;
			return 0;
		}
		
	private:
		std::vector<std::string> m_args;
};

} // engine

using namespace engine;

#endif // ENGINE_GAME_H


