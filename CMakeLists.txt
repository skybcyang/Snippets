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
        sort/bubble_sort/BubbleSort.h
        sort/test_sort.cpp
        sort/strange_sort/MonkeySort.h
        sort/strange_sort/SleepSort.h
        sort/strange_sort/test_strange_sort.cpp
        find_way/bfs/bfs.h
        find_way/dfs/test_dfs.cpp
        find_way/dfs/dfs.h
        find_way/base.h
        find_way/bfs/test_bfs.cpp
        others/timer/timer.cpp others/para_binding/test_para_binding.cpp find_way/astar/astar.h find_way/astar/test_astar.cpp)

target_link_libraries(Snippets PRIVATE Catch2::Catch2WithMain)