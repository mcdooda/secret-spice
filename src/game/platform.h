#ifndef GAME_PLATFORM_H
#define GAME_PLATFORM_H

#include "../engine/game.h"

namespace game
{

class Platform
{
	public:
		Platform(const geometry::Rectangle& rectangle, float time, const video::Color& color);
		~Platform();
		
		void draw(video::Attribute vertexAttribute, const video::Uniform& colorUniform);
		
		inline float getTime() const { return m_time; }
		inline const video::Color& getColor() const { return m_color; }
		
	private:
		geometry::Rectangle m_rectangle;
		float m_time;
		video::Color m_color;
};

} // game

#endif // GAME_LEVEL_G


