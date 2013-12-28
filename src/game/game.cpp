#include <iostream>
#include <GL/gl.h>
#include "game.h"
#include "../engine/game.h"

namespace game
{

Game::Game() : engine::Game("BEATSHAPT")
{
	
}

Game::~Game()
{
	
}

void Game::begin()
{
	video::View view(
		geometry::Vector2d(
			video::window::getWidth() / 2,
			video::window::getHeight() / 2
		),
		1
	);
	video::window::setView(view);
}

bool Game::frame()
{
	bool keepRunning = !input::keyboard::isJustPressed(K(ESCAPE));
	
	int mouseX = input::mouse::getX();
	int mouseY = input::mouse::getY();
	
	geometry::Circle circle(geometry::Vector2d(mouseX, mouseY), 20);
	circle.show();
	
	return keepRunning;
}

void Game::end()
{
	
}

} // game


