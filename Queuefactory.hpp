#ifndef QUEUE_FACTORY_HPP
#define QUEUE_FACTORY_HPP

#include "Queue.hpp"
#include "ArrayQueue.hpp"
#include "LinkedQueue.hpp"

using namespace std;

// -------------------------------------------------------
// QueueFactory
// -------------------------------------------------------
template <typename T>
class QueueFactory {
    public:
        static Queue<T>* GetQueue() {
            return new LinkedQueue<T>();
        }
        static Queue<T>* GetQueue(int capacity) {
            return new ArrayQueue<T>(capacity);
        }
};

#endif