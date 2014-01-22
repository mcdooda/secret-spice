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
	
	return keepRunning;
}

void Game::draw()
{
	program.use();
	
	int vertexAttrib = program.getAttribLocation("position");
	video::Uniform colorUniform = program.getUniform("color");
	video::Uniform viewProjectionMatrixUniform = program.getUniform("vpMatrix");
	
	video::View view;
	view.zoom(engine->time->getTime() * 50);
	view.updateProjectionMatrix(engine->video->window->getSize());
	
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


