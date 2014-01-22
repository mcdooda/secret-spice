#include <GL/glew.h>
#include "uniform.h"

namespace engine
{
namespace video
{

Uniform::Uniform(int uniformLocation) :
	m_uniformLocation(uniformLocation)
{
	
}

Uniform::~Uniform()
{
	
}

void Uniform::setColor(const Color& color)
{
	glUniform4f(m_uniformLocation, color.getR() / 255.f, color.getG() / 255.f, color.getB() / 255.f, color.getA() / 255.f);
}

void Uniform::setVector2(const geometry::Vector2& vector2)
{
	glUniform4f(m_uniformLocation, vector2.getX(), vector2.getY(), 0, 1);
}

void Uniform::setMatrix4(const geometry::Matrix4& matrix4)
{
	glUniformMatrix4fv(m_uniformLocation, 1, GL_TRUE, matrix4.getData());
}

} // video
} // engine


