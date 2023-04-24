if(NOT DEFINED ENV{NO_CLANG_CHECK})
    set(CMAKE_CXX_CLANG_TIDY clang-tidy -extra-arg=-std=c++20 -checks=cppcore*,-readability-magic-numbers,-cppcoreguidelines-pro-bounds-constant-array-index,-cppcoreguidelines-avoid-magic-numbers,-cppcoreguidelines-pro-bounds-pointer-arithmetic,-cppcoreguidelines-pro-type-const-cast,-cppcoreguidelines-pro-type-union-access,cplusplus*)
endif()

SET(CMAKE_CXX_FLAGS_COVERAGE
    "-g --coverage -fprofile-arcs -ftest-coverage"
    CACHE STRING "Flags used by the C++ compiler during coverage builds."
    FORCE )
set(CMAKE_CXX_WARNINGS
    "-Wall -Wunused-variable -Wpedantic -Wuninitialized")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  ${CMAKE_CXX_WARNINGS} ${CMAKE_CXX_FLAGS_COVERAGE}")

add_library(mos6502_lib mos6502.cpp opcode_table.cpp)

add_library(apu_lib apu.cpp)
add_library(nes_lib nes.cpp system_bus.cpp)
add_executable(mos6502 emu.cpp)

option(USE_ASAN "Use ASAN" OFF) #OFF by default
if(USE_ASAN)
    target_compile_options(mos6502 PRIVATE -fsanitize=address)
    target_link_options(mos6502 PRIVATE -fsanitize=address)
endif()
unset(USE_ASAN CACHE)

add_subdirectory(logger)
add_subdirectory(result)
add_subdirectory(option_parser)
add_subdirectory(cartridge)
add_subdirectory(ppu)
add_subdirectory(assembler)

add_common_dependency(nes_lib Logger)
target_link_libraries(nes_lib PUBLIC
    Logger
    mos6502_lib
    ppu_lib
    apu_lib
    cartridge_lib)

add_common_dependency(mos6502_lib Logger)
target_link_libraries(mos6502_lib PUBLIC Logger)

add_common_dependency(mos6502 Logger)
target_link_libraries(mos6502 PUBLIC nes_lib OptionParser)

install(TARGETS mos6502 DESTINATION bin)
