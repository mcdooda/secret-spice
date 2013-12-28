#ifndef ENGINE_GEOMETRY_RECTANGLE_H
#define ENGINE_GEOMETRY_RECTANGLE_H

#include "polygon.h"

namespace engine
{
namespace geometry
{

class Rectangle : public Polygon
{
	public:
		Rectangle(Vector2d position, Vector2d size);
		
		inline float getWidth()  const { return m_vertices[3] - m_vertices[0]; }
		inline float getHeight() const { return m_vertices[7] - m_vertices[1]; }
		
};

} // geometry
} // engine

#endif // ENGINE_GEOMETRY_RECTANGLE_H


