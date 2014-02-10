#include <GL/glew.h>
#include "uniform.h"

namespace engine
{
namespace video
{

Uniform::Uniform(GLint uniformLocation) :
	m_uniformLocation(uniformLocation)
{
	
}

Uniform::Uniform() :
	m_uniformLocation(0)
{
	
}

Uniform::~Uniform()
{
	
}

void Uniform::setColor(const Color& color) const
{
	glUniform4f(m_uniformLocation, color.getR(), color.getG(), color.getB(), color.getA());
}

void Uniform::setVector2(const geometry::Vector2& vector2) const
{
	glUniform4f(m_uniformLocation, vector2.getX(), vector2.getY(), 0, 1);
}

void Uniform::setMatrix4(const geometry::Matrix4& matrix4) const
{
	glUniformMatrix4fv(m_uniformLocation, 1, GL_TRUE, matrix4.getData());
}

} // video
} // engine


