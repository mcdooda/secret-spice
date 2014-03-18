#include <iostream>
#include "game.h"
#include "globalstate.h"
#include "loadingstate.h"
#include "gamestate.h"
#include "../engine/game.h"

namespace game
{

Game::Game(const std::vector<std::string>& args) : engine::Game(args)
{
	getStateMachine()->setGlobalState(new GlobalState());
	getStateMachine()->setState(new LoadingState());
}

Game::~Game()
{
	
}

void Game::checkArgs()
{
	argCheckString(1);
}

} // game


