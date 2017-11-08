#include <exception>
#include <iostream>

#include "Printer.h"
#include "ThreadPool.h"

void printHelloWorld()
{
    ThreadPool threadPool(2);

    Printer p1;
    p1.setThreadPool(&threadPool, 0);
    p1.setNextPrinter(&p2);
    p1.setNextText("World!\n");

    Printer p2;
    p2.setThreadPool(&threadPool, 1);
    p2.setNextPrinter(&p1);
    p2.setNextText("Hello ");

    p1.print("Hello ");
}

int main()
{
    try {
        printHelloWorld();
    } catch (std::exception e) {
        std::cout << e.what() << std::endl;
    } catch (...) {
        std::cout << "Unknown exception." << std::endl;
    }
}
