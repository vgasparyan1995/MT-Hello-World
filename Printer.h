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

private:
    ThreadPool* m_threadPool;
    const int   m_threadIndex;
    Printer*    m_nextPrinter;
    std::string m_nextText;
    bool        m_readyToPrint;
};
