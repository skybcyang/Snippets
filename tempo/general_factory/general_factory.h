//
// Created by skybcyang on 2021/11/10.
//

#ifndef TEMPO_GENERAL_FACTORY_H
#define TEMPO_GENERAL_FACTORY_H

#include <string>
#include <mutex>
#include <memory>
#include <unordered_map>

template<typename T, typename KeyT>
struct GeneralFactory{
    static GeneralFactory& Instance(){
        static GeneralFactory general_factory;
        return general_factory;
    }

    std::shared_ptr<T> Create(const KeyT& key) {
        auto creator = creator_map.find(key);
        if (creator == creator_map.end()) {
            return nullptr;
        }
        return (creator->second)();
    }

    template<typename F>
    int Register(const KeyT& key) {
        std::lock_guard<std::mutex> lock(mtx);
        auto creator = creator_map.find(key);
        if (creator == creator_map.end()) {
            creator_map.emplace(key, []() -> std::shared_ptr<T> {
                return std::make_shared<F>();
            });
        }
        return 0;
    }
private:
    std::mutex mtx;
    using Creator = std::function<std::shared_ptr<T>()>;
    std::unordered_map<KeyT, Creator> creator_map;
};

#endif //TEMPO_GENERAL_FACTORY_H
