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

void Game::initPasses()
{
	// 1st pass
	pass1.init(engine->video->window->getSize());
	pass1.load("rsrc/shader/render.frag", "rsrc/shader/render.vert");
	
	colorTexture = pass1.newColorTexture("colorTexture");
	
	vertexAttrib = pass1.getPositionAttrib();
	vpMatrixUniform = pass1.getVpMatrixUniform();
	colorUniform = pass1.getUniform("color");
	
	// 2nd pass
	finalRender.load("rsrc/shader/blur.frag", "rsrc/shader/blur.vert");
	finalRender.addInputTexture(colorTexture);
}

void Game::initObjects()
{
	// drawable objects
	circle1 = geometry::Circle(geometry::Vector2(0, 1), 1);
	circle2 = geometry::Circle(geometry::Vector2(0,-1), 1);
	
	x = geometry::LineSegment(geometry::Vector2(), geometry::Vector2(1, 0));
	y = geometry::LineSegment(geometry::Vector2(), geometry::Vector2(0, 1));
}

void Game::initView()
{
	// camera
	view = video::View();
	view.updateProjection(engine->video->window->getSize());
	view.zoom(20.0f);
}

void Game::initLogic()
{
	// zoom or unzoom?
	zoom = true;
}

void Game::begin()
{
	initPasses();
	initObjects();
	initView();
	initLogic();
}

bool Game::update()
{
	// toggle full screen
	if (engine->input->keyboard->isJustPressed(K(f)))
		engine->video->window->toggleFullScreen();
		
	// toggle pause
	if (engine->input->keyboard->isJustPressed(K(p)))
		engine->time->togglePause();
	
	// toggle zoom / unzoom
	if (engine->input->mouse->isJustPressed(M(LEFT)))
		zoom = !zoom;
	
	// scale
	float z = 1.0f + (zoom ? 1 : -1) * engine->time->getFrameTime();
	view.zoom(z);
		
	// rotate
	view.rotate(engine->time->getFrameTime());
	
	// update projection
	if (engine->input->window->isResized())
		view.updateProjection(engine->video->window->getSize());
	
	// update mouse position
	viewMouse = view.getRelativePosition(engine->input->mouse->getPosition(), engine->video->window->getSize());
	
	circle1.setCenter(viewMouse - geometry::Vector2(0, 1));
	circle2.setCenter(viewMouse + geometry::Vector2(0, 1));
	
	bool keepRunning = !engine->input->keyboard->isJustPressed(K(ESCAPE));
	return keepRunning;
}

void Game::draw()
{
	// 1st pass: draw scene
	pass1.use();
	
	vpMatrixUniform.setMatrix4(view.getViewProjectionMatrix());
	
	colorUniform.setColor(video::Color(128, 255, 0, 255));
	circle1.draw(vertexAttrib);
	
	colorUniform.setColor(video::Color(128, 0, 255, 255));
	circle2.draw(vertexAttrib);
	
	colorUniform.setColor(video::Color(255, 0, 0, 255));
	x.draw(vertexAttrib);
	
	colorUniform.setColor(video::Color(0, 0, 255, 255));
	y.draw(vertexAttrib);
	
	// final pass: render on screen with blur effect
	finalRender.draw();
}

void Game::end()
{
	
}

} // game


