//
// Created by user064 on 26.03.24.
//

#ifndef MUSIC_DB_OUT_HPP
#define MUSIC_DB_OUT_HPP

#include <string>
#include <format>
#include <iostream>
#define FORMAT false

namespace out{
    template <typename... Args>
    void print(const std::string& str, Args&&... args) {
#if FORMAT
        if constexpr (sizeof...(args) > 0) {
            std::cout << std::format("{{    message: {}\n   args: {}}}", str,  std::forward<Args>(args)...) << std::endl;
        } else {
            std::cout << std::format("{{    message: {}\n   args: nullptr }}", str)<< std::endl;
        }
#else
        if constexpr (sizeof...(args) > 0) {
            std::cout << std::format("{{{} {}}}", str,  std::forward<Args>(args)...) << std::endl;
        } else {
            std::cout << str<< std::endl;
        }
#endif
    }

    template <typename... Args>
    void error(const char* str, Args&&... args) {
#if FORMAT
        if constexpr (sizeof...(args) > 0) {
            std::cerr << std::format("{{    message: {}\n   args: {}}}", str,  std::forward<Args>(args)...) << std::endl;
        } else {
            std::cerr << std::format("{{    message: {}\n   args: nullptr }}", str)<< std::endl;
        }
#else
        if constexpr (sizeof...(args) > 0) {
            std::cerr << std::format("{{{} {}}}", str,  std::forward<Args>(args)...) << std::endl;
        } else {
            std::cerr << str<< std::endl;
        }
#endif
    }
}

#endif //MUSIC_DB_OUT_HPP
