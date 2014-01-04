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
	circle = geometry::Circle(geometry::Vector2d(), 20);
}

bool Game::update()
{
	bool keepRunning = !engine->input->keyboard->isJustPressed(K(ESCAPE));
	
	if (engine->input->keyboard->isPressed(K(UP)))
	{
		video::View view = engine->video->window->getView();
		view.zoom(1.f + engine->time->getFrameTime(), 10.f);
		engine->video->window->setView(view);
	}
	else if (engine->input->keyboard->isPressed(K(DOWN)))
	{
		video::View view = engine->video->window->getView();
		view.zoom(1.f - engine->time->getFrameTime(), .1f);
		engine->video->window->setView(view);
	}
	
	geometry::Vector2d mousePosition = engine->input->mouse->getPosition();
	const video::View& view = engine->video->window->getView();
	geometry::Vector2d center = view.getRelativePosition(mousePosition, engine->video->window->getSize());
	
	circle.setCenter(center);
	
	return keepRunning;
}

void Game::draw()
{
	circle.draw();
}

void Game::end()
{
	
}

} // game


