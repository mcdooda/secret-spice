#ifndef ENGINE_VIDEO_RENDER_H
#define ENGINE_VIDEO_RENDER_H

#include "program.h"

namespace engine
{
namespace video
{

class Render : public Program
{
	public:
		Render();
		virtual ~Render();
		
		void draw();
};

} // video
} // engine

#endif // ENGINE_VIDEO_RENDER_H


