add_library(asm_lib assembler.cpp tokenizer.cpp ../opcode_table.cpp)
target_include_directories(asm_lib PRIVATE ..)
