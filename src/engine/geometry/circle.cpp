#include <cmath>
#include "circle.h"

namespace engine
{
namespace geometry
{

Circle::Circle(Vector2d center, float radius)
{
	const int numVertices = 20;
	std::vector<Vector2d> vertices;
	for (int i = 0; i < numVertices; i++)
	{
		Vector2d vertex(
			center.getX() + cos(M_PI * 2 * (float) i / numVertices) * radius,
			center.getY() + sin(M_PI * 2 * (float) i / numVertices) * radius
		);
		vertices.push_back(vertex);
	}
	initVertices(vertices);
}

} // geometry
} // engine


