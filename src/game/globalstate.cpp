#include "game.h"
#include "globalstate.h"

namespace game
{

void GlobalState::enter(state::Agent* agent)
{
	game::Game* game = (game::Game*) agent;
	
	game->video->window->setTitle("BEATSHAPT");
	
	game->levelProgram.load("rsrc/shader/renderlevel.frag", "rsrc/shader/renderlevel.vert");
	
	game->levelPositionAttribute = game->levelProgram.getAttribute("position");
	game->levelUvAttribute = game->levelProgram.getAttribute("uv");
	game->levelVpMatrixUniform = game->levelProgram.getUniform("vpMatrix");
	game->levelColorUniform = game->levelProgram.getUniform("color");
	
	resetViews(game);
	
	AudioAnalyzer::open();
}

void GlobalState::execute(state::Agent* agent)
{
	game::Game* game = (game::Game*) agent;
	
	if (game->input->window->isResized())
		resetViews(game);
		
	if (game->input->keyboard->isJustPressed(K(ESCAPE)))
		game->stop();
}

void GlobalState::exit(state::Agent* agent)
{
	//game::Game* game = (game::Game*) agent;
	
	AudioAnalyzer::close();
}

void GlobalState::resetViews(game::Game* game)
{
	const geometry::Vector2 windowSize = game->video->window->getSize();
	
	game->view.reset();
	game->view.updateProjection(windowSize);
	
	game->interfaceView.reset();
	game->interfaceView.move(windowSize / -2.0f);
	game->interfaceView.updateProjection(windowSize);
}

} // game


