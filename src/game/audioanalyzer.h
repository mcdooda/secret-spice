#ifndef GAME_AUDIO_ANALYZER_H
#define GAME_AUDIO_ANALYZER_H

#include <string>
#include <essentia/essentia.h>

#include "spectrum.h"

namespace game
{

class AudioAnalyzer
{
	public:
		AudioAnalyzer();
		~AudioAnalyzer();
		
		static void open();
		static void close();
		
		void setInputFileName(std::string inputFileName) { m_inputFileName = inputFileName; }
		void analyze();
		
		essentia::Real getDuration() const { return m_duration; }
		const std::vector<essentia::Real>& getTicks() const { return m_ticks; }
		
		void getSpectrum(float time, Spectrum** spectrum) const;
		
		inline essentia::Real getMaxAverage() const { return m_maxAverage; }
		
	private:
		void computeMaxAverage();
		
	private:
		std::string m_inputFileName;
		
		essentia::Real m_duration;
		std::vector<essentia::Real> m_ticks;
		std::vector<Spectrum> m_spectrums;
		essentia::Real m_maxAverage;
};

} // game

#endif // GAME_AUDIO_ANALYZER_H


