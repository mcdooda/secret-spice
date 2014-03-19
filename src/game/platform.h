#ifndef GAME_PLATFORM_H
#define GAME_PLATFORM_H

#include "../engine/game.h"

namespace game
{

class Platform
{
	public:
		Platform(const geometry::Rectangle& rectangle, const geometry::Vector2& center, float angle, float angleY, float time, const video::Color& color, bool strongPeak);
		~Platform();
		
		void draw(video::Attribute positionAttribute, video::Attribute uvAttribute, const video::Uniform& colorUniform);
		
		inline float getTime() const { return m_time; }
		
		inline const video::Color& getColor() const { return m_color; }
		inline void setColor(const video::Color& color) { m_color = color; }
		
		inline bool getStrongPeak() const { return m_strongPeak; }
		
		inline const geometry::Vector2 getSize() const { return m_rectangle.getSize(); }
		inline void setSize(const geometry::Vector2& size) { m_rectangle.setSize(size); }
		
		inline const geometry::Vector2& getCenter() const { return m_center; }
		
		inline float getAngle() const { return m_angle; }
		inline float getAngleY() const { return m_angleY; }
		
	private:
		geometry::Rectangle m_rectangle;
		geometry::Vector2 m_center;
		float m_angle;
		float m_angleY;
		float m_time;
		video::Color m_color;
		bool m_strongPeak;
};

} // game

#endif // GAME_LEVEL_G


