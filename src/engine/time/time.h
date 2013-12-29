#ifndef ENGINE_TIME_H
#define ENGINE_TIME_H

namespace engine
{
namespace time
{

class Time
{
	public:
		Time();
		~Time();
		
		void beginFrame();
		void endFrame();
		void setFrameRate(float rate);

		void sleep(float duration);
		float getRealTime();

		void pause();
		void resume();
		bool isPaused();

		float getTime();
		float getFrameTime();
		
	private:
		bool m_timePaused;
		float m_pauseTime;
		float m_pauseRealTime;
		float m_pauseElapsedTime;

		float m_frameTime;
		float m_beginFrameTime;
		float m_frameDuration;
};

} // time
} // engine

#endif // ENGINE_TIME_H


