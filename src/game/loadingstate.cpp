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
	
	if (game->audioAnalyzer.isLoaded())
		game->getStateMachine()->setState(new GameState());
}

void LoadingState::draw(game::Game* game)
{
	game->levelProgram.use(game->video->window);
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
}

void LoadingState::loadLevel(game::Game* game)
{
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
		
		const geometry::Vector2& max = game->currentSpectrum->getMax();
		float maxAverage = game->audioAnalyzer.getMaxAverage();
		
		float angle = -(max.getY() - maxAverage / 2);
		bool strongPeak = false;
		if (max.getY() > maxAverage * 1.6f && max.getX() < 0.5f)
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
		
		bool addPlatform = strongPeak || max.getY() > maxAverage * 0.4f;
		//bool addPlatform = true;
		
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
	game->audioAnalyzer.computeMaxAverage();
	
	copy(game->audioAnalyzer.getTicks().begin(), game->audioAnalyzer.getTicks().end(), std::back_inserter(game->ticks));
	
	loadLevel(game);
}

} // game


