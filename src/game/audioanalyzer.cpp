#include <essentia/algorithmfactory.h>
#include <essentia/essentiamath.h>
#include "audioanalyzer.h"

namespace game
{

using namespace essentia;

AudioAnalyzer::AudioAnalyzer()
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

void AudioAnalyzer::analyze()
{
	essentia::standard::AlgorithmFactory& factory = essentia::standard::AlgorithmFactory::instance();
	
	essentia::standard::Algorithm* monoLoader = factory.create(
		"MonoLoader",
		"filename", m_inputFileName
	);
	std::vector<essentia::Real> audioBuffer;
	
	// -->
	monoLoader->output("audio").set(audioBuffer);
	
	monoLoader->compute();
	delete monoLoader;
	
	essentia::standard::Algorithm* duration = factory.create("Duration");
	
	// <--
	duration->input("signal").set(audioBuffer);
	
	// -->
	duration->output("duration").set(m_duration);
	
	duration->compute();
	delete duration;
	
	essentia::standard::Algorithm* rhythmExtractor = factory.create(
		"RhythmExtractor2013",
		"method", "multifeature"
	);
	
	// <--
	rhythmExtractor->input("signal").set(audioBuffer);
	
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
	
	essentia::standard::Algorithm* frameCutter = factory.create(
		"FrameCutter"
	);
	std::vector<Real> frame;
	
	// <--
	frameCutter->input("signal").set(audioBuffer);
	
	// -->
	frameCutter->output("frame").set(frame);
	
	essentia::standard::Algorithm* windowing = factory.create(
		"Windowing",
		"type", "blackmanharris62"
	);
	std::vector<Real> windowedFrame;
	
	// <--
	windowing->input("frame").set(frame);
	
	// -->
	windowing->output("frame").set(windowedFrame);
	
	essentia::standard::Algorithm* spectrum = factory.create("Spectrum");
	std::vector<essentia::Real> spectrumBuffer;
	
	// <--
	spectrum->input("frame").set(windowedFrame);
	
	// -->
	spectrum->output("spectrum").set(spectrumBuffer);
	
	while (true) {
		frameCutter->compute();
		
		if (!frame.size())
			break;
			
		if (essentia::isSilent(frame))
			continue;

		windowing->compute();
		spectrum->compute();
		
		m_spectrums.push_back(Spectrum(spectrumBuffer));
	}
	
	delete frameCutter;
	delete windowing;
	delete spectrum;
	
	computeMaxAverage();
}

void AudioAnalyzer::getSpectrum(float time, Spectrum** spectrum) const
{
	unsigned int index = floor(time / m_duration * m_spectrums.size());
	
	if (index < m_spectrums.size())
		*spectrum = (Spectrum*) &m_spectrums[index];
	
	else
		*spectrum = NULL;
}

void AudioAnalyzer::computeMaxAverage()
{
	m_maxAverage = 0;
	for (std::vector<Spectrum>::iterator it = m_spectrums.begin(); it != m_spectrums.end(); it++)
		m_maxAverage += it->getMax().getY();
		
	m_maxAverage /= m_spectrums.size();
}

} // game


