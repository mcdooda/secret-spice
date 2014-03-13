#include <cstring>
#include "rectangle.h"

namespace engine
{
namespace geometry
{

Rectangle::Rectangle(const Vector2& position, const Vector2& size)
{
	setPositionSize(position, size);
}

Rectangle::Rectangle()
{
	setPositionSize(Vector2(), Vector2());
}

Rectangle::~Rectangle()
{
	
}

void Rectangle::setPositionSize(const Vector2& position, const Vector2& size)
{
	std::vector<Vector2> vertices;
	vertices.push_back(position);
	vertices.push_back(Vector2(position.getX() + size.getX(), position.getY()));
	vertices.push_back(position + size);
	vertices.push_back(Vector2(position.getX(), position.getY() + size.getY()));
	initVertices(vertices);
}

void Rectangle::setSize(const Vector2& size)
{
	Vector2 position = getPosition();
	setPositionSize(position, size);
}

Vector2 Rectangle::getSize() const
{
	float width = m_vertices[1].getX() - m_vertices[0].getX();
	float height = m_vertices[3].getY() - m_vertices[0].getY();
	return Vector2(width, height);
}

void Rectangle::setPosition(const Vector2& position)
{
	Vector2 size = getSize();
	setPositionSize(position, size);
}

Vector2 Rectangle::getPosition()
{
	return m_vertices[0];
}

} // geometry
} // engine


