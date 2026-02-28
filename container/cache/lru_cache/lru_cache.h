//
// Created by skybcyang on 2026/2/23.
//

#ifndef SNIPPETS_LRU_CACHE_H
#define SNIPPETS_LRU_CACHE_H

#include <unordered_map>
#include <list>
#include <optional>

template<typename KeyT, typename ValueT>
class lru_cache {
public:
    explicit lru_cache(size_t capacity) : m_capacity(capacity) {}

    std::optional<ValueT> get(const KeyT& key) {
        auto iter = m_cache_map.find(key);
        if (iter == m_cache_map.end()) {
            return std::nullopt;
        }
        // Move to front (most recently used)
        m_cache_list.splice(m_cache_list.begin(), m_cache_list, iter->second);
        return iter->second->second;
    }

    void put(const KeyT& key, const ValueT& value) {
        auto iter = m_cache_map.find(key);
        if (iter != m_cache_map.end()) {
            // Update existing key and move to front
            iter->second->second = value;
            m_cache_list.splice(m_cache_list.begin(), m_cache_list, iter->second);
            return;
        }

        // Check capacity
        if (m_cache_map.size() >= m_capacity) {
            // Remove least recently used
            auto last = m_cache_list.back();
            m_cache_map.erase(last.first);
            m_cache_list.pop_back();
        }

        // Insert new key-value pair
        m_cache_list.emplace_front(key, value);
        m_cache_map.emplace(key, m_cache_list.begin());
    }

    size_t size() const {
        return m_cache_map.size();
    }

    void clear() {
        m_cache_map.clear();
        m_cache_list.clear();
    }

private:
    size_t m_capacity;
    std::list<std::pair<KeyT, ValueT>> m_cache_list;
    std::unordered_map<KeyT, typename std::list<std::pair<KeyT, ValueT>>::iterator> m_cache_map;
};

#endif //SNIPPETS_LRU_CACHE_H
