#include <iostream>
#include "audio.h"

namespace engine
{
namespace audio
{

Audio::Audio()
{
	fmodCheck(FMOD::System_Create(&m_fmodSystem));
	fmodCheck(m_fmodSystem->init(32, FMOD_INIT_NORMAL, 0));
}

Audio::~Audio()
{
	fmodCheck(m_fmodSystem->release());
}

void Audio::beginFrame()
{
	m_fmodSystem->update();
}

Music* Audio::loadMusic(std::string filename)
{
	FMOD::Sound* sound;
	m_fmodSystem->createStream(filename.c_str(), FMOD_SOFTWARE | FMOD_LOOP_NORMAL, 0, &sound);
	return new Music(this, sound);
}

void Audio::fmodCheck(FMOD_RESULT result) {
	if (result != FMOD_OK)
		std::cerr << "Warning: fmod error: " << FMOD_ErrorString(result) << std::endl;
}

} // audio
} // engine


