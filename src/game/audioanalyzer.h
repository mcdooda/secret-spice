#ifndef GAME_AUDIO_ANALYZER_H
#define GAME_AUDIO_ANALYZER_H

#include <string>
#include <essentia/streaming/algorithms/poolstorage.h>

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
		
		const std::vector<essentia::Real>& getSpectrum(float time) const;
		
	private:
		std::string m_inputFileName;
		
		essentia::Real m_duration;
		std::vector<essentia::Real> m_ticks;
		std::vector<std::vector<essentia::Real> > m_spectrums;
};

} // game

#endif // GAME_AUDIO_ANALYZER_H


