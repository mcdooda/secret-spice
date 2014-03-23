#include "game.h"
#include "loadingstate.h"
#include "gamestate.h"

namespace game
{

void LoadingState::enter(state::Agent* agent)
{
	game::Game* game = (game::Game*) agent;
	m_frameRate = game->time->getFrameRate();
	game->time->setNoLimitFrameRate();
	
	game->audioAnalyzer.setInputFileName(game->argGetString(1));
	game->audioAnalyzer.loadAlgorithms();
}

void LoadingState::execute(state::Agent* agent)
{
	game::Game* game = (game::Game*) agent;
	draw(game);
	update(game);
}

void LoadingState::update(game::Game* game)
{
	game->audioAnalyzer.analyzeStep();
	
	/*if (game->audioAnalyzer.isLoaded())
		game->getStateMachine()->setState(new GameState());*/
}

void LoadingState::draw(game::Game* game)
{
	game->levelPass.use();
	game->video->setClearColor(video::Color::BLACK);
	game->video->clear();
	game->levelVpMatrixUniform.setMatrix4(game->view.getViewProjectionMatrix());
	geometry::Rectangle r(geometry::Vector2(-1.0f, -1.0f), geometry::Vector2(2.0f, 2.0f));
	geometry::Matrix4 matrix4;
	matrix4.scale(20.0f + fmodf(game->time->getTime() * 4.0f, 10.0f));
	matrix4.rotateZ(game->time->getTime());
	r.transform(matrix4);
	game->levelColorUniform.setColor(video::Color(0.5f - fmodf(game->time->getTime() * 0.2f, 0.5f)));
	r.draw(game->levelPositionAttribute);
	
	game->renderProgram.use(game->video->window);
	game->video->setClearColor(video::Color::WHITE);
	game->video->clear();
	geometry::Rectangle r2(geometry::Vector2(-0.9f, -0.9f), geometry::Vector2(1.8f, 1.8f));
	r2.draw(game->renderPositionAttribute, game->renderUvAttribute);
}

void LoadingState::loadLevel(game::Game* game)
{
	video::View levelView;
	geometry::Vector2 zero;
	video::Color red(1.0f, 0.0f, 0.0f, 1.0f);
	video::Color purple(1.0f, 0.0f, 1.0f, 1.0f);
	geometry::Rectangle rectangle(geometry::Vector2(-1.0f, -1.0f), geometry::Vector2(2.0f, 2.0f));
	essentia::Real averageLoudness = game->audioAnalyzer.getAverageLoudness();
	float angleY = 0;
	int i = 0;
	int length = game->ticks.size();
	for (std::list<essentia::Real>::iterator it = game->ticks.begin(); it != game->ticks.end(); it++)
	{
		essentia::Real tick = *it;
		
		essentia::Real prevPrevTick;
		essentia::Real prevTick;
		if (i > 0)
		{
			it--;
			prevTick = *it;
			if (i > 1)
			{
				it--;
				prevPrevTick = *it;
				it++;
			}
			else
				prevPrevTick = prevTick;
			it++;
		}
		else
		{
			prevTick = tick;
			prevPrevTick = prevTick;
		}
			
		essentia::Real nextTick;
		if (i < length - 1)
		{
			it++;
			nextTick = *it;
			it--;
		}
		else
			nextTick = tick;
		
		geometry::Vector2 center = levelView.getViewMatrix() * zero;
		
		Spectrum* prevPrevSpectrum;
		Spectrum* prevSpectrum;
		Spectrum* currentSpectrum;
		Spectrum* nextSpectrum;
		
		game->audioAnalyzer.getSpectrum(prevPrevTick, &prevPrevSpectrum);
		game->audioAnalyzer.getSpectrum(prevTick, &prevSpectrum);
		game->audioAnalyzer.getSpectrum(tick, &currentSpectrum);
		game->audioAnalyzer.getSpectrum(nextTick, &nextSpectrum);
		
		essentia::Real prevPrevLoudness = prevPrevSpectrum->getLoudness();
		essentia::Real prevLoudness = prevSpectrum->getLoudness();
		essentia::Real loudness = currentSpectrum->getLoudness();
		essentia::Real nextLoudness = nextSpectrum->getLoudness();
		
		float angle = -(loudness - averageLoudness / 2.0f) / (averageLoudness * 8.0f);
		bool strongPeak = false;
		if (prevPrevLoudness < loudness && prevLoudness < loudness && nextLoudness < loudness)
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
		
		bool addPlatform = loudness > averageLoudness * 0.2f;
		
		if (addPlatform)
			game->level.addPlatform(Platform(r, center, angle, angleY, tick, strongPeak ? purple : red, strongPeak));
			
		else
		{
			it = game->ticks.erase(it);
			it--;
		}
		
		std::list<essentia::Real>::iterator nextIt = it;
		nextIt++;
		if (nextIt != game->ticks.end())
		{
			essentia::Real nextTick = *nextIt;
			geometry::Vector2 move(200.0f * (nextTick - tick), 0);
			levelView.move(move);
		}
		
		i++;
	}
}

void LoadingState::exit(state::Agent* agent)
{
	game::Game* game = (game::Game*) agent;
	game->time->setFrameRate(m_frameRate);
	
	game->audioAnalyzer.freeAlgorithms();
	game->audioAnalyzer.computeAverageLoudness();
	
	copy(game->audioAnalyzer.getTicks().begin(), game->audioAnalyzer.getTicks().end(), std::back_inserter(game->ticks));
	
	loadLevel(game);
}

} // game


