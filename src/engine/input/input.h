#ifndef ENGINE_INPUT_INPUT_H
#define ENGINE_INPUT_INPUT_H

namespace engine
{
namespace input
{

void poll();
void clearAll();

/* private */
void open();
void close();

} // input
} // engine

#endif // ENGINE_INPUT_INPUT_H


