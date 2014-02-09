#include "game.h"

namespace engine
{

Game::Game(std::vector<std::string> args)
{
	engine = new Engine();
	engine->video->window->open(engine->video->window->getDesktopSize() / 2, false, true);
	this->args = args;
}

Game::~Game()
{
	delete engine;
}

void Game::begin()
{
	
}

void Game::loop()
{
	bool running = true;
	while (running)
	{
		engine->time->beginFrame();
		
		engine->input->poll();
		running = update() && !engine->input->window->isClosed();
	
		draw();
		engine->video->endFrame();
		
		engine->time->endFrame();
	}
}

void Game::end()
{
	
}

} // engine


