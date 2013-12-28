#ifndef ENGINE_VIDEO_VIDEO_H
#define ENGINE_VIDEO_VIDEO_H

namespace engine
{
namespace video
{

void beginFrame();
void endFrame();

/* private */
void open();
void close();

} // video
} // engine

#endif // ENGINE_VIDEO_VIDEO_H


