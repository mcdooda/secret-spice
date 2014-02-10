#include "platform.h"

namespace game
{

Platform::Platform(const geometry::Rectangle& rectangle, float time, const video::Color& color) :
	m_rectangle(rectangle),
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


