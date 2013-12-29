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
	video::View view(engine->video->window->getSize() / 2, 1);
	engine->video->window->setView(view);
}

bool Game::update()
{
	bool keepRunning = !engine->input->keyboard->isJustPressed(K(ESCAPE));
	return keepRunning;
}

void Game::draw()
{
	engine::geometry::Vector2d mousePosition = engine->input->mouse->getPosition();
	
	geometry::Circle circle(mousePosition, 20);
	circle.show();
}

void Game::end()
{
	
}

} // game


