#include "game.h"

namespace engine
{

Game::Game(std::string name)
{
	open();
	video::window::open(
		video::window::getDesktopWidth(),
		video::window::getDesktopHeight(),
		name,
		true
	);
}

Game::~Game()
{
	close();
}

void Game::loop()
{
	bool running = true;
	while (running)
	{
		time::beginFrame();
		video::beginFrame();
		
		input::poll();
		
		running = frame();
		
		video::endFrame();
		time::endFrame();
	}
}

} // engine


