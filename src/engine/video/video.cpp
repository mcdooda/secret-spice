#include <GL/glew.h>
#include <SDL2/SDL.h>
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

void Video::endFrame()
{
	window->endFrame();
}

} // video
} // engine


