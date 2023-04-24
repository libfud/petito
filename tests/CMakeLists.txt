add_executable(test_mos6502 test_mos6502.cpp test_flags.cpp test_system_bus.cpp)
target_include_directories(test_mos6502 PRIVATE ../src)
target_link_libraries(test_mos6502
    PRIVATE
    mos6502_lib
    nes_lib
    gtest gtest_main gmock)

gtest_add_tests(
    TARGET test_mos6502
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    EXTRA_ARGS --gtest_output=xml:${CMAKE_BINARY_DIR}/Test${ModuleName}.xml)

add_executable(test_nes test_nes.cpp)
target_include_directories(test_nes PRIVATE ../src)
target_link_libraries(test_nes
    PRIVATE
    mos6502_lib
    nes_lib
    gtest gtest_main gmock)

gtest_add_tests(
    TARGET test_nes
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    EXTRA_ARGS --gtest_output=xml:${CMAKE_BINARY_DIR}/Test${ModuleName}.xml)

add_executable(test_asm test_assembler.cpp)
target_include_directories(test_asm PRIVATE ../src ../src/assembler)
target_link_libraries(test_asm
    PRIVATE
    asm_lib
    gtest gtest_main gmock)

gtest_add_tests(
    TARGET test_asm
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    EXTRA_ARGS --gtest_output=xml:${CMAKE_BINARY_DIR}/Test${ModuleName}.xml)
