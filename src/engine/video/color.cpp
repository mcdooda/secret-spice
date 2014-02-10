#include "color.h"

namespace engine
{
namespace video
{

Color Color::WHITE = Color(1.0f);
Color Color::BLACK = Color(0.0f);

Color::Color(GLfloat r, GLfloat g, GLfloat b, GLfloat a) :
	m_r(r),
	m_g(g),
	m_b(b),
	m_a(a)
{

}

Color::Color(GLfloat gray) :
	m_r(gray),
	m_g(gray),
	m_b(gray),
	m_a(1.0f)
{
	
}

Color* Color::newCopy()
{
	return new Color(m_r, m_g, m_b, m_a);
}

} // video
} // engine


