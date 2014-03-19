#include <essentia/essentiamath.h>
#include "audioanalyzer.h"

namespace game
{

using namespace essentia;

AudioAnalyzer::AudioAnalyzer() :
	m_loaded(false)
{
	
}

AudioAnalyzer::~AudioAnalyzer()
{
	
}

void AudioAnalyzer::open()
{
	essentia::init();
}

void AudioAnalyzer::close()
{
	essentia::shutdown();
}

void AudioAnalyzer::loadAlgorithms()
{
	essentia::standard::AlgorithmFactory& factory = essentia::standard::AlgorithmFactory::instance();
	
	/*
	 * MonoLoader
	 */
	essentia::standard::Algorithm* monoLoader = factory.create(
		"MonoLoader",
		"filename", m_inputFileName
	);
	m_audioBuffer = new std::vector<essentia::Real>();
	
	// -->
	monoLoader->output("audio").set(*m_audioBuffer);
	
	monoLoader->compute();
	delete monoLoader;
	
	/*
	 * Duration
	 */
	essentia::standard::Algorithm* duration = factory.create("Duration");
	
	// <--
	duration->input("signal").set(*m_audioBuffer);
	
	// -->
	duration->output("duration").set(m_duration);
	
	duration->compute();
	delete duration;
	
	/*
	 * RhythmExtractor2013
	 */
	essentia::standard::Algorithm* rhythmExtractor = factory.create(
		"RhythmExtractor2013",
		"method", "multifeature"
	);
	
	// <--
	rhythmExtractor->input("signal").set(*m_audioBuffer);
	
	// -->
	essentia::Real bpm;
	essentia::Real confidence;
	std::vector<essentia::Real> estimates;
	std::vector<essentia::Real> bpmIntervals;
	rhythmExtractor->output("bpm").set(bpm);
	rhythmExtractor->output("ticks").set(m_ticks);
	rhythmExtractor->output("confidence").set(confidence);
	rhythmExtractor->output("estimates").set(estimates);
	rhythmExtractor->output("bpmIntervals").set(bpmIntervals);
	
	// compute
	rhythmExtractor->compute();
	delete rhythmExtractor;
	
	/*
	 * FrameCutter
	 */
	m_frameCutter = factory.create(
		"FrameCutter",
		"hopSize", 2048,
		"frameSize", 4096
	);
	m_frame = new std::vector<essentia::Real>();
	
	// <--
	m_frameCutter->input("signal").set(*m_audioBuffer);
	
	// -->
	m_frameCutter->output("frame").set(*m_frame);
	
	/*
	 * Windowing
	 */
	m_windowing = factory.create(
		"Windowing",
		"type", "blackmanharris62"
	);
	m_windowedFrame = new std::vector<essentia::Real>();
	
	// <--
	m_windowing->input("frame").set(*m_frame);
	
	// -->
	m_windowing->output("frame").set(*m_windowedFrame);
	
	/*
	 * Spectrum
	 */
	m_spectrum = factory.create(
		"Spectrum",
		"size", 4096
	);
	m_spectrumBuffer = new std::vector<essentia::Real>();
	
	// <--
	m_spectrum->input("frame").set(*m_windowedFrame);
	
	// -->
	m_spectrum->output("spectrum").set(*m_spectrumBuffer);
	
	/*
	 * StrongPeak
	 */
	m_strongPeak = factory.create(
		"StrongPeak"
	);
	
	// <--
	m_strongPeak->input("spectrum").set(*m_spectrumBuffer);
	
	// -->
	m_strongPeak->output("strongPeak").set(m_strongPeakValue);
}

void AudioAnalyzer::analyzeStep()
{
	for (int i = 0; i < 20; i++)
	{
		m_frameCutter->compute();
		
		if (!m_frame->size())
		{
			m_loaded = true;
			break;
		}
			
		if (essentia::isSilent(*m_frame))
			continue;
		
		m_windowing->compute();
		m_spectrum->compute();
		m_strongPeak->compute();
		m_spectrums.push_back(Spectrum(*m_spectrumBuffer, m_strongPeakValue));
	}
}

void AudioAnalyzer::computeMaxAverage()
{
	m_maxAverage = 0;
	for (std::vector<Spectrum>::iterator it = m_spectrums.begin(); it != m_spectrums.end(); it++)
		m_maxAverage += it->getMax().getY();
		
	m_maxAverage /= m_spectrums.size();
}

void AudioAnalyzer::freeAlgorithms()
{
	// algorithms' data
	delete m_audioBuffer;
	delete m_frame;
	delete m_windowedFrame;
	delete m_spectrumBuffer;
	
	// algorithms
	delete m_frameCutter;
	delete m_windowing;
	delete m_spectrum;
	delete m_strongPeak;
}

void AudioAnalyzer::getSpectrum(float time, Spectrum** spectrum) const
{
	unsigned int index = floor(time / m_duration * m_spectrums.size());
	
	if (index < m_spectrums.size())
		*spectrum = (Spectrum*) &m_spectrums[index];
	
	else
		*spectrum = NULL;
}

} // game


