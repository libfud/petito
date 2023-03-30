cmake_minimum_required(VERSION 3.16)

find_package(Qt6 REQUIRED COMPONENTS Widgets)
qt_standard_project_setup()

if(NOT DEFINED ENV{NO_CLANG_CHECK})
    set(CMAKE_CXX_CLANG_TIDY clang-tidy)
endif()

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -Wunused-variable)

add_executable(petito
    petito.cpp
    main_window.cpp
    cpu_info.cpp
    custom_memory.cpp
    computer_model.cpp
)

target_link_libraries(petito
    PRIVATE
    Qt6::Widgets
    mos6502_lib
    OptionParser)
target_include_directories(petito PRIVATE ../src)

install(TARGETS petito DESTINATION bin)
