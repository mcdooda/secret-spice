#ifndef GAME_GAME_H
#define GAME_GAME_H

#include "../engine/game.h"

namespace game
{

class Game : public engine::Game
{
	public:
		Game();
		virtual ~Game();
		
		virtual void begin();
		virtual bool frame();
		virtual void end();
};

} // game

#endif // GAME_GAME_H


