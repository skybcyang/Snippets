cmake_minimum_required(VERSION 3.20)
project(Snippets)

set(CMAKE_CXX_STANDARD 20)

Include(FetchContent)

FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v3.0.0-preview3
)

FetchContent_MakeAvailable(Catch2)

add_executable(Snippets
        sort/BubbleSort.h
        sort/test_sort.cpp
        strange_sort/MonkeySort.h
        strange_sort/SleepSort.h
        strange_sort/test_strange_sort.cpp)

target_link_libraries(Snippets PRIVATE Catch2::Catch2WithMain)