#include <cstring>
#include "spectrum.h"

namespace engine
{
namespace audio
{

Spectrum::Spectrum()
{
	memset(m_spectrum, 0, sizeof(m_spectrum));
}

Spectrum::Spectrum(const Spectrum& spectrum)
{
	*this = spectrum;
}

void Spectrum::operator=(const Spectrum& spectrum)
{
	memcpy(m_spectrum, spectrum.m_spectrum, sizeof(m_spectrum));
}

Spectrum::~Spectrum()
{
	
}

geometry::Vector2 Spectrum::getMax()
{
	int max = 0;
	for (int i = 1; i < SPECTRUM_SIZE; i++)
	{
		if (m_spectrum[i] > m_spectrum[max])
			max = i;
	}
	return geometry::Vector2((float) max / SPECTRUM_SIZE, m_spectrum[max]);
}

float Spectrum::getAverage()
{
	float total = 0;
	for (int i = 0; i < SPECTRUM_SIZE; i++)
		total += m_spectrum[i];
	
	return total / SPECTRUM_SIZE;
}

} // audio
} // engine


