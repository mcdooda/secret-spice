#ifndef GAME_GAMESTATE_H
#define GAME_GAMESTATE_H

#include "../engine/game.h"
#include "game.h"

namespace game
{

class GameState : public state::State
{
	public:
		virtual void enter(state::Agent* agent);
		virtual void execute(state::Agent* agent);
		void update(game::Game* game);
		void draw(game::Game* game);
		virtual void exit(state::Agent* agent);
};

}

#endif // GAME_GAMESTATE_H


