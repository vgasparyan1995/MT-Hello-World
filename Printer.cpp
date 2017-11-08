#include "ThreadPool.h"

#include "Printer.h"

Printer::Printer()
    : m_threadPool(nullptr)
    , m_threadIndex(0),
    , m_nextPrinter(nullptr)
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
    m_nextPrinter = printer;
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
    m_threadPool->schedule(m_threadIndex, [this, text] ()
        {
            std::cout << text;
            if (m_nextPrinter != nullptr) {
                m_nextPrinter->print(m_nextText);
            }
        });
}

