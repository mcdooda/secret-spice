#include <cstring>
#include <GL/glew.h>
#include "polygon.h"

namespace engine
{
namespace geometry
{

Polygon::Polygon(const std::vector<Vector2>& vertices) :
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
	m_vertices = new Vector2[m_numVertices];
	memcpy(m_vertices, polygon.m_vertices, m_numVertices * sizeof(Vector2));
}

Polygon::~Polygon()
{
	delete m_vertices;
}

void Polygon::draw(video::Attribute vertexAttribute)
{
	if (m_numVertices > 0)
	{
		glEnableVertexAttribArray(vertexAttribute);
		glVertexAttribPointer(vertexAttribute, 2, GL_FLOAT, GL_FALSE, 0, m_vertices);
		glDrawArrays(GL_POLYGON, 0, m_numVertices);
		glDisableVertexAttribArray(vertexAttribute);
	}
}

void Polygon::transform(const Matrix4& matrix4)
{
	for (unsigned int i = 0; i < m_numVertices; i++)
		m_vertices[i] = matrix4 * m_vertices[i];
}

Polygon::Polygon() :
	m_vertices(NULL),
	m_numVertices(0)
{
	
}

void Polygon::initVertices(const std::vector<Vector2>& vertices)
{
	if (vertices.size() != m_numVertices)
	{
		delete m_vertices;
		m_numVertices = vertices.size();
		m_vertices = new Vector2[m_numVertices];
	}
	int i = 0;
	for (std::vector<Vector2>::const_iterator it = vertices.begin(); it != vertices.end(); it++)
	{
		m_vertices[i] = *it;
		i++;
	}
}

} // geometry
} // engine


