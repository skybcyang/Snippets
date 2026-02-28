cmake_minimum_required(VERSION 3.17)
project(Metaprogramming)

set(CMAKE_CXX_STANDARD 17)

Include(FetchContent)

FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://gitclone.com/github.com/catchorg/Catch2
        GIT_TAG        v3.0.0-preview3
)

FetchContent_Declare(
        nanobench
        GIT_REPOSITORY https://gitclone.com/github.com/martinus/nanobench
        GIT_TAG        v4.1.0
)

FetchContent_MakeAvailable(Catch2)
FetchContent_MakeAvailable(nanobench)

add_executable(Metaprogramming
        misc/others/multi_stream_input_and_sync.cpp
        ../container/smart_ptr/non_intrusive_shared_ptr.h
        ../container/smart_ptr/test_non_intrusive_shared_ptr.cpp
        tuple/tuple_for_each/tuple_for_each.h
        tuple/tuple_for_each/test_tuple_for_each.cpp
        static_reflection/static_reflection.cpp
        type_traits/member_wrapper/struct_wrapper.h
        type_traits/member_wrapper/enum_wrapper.h
        type_traits/member_wrapper/test_enum_wrapper.cpp
        type_traits/member_wrapper/test_struct_wrapper.cpp
        ../pattern/structural/crtp/crtp.h
        ../pattern/structural/crtp/test_crtp.cpp
        misc/static_crtp/static_crtp.h
        misc/static_crtp/test_static_crtp.cpp
        misc/calc_array_size/calc_array_size.h
        misc/calc_array_size/test_calc_array_size.cpp
        factory/general_factory/general_factory.h
        factory/general_factory/offline_register.h
        factory/general_factory/test_general_factory.cpp
        type_traits/empty_class_checker/empty_class_checker.h
        type_traits/empty_class_checker/test_empty_class_checker.cpp
        type_traits/empty_class_checker/how_to_detect_if_a_class_has_member_variables.h
        misc/dt/test_data_table.cpp
        misc/dt/new_dt.h
        misc/dt/old_dt.h
        misc/dt/common.h
        ../container/smart_ptr/intrusive_shared_ptr.h
        ../container/smart_ptr/test_intrusive_shared_ptr.cpp
        misc/bitset/dynamic_bitset.h
        misc/bitset/test_dynamic_bitset.cpp
        misc/bitset/static_bitset.h
        misc/bitset/bitmap.h
        misc/scope_guard/ScopeGuard.h
        misc/scope_guard/test_scope_guard.cpp
        misc/map_macro_to_struct/map_macro_to_struct.h
        misc/map_macro_to_struct/test_map_macro_to_struct.cpp
        misc/data_container/include/meta_info.h
        misc/class_unity/class_unity.h
        misc/class_unity/test_class_unity.cpp)

target_link_libraries(Metaprogramming PRIVATE Catch2::Catch2WithMain nanobench)
