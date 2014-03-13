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
	geometry::Rectangle rectangle(geometry::Vector2(-1.0f, -1.0f), geometry::Vector2(2.0f, 2.0f));
	int i = 0;
	float lastAngleY = 0;
	for (std::list<essentia::Real>::iterator it = ticks.begin(); it != ticks.end(); it++)
	{
		essentia::Real tick = *it;
		video::Color red(1.0f, 0.0f, 0.0f, 1.0f);
		
		geometry::Vector2 center = levelView.getViewMatrix() * zero;
		
		audioAnalyzer.getSpectrum(tick, &currentSpectrum);
		float angle = -(currentSpectrum->getMax().getY() - audioAnalyzer.getMaxAverage() / 2);
		float angleY = lastAngleY;
		if (currentSpectrum->getMax().getY() > audioAnalyzer.getMaxAverage() * 2.0f)
		{
			if (lastAngleY == 0)
				angleY = M_PI;
			else
				angleY = 0;
		}
		lastAngleY = angleY;
		
		geometry::Matrix4 matrix4;
		matrix4.scale(20.0f);
		matrix4.rotateZ(angle);
		matrix4.translate(center);
		
		geometry::Rectangle r = rectangle;
		r.transform(matrix4);
		
		level.addPlatform(Platform(r, center, angle, angleY, tick, red));
		
		std::list<essentia::Real>::iterator nextIt = it;
		nextIt++;
		if (nextIt != ticks.end())
		{
			essentia::Real nextTick = *nextIt;
			levelView.move(geometry::Vector2(characterSpeed * (nextTick - tick), 0));
		}
		
		i++;
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
	
	Platform* previousPlatform;
	Platform* nextPlatform;
	level.getCurrentPlatforms(time, &previousPlatform, &nextPlatform);
	
	float viewAngle;
	float viewAngleY;
	geometry::Vector2 viewPosition;
	
	if (nextPlatform != NULL)
	{
		float alpha = (time - previousPlatform->getTime()) / (nextPlatform->getTime() - previousPlatform->getTime());
		alpha = powf(alpha, 5.0f);
		viewPosition = (previousPlatform->getCenter() + (nextPlatform->getCenter() - previousPlatform->getCenter()) * alpha) * -1;
		viewAngle = -(previousPlatform->getAngle() + (nextPlatform->getAngle() - previousPlatform->getAngle()) * alpha);
		viewAngleY = -(previousPlatform->getAngleY() + (nextPlatform->getAngleY() - previousPlatform->getAngleY()) * alpha);
	}
	else
	{
		viewPosition = previousPlatform->getCenter() * -1;
		viewAngle = -previousPlatform->getAngle();
		viewAngleY = previousPlatform->getAngle();
	}
	
	audioAnalyzer.getSpectrum(time, &currentSpectrum);
	
	view.reset();
	view.move(viewPosition);
	view.rotateZ(viewAngle);
	view.rotateY(viewAngleY);
	
	return keepRunning;
}

void Game::draw()
{
	float time = engine->time->getTime() - beginTime;
	float flashDuration = 0.1f;
	
	if (time - lastTick < flashDuration)
		engine->video->setClearColor(video::Color((time - lastTick) / flashDuration, 0.0f, 0.0f, 1.0f));
		
	else if (currentSpectrum != NULL)
	{
		float gray = currentSpectrum->getMax().getY();
		engine->video->setClearColor(video::Color(gray));
	}
	else
		engine->video->setClearColor(video::Color::BLACK);
	
	program.use(engine->video->window);
	
	vpMatrixUniform.setMatrix4(view.getViewProjectionMatrix());
	
	level.draw(vertexAttribute, colorUniform);
}

} // game


