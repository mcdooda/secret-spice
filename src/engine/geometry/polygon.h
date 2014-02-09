#ifndef ENGINE_VIDEO_POLYGON_H
#define ENGINE_VIDEO_POLYGON_H

#include <vector>
#include "vector2.h"
#include "../video/attribute.h"

namespace engine
{
namespace geometry
{

class Polygon
{
	public:
		Polygon(const std::vector<Vector2>& vertices);
		Polygon(const Polygon& polygon);
		void operator=(const Polygon& polygon);
		virtual ~Polygon();
		
		void draw(video::Attribute vertexAttribute);
		
	protected:
		Polygon();
		
		void initVertices(const std::vector<Vector2>& vertices);
		
	protected:
		float* m_vertices;
		unsigned int m_numVertices;
};

} // geometry
} // engine

#endif // ENGINE_VIDEO_POLYGON_H


