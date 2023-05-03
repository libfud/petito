add_library(asm_lib assembler.cpp
    assembler_types.cpp
    arithmetic.cpp
    asm_line.cpp
    asm_instruction.cpp
    ../opcode_table.cpp)
target_include_directories(asm_lib PRIVATE .. /usr/include/antlr4-runtime)
add_subdirectory(gen)
target_link_libraries(asm_lib PRIVATE asm6502_lib antlr4-runtime Logger)
