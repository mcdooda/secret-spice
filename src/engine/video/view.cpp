#include "view.h"
#include "window.h"

namespace engine
{
namespace video
{

View::View(geometry::Vector2d center, float scale) :
	m_center(center),
	m_scale(scale)
{

}

View::View() :
	m_center(0, 0),
	m_scale(1)
{

}

void View::zoom(float factor, float minOrMax)
{
	m_scale *= factor;

	if (factor < 1 && m_scale < minOrMax)
		m_scale = minOrMax;

	else if (factor > 1 && m_scale > minOrMax)
		m_scale = minOrMax;
}

void View::move(geometry::Vector2d move)
{
	m_center += move;
}

void View::updateBorders(geometry::Vector2d windowSize)
{
	float width = windowSize.getX();
	float height = windowSize.getY();
	m_left = m_center.getX() - width / 2 / m_scale;
	m_right = m_center.getX() + width / 2 / m_scale;
	m_bottom = m_center.getY() - height / 2 / m_scale;
	m_top = m_center.getY() + height / 2 / m_scale;
	m_width = width / m_scale;
	m_height = height / m_scale;
}

engine::geometry::Vector2d View::getRelativePosition(const geometry::Vector2d& windowPosition, const geometry::Vector2d& windowSize) const
{
	return engine::geometry::Vector2d(
		m_left + (m_right - m_left) * (windowPosition.getX() / windowSize.getX()),
		m_bottom + (m_top - m_bottom) * (windowPosition.getY() / windowSize.getY())
	);
}

} // video
} // engine


