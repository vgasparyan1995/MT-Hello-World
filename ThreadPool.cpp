#include "ThreadPool.h"

ThreadPool::ThreadPool(const int threadCount)
    : m_conditionVariables(threadCount)
    , m_taskQueues(threadCount)
    , m_stop(false)
{
    if (int <= 0) {
        throw std::invalid_argument("The argument \'threadCount\' must be greater than 0.");
    }
    for (int i = 0; i < threadCount; ++i) {
        m_pool.emplace_back([this] ()
            {
                std::unique_lock<std::mutex> lk(m_mutex);
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
    stop();
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
    std::lock_guard<std::mutex> lk(m_mutex);
    m_taskQueues[i].push(f);
    m_conditionVariables[i].notify_one();
}

void ThreadPool::stop()
{
    m_stop = true;
    for (auto& cond : m_conditionVariables) {
        cond.notify_one();
    }
}
