//
// Created by skybcyang on 2026/2/23.
//

#include <iostream>
#include <catch2/catch_test_macros.hpp>
#include "singleton.h"

// Test macro-based singleton
class ConfigManager {
    DEFINE_SINGLETON(ConfigManager)
public:
    void SetValue(const std::string& key, const std::string& value) {
        m_config[key] = value;
    }
    
    std::string GetValue(const std::string& key) const {
        auto it = m_config.find(key);
        if (it != m_config.end()) {
            return it->second;
        }
        return "";
    }
    
private:
    std::unordered_map<std::string, std::string> m_config;
};

// Test template-based singleton
class Logger : public singleton<Logger> {
    friend class singleton<Logger>;
public:
    void Log(const std::string& msg) {
        m_logs.push_back(msg);
    }
    
    size_t LogCount() const {
        return m_logs.size();
    }
    
    void Clear() {
        m_logs.clear();
    }

private:
    Logger() = default;
    std::vector<std::string> m_logs;
};

// Test DCL singleton
class Counter : public singleton_dcl<Counter> {
    friend class singleton_dcl<Counter>;
public:
    void Increment() {
        ++m_count;
    }
    
    int GetCount() const {
        return m_count;
    }

private:
    Counter() : m_count(0) {}
    int m_count;
};

TEST_CASE("test_meyers_singleton_macro") {
    auto& config1 = ConfigManager::Instance();
    auto& config2 = ConfigManager::Instance();
    
    // Same instance
    REQUIRE(&config1 == &config2);
    
    config1.SetValue("name", "test");
    REQUIRE(config2.GetValue("name") == "test");
}

TEST_CASE("test_template_singleton") {
    auto& logger1 = Logger::Instance();
    auto& logger2 = Logger::Instance();
    
    REQUIRE(&logger1 == &logger2);
    
    logger1.Clear();
    logger1.Log("msg1");
    logger2.Log("msg2");
    
    REQUIRE(logger1.LogCount() == 2);
}

TEST_CASE("test_dcl_singleton") {
    auto& counter1 = Counter::Instance();
    auto& counter2 = Counter::Instance();
    
    REQUIRE(&counter1 == &counter2);
    
    counter1.Increment();
    counter2.Increment();
    
    REQUIRE(counter1.GetCount() == 2);
}
