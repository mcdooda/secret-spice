#ifndef ENGINE_STATE_MACHINE_H
#define ENGINE_STATE_MACHINE_H

#include "state.h"

namespace engine
{
namespace state
{

class Agent;
class State;

class Machine
{
	public:
		Machine(Agent* agent);
		~Machine();

		void setState(State* state);
		void revertToPreviousState();
		void setGlobalState(State* globalState);

		void update();

	private:
		State* m_currentState;
		State* m_previousState;
		State* m_globalState;
		Agent* m_agent;
};

} // state
} // engine

#endif // ENGINE_STATE_MACHINE_H


