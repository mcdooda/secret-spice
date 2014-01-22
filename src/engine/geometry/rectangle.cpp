#include "rectangle.h"

namespace engine
{
namespace geometry
{

Rectangle::Rectangle(Vector2 position, Vector2 size)
{
	std::vector<Vector2> vertices;
	vertices.push_back(position);
	vertices.push_back(Vector2(position.getX() + size.getX(), position.getY()));
	vertices.push_back(position + size);
	vertices.push_back(Vector2(position.getX(), position.getY() + size.getY()));
	initVertices(vertices);
}

} // geometry
} // engine


