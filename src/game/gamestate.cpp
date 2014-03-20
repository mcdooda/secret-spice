#include "gamestate.h"

namespace game
{

void GameState::enter(state::Agent* agent)
{
	game::Game* game = (game::Game*) agent;
	
	game->music = game->audio->loadMusic(game->argGetString(1));
	game->music->play();
	
	game->beginTime = game->time->getTime();
	game->lastTick = -2.0f;
}

void GameState::execute(state::Agent* agent)
{
	game::Game* game = (game::Game*) agent;
	
	update(game);
	draw(game);
}

void GameState::update(game::Game* game)
{
	float currentTime = game->time->getTime() - game->beginTime;
	
	if (!game->ticks.empty() && currentTime > *game->ticks.begin())
	{
		game->lastTick = *game->ticks.begin();
		game->ticks.pop_front();
	}
	
	game->level.fadeOldPlatforms(currentTime);
	game->level.removeOldPlatforms(currentTime - 7.0f);
	
	Platform* previousPlatform;
	Platform* nextPlatform;
	game->level.getCurrentPlatforms(currentTime, &previousPlatform, &nextPlatform);
	
	if (previousPlatform != NULL && nextPlatform != NULL)
	{
		float viewAngle;
		float viewAngleY;
		geometry::Vector2 viewPosition;
		
		float alpha;
		if (previousPlatform != nextPlatform)
		{
			alpha = (currentTime - previousPlatform->getTime()) / (nextPlatform->getTime() - previousPlatform->getTime());
			alpha = powf(alpha, 5.0f);
		}
		else
			alpha = 0;
		
		viewPosition = (previousPlatform->getCenter() + (nextPlatform->getCenter() - previousPlatform->getCenter()) * alpha) * -1;
		viewAngle = -(previousPlatform->getAngle() + (nextPlatform->getAngle() - previousPlatform->getAngle()) * alpha);
		viewAngleY = -(previousPlatform->getAngleY() + (nextPlatform->getAngleY() - previousPlatform->getAngleY()) * alpha);
		
		game->view.reset();
		game->view.move(viewPosition);
		game->view.rotateZ(viewAngle);
		game->view.rotateY(viewAngleY);
		
		game->audioAnalyzer.getSpectrum(currentTime, &game->currentSpectrum);
	}
}

void GameState::draw(game::Game* game)
{
	float currentTime = game->time->getTime() - game->beginTime;
	float flashDuration = 0.1f;
	
	if (currentTime - game->lastTick < flashDuration)
		game->video->setClearColor(video::Color((currentTime - game->lastTick) / flashDuration, 0.0f, 0.0f, 1.0f));
	
	else if (game->currentSpectrum != NULL)
	{
		float gray = game->currentSpectrum->getMax().getY();
		game->video->setClearColor(video::Color(gray));
	}
	else
		game->video->setClearColor(video::Color::BLACK);
	
	game->video->clear();
	game->levelProgram.use(game->video->window);
	
	game->levelVpMatrixUniform.setMatrix4(game->view.getViewProjectionMatrix());
	game->level.draw(currentTime + 7.0f, game->levelPositionAttribute, game->levelUvAttribute, game->levelColorUniform);
	
	game->levelColorUniform.setColor(video::Color(1.0f, 0.0f, 0.0f, 1.0f));
	const geometry::Vector2 windowSize = game->video->window->getSize();
	float cursorPosition = currentTime / game->audioAnalyzer.getDuration();
	cursorPosition = cursorPosition > 1.0f ? 1.0f : cursorPosition;
	geometry::Rectangle r(geometry::Vector2(2.0f, 2.0f), geometry::Vector2((windowSize.getX() - 4.0f) * cursorPosition, 2.0f));
	game->levelVpMatrixUniform.setMatrix4(game->interfaceView.getViewProjectionMatrix());
	r.draw(game->levelPositionAttribute, game->levelUvAttribute);
}

void GameState::exit(state::Agent* agent)
{
	//game::Game* game = (game::Game*) agent;
	
	
}

} // game


