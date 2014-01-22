#include <SDL2/SDL.h>
#include "time.h"

namespace engine
{
namespace time
{

Time::Time()
{
	m_timePaused = false;
	m_pauseElapsedTime = 0;
	setFrameRate(60.0f);
}

Time::~Time()
{

}

void Time::beginFrame()
{
	m_beginFrameTime = getRealTime();
}

void Time::endFrame()
{
	float endFrameTime = getRealTime();
	m_frameTime = endFrameTime - m_beginFrameTime;
	if (m_frameTime < m_frameDuration)
	{
		sleep(m_frameDuration - m_frameTime);
		m_frameTime = m_frameDuration;
	}
}

void Time::setFrameRate(float rate)
{
	m_frameDuration = 1.f / rate;
}

void Time::sleep(float duration)
{
	SDL_Delay(duration * 1000);
}

float Time::getRealTime()
{
	return SDL_GetTicks() / 1000.f;
}

void Time::pause()
{
	if (!m_timePaused)
	{
		m_pauseTime = getTime();
		m_pauseRealTime = getRealTime();
		m_timePaused = true;
	}
}

void Time::resume()
{
	m_timePaused = false;
	m_pauseElapsedTime += getRealTime() - m_pauseRealTime;
}

bool Time::isPaused()
{
	return m_timePaused;
}

float Time::getTime()
{
	return m_timePaused ? m_pauseTime : getRealTime() - m_pauseElapsedTime;
}

float Time::getFrameTime()
{
	return m_timePaused ? 0 : m_frameTime;
}

} // time
} // engine


