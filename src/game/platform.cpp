#include "platform.h"

namespace game
{

Platform::Platform(const geometry::Rectangle& rectangle, const geometry::Vector2& center, float angle, float angleY, float time, const video::Color& color) :
	m_rectangle(rectangle),
	m_center(center),
	m_angle(angle),
	m_angleY(angleY),
	m_time(time),
	m_color(color)
{
	
}

Platform::~Platform()
{
	
}

void Platform::draw(video::Attribute vertexAttribute, const video::Uniform& colorUniform)
{
	colorUniform.setColor(m_color);
	m_rectangle.draw(vertexAttribute);
}

} // game


