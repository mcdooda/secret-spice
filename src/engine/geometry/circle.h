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
		Circle();
		
		void setCenter(Vector2d center);
		void setRadius(float radius);
		
		inline const Vector2d& getCenter() const { return m_center; }
		inline float getRadius() const { return m_radius; }
		
	private:
		void buildCircle();
		
	private:
		Vector2d m_center;
		float m_radius;
};

} // geometry
} // engine

#endif // ENGINE_GEOMETRY_CIRCLE_H


