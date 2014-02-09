#include <iostream>
#include "game.h"
#include "../engine/game.h"

namespace game
{

Game::Game(std::vector<std::string> args) : engine::Game(args)
{
	
}

Game::~Game()
{
	
}

void Game::initPasses()
{
	program.load("rsrc/shader/render.frag", "rsrc/shader/render.vert");
	
	vertexAttribute = program.getAttribute("position");
	vpMatrixUniform = program.getUniform("vpMatrix");
	colorUniform = program.getUniform("color");
}

void Game::initObjects()
{
	// drawable objects
	circle1 = geometry::Circle(geometry::Vector2(0, 1), 1);
	circle2 = geometry::Circle(geometry::Vector2(0,-1), 1);
	
	unitSquare = geometry::Rectangle(geometry::Vector2(), geometry::Vector2(1, 1));
	
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
	engine->video->window->setTitle("BEATSHAPT");
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
	program.use();
	
	vpMatrixUniform.setMatrix4(view.getViewProjectionMatrix());
	
	colorUniform.setColor(video::Color(128, 255, 0, 255));
	circle1.draw(vertexAttribute);
	
	colorUniform.setColor(video::Color(128, 0, 255, 255));
	circle2.draw(vertexAttribute);
	
	colorUniform.setColor(video::Color(128, 128, 128, 255));
	unitSquare.draw(vertexAttribute);
	
	colorUniform.setColor(video::Color(255, 0, 0, 255));
	x.draw(vertexAttribute);
	
	colorUniform.setColor(video::Color(0, 0, 255, 255));
	y.draw(vertexAttribute);
}

void Game::end()
{
	
}

} // game


