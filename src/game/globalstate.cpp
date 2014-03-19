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
	
	game->view = video::View();
	game->view.updateProjection(game->video->window->getSize());
	
	AudioAnalyzer::open();
}

void GlobalState::execute(state::Agent* agent)
{
	game::Game* game = (game::Game*) agent;
	
	if (game->input->window->isResized())
		game->view.updateProjection(game->video->window->getSize());
		
	if (game->input->keyboard->isJustPressed(K(ESCAPE)))
		game->stop();
}

void GlobalState::exit(state::Agent* agent)
{
	//game::Game* game = (game::Game*) agent;
	
	AudioAnalyzer::close();
}

} // game


