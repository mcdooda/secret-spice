#ifndef ENGINE_INPUT_WINDOW_H
#define ENGINE_INPUT_WINDOW_H

#include <SDL/SDL.h>

namespace engine
{
namespace input
{
namespace window
{

bool closed();
bool resized();

/* private */
void clearEvents();
void addEvent(const SDL_Event& e);

void open();
void close();

} // window
} // input
} // engine

#endif // ENGINE_INPUT_WINDOW_H


