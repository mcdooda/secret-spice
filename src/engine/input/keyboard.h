#ifndef ENGINE_INPUT_KEYBOARD_H
#define ENGINE_INPUT_KEYBOARD_H

#include <vector>
#include <SDL/SDL.h>

#define K(k) SDLK_##k

namespace engine
{
namespace input
{

typedef SDLKey Key;

class Keyboard
{
	public:
		Keyboard();
		~Keyboard();
		
		bool isPressed(Key k);
		bool isJustPressed(Key k);
		bool isJustReleased(Key k);

		std::vector<Key> getPressedKeys();
		std::vector<Key> getJustPressedKeys();
		std::vector<Key> getJustReleasedKeys();

		Uint16* getUnicodeText(int* length);

		void clearEvents();
		void addEvent(const SDL_Event& e);
		
	private:
		int m_numKeys;
		bool* m_justPressedKeys;
		bool* m_justReleasedKeys;

		Uint16 m_unicodeText[SDLK_LAST];
		int m_unicodeLength;
};

} // input
} // engine

#endif // ENGINE_INPUT_KEYBOARD_H


