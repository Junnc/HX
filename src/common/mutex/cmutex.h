#pragma once
#include <mutex>

class CMutex
{
public:
	CMutex() =default;
	~CMutex() =default;

	void lock() { m_mutex.lock(); }
	void unlock() { m_mutex.unlock(); }

protected:
	//CRITICAL_SECTION m_mutex;
	std::mutex m_mutex;
};

class CScopedLock
{
public:
	CScopedLock(CMutex& mtx) : m_mtx(mtx) { m_mtx.lock(); }
	~CScopedLock() { m_mtx.unlock(); }

protected:
	CMutex& m_mtx;
};
