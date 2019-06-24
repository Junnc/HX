#pragma once
#include <list>
#include <thread>
#include <functional>
#include <memory>
#include <atomic>
#include "SyncQueue.hpp"

const int MaxTaskCount = 2000;

class ThreadPool
{
private:
	ThreadPool& operator=(const ThreadPool& other);

public:
	using Task = std::function<void()>;

	ThreadPool(): m_queue(MaxTaskCount){}

	~ThreadPool(void)
	{
		std::cout << "stop" << endl;
		Stop();
	}

	void Stop()
	{
		//保证多线程情况下只调用一次StopThreadGroup
		std::call_once(m_flag, [this] {StopThreadGroup(); });

	}

	void AddTask(Task&& task)
	{
		m_queue.Put(std::forward<Task>(task));
		std::cout << "add success,queueSize:"<<m_queue.Size() << endl;
	}

	void AddTask(const Task& task)
	{
		m_queue.Put(task);
		std::cout << "add success const" << endl;
	}

	void Start(int numThreads = std::thread::hardware_concurrency())
	{
		m_running = true;
		std::cout << "start,m_running:" << m_running << endl;
		//创建线程组
		for (int i = 0; i < numThreads; ++i)
		{
			m_threadgroup.push_back(std::make_shared<std::thread>(&ThreadPool::RunInThread, this));
		}
	}

private:
	void RunInThread()
	{
		std::cout << "execute,m_running:" << m_running << endl;
		while (m_running)
		{
			//取任务分别执行
			std::list<Task> list;
			Task task;
			m_queue.Take(task);
			std::cout << "execute,listSize:"<<list.size() <<",thread_id:"<< pthread_self() << endl;
			//for (auto& task : list)
			{
				if (!m_running)
					return;
				std::cout << "pre-execute" << endl;
				task();
				std::cout << "later_execute" << endl;
			}
		}
	}

	void StopThreadGroup()
	{
		m_queue.Stop();//让同步队列中的线程停止
		m_running = false; //置为false,让内部线程跳出循环并退出

		for (auto thread : m_threadgroup)
		{
			if (thread)
			{
				thread->join();
			}
		}

		m_threadgroup.clear();
	}

private:
	std::list<std::shared_ptr<std::thread>> m_threadgroup;//处理任务的线程组
	SyncQueue<Task> m_queue;		//同步队列
	atomic_bool m_running;          //是否停止标志(为了保证线程安全，使用原子变量atomic_bool)
	std::once_flag m_flag;
};