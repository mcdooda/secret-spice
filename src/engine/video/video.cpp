#include <GL/glew.h>
#include <SDL/SDL.h>
#include "video.h"
#include "text.h"

namespace engine
{
namespace video
{

Video::Video()
{
	Text::open();
	window = new Window;
}

Video::~Video()
{
	Text::close();
	delete window;
}

void Video::beginFrame()
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void Video::endFrame()
{
	glFlush();
	SDL_GL_SwapBuffers();
}

} // video
} // engine


