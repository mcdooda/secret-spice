#ifndef GAME_SPECTRUM_H
#define GAME_SPECTRUM_H

#include <essentia/essentia.h>

#include "../engine/game.h"

namespace game
{

class Spectrum
{
	public:
		Spectrum(const std::vector<essentia::Real>& spectrum);
		~Spectrum();
		
		inline const geometry::Vector2& getMax() const { return m_max; }
		
	private:
		void computeMax();
		
	private:
		std::vector<essentia::Real> m_spectrum;
		geometry::Vector2 m_max;
};

} // game

#endif // GAME_SPECTRUM_H


