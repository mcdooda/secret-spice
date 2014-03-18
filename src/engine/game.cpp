#include <iostream>
#include "game.h"

namespace engine
{

Game::Game()
{
	video->window->open(video->window->getDesktopSize(), true, true);
}

Game::~Game()
{
	
}

void Game::setArgs(std::vector<std::string> args)
{
	m_args = args;
	checkArgs();
}

void Game::checkArgs()
{
	
}

void Game::argCheckString(int index)
{
	if (index < 0 || index >= (int) m_args.size())
	{
		std::cerr << "Argument #" << index << " must be of type string" << std::endl;
		exit(1);
	}
}

std::string Game::argGetString(int index)
{
	return index >= 0 && index < (int) m_args.size() ? m_args[index] : "";
}

void Game::argCheckInt(int index)
{
	if (index < 0 || index >= (int) m_args.size())
	{
		std::cerr << "Argument #" << index << " must be of type int" << std::endl;
		exit(1);
	}
}

int Game::argGetInt(int index)
{
	return index >= 0 && index < (int) m_args.size() ? atoi(m_args[index].c_str()) : 0;
}

void Game::begin()
{
	
}

void Game::loop()
{
	bool running = true;
	while (running)
	{
		time->beginFrame();
		
		input->poll();
		running = update() && !input->window->isClosed();
	
		draw();
		video->endFrame();
		
		time->endFrame();
	}
}

void Game::end()
{
	
}

} // engine


