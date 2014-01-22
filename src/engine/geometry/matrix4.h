#ifndef ENGINE_GEOMETRY_MATRIX4_H
#define ENGINE_GEOMETRY_MATRIX4_H

#include "vector2.h"

namespace engine
{
namespace geometry
{

class Matrix4
{
	public:
		Matrix4();
		Matrix4(const Matrix4& matrix4);
		void operator=(const Matrix4& matrix4);
		~Matrix4();
		
		Matrix4 operator*(const Matrix4& matrix4) const;
		
		Vector2 operator*(const Vector2& vector2) const;
		
		void setAll(float v00, float v01, float v02, float v03,
		            float v10, float v11, float v12, float v13,
		            float v20, float v21, float v22, float v23,
		            float v30, float v31, float v32, float v33);
		
		void setIdentity();
		
		void setOrtho(float left, float right, float bottom, float top, float near = -1.0f, float far = 1.0f);
		
		void setInverse();
		
		void scale(float scale);
		void scale(float scaleX, float scaleY, float scaleZ = 1.0f);
		
		void translate(const Vector2& vector2);
		void translate(float translateX, float translateY, float translateZ = 0.0f);
		
		void rotateX(float rotateX);
		void rotateY(float rotateY);
		void rotateZ(float rotateZ);
		
		inline float get(int y, int x) const { return m_matrix[y * 4 + x]; }
		inline void set(int y, int x, float value) { m_matrix[y * 4 + x] = value; }
		
		inline const float* getData() const { return m_matrix; }
		
		friend std::ostream& operator<<(std::ostream& out, Matrix4 matrix4);
	
	private:
		void copy(const Matrix4& matrix4);
	
	private:
		float m_matrix[4 * 4];
};

} // geometry
} // engine

#endif // ENGINE_GEOMETRY_MATRIX4_H


