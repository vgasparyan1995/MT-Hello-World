#include <chrono>
#include <condition_variable>
#include <cstring>
#include <exception>
#include <iostream>
#include <limits>
#include <mutex>
#include <stdlib.h>
#include <thread>

namespace HelloWorld
{

std::condition_variable g_printHelloNotifier;
std::condition_variable g_printWorldNotifier;
std::mutex              g_hwMutex;
int                     g_maxLine = std::numeric_limits<int>::max();

void printHello()
{
    std::unique_lock<std::mutex> lk(g_hwMutex);
    g_printHelloNotifier.wait_for(lk, std::chrono::milliseconds(1));
    auto hCounter = 0;
    while (hCounter++ < g_maxLine) {
        std::cout << "Hello ";
        g_printWorldNotifier.notify_one();
        g_printHelloNotifier.wait(lk);
    }
}

void printWorld()
{
    std::unique_lock<std::mutex> lk(g_hwMutex);
    auto wCounter = 0;
    while (wCounter++ < g_maxLine) {
        g_printWorldNotifier.wait(lk);
        std::cout << "World!" << std::endl;
        g_printHelloNotifier.notify_one();
    }
}

void print()
{
    std::thread helloThread(printHello);
    std::thread worldThread(printWorld);
    helloThread.join();
    worldThread.join();
}

};

int main(int argc, char** argv)
{
    try {
        switch (argc) {
        case 1:
            HelloWorld::print();
            break;
        case 3:
            if (0 == memcmp(argv[1], "-n", 2)) {
                HelloWorld::g_maxLine = atoi(argv[2]);
                HelloWorld::print();
            }
            break;
        }
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    } catch (...) {
        std::cout << "Exception not handled." << std::endl;
    }
}
