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
		virtual bool update();
		virtual void draw();
		virtual void end();
		
	private:
		geometry::Circle circle;
};

} // game

#endif // GAME_GAME_H


