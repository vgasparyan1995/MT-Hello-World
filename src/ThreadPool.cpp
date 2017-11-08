#include "ThreadPool.h"

ThreadPool::ThreadPool(const int threadCount)
    : m_conditionVariables(threadCount)
    , m_taskQueues(threadCount)
    , m_stop(false)
{
    if (threadCount <= 0) {
        throw std::invalid_argument("The argument \'threadCount\' must be greater than 0.");
    }
    for (int i = 0; i < threadCount; ++i) {
        m_pool.emplace_back([this, i] ()
            {
                std::unique_lock<MutexT> lk(m_mutex);
                while (true) {
                    while (!m_stop && m_taskQueues[i].empty()) {
                        m_conditionVariables[i].wait(lk);
                    }
                    if (m_stop) {
                        return;
                    }
                    auto task = std::move(m_taskQueues[i].front());
                    m_taskQueues[i].pop();
                    task();
                }
            });
    }
}

ThreadPool::~ThreadPool()
{
    for (auto& thread : m_pool) {
        thread.join();
    }
}

int ThreadPool::numberOfThreads() const
{
    return m_pool.size();
}

void ThreadPool::schedule(const int threadIndex, std::function<void()> f)
{
    m_taskQueues[threadIndex].push(f);
    m_conditionVariables[threadIndex].notify_one();
}

void ThreadPool::stop()
{
    m_stop = true;
    for (auto& cond : m_conditionVariables) {
        cond.notify_one();
    }
}
