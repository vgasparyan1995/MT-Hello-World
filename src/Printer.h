#pragma once

#include <string>

class ThreadPool;

class Printer
{
public:
    Printer();
    void setThreadPool(ThreadPool* threadPool, const int threadIndex);
    void setNextPrinter(Printer* p);
    void setNextText(const std::string& text);
    void print(const std::string& text);
    void setLimit(const int limit);

private:
    ThreadPool* m_threadPool;
    int         m_threadIndex;
    Printer*    m_nextPrinter;
    std::string m_nextText;
    int         m_index;
    int         m_limit;
    bool        m_readyToPrint;
};
