#ifndef GAME_LOADINGSTATE_H
#define GAME_LOADINGSTATE_H

#include "../engine/game.h"

namespace game
{

class LoadingState : public state::State
{
	public:
		virtual void enter(state::Agent* agent);
		virtual void execute(state::Agent* agent);
		virtual void exit(state::Agent* agent);
};

}

#endif // GAME_LOADINGSTATE_H


