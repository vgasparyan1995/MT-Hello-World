#include <iostream>
#include <limits>

#include "ThreadPool.h"

#include "Printer.h"

Printer::Printer()
    : m_threadPool(nullptr)
    , m_threadIndex(0)
    , m_nextPrinter(nullptr)
    , m_index(0)
    , m_limit(std::numeric_limits<int>::max())
    , m_readyToPrint(false)
{
}

void Printer::setThreadPool(ThreadPool* threadPool, const int threadIndex)
{
    m_threadPool = threadPool;
    m_threadIndex = threadIndex;
    m_readyToPrint = (m_threadPool != nullptr) &&
                     (m_threadIndex < m_threadPool->numberOfThreads()) &&
                     (m_threadIndex >= 0);
}

void Printer::setNextPrinter(Printer* p)
{
    m_nextPrinter = p;
}

void Printer::setNextText(const std::string& text)
{
    m_nextText = text;
}

void Printer::print(const std::string& text)
{
    if (!m_readyToPrint) {
        return;
    }
    if (m_index++ >= m_limit) {
        m_threadPool->stop();
        return;
    }
    m_threadPool->schedule(m_threadIndex, [this, text] ()
        {
            std::cout << text;
            if (m_nextPrinter != nullptr) {
                m_nextPrinter->print(m_nextText);
            }
        });
}

void Printer::setLimit(const int limit)
{
    m_limit = limit;
}
