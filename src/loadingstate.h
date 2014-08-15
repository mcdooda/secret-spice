#ifndef GAME_LOADINGSTATE_H
#define GAME_LOADINGSTATE_H

#include <flat.h>
using namespace flat;

namespace game
{

class LoadingState : public thread::Thread, public state::State
{
	public:
		virtual void task();
		
		virtual void enter(state::Agent* agent);
		virtual void execute(state::Agent* agent);
		void update();
		void draw();
		void loadLevel();
		virtual void exit(state::Agent* agent);
		
	private:
		float m_frameRate;
		bool m_loaded;
		Game* m_game;
		AudioAnalyzer* m_audioAnalyzer;
};

}

#endif // GAME_LOADINGSTATE_H


