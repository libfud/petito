if(NOT DEFINED ENV{NO_CLANG_CHECK})
    set(CMAKE_CXX_CLANG_TIDY clang-tidy)
endif()

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -Wunused-variable)

add_library(mos6502_lib mos6502.cpp opcode_table.cpp)

add_library(apu_lib apu.cpp)
add_library(nes_lib nes.cpp)
add_executable(mos6502 emu.cpp)

add_subdirectory(logger)
add_subdirectory(result)
add_subdirectory(option_parser)
add_subdirectory(cartridge)
add_subdirectory(ppu)

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

add_executable(test_mos6502 test_mos6502.cpp)
target_link_libraries(test_mos6502
    PRIVATE
    mos6502_lib
    nes_lib
    gtest gtest_main gmock)

gtest_add_tests(
    TARGET test_mos6502
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    EXTRA_ARGS --gtest_output=xml:${CMAKE_BINARY_DIR}/Test${ModuleName}.xml)

install(TARGETS mos6502 DESTINATION bin)
