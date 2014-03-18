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
	levelProgram.load("rsrc/shader/renderlevel.frag", "rsrc/shader/renderlevel.vert");
	
	levelVertexAttribute = levelProgram.getAttribute("position");
	levelVpMatrixUniform = levelProgram.getUniform("vpMatrix");
	levelColorUniform = levelProgram.getUniform("color");
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
	video::Color red(1.0f, 0.0f, 0.0f, 1.0f);
	video::Color purple(1.0f, 0.0f, 1.0f, 1.0f);
	geometry::Rectangle rectangle(geometry::Vector2(-1.0f, -1.0f), geometry::Vector2(2.0f, 2.0f));
	int i = 0;
	float angleY = 0;
	for (std::list<essentia::Real>::iterator it = ticks.begin(); it != ticks.end(); it++)
	{
		essentia::Real tick = *it;
		
		geometry::Vector2 center = levelView.getViewMatrix() * zero;
		
		audioAnalyzer.getSpectrum(tick, &currentSpectrum);
		float angle = -(currentSpectrum->getMax().getY() - audioAnalyzer.getMaxAverage() / 2);
		bool strongPeak = false;
		if (currentSpectrum->getMax().getY() > audioAnalyzer.getMaxAverage() * 2.8f)
		{
			strongPeak = true;
			angleY += M_PI;
		}
		
		geometry::Matrix4 matrix4;
		matrix4.scale(20.0f);
		matrix4.rotateZ(angle);
		matrix4.translate(center);
		
		geometry::Rectangle r = rectangle;
		r.transform(matrix4);
		
		if (currentSpectrum->getMax().getY() > audioAnalyzer.getMaxAverage() * 0.5f)
			level.addPlatform(Platform(r, center, angle, angleY, tick, strongPeak ? purple : red));
			
		else
		{
			it = ticks.erase(it);
			it--;
		}
		
		std::list<essentia::Real>::iterator nextIt = it;
		nextIt++;
		if (nextIt != ticks.end())
		{
			essentia::Real nextTick = *nextIt;
			geometry::Vector2 move(characterSpeed * (nextTick - tick), 0);
			levelView.move(move);
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
	lastTick = -2.0f;
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
	level.removeOldPlatforms(time - 7.0f);
	
	Platform* previousPlatform;
	Platform* nextPlatform;
	level.getCurrentPlatforms(time, &previousPlatform, &nextPlatform);
	
	if (previousPlatform != NULL && nextPlatform != NULL)
	{
		float viewAngle;
		float viewAngleY;
		geometry::Vector2 viewPosition;
		
		float alpha;
		if (previousPlatform != nextPlatform)
		{
			alpha = (time - previousPlatform->getTime()) / (nextPlatform->getTime() - previousPlatform->getTime());
			alpha = powf(alpha, 5.0f);
		}
		else
			alpha = 0;
		
		viewPosition = (previousPlatform->getCenter() + (nextPlatform->getCenter() - previousPlatform->getCenter()) * alpha) * -1;
		viewAngle = -(previousPlatform->getAngle() + (nextPlatform->getAngle() - previousPlatform->getAngle()) * alpha);
		viewAngleY = -(previousPlatform->getAngleY() + (nextPlatform->getAngleY() - previousPlatform->getAngleY()) * alpha);
		
		view.reset();
		view.move(viewPosition);
		view.rotateZ(viewAngle);
		view.rotateY(viewAngleY);
		
		audioAnalyzer.getSpectrum(time, &currentSpectrum);
	}
	
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
	
	levelProgram.use(engine->video->window);
	levelProgram.clear();
	levelVpMatrixUniform.setMatrix4(view.getViewProjectionMatrix());
	level.draw(time + 7.0f, levelVertexAttribute, levelColorUniform);
}

} // game


