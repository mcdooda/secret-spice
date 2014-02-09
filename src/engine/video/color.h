#ifndef ENGINE_VIDEO_COLOR_H
#define ENGINE_VIDEO_COLOR_H

namespace engine
{
namespace video
{

class Color
{
	public:
		Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
		Color(unsigned char gray);

		inline unsigned char getR() const { return m_r; }
		inline unsigned char getG() const { return m_g; }
		inline unsigned char getB() const { return m_b; }
		inline unsigned char getA() const { return m_a; }

		inline void setR(unsigned char r) { m_r = r; }
		inline void setG(unsigned char g) { m_g = g; }
		inline void setB(unsigned char b) { m_b = b; }
		inline void setA(unsigned char a) { m_a = a; }
		
		Color* newCopy();
		
		static Color WHITE;
		static Color BLACK;

	protected:
		unsigned char m_r;
		unsigned char m_g;
		unsigned char m_b;
		unsigned char m_a;
};

} // video
} // engine

#endif // ENGINE_VIDEO_COLOR_H


