#include <cstring>
#include <exception>
#include <iostream>
#include <limits>

#include "Printer.h"
#include "ThreadPool.h"

void printHelloWorld(const int maxNumber = std::numeric_limits<int>::max())
{
    ThreadPool threadPool(2);

    Printer p1;
    p1.setThreadPool(&threadPool, 0);
    p1.setNextText("World!\n");
    p1.setLimit(maxNumber);

    Printer p2;
    p2.setThreadPool(&threadPool, 1);
    p2.setNextText("Hello ");

    p1.setNextPrinter(&p2);
    p2.setNextPrinter(&p1);

    p1.print("Hello ");
}

int main(int argc, char** argv)
{
    try {
        switch (argc) {
        case 1:
            printHelloWorld();
            break;
        case 3:
            if (0 == memcmp(argv[1], "-n", 2)) {
                printHelloWorld(atoi(argv[2]));
            }
            break;
        }
    } catch (std::exception e) {
        std::cout << e.what() << std::endl;
    } catch (...) {
        std::cout << "Unknown exception." << std::endl;
    }
}
