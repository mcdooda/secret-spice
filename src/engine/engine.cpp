#include <SDL2/SDL.h>
#include "engine.h"

#include "input/input.h"
#include "video/video.h"
#include "audio/audio.h"
#include "time/time.h"
#include "random/random.h"

namespace engine
{

Engine::Engine()
{
	openSDL();
	time = new time::Time;
	video = new video::Video;
	audio = new audio::Audio;
	random = new random::Random;
	input = new input::Input(video->window);
}

Engine::~Engine()
{
	closeSDL();
	delete time;
	delete video;
	delete audio;
	delete random;
	delete input;
}

/* private */

void Engine::openSDL()
{
	SDL_Init(SDL_INIT_VIDEO);
}

void Engine::closeSDL()
{
	SDL_Quit();
}

} // engine


