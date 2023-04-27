
// Generated from asm6502.g4 by ANTLR 4.10.1

#pragma once


#include "antlr4-runtime.h"




class  asm6502Lexer : public antlr4::Lexer {
public:
  enum {
    COMMENT = 1, WHITESPACE = 2, NEWLINE = 3, UNDERSCORE = 4, PLUS = 5, 
    MINUS = 6, STAR = 7, SLASH = 8, LOW_BYTE_VALUE = 9, HIGH_BYTE_VALUE = 10, 
    LBRACKET = 11, RBRACKET = 12, LPAREN = 13, RPAREN = 14, HASH = 15, COLON = 16, 
    AT = 17, X_INDEX = 18, Y_INDEX = 19, OCTAL_BYTE = 20, OCTAL_NUMBER = 21, 
    HEX_BYTE = 22, HEX_NUMBER = 23, DECIMAL_BYTE = 24, DECIMAL_NUMBER = 25, 
    BINARY_BYTE = 26, BINARY_NUMBER = 27, CHARACTER = 28, ORG = 29, EQU = 30, 
    NOP = 31, IMPLIED = 32, BRANCH = 33, SHIFT = 34, JUMP = 35, JSR = 36, 
    MNEMONIC = 37, ILLEGAL = 38, ACC = 39, SYMBOL = 40
  };

  explicit asm6502Lexer(antlr4::CharStream *input);

  ~asm6502Lexer() override;


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

