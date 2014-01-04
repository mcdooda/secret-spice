#include "game.h"

namespace engine
{

Game::Game(std::string name)
{
	engine = new Engine();
	engine->video->window->open(engine->video->window->getDesktopSize(), name, true);
	engine->video->window->setInterfaceView();
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
	
		engine->video->beginFrame();
		draw();
		engine->video->endFrame();
		
		engine->time->endFrame();
	}
}

void Game::end()
{
	
}

} // engine


