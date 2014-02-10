#ifndef AUDIO_AUDIO_H
#define AUDIO_AUDIO_H

#include <string>
#include <fmod/fmod.hpp>
#include <fmod/fmod_errors.h>
#include "music.h"

namespace engine
{
namespace audio
{

class Music;

class Audio
{
	public:
		Audio();
		~Audio();
		
		void beginFrame();
		
		Music* loadMusic(std::string filename);
		
		friend class Music;
		
	private:
		static void fmodCheck(FMOD_RESULT result);
		
	private:
		FMOD::System* m_fmodSystem;
};

} // audio
} // engine

#endif // AUDIO_AUDIO_H


