#ifndef ENGINE_AUDIO_SPECTRUM_H
#define ENGINE_AUDIO_SPECTRUM_H

#include "../geometry/vector2.h"
#include "music.h"

namespace engine
{
namespace audio
{
class Music;

class Spectrum
{
	public:
		Spectrum();
		Spectrum(const Spectrum& spectrum);
		void operator=(const Spectrum& spectrum);
		~Spectrum();
		
		geometry::Vector2 getMax();
		float getAverage();
		
		friend class Music;
		
	private:
		const static int SPECTRUM_SIZE = 128;
		float m_spectrum[SPECTRUM_SIZE];
};

} // audio
} // engine

#endif // ENGINE_AUDIO_SPECTRUM_H


