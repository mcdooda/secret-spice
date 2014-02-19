#include <essentia/algorithmfactory.h>
#include <essentia/streaming/algorithms/poolstorage.h>
#include <essentia/scheduler/network.h>
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
	essentia::Pool pool, pool2;
	
	essentia::streaming::AlgorithmFactory& factory = essentia::streaming::AlgorithmFactory::instance();
	
	essentia::streaming::Algorithm* monoloader = factory.create(
		"MonoLoader",
		"filename", m_inputFileName,
		"sampleRate", 44100.0
	);
	
	essentia::streaming::Algorithm* rhythmextractor = factory.create(
		"RhythmExtractor2013",
		"method", "multifeature"
	);
	
	monoloader->output("audio")				>> rhythmextractor->input("signal");
	rhythmextractor->output("ticks")		>> PC(pool, "rhythm.ticks");
	rhythmextractor->output("confidence")	>> PC(pool, "rhythm.ticks_confidence");
	rhythmextractor->output("bpm")			>> PC(pool, "rhythm.bpm");
	rhythmextractor->output("estimates")	>> PC(pool, "rhythm.estimates");
	rhythmextractor->output("bpmIntervals")	>> PC(pool, "rhythm.bpmIntervals");
	
	essentia::scheduler::Network network(monoloader);
	network.run();
	
	m_ticks = pool.value<std::vector<essentia::Real> >("rhythm.ticks");
	
	/*
	essentia::streaming::Algorithm* monoloader2 = factory.create(
		"MonoLoader",
		"filename", m_inputFileName,
		"sampleRate", 44100.0
	);
	
	essentia::streaming::Algorithm* rhythmextractor2 = factory.create(
		"BeatsLoudness",
		"sampleRate", 44100.0,
		"beats", m_ticks
	);
	
	monoloader2->output("audio")				>> rhythmextractor2->input("signal");
	rhythmextractor2->output("loudness")	>> PC(pool2, "loudness");
	rhythmextractor2->output("loudnessBandRatio")	>> PC(pool2, "rhythm.loudnessBandRatio");
	
	essentia::scheduler::Network network2(monoloader);
	network2.run();
	
	//std::cout << "bpm: " << pool.value<essentia::Real>("rhythm.bpm") << std::endl;
	//std::cout << "ticks: " << pool.value<std::vector<essentia::Real> >("rhythm.ticks") << std::endl;
	//std::cout << "ticks detection confidence: " << pool.value<essentia::Real>("rhythm.ticks_confidence") << std::endl; 
	//std::cout << "estimates: " << pool.value<std::vector<essentia::Real> >("rhythm.estimates") << std::endl;
	//std::cout << "bpmIntervals: " << pool.value<std::vector<essentia::Real> >("rhythm.bpmIntervals") << std::endl;
	
	
	for (std::vector<essentia::Real>::iterator it = m_ticks.begin(); it != m_ticks.end(); it++)
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;
	
	std::vector<std::string> names = pool2.descriptorNames();
	for (std::vector<std::string>::iterator it = names.begin(); it != names.end(); it++)
	{
		std::cout << *it << " ";
	}
	std::cout << "(" << names.size() << ")" << std::endl;*/
}

} // game


