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

void Game::initWindow()
{
	engine->video->window->setTitle("BEATSHAPT");
}

void Game::initAudio()
{
	music = engine->audio->loadMusic("rsrc/music/spica_short.mp3");
	music->play();
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
	level.addPlatform(Platform(geometry::Rectangle(geometry::Vector2(0, 0), geometry::Vector2(10, 10)), time, video::Color::WHITE));
}

void Game::begin()
{
	initWindow();
	initAudio();
	initPasses();
	initView();
	initLevel();
}

bool Game::update()
{
	bool keepRunning = !engine->input->keyboard->isJustPressed(K(ESCAPE));
	
	if (engine->input->window->isResized())
		view.updateProjection(engine->video->window->getSize());
		
	static const float loopDuration = 2.0f;
	
	view.rotate(engine->time->getFrameTime() * M_PI / loopDuration);
	
	audio::Spectrum* spectrum = music->getSpectrum();
	geometry::Vector2 max = spectrum->getMax();
	float average = spectrum->getAverage();
	if (max.getY() > average * 10.0f)
	{
		std::cout << max << std::endl;
		float time = engine->time->getTime();
		video::Color color(engine->random->nextFloat(0.5f, 1.0f), engine->random->nextFloat(0.5f, 1.0f), engine->random->nextFloat(0.5f, 1.0f), 1.0f);
		
		geometry::Vector2 position = view.getRelativePosition(
			engine->video->window->getSize() / 2 + geometry::Vector2(max.getY() * 200, 0),
			engine->video->window->getSize()
		) - geometry::Vector2(5, 5);
		
		level.addPlatform(Platform(geometry::Rectangle(position, geometry::Vector2(10, 10)), time, color));
	}
	
	level.removeOldPlatforms(engine->time->getTime() - 2.0f * loopDuration);
	
	return keepRunning;
}

void Game::draw()
{
	program.use(engine->video->window);
	
	vpMatrixUniform.setMatrix4(view.getViewProjectionMatrix());
	
	level.draw(vertexAttribute, colorUniform);
}

void Game::end()
{
	
}

} // game


