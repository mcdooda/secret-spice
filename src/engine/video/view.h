#ifndef ENGINE_VIDEO_VIEW_H
#define ENGINE_VIDEO_VIEW_H

#include "../geometry/vector2.h"
#include "../geometry/matrix4.h"

namespace engine
{
namespace video
{

class View
{
	public:
		View();

		void zoom(float factor);
		void move(geometry::Vector2 position);
		
		geometry::Vector2 getRelativePosition(const geometry::Vector2& windowPosition) const;

		void updateProjectionMatrix(const geometry::Vector2& windowSize);
		
		inline const geometry::Matrix4& getProjectionMatrix() const { return m_projectionMatrix; }
		inline const geometry::Matrix4& getViewMatrix() const { return m_viewMatrix; }
		inline geometry::Matrix4 getViewProjectionMatrix() const { return m_projectionMatrix * m_viewMatrix; }

	private:
		geometry::Matrix4 m_projectionMatrix;
		geometry::Matrix4 m_viewMatrix;
};

} // video
} // engine

#endif // ENGINE_VIDEO_VIEW_H


