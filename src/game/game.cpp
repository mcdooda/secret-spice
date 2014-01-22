#include <iostream>
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
	program.load("rsrc/shader/shader.frag", "rsrc/shader/shader.vert");
	
	circle1 = geometry::Circle(geometry::Vector2(0, 1), 1);
	circle2 = geometry::Circle(geometry::Vector2(0,-1), 1);
	
	view = video::View();
	view.updateProjection(engine->video->window->getSize());
	
	zoom = true;
}

bool Game::update()
{
	bool keepRunning = !engine->input->keyboard->isJustPressed(K(ESCAPE));
	
	if (engine->input->keyboard->isJustPressed(K(f)))
		engine->video->window->toggleFullScreen();
		
	if (engine->input->keyboard->isJustPressed(K(p)))
	{
		if (engine->time->isPaused())
			engine->time->resume();
			
		else
			engine->time->pause();
	}
	
	if (engine->input->mouse->isJustPressed(M(LEFT)))
		zoom = !zoom;
	
	if (zoom)
		view.zoom(1.0f + engine->time->getFrameTime());
		
	else
		view.zoom(1.0f - engine->time->getFrameTime());
		
	view.rotate(engine->time->getFrameTime());
	
	if (engine->input->window->isResized())
		view.updateProjection(engine->video->window->getSize());
	
	viewMouse = view.getRelativePosition(engine->input->mouse->getPosition(), engine->video->window->getSize());
	
	circle1.setCenter(viewMouse - geometry::Vector2(0, 1));
	circle2.setCenter(viewMouse + geometry::Vector2(0, 1));
	
	return keepRunning;
}

void Game::draw()
{
	program.use();
	
	int vertexAttrib = program.getAttribLocation("position");
	video::Uniform colorUniform = program.getUniform("color");
	video::Uniform viewProjectionMatrixUniform = program.getUniform("vpMatrix");
	
	viewProjectionMatrixUniform.setMatrix4(view.getViewProjectionMatrix());
	
	colorUniform.setColor(video::Color(255, 0, 0, 255));
	circle1.draw(vertexAttrib);
	
	colorUniform.setColor(video::Color(0, 255, 0, 255));
	circle2.draw(vertexAttrib);
}

void Game::end()
{
	
}

} // game


