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
}

} // game


