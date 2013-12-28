#include <GL/gl.h>
#include "polygon.h"

namespace engine
{
namespace geometry
{

Polygon::Polygon(const std::vector<Vector2d>& vertices)
{
	initVertices(vertices);
}

Polygon::~Polygon()
{
	delete m_vertices;
}

void Polygon::show()
{
    glVertexPointer(2, GL_FLOAT, 0, m_vertices);
    glDrawArrays(GL_POLYGON, 0, m_numVertices);
}

Polygon::Polygon()
{
	
}

void Polygon::initVertices(const std::vector<Vector2d>& vertices)
{
	m_numVertices = vertices.size();
	m_vertices = new float[m_numVertices * 2];
	int i = 0;
	for (std::vector<Vector2d>::const_iterator it = vertices.begin(); it != vertices.end(); it++)
	{
		m_vertices[i * 2]     = it->getX();
		m_vertices[i * 2 + 1] = it->getY();
		i++;
	}
}

} // geometry
} // engine


