#include "thread.h"

namespace engine
{
namespace thread
{

int Thread::count = 0;

// thread function
int runTask(void* thread)
{
	Thread* t = (Thread*) thread;
	SDL_SetThreadPriority((SDL_ThreadPriority) t->m_priority);
	t->task();
	return 0;
}

Thread::Thread() :
	m_thread(NULL),
	m_state(NEW),
	m_priority(NORMAL)
{
	
}

Thread::~Thread()
{
	
}

void Thread::run()
{
	m_thread = SDL_CreateThread(runTask, getNewThreadName().c_str(), this);
}

void Thread::wait()
{
	SDL_WaitThread(m_thread, NULL);
}

void Thread::setPriority(Priority priority)
{
	m_priority = priority;
	if (m_state == RUNNING)
		SDL_SetThreadPriority((SDL_ThreadPriority) priority);
}

std::string Thread::getNewThreadName()
{
	std::string threadName = "Thread-" + count;
	count++;
	return threadName;
}

} // thread
} // engine


