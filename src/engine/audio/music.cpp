#include "music.h"
#include "audio.h"

namespace engine
{
namespace audio
{

Music::Music(Audio* audio, FMOD::Sound* sound) :
	m_audio(audio),
	m_sound(sound),
	m_musicChannel(NULL),
	m_spectrum(NULL)
{
	
}

Music::~Music()
{
	if (m_musicChannel != NULL)
		Audio::fmodCheck(m_musicChannel->stop());
	
	Audio::fmodCheck(m_sound->release());
	
	if (m_spectrum != NULL)
		delete m_spectrum;
}

void Music::play()
{
	Audio::fmodCheck(m_audio->m_fmodSystem->playSound(FMOD_CHANNEL_FREE, m_sound, false, &m_musicChannel));
}

Spectrum* Music::getSpectrum()
{
	if (m_spectrum == NULL)
		m_spectrum = new Spectrum();
	
	m_musicChannel->getSpectrum(m_spectrum->m_spectrum, Spectrum::SPECTRUM_SIZE, 0, FMOD_DSP_FFT_WINDOW_RECT);
	return m_spectrum;
}

} // audio
} // engine


