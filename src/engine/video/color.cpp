#include <GL/glew.h>
#include "color.h"

namespace engine
{
namespace video
{

Color Color::WHITE = Color(255);
Color Color::BLACK = Color(0);

Color::Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a) :
	m_r(r),
	m_g(g),
	m_b(b),
	m_a(a)
{

}

Color::Color(unsigned char gray) :
	m_r(gray),
	m_g(gray),
	m_b(gray),
	m_a(255)
{
	
}

void Color::use()
{
	glColor4ub(m_r, m_g, m_b, m_a);
}

void Color::unuse()
{
	WHITE.use();
}

void Color::clear()
{
	glClearColor(m_r / 255.f, m_g / 255.f, m_b / 255.f, 0);
}

Color* Color::newCopy()
{
	return new Color(m_r, m_g, m_b, m_a);
}

} // video
} // engine


