//
// Created by skybcyang on 2026/2/23.
//

#ifndef SNIPPETS_STRING_SPLIT_H
#define SNIPPETS_STRING_SPLIT_H

#include <string>
#include <vector>
#include <sstream>
#include <charconv>

// Split string by delimiter, return vector<string>
inline std::vector<std::string> StringSplit(const std::string& str, char delimiter) {
    std::vector<std::string> result;
    std::stringstream ss(str);
    std::string item;
    
    while (std::getline(ss, item, delimiter)) {
        result.push_back(item);
    }
    
    return result;
}

// Split string by delimiter, return vector<string> (string_view version)
inline std::vector<std::string_view> StringSplitSV(std::string_view str, char delimiter) {
    std::vector<std::string_view> result;
    size_t start = 0;
    size_t end = str.find(delimiter);
    
    while (end != std::string_view::npos) {
        result.emplace_back(str.substr(start, end - start));
        start = end + 1;
        end = str.find(delimiter, start);
    }
    
    result.emplace_back(str.substr(start));
    return result;
}

// Split string by multiple delimiters (any char in delimiters)
inline std::vector<std::string> StringSplitAny(const std::string& str, const std::string& delimiters) {
    std::vector<std::string> result;
    size_t start = 0;
    size_t end = str.find_first_of(delimiters);
    
    while (end != std::string_view::npos) {
        if (end > start) {
            result.emplace_back(str.substr(start, end - start));
        }
        start = end + 1;
        end = str.find_first_of(delimiters, start);
    }
    
    if (start < str.size()) {
        result.emplace_back(str.substr(start));
    }
    
    return result;
}

// Trim whitespace from both ends
inline std::string StringTrim(const std::string& str) {
    size_t start = str.find_first_not_of(" \t\n\r");
    if (start == std::string::npos) {
        return "";
    }
    size_t end = str.find_last_not_of(" \t\n\r");
    return str.substr(start, end - start + 1);
}

// Join strings with delimiter
template<typename Container>
inline std::string StringJoin(const Container& container, const std::string& delimiter) {
    std::string result;
    bool first = true;
    
    for (const auto& item : container) {
        if (!first) {
            result += delimiter;
        }
        result += item;
        first = false;
    }
    
    return result;
}

// Parse string to number using std::from_chars (C++17)
template<typename T>
inline std::optional<T> ParseNumber(std::string_view str) {
    T value;
    auto result = std::from_chars(str.data(), str.data() + str.size(), value);
    if (result.ec == std::errc() && result.ptr == str.data() + str.size()) {
        return value;
    }
    return std::nullopt;
}

#endif //SNIPPETS_STRING_SPLIT_H
