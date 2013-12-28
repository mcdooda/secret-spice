#include <GL/gl.h>
#include <SDL/SDL.h>
#include "video.h"
#include "text.h"

namespace engine
{
namespace video
{

void beginFrame()
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void endFrame()
{
	glFlush();
	SDL_GL_SwapBuffers();
}

/* private */

void open()
{
	Text::open();
}

void close()
{
	Text::close();
}

} // video
} // engine


