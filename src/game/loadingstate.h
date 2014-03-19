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
		void update(game::Game* game);
		void draw(game::Game* game);
		void loadLevel(game::Game* game);
		virtual void exit(state::Agent* agent);
		
	private:
		float m_frameRate;
};

}

#endif // GAME_LOADINGSTATE_H


