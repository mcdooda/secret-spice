#ifndef ENGINE_VIDEO_VIEW_H
#define ENGINE_VIDEO_VIEW_H

#include "../geometry/vector2d.h"

namespace engine
{
namespace video
{

class View
{
	public:
		View(geometry::Vector2d center, float scale);
		View();

		void zoom(float factor, float minOrMax);
		void move(geometry::Vector2d position);
		inline void setCenter(geometry::Vector2d center) { m_center = center; }
		inline void setScale(float scale) { m_scale = scale; }

		inline geometry::Vector2d getCenter() const { return m_center; }
		inline float getScale() const { return m_scale; }

		inline float getLeft()   const { return m_left; }
		inline float getRight()  const { return m_right; }
		inline float getBottom() const { return m_bottom; }
		inline float getTop()	 const { return m_top; }

		inline float getWidth()  const { return m_width; }
		inline float getHeight() const { return m_height; }
		
		geometry::Vector2d getRelativePosition(const geometry::Vector2d& windowPosition, const geometry::Vector2d& windowSize) const;

		void updateBorders(geometry::Vector2d windowSize);

	private:

		geometry::Vector2d m_center;
		float m_scale;

		float m_left;
		float m_right;
		float m_bottom;
		float m_top;

		float m_width;
		float m_height;
};

} // video
} // engine

#endif // ENGINE_VIDEO_VIEW_H


