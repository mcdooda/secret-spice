#include "view.h"
#include "window.h"

namespace engine
{
namespace video
{

View::View()
{
	
}

void View::zoom(float factor)
{
	m_viewMatrix.scale(factor);
}

void View::move(geometry::Vector2 move)
{
	m_viewMatrix.translate(move);
}

void View::updateProjectionMatrix(const geometry::Vector2& windowSize)
{
	float halfWidth = windowSize.getX() / 2;
	float halfHeight = windowSize.getY() / 2;
	m_projectionMatrix.setOrtho(-halfWidth, halfWidth, -halfHeight, halfHeight);
}

engine::geometry::Vector2 View::getRelativePosition(const geometry::Vector2& windowPosition) const
{
	/*return engine::geometry::Vector2(
		m_left + (m_right - m_left) * (windowPosition.getX() / windowSize.getX()),
		m_bottom + (m_top - m_bottom) * (windowPosition.getY() / windowSize.getY())
	);*/
	return geometry::Vector2();
}

} // video
} // engine


