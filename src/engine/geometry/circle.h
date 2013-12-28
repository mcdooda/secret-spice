#ifndef ENGINE_GEOMETRY_CIRCLE_H
#define ENGINE_GEOMETRY_CIRCLE_H

#include "polygon.h"

namespace engine
{
namespace geometry
{

class Circle : public Polygon
{
	public:
		Circle(Vector2d center, float radius);
};

} // geometry
} // engine

#endif // ENGINE_GEOMETRY_CIRCLE_H


