#include <iostream>
#include "keyboard.h"

namespace engine
{
namespace input
{

Keyboard::Keyboard()
{
	SDL_EnableUNICODE(1);
	SDL_GetKeyState(&m_numKeys);
	m_justPressedKeys = new bool[m_numKeys];
	m_justReleasedKeys = new bool[m_numKeys];
	m_unicodeLength = 0;
	clearEvents();
}

Keyboard::~Keyboard()
{
	delete m_justPressedKeys;
	delete m_justReleasedKeys;
}

bool Keyboard::isPressed(Key k)
{
	Uint8* m_pressedKeys = SDL_GetKeyState(NULL);
	return (bool) m_pressedKeys[k];
}

bool Keyboard::isJustPressed(Key k)
{
	return m_justPressedKeys[k];
}

bool Keyboard::isJustReleased(Key k)
{
	return m_justReleasedKeys[k];
}

Uint16* Keyboard::getUnicodeText(int* length)
{
	*length = m_unicodeLength;
	return m_unicodeText;
}

std::vector<Key> Keyboard::getPressedKeys()
{
	std::vector<Key> pressedKeysVector;
	Uint8* pressedKeys = SDL_GetKeyState(NULL);
	for (int k = 0; k < m_numKeys; k++)
	{
		if (pressedKeys[k])
			pressedKeysVector.push_back((Key) k);
	}
	return pressedKeysVector;
}

std::vector<Key> Keyboard::getJustPressedKeys()
{
	std::vector<Key> justPressedKeysVector;
	for (int k = 0; k < m_numKeys; k++)
	{
		if (m_justPressedKeys[k])
			justPressedKeysVector.push_back((Key) k);
	}
	return justPressedKeysVector;
}

std::vector<Key> Keyboard::getJustReleasedKeys()
{
	std::vector<Key> justReleasedKeysVector;
	for (int k = 0; k < m_numKeys; k++)
	{
		if (m_justReleasedKeys[k])
			justReleasedKeysVector.push_back((Key) k);
	}
	return justReleasedKeysVector;
}

void Keyboard::clearEvents()
{
	memset(m_justPressedKeys, 0, m_numKeys * sizeof(bool));
	memset(m_justReleasedKeys, 0, m_numKeys * sizeof(bool));
	m_unicodeLength = 0;
}

void Keyboard::addEvent(const SDL_Event& e)
{
	switch (e.type)
	{
		case SDL_KEYDOWN:
		m_justPressedKeys[e.key.keysym.sym] = 1;
		m_unicodeText[m_unicodeLength] = e.key.keysym.unicode;
		m_unicodeLength++;
		break;

		case SDL_KEYUP:
		m_justReleasedKeys[e.key.keysym.sym] = 1;
		break;
	}
}

} // input
} // engine


