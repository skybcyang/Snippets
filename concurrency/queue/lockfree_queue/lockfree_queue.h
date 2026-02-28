//
// Created by skybcyang on 2026/2/23.
//
// Note: The unbounded lockfree_queue implementation is non-trivial and has
// been removed to avoid complex concurrency bugs. Use bounded_lockfree_queue
// for lock-free operations, or use std::queue with mutex for general cases.
//

#ifndef SNIPPETS_LOCKFREE_QUEUE_H
#define SNIPPETS_LOCKFREE_QUEUE_H

#include <atomic>
#include <memory>
#include <optional>
#include <vector>
#include <stdexcept>

// Lock-free bounded queue based on ring buffer (Michael-Scott style)
template<typename T, size_t Capacity>
class bounded_lockfree_queue {
private:
    struct cell {
        std::atomic<size_t> sequence;
        T data;
    };

    alignas(64) std::atomic<size_t> m_enqueue_pos;
    alignas(64) std::atomic<size_t> m_dequeue_pos;
    std::vector<cell> m_buffer;

public:
    bounded_lockfree_queue()
        : m_enqueue_pos(0), m_dequeue_pos(0), m_buffer(Capacity) {
        for (size_t i = 0; i < Capacity; ++i) {
            m_buffer[i].sequence.store(i, std::memory_order_relaxed);
        }
    }

    bool try_enqueue(const T& value) {
        cell* cell_ptr;
        size_t pos = m_enqueue_pos.load(std::memory_order_relaxed);

        while (true) {
            cell_ptr = &m_buffer[pos % Capacity];
            size_t seq = cell_ptr->sequence.load(std::memory_order_acquire);
            intptr_t diff = static_cast<intptr_t>(seq) - static_cast<intptr_t>(pos);

            if (diff == 0) {
                // Cell is ready, try to claim it
                if (m_enqueue_pos.compare_exchange_weak(
                        pos, pos + 1,
                        std::memory_order_relaxed)) {
                    break;
                }
                // Failed, retry with new position
            } else if (diff < 0) {
                // Queue is full
                return false;
            } else {
                // Position is behind, update and retry
                pos = m_enqueue_pos.load(std::memory_order_relaxed);
            }
        }

        // Write data and mark cell ready for dequeue
        cell_ptr->data = value;
        cell_ptr->sequence.store(pos + 1, std::memory_order_release);
        return true;
    }

    std::optional<T> try_dequeue() {
        cell* cell_ptr;
        size_t pos = m_dequeue_pos.load(std::memory_order_relaxed);

        while (true) {
            cell_ptr = &m_buffer[pos % Capacity];
            size_t seq = cell_ptr->sequence.load(std::memory_order_acquire);
            intptr_t diff = static_cast<intptr_t>(seq) - static_cast<intptr_t>(pos + 1);

            if (diff == 0) {
                // Cell is ready, try to claim it
                if (m_dequeue_pos.compare_exchange_weak(
                        pos, pos + 1,
                        std::memory_order_relaxed)) {
                    break;
                }
                // Failed, retry with new position
            } else if (diff < 0) {
                // Queue is empty
                return std::nullopt;
            } else {
                // Position is behind, update and retry
                pos = m_dequeue_pos.load(std::memory_order_relaxed);
            }
        }

        // Read data and mark cell ready for next enqueue
        T result = std::move(cell_ptr->data);
        cell_ptr->sequence.store(pos + Capacity, std::memory_order_release);
        return result;
    }

    bool empty() const {
        return m_dequeue_pos.load(std::memory_order_acquire) ==
               m_enqueue_pos.load(std::memory_order_acquire);
    }

    size_t size() const {
        size_t enqueue_pos = m_enqueue_pos.load(std::memory_order_acquire);
        size_t dequeue_pos = m_dequeue_pos.load(std::memory_order_acquire);
        return enqueue_pos - dequeue_pos;
    }

    static constexpr size_t capacity() {
        return Capacity;
    }
};

#endif //SNIPPETS_LOCKFREE_QUEUE_H
