#pragma once
#include <mutex>

class Mutex
{
public:
	/*
	 *Mutex() { InitializeCriticalSection(&m_mutex); }
	 *~Mutex() { DeleteCriticalSection(&m_mutex); }
	 */
	Mutex() =default;
	~Mutex() =default;

	void lock() { m_mutex.lock(); }
	void unlock() { m_mutex.unlock(); }

protected:
	//CRITICAL_SECTION m_mutex;
	std::mutex m_mutex;
};

class scoped_lock
{
public:
	scoped_lock(Mutex& mtx) : m_mtx(mtx) { m_mtx.lock(); }
	~scoped_lock() { m_mtx.unlock(); }

protected:
	Mutex& m_mtx;
};
