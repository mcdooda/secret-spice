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
		
		const std::vector<essentia::Real>& getTicks() const { return m_ticks; }
		
	private:
		std::string m_inputFileName;
		
		std::vector<essentia::Real> m_ticks;
};

} // game

#endif // GAME_AUDIO_ANALYZER_H


