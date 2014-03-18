#ifndef GAME_CHARACTER_H
#define GAME_CHARACTER_H

#include <iostream>

#include "../engine/game.h"

#include "spectrum.h"

namespace game
{

class Character
{
	public:
		Character();
		~Character();
		
		void setSpectrum(Spectrum* spectrum);
		
		void draw(video::Attribute vertexAttribute, const video::Uniform& colorUniform, const video::Uniform& centerUniform);
		
		inline void setPosition(const geometry::Vector2& position) { m_position = position; }
		inline const geometry::Vector2& getPosition() const { return m_position; }
		
	private:
		geometry::Polygon m_shape;
		geometry::Vector2 m_position;
};

} // game

#endif // GAME_CHARACTER_H


