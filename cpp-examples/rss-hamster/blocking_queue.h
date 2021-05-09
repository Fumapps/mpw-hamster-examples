//
// Created by Steffen Becker on 08.05.21.
//

#ifndef MPW_HAMSTER_EXAMPLES_BLOCKING_QUEUE_H
#define MPW_HAMSTER_EXAMPLES_BLOCKING_QUEUE_H

#include <iostream>
#include <algorithm>
#include <queue>
#include <mutex>
#include <thread>
#include <condition_variable>

template<typename T>
class blocking_queue {
private:
    size_t _capacity;
    std::queue<T> _queue;
    std::mutex _mutex;
    std::condition_variable _not_full;
    std::condition_variable _not_empty;

public:
    inline blocking_queue(size_t capacity) : _capacity(capacity) {
        // empty
    }

    inline size_t size() const {
        std::unique_lock<std::mutex> lock(_mutex);
        return _queue.size();
    }

    inline bool empty() const {
        std::unique_lock<std::mutex> lock(_mutex);
        return _queue.empty();
    }

    inline void push(const T& elem) {
        {
            std::unique_lock<std::mutex> lock(_mutex);

            // wait while the queue is full
            while (_queue.size() >= _capacity) {
                _not_full.wait(lock);
            }
            //std::cout << "pushing element " << elem << std::endl;
            _queue.push(elem);
        }
        _not_empty.notify_all();
    }

    inline void pop() {
        {
            std::unique_lock<std::mutex> lock(_mutex);

            // wait while the queue is empty
            while (_queue.size() == 0) {
                _not_empty.wait(lock);
            }
            //std::cout << "popping element " << _queue.front() << std::endl;
            _queue.pop();
        }
        _not_full.notify_one();
    }

    inline const T& front() {
        std::unique_lock<std::mutex> lock(_mutex);

        // wait while the queue is empty
        while (_queue.size() == 0) {
            _not_empty.wait(lock);
        }
        return _queue.front();
    }
};

#endif //MPW_HAMSTER_EXAMPLES_BLOCKING_QUEUE_H
