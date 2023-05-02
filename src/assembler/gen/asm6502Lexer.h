
// Generated from asm6502Lexer.g4 by ANTLR 4.10.1

#pragma once


#include "antlr4-runtime.h"




class  asm6502Lexer : public antlr4::Lexer {
public:
  enum {
    COMMENT = 1, WHITESPACE = 2, NEWLINE = 3, PLUS = 4, MINUS = 5, STAR = 6, 
    SLASH = 7, LOW_BYTE_VALUE = 8, HIGH_BYTE_VALUE = 9, LBRACKET = 10, RBRACKET = 11, 
    LPAREN = 12, RPAREN = 13, HASH = 14, COLON = 15, AT = 16, FORCED_BYTE = 17, 
    FORCED_WORD = 18, COMMA = 19, X_INDEX = 20, Y_INDEX = 21, OCTAL_BYTE = 22, 
    OCTAL_NUMBER = 23, HEX_BYTE = 24, HEX_NUMBER = 25, DECIMAL_BYTE = 26, 
    DECIMAL_NUMBER = 27, BINARY_BYTE = 28, BINARY_NUMBER = 29, DORG = 30, 
    DBYTE = 31, DDBYTE = 32, DWORD = 33, DTEXT = 34, DALIGN = 35, DFILL = 36, 
    DREPEAT = 37, CHARACTER = 38, EQU = 39, NOP = 40, IMPLIED = 41, BRANCH = 42, 
    SHIFT = 43, JUMP = 44, JSR = 45, MNEMONIC = 46, ILLEGAL = 47, ACC = 48, 
    SYMBOL = 49, DQUOTE = 50, TEXT = 51, ESCAPE_SEQUENCE = 52
  };

  enum {
    IN_STRING = 1
  };

  explicit asm6502Lexer(antlr4::CharStream *input);

  ~asm6502Lexer() override;


      int nesting = 0;


  std::string getGrammarFileName() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const std::vector<std::string>& getChannelNames() const override;

  const std::vector<std::string>& getModeNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;

  const antlr4::atn::ATN& getATN() const override;

  // By default the static state used to implement the lexer is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:

  // Individual action functions triggered by action() above.

  // Individual semantic predicate functions triggered by sempred() above.

};

