cmake_minimum_required(VERSION 3.20)
project(Snippets)

set(CMAKE_CXX_STANDARD 20)

Include(FetchContent)

FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://gitclone.com/github.com/catchorg/Catch2
        GIT_TAG        v3.0.0-preview3
)

FetchContent_MakeAvailable(Catch2)

FetchContent_Declare(
        nanobench
        GIT_REPOSITORY https://gitclone.com/github.com/martinus/nanobench
        GIT_TAG        v4.1.0
)

FetchContent_MakeAvailable(nanobench)

add_subdirectory(tempo)

add_executable(Snippets
        sort/bubble_sort/bubble_sort.h
        sort/test_sort.cpp
        sort/strange_sort/monkey_sort.h
        sort/strange_sort/sleep_sort.h
        find_way/bfs/bfs.h
        find_way/dfs/test_dfs.cpp
        find_way/dfs/dfs.h
        find_way/base.h
        find_way/bfs/test_bfs.cpp
        others/timer/timer.cpp
        others/para_binding/test_para_binding.cpp
        find_way/astar/astar.h
        find_way/astar/test_astar.cpp
        sort/merge_sort/merge_sort.h
        sort/selection_sort/selection_sort.h
        mthread/thread_guard/thread_guard.h
        mthread/thread_guard/test_thread_guard.cpp
        mthread/thread_task/thread_task.h
        mthread/thread_task/test_thread_task.cpp
        others/x_macro_patterns/x_macro_patterns_demo.h
        others/x_macro_patterns/test_x_macro_patterns_demo.cpp others/det_mutex_conflict/det_mutex_conflict.h others/det_mutex_conflict/det_shared_mutex_conflict.h others/det_mutex_conflict/test_det_mutex_conflict.cpp others/det_mutex_conflict/test_det_shared_mutex_conflict.cpp mthread/msg_queue/msg_queue.h mthread/mutex_with_count/mutex_with_count.h mthread/mutex_with_count/mutex_with_count.cpp mthread/mutex_with_count/test_mutex_with_count.cpp)

target_link_libraries(Snippets PRIVATE Catch2::Catch2WithMain nanobench)