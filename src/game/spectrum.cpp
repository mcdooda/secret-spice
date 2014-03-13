#include "spectrum.h"

namespace game
{

Spectrum::Spectrum(const std::vector<essentia::Real>& spectrum) :
	m_spectrum(spectrum)
{
	computeMax();
}

Spectrum::~Spectrum()
{
	
}

void Spectrum::computeMax()
{
	float max = 0;
	int i = 0;
	int imax = 0;
	for (std::vector<essentia::Real>::iterator it2 = m_spectrum.begin(); it2 != m_spectrum.end(); it2++)
	{
		if (*it2 > max)
		{
			max = *it2;
			imax = i;
		}
		i++;
	}
	m_max.setX((float) imax / m_spectrum.size());
	m_max.setY(max);
}

} // game


