#include <SDL/SDL.h>
#include "engine.h"

#include "input/input.h"
#include "video/video.h"
#include "audio/audio.h"
#include "time/time.h"
#include "random/random.h"

namespace engine
{

void open()
{
	openSDL();
	input::open();
	time::open();
	video::open();
	audio::open();
	random::open();
}

void close()
{
	closeSDL();
	input::close();
	time::close();
	video::close();
	audio::close();
	random::close();
}

/* private */
void openSDL()
{
	SDL_Init(SDL_INIT_VIDEO);
}

void closeSDL()
{
	SDL_Quit();
}

} // engine


