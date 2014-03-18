#ifndef GAME_SPECTRUM_H
#define GAME_SPECTRUM_H

#include <essentia/essentia.h>

#include "../engine/game.h"

namespace game
{

class Spectrum
{
	public:
		Spectrum(const std::vector<essentia::Real>& spectrum, essentia::Real strongPeak);
		~Spectrum();
		
		inline const geometry::Vector2& getMax() const { return m_max; }
		inline const std::vector<essentia::Real>& getSpectrum() const { return m_spectrum; }
		inline essentia::Real getStrongPeak() const { return m_strongPeak; }
		
	private:
		void computeMax();
		
	private:
		std::vector<essentia::Real> m_spectrum;
		essentia::Real m_strongPeak;
		geometry::Vector2 m_max;
};

} // game

#endif // GAME_SPECTRUM_H


