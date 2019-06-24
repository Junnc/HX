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
		//��֤���߳������ֻ����һ��StopThreadGroup
		std::call_once(m_flag, [this] {StopThreadGroup(); });

	}

	void AddTask(Task&& task)
	{
		m_queue.Put(std::forward<Task>(task));
		//std::cout << "add success,queueSize:"<<m_queue.Size() << endl;
	}

	void AddTask(const Task& task)
	{
		m_queue.Put(task);
		//std::cout << "add success const" << endl;
	}

	void Start(int numThreads = std::thread::hardware_concurrency())
	{
		m_running = true;
		//std::cout << "start,m_running:" << m_running << endl;
		//�����߳���
		for (int i = 0; i < numThreads; ++i)
		{
			m_threadgroup.push_back(std::make_shared<std::thread>(&ThreadPool::RunInThread, this));
		}
	}

private:
	void RunInThread()
	{
		//std::cout << "execute,m_running:" << m_running << endl;
		while (m_running)
		{
			//ȡ����ֱ�ִ��
			std::list<Task> list;
			Task task;
			m_queue.Take(task);
			//std::cout << "execute,listSize:"<<list.size() <<",thread_id:"<< pthread_self() << endl;
			//for (auto& task : list)
			{
				if (!m_running)
					return;
				//std::cout << "pre-execute" << endl;
				task();
				//std::cout << "later_execute" << endl;
			}
		}
	}

	void StopThreadGroup()
	{
		m_queue.Stop();//��ͬ�������е��߳�ֹͣ
		m_running = false; //��Ϊfalse,���ڲ��߳�����ѭ�����˳�

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
	std::list<std::shared_ptr<std::thread>> m_threadgroup;//����������߳���
	SyncQueue<Task> m_queue;		//ͬ������
	atomic_bool m_running;          //�Ƿ�ֹͣ��־(Ϊ�˱�֤�̰߳�ȫ��ʹ��ԭ�ӱ���atomic_bool)
	std::once_flag m_flag;
};
