#ifndef ENGINE_AUDIO_MUSIC_H
#define ENGINE_AUDIO_MUSIC_H

#include <fmod/fmod.hpp>
#include "audio.h"
#include "spectrum.h"

namespace engine
{
namespace audio
{
class Audio;
class Spectrum;

class Music
{
	public:
		Music(Audio* audio, FMOD::Sound* sound);
		~Music();
		
		void play();
		
		Spectrum* getSpectrum();
		
	private:
		Audio* m_audio;
		FMOD::Sound* m_sound;
		FMOD::Channel* m_musicChannel;
		Spectrum* m_spectrum;
};

} // audio
} // engine

#endif // ENGINE_AUDIO_MUSIC_H


