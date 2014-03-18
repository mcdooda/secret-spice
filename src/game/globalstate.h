#ifndef GAME_GLOBALSTATE_H
#define GAME_GLOBALSTATE_H

#include "../engine/game.h"

namespace game
{

class GlobalState : public state::State
{
	public:
		virtual void enter(state::Agent* agent);
		virtual void execute(state::Agent* agent);
		virtual void exit(state::Agent* agent);
};

}

#endif // GAME_GLOBALSTATE_H


