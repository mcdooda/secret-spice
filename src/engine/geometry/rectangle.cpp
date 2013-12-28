#include "rectangle.h"

namespace engine
{
namespace geometry
{

Rectangle::Rectangle(Vector2d position, Vector2d size)
{
	std::vector<Vector2d> vertices;
	vertices.push_back(position);
	vertices.push_back(Vector2d(position.getX() + size.getX(), position.getY()));
	vertices.push_back(position + size);
	vertices.push_back(Vector2d(position.getX(), position.getY() + size.getY()));
	initVertices(vertices);
}

} // geometry
} // engine


