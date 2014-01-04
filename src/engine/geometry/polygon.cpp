#include <cstring>
#include <GL/gl.h>
#include "polygon.h"

namespace engine
{
namespace geometry
{

Polygon::Polygon(const std::vector<Vector2d>& vertices) :
	m_vertices(NULL),
	m_numVertices(0)
{
	initVertices(vertices);
}

Polygon::Polygon(const Polygon& polygon)
{
	*this = polygon;
}

void Polygon::operator=(const Polygon& polygon)
{
	m_numVertices = polygon.m_numVertices;
	m_vertices = new float[m_numVertices * 2];
	memcpy(m_vertices, polygon.m_vertices, m_numVertices * 2 * sizeof(float));
}

Polygon::~Polygon()
{
	delete m_vertices;
}

void Polygon::draw()
{
	if (m_numVertices > 0)
	{
		glVertexPointer(2, GL_FLOAT, 0, m_vertices);
		glDrawArrays(GL_POLYGON, 0, m_numVertices);
    }
}

Polygon::Polygon() :
	m_vertices(NULL),
	m_numVertices(0)
{
	
}

void Polygon::initVertices(const std::vector<Vector2d>& vertices)
{
	if (vertices.size() != m_numVertices)
	{
		delete m_vertices;
		m_numVertices = vertices.size();
		m_vertices = new float[m_numVertices * 2];
	}
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


