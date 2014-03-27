#ifndef ENGINE_THREAD_H
#define ENGINE_THREAD_H

#include <SDL2/SDL.h>
#include <string>

namespace engine
{
namespace thread
{

extern "C" int runTask(void* thread);

class Thread
{
	public:
		enum State {
			NEW,
			RUNNING,
			DONE
		};
		enum Priority {
			LOW = SDL_THREAD_PRIORITY_LOW,
			NORMAL = SDL_THREAD_PRIORITY_NORMAL,
			HIGH = SDL_THREAD_PRIORITY_HIGH
		};
		
	public:
		Thread();
		virtual ~Thread();
		
		virtual void task() = 0;
		
		void run();
		void wait();
		void setPriority(Priority priority);
		
		friend int runTask(void* thread);
		
	private:
		std::string getNewThreadName();
		
	private:
		SDL_Thread* m_thread;
		State m_state;
		Priority m_priority;
		
		static int count;
};

} // thread
} // engine

#endif // ENGINE_THREAD_H


