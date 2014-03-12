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
		Rectangle(const Vector2& position, const Vector2& size);
		Rectangle();
		virtual ~Rectangle();
		
		void setPositionSize(const Vector2& position, const Vector2& size);
		
		void setSize(const Vector2& size);
		Vector2 getSize() const;
		
		void setPosition(const Vector2& position);
		Vector2 getPosition();
		
};

} // geometry
} // engine

#endif // ENGINE_GEOMETRY_RECTANGLE_H


