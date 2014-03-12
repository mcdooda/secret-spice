#include <iostream>
#include "game.h"
#include "../engine/game.h"

namespace game
{

static const float characterSpeed = 200.0f;

void Game::checkArgs()
{
	argCheckString(1);
}

void Game::initWindow()
{
	engine->video->window->setTitle("BEATSHAPT");
}

void Game::initAudioAnalyzer()
{
	AudioAnalyzer::open();
	audioAnalyzer.setInputFileName(argGetString(1));
	audioAnalyzer.analyze();
	copy(audioAnalyzer.getTicks().begin(), audioAnalyzer.getTicks().end(), std::back_inserter(ticks));
}

void Game::initAudio()
{
	music = engine->audio->loadMusic(argGetString(1));
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
	video::View levelView;
	geometry::Vector2 zero;
	geometry::Vector2 size(10, 10);
	for (std::list<essentia::Real>::iterator it = ticks.begin(); it != ticks.end(); it++)
	{
		essentia::Real tick = *it;
		video::Color red(1.0f, 0.0f, 0.0f, 1.0f);
		
		geometry::Vector2 position = levelView.getViewMatrix() * zero;
		level.addPlatform(Platform(geometry::Rectangle(position, size), tick, red));
		
		std::list<essentia::Real>::iterator nextIt = it;
		nextIt++;
		if (nextIt != ticks.end())
			levelView.move(geometry::Vector2(characterSpeed * (*nextIt - *it), 0));
	}
}

void Game::begin()
{
	initWindow();
	initAudioAnalyzer();
	initPasses();
	initView();
	initLevel();
	
	rotateDirection = 0.0f;
	
	initAudio();
	beginTime = engine->time->getTime();
	lastTick = beginTime;
}

void Game::end()
{
	AudioAnalyzer::close();
}

bool Game::update()
{
	bool keepRunning = !engine->input->keyboard->isJustPressed(K(ESCAPE));
	
	float time = engine->time->getTime() - beginTime;
	
	if (engine->input->window->isResized())
		view.updateProjection(engine->video->window->getSize());
	
	if (!ticks.empty() && time > *ticks.begin())
	{
		lastTick = *ticks.begin();
		ticks.pop_front();
	}
	
	level.fadeOldPlatforms(time);
	level.removeOldPlatforms(time - 3.0f);
	
	currentSpectrum = audioAnalyzer.getSpectrum(time);
	
	view.reset();
	view.move(geometry::Vector2(-characterSpeed * time, 0));
	
	return keepRunning;
}

void Game::draw()
{
	float time = engine->time->getTime() - beginTime;
	float flashDuration = 0.1f;
	
	if (time - lastTick < flashDuration)
		engine->video->setClearColor(video::Color((time - lastTick) / flashDuration, 0.0f, 0.0f, 1.0f));
		
	else
	{
		essentia::Real max = 0;
		int kmax = 0;
		int k = 0;
		for (std::vector<essentia::Real>::iterator it = currentSpectrum.begin(); it != currentSpectrum.end(); it++)
		{
			if (*it > max)
			{
				max = *it;
				kmax = k;
			}
			k++;
		}
		//float gray = (float) kmax / currentSpectrum.size();
		float gray = max;
		engine->video->setClearColor(video::Color(gray));
	}
	
	program.use(engine->video->window);
	
	vpMatrixUniform.setMatrix4(view.getViewProjectionMatrix());
	
	level.draw(vertexAttribute, colorUniform);
}

} // game


