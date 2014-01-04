#include <cmath>
#include <cstdlib>
#include "circle.h"

namespace engine
{
namespace geometry
{

Circle::Circle(Vector2d center, float radius) : Polygon(),
	m_center(center),
	m_radius(radius)
{
	buildCircle();
}

Circle::Circle() : Polygon()
{
	
}

void Circle::setCenter(Vector2d center)
{
	m_center = center;
	buildCircle();
}

void Circle::setRadius(float radius)
{
	m_radius = radius;
	buildCircle();
}

void Circle::buildCircle()
{
	const int numVertices = 20;
	std::vector<Vector2d> vertices;
	for (int i = 0; i < numVertices; i++)
	{
		Vector2d vertex(
			m_center.getX() + cos(M_PI * 2 * (float) i / numVertices) * m_radius,
			m_center.getY() + sin(M_PI * 2 * (float) i / numVertices) * m_radius
		);
		vertices.push_back(vertex);
	}
	initVertices(vertices);
}

} // geometry
} // engine


