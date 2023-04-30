set(CMAKE_CXX_CLANG_TIDY "")
add_library(asm6502_lib asm6502Lexer.cpp asm6502Parser.cpp)
target_include_directories(asm6502_lib PRIVATE /usr/include/antlr4-runtime)
target_link_libraries(asm6502_lib PRIVATE antlr4-runtime Logger)
