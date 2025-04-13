#include <iostream>
#include <thread>
#include "threadQueue.hpp"

ThreadQueue<int> ts_queue;

void producer() {
    std::cout << "Producer thread started\n";
    for (int i = 0; i < 5; ++i) {
        ts_queue.push(i);
        std::cout << "[Producer] pushed " << i << "\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

void consumer() {
    std::cout << "Consumer thread started\n";
    int result = 0;
    int val = -1;
    int received = 0;

    while (received < 5) {
        if ((result = ts_queue.blocking_pop(val)) == 0) {
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
            received++;
            std::cout << "[Consumer] popped " << val << "\n";
        }
    }
}

int main() {
    std::thread t1(producer);
    std::thread t2(consumer);

    t1.join();
    t2.join();
    return 0;
}