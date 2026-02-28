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

add_subdirectory(metaprogramming)

add_executable(Snippets
        algorithm/sort/bubble_sort/bubble_sort.h
        algorithm/sort/test_sort.cpp
        algorithm/sort/strange_sort/monkey_sort.h
        algorithm/sort/strange_sort/sleep_sort.h
        algorithm/sort/merge_sort/merge_sort.h
        algorithm/sort/selection_sort/selection_sort.h
        algorithm/graph/base.h
        algorithm/graph/bfs/bfs.h
        algorithm/graph/bfs/test_bfs.cpp
        algorithm/graph/dfs/dfs.h
        algorithm/graph/dfs/test_dfs.cpp
        algorithm/graph/astar/astar.h
        algorithm/graph/astar/test_astar.cpp
        concurrency/thread/thread_guard/thread_guard.h
        concurrency/thread/thread_guard/test_thread_guard.cpp
        concurrency/thread/thread_task/thread_task.h
        concurrency/thread/thread_task/test_thread_task.cpp
        concurrency/sync/mutex_with_count/mutex_with_count.h
        concurrency/sync/mutex_with_count/mutex_with_count.cpp
        concurrency/sync/mutex_with_count/test_mutex_with_count.cpp
        concurrency/sync/det_mutex_conflict/det_mutex_conflict.h
        concurrency/sync/det_mutex_conflict/det_shared_mutex_conflict.h
        concurrency/sync/det_mutex_conflict/test_det_mutex_conflict.cpp
        concurrency/sync/det_mutex_conflict/test_det_shared_mutex_conflict.cpp
        concurrency/queue/msg_queue/msg_queue.h
        concurrency/queue/lockfree_queue/lockfree_queue.h
        concurrency/queue/lockfree_queue/test_lockfree_queue.cpp
        concurrency/pool/thread_pool/thread_pool.h
        concurrency/pool/thread_pool/test_thread_pool.cpp
        container/cache/lru_cache/lru_cache.h
        container/cache/lru_cache/test_lru_cache.cpp
        pattern/creational/singleton/singleton.h
        pattern/creational/singleton/test_singleton.cpp
        pattern/behavioral/observer/observer.h
        pattern/behavioral/observer/test_observer.cpp
        utility/timer/timer.cpp
        utility/para_binding/test_para_binding.cpp
        utility/macro/x_macro_patterns/x_macro_patterns_demo.h
        utility/macro/x_macro_patterns/test_x_macro_patterns_demo.cpp
        utility/string/string_split/string_split.h
        utility/string/string_split/test_string_split.cpp)

target_link_libraries(Snippets PRIVATE Catch2::Catch2WithMain nanobench)
