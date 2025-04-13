#ifndef THREAD_QUEUE_HPP
#define THREAD_QUEUE_HPP

#include <queue>
#include <mutex>
#include <condition_variable>

template<typename T>
class ThreadQueue {
private:
    std::queue<T> queue; 
    size_t max_size;
    mutable std::mutex mutex; 
    std::condition_variable cond_var;

public:
    ThreadQueue() : max_size(0) {}; // unlimited queue size
    ThreadQueue(size_t s) : max_size(s) {}; // limited queue size
    ~ThreadQueue() = default;

    ThreadQueue(const ThreadQueue&) = delete;
    ThreadQueue& operator=(const ThreadQueue&) = delete;

    /**
     * push with copy
     * RETURN: 0 on success, -1 on fail */
    int push(const T& item) {
        std::lock_guard<std::mutex> lock(mutex);
        {
            if (max_size == 0 || queue.size() < max_size) {
                queue.push(item);
                cond_var.notify_one();
                return 0;
            }
        }
        return -1;
    }   

    /**
     * push with move
     * RETURN: 0 on success, -1 on fail */
    bool push(T&& item) {
        std::lock_guard<std::mutex> lock(mutex);
        {
            if (max_size == 0 || queue.size() < max_size) {
                queue.push(std::move(item));
                cond_var.notify_one();
                return 0;
            }
        }
        return -1;
    }

    /**
     * blocking pop
     * RETURN: 0 on success, -1 on fail */
    int blocking_pop(T& item) {
        std::unique_lock<std::mutex> lock(mutex);
        cond_var.wait(lock, [this] { return !queue.empty(); });

        item = std::move(queue.front());
        queue.pop();
        return 0;
    }   

    /**
     * non-blocking pop
     * RETURN: 0 on success, -1 on fail */
    int non_blocking_pop(T& item) {
        std::unique_lock<std::mutex> lock(mutex);
        {
            if (queue.empty()) {
                return -1;
            }
            item = std::move(queue.front());
            queue.pop();
        }
        return 0;
    }
    
    /* queue empty */
    bool empty() const {
        std::unique_lock<std::mutex> lock(mutex);
        return queue.empty();
    }      
    
    /* queue size */
    size_t size() const {
        std::unique_lock<std::mutex> lock(mutex);
        return queue.size();
    };            
};  


#endif