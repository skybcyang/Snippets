cmake_minimum_required(VERSION 3.17)
project(Tempo)

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

add_executable(Tempo
        others/multi_stream_input_and_sync.cpp
        my_smart_ptr/my_shared_ptr.h
        my_smart_ptr/test_my_shared_ptr.cpp
        tuple_for_each/tuple_for_each.h
        tuple_for_each/test_tuple_for_each.cpp
        static_reflection/static_reflection.cpp
        member_wrapper/struct_wrapper.h
        member_wrapper/enum_wrapper.h
        member_wrapper/test_enum_wrapper.cpp
        member_wrapper/test_struct_wrapper.cpp
        crtp/crtp.h
        crtp/test_crtp.cpp
        static_crtp/static_crtp.h
        static_crtp/test_static_crtp.cpp
        calc_array_size/calc_array_size.h
        calc_array_size/test_calc_array_size.cpp
        general_factory/general_factory.h
        general_factory/offline_register.h
        general_factory/test_general_factory.cpp
        empty_class_checker/empty_class_checker.h
        empty_class_checker/test_empty_class_checker.cpp
        empty_class_checker/how_to_detect_if_a_class_has_member_variables.h
        dt/test_data_table.cpp
        dt/new_dt.h
        dt/old_dt.h
        dt/common.h)

target_link_libraries(Tempo PRIVATE Catch2::Catch2WithMain nanobench)