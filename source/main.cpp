#include <iostream>
#include <chrono>
#include <thread>

#include "queue/queue.hpp"

int main(){
   Queue<int> queue;
   std::thread t{[&queue](){
      std::this_thread::sleep_for(std::chrono::milliseconds(2000));
      queue.push(42);
   }};

   std::cout << "Value waited for:" << *(queue.pop_block()) << std::endl;

   t.join();
}