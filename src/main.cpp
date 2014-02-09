#include "engine/game.h"
#include "game/game.h"

int main(int argc, char* argv[])
{
	std::vector<std::string> args;
	args.assign(argv, argv + argc);
	return Game::run<game::Game>(args);
}


