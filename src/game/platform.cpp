#include <iostream>
#include "platform.h"

namespace game
{

Platform::Platform(const geometry::Rectangle& rectangle, const geometry::Vector2& center, float angle, float angleY, float time, const video::Color& color, bool strongPeak) :
	m_rectangle(rectangle),
	m_center(center),
	m_angle(angle),
	m_angleY(angleY),
	m_time(time),
	m_color(color),
	m_strongPeak(strongPeak)
{
	
}

Platform::~Platform()
{
	
}

void Platform::draw(video::Attribute positionAttribute, video::Attribute uvAttribute, const video::Uniform& colorUniform)
{
	colorUniform.setColor(m_color);
	m_rectangle.draw(positionAttribute, uvAttribute);
}

} // game


