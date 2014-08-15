#include <flat/game.h>

#include "game.h"

int main(int argc, char* argv[])
{
	std::vector<std::string> args;
	args.assign(argv, argv + argc);
	return flat::Game::run<game::Game>(args);
}


