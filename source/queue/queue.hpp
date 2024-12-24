#ifndef QUEUE_HPP_
#define QUEUE_HPP_

#include <memory>
#include <vector>
#include <mutex>
#include <condition_variable>

template <typename T>
class Queue {
public:
   // move-only
   void push(T&& element){
      std::lock_guard<decltype(the_mutex)> a_lock{the_mutex};
      internal_container.push_back(std::make_shared<T>(std::move(element)));
      the_cv.notify_one();
   }
   std::shared_ptr<T> pop_block(){
      std::shared_ptr<T> result {nullptr};
      {
         std::unique_lock<decltype(the_mutex)> the_lock(the_mutex);
         the_cv.wait(the_lock, [this](){ return !(internal_container.empty()); });
         result = internal_container.back();
         internal_container.pop_back();
      }
      return result;
   }
   std::vector<std::shared_ptr<T>> internal_container{};
   std::mutex the_mutex;
   std::condition_variable the_cv;
};

#endif //QUEUE_HPP_