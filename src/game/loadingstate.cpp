#include "game.h"
#include "loadingstate.h"
#include "gamestate.h"

namespace game
{

void LoadingState::enter(state::Agent* agent)
{
	game::Game* game = (game::Game*) agent;
	
	/*
	 * LOADING MUSIC
	 */
	
	game->audioAnalyzer.setInputFileName(game->argGetString(1));
	game->audioAnalyzer.analyze();
	copy(game->audioAnalyzer.getTicks().begin(), game->audioAnalyzer.getTicks().end(), std::back_inserter(game->ticks));
	
	/*
	 * ANALYZING MUSIC
	 */
	 
	video::View levelView;
	geometry::Vector2 zero;
	video::Color red(1.0f, 0.0f, 0.0f, 1.0f);
	video::Color purple(1.0f, 0.0f, 1.0f, 1.0f);
	geometry::Rectangle rectangle(geometry::Vector2(-1.0f, -1.0f), geometry::Vector2(2.0f, 2.0f));
	int i = 0;
	float angleY = 0;
	for (std::list<essentia::Real>::iterator it = game->ticks.begin(); it != game->ticks.end(); it++)
	{
		essentia::Real tick = *it;
		
		geometry::Vector2 center = levelView.getViewMatrix() * zero;
		
		game->audioAnalyzer.getSpectrum(tick, &game->currentSpectrum);
		float angle = -(game->currentSpectrum->getMax().getY() - game->audioAnalyzer.getMaxAverage() / 2);
		bool strongPeak = false;
		if (game->currentSpectrum->getMax().getY() > game->audioAnalyzer.getMaxAverage() * 2.8f)
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
		
		if (game->currentSpectrum->getMax().getY() > game->audioAnalyzer.getMaxAverage() * 0.5f)
			game->level.addPlatform(Platform(r, center, angle, angleY, tick, strongPeak ? purple : red));
			
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

void LoadingState::execute(state::Agent* agent)
{
	game::Game* game = (game::Game*) agent;
	
	game->getStateMachine()->setState(new GameState());
}

void LoadingState::exit(state::Agent* agent)
{
	//game::Game* game = (game::Game*) agent;
	
	
}

} // game


