#ifndef ENGINE_VIDEO_POLYGON_H
#define ENGINE_VIDEO_POLYGON_H

#include <vector>
#include "vector2d.h"

namespace engine
{
namespace geometry
{

class Polygon
{
	public:
		Polygon(const std::vector<Vector2d>& vertices);
		Polygon(const Polygon& polygon);
		void operator=(const Polygon& polygon);
		virtual ~Polygon();
		
		void draw();
		
	protected:
		Polygon();
		
		void initVertices(const std::vector<Vector2d>& vertices);
		
	protected:
		float* m_vertices;
		unsigned int m_numVertices;
};

} // geometry
} // engine

#endif // ENGINE_VIDEO_POLYGON_H


