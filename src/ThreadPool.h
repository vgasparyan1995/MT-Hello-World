#pragma once

#include <condition_variable>
#include <functional>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

class ThreadPool
{
public:
    explicit ThreadPool(const int threadCount);
    ThreadPool(const ThreadPool&) = delete;
    ThreadPool(ThreadPool&&) = default;
    ThreadPool& operator= (const ThreadPool&) = delete;
    ThreadPool& operator= (ThreadPool&&) = default;
    ~ThreadPool();

    int numberOfThreads() const;
    void schedule(const int threadIndex, std::function<void()> f);
    void stop();

private:
    using Pool = std::vector<std::thread>;
    using CondVars = std::vector<std::condition_variable>;
    using Tasks = std::queue<std::function<void()> >;
    using Queues = std::vector<Tasks>;
    using MutexT = std::mutex;

    Pool        m_pool;
    CondVars    m_conditionVariables;
    Queues      m_taskQueues;
    MutexT      m_mutex;
    bool        m_stop;
};
