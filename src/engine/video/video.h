#ifndef ENGINE_VIDEO_VIDEO_H
#define ENGINE_VIDEO_VIDEO_H

#include "window.h"

namespace engine
{
namespace video
{

class Video
{
	public:
		Video();
		~Video();
		
		void endFrame();

	public:
		Window* window;
};

} // video
} // engine

#endif // ENGINE_VIDEO_VIDEO_H


