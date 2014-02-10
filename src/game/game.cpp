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

void Game::initView()
{
	// camera
	view = video::View();
	view.updateProjection(engine->video->window->getSize());
}

void Game::initLevel()
{
	float time = engine->time->getTime();
	level.addPlatform(Platform(geometry::Rectangle(geometry::Vector2(0, 0), geometry::Vector2(200, 100)), time));
}

void Game::begin()
{
	engine->video->window->setTitle("BEATSHAPT");
	initPasses();
	initView();
	initLevel();
}

bool Game::update()
{
	bool keepRunning = !engine->input->keyboard->isJustPressed(K(ESCAPE));
	
	level.removeOldPlatforms(engine->time->getTime() - 20.0f);
	
	return keepRunning;
}

void Game::draw()
{
	program.use(engine->video->window);
	
	vpMatrixUniform.setMatrix4(view.getViewProjectionMatrix());
	
	colorUniform.setColor(video::Color(128, 255, 0, 255));
	
	level.draw(vertexAttribute);
}

void Game::end()
{
	
}

} // game


