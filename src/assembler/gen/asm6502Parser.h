
// Generated from asm6502.g4 by ANTLR 4.10.1

#pragma once


#include "antlr4-runtime.h"




class  asm6502Parser : public antlr4::Parser {
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

  enum {
    RuleProgram = 0, RuleLine = 1, RuleLabel = 2, RuleAssign = 3, RuleInstruction = 4, 
    RuleComment = 5, RuleNop = 6, RuleImplicit = 7, RuleAcc = 8, RuleImmediate = 9, 
    RuleX_index = 10, RuleY_index = 11, RuleX_indirect = 12, RuleIndirect_y = 13, 
    RuleAbsolute = 14, RuleRelative = 15, RuleMnemonic = 16, RuleShift = 17, 
    RuleJump = 18, RuleJsr = 19, RuleExpression = 20, RuleBinary_op = 21, 
    RuleUnary_op = 22, RuleAtom = 23, RuleByte = 24, RuleMultibyte = 25, 
    RuleCharacter = 26
  };

  explicit asm6502Parser(antlr4::TokenStream *input);

  asm6502Parser(antlr4::TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options);

  ~asm6502Parser() override;

  std::string getGrammarFileName() const override;

  const antlr4::atn::ATN& getATN() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;


  class ProgramContext;
  class LineContext;
  class LabelContext;
  class AssignContext;
  class InstructionContext;
  class CommentContext;
  class NopContext;
  class ImplicitContext;
  class AccContext;
  class ImmediateContext;
  class X_indexContext;
  class Y_indexContext;
  class X_indirectContext;
  class Indirect_yContext;
  class AbsoluteContext;
  class RelativeContext;
  class MnemonicContext;
  class ShiftContext;
  class JumpContext;
  class JsrContext;
  class ExpressionContext;
  class Binary_opContext;
  class Unary_opContext;
  class AtomContext;
  class ByteContext;
  class MultibyteContext;
  class CharacterContext; 

  class  ProgramContext : public antlr4::ParserRuleContext {
  public:
    ProgramContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *EOF();
    std::vector<LineContext *> line();
    LineContext* line(size_t i);

   
  };

  ProgramContext* program();

  class  LineContext : public antlr4::ParserRuleContext {
  public:
    LineContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    LabelContext *label();
    std::vector<antlr4::tree::TerminalNode *> WHITESPACE();
    antlr4::tree::TerminalNode* WHITESPACE(size_t i);
    InstructionContext *instruction();
    CommentContext *comment();
    antlr4::tree::TerminalNode *NEWLINE();
    AssignContext *assign();

   
  };

  LineContext* line();

  class  LabelContext : public antlr4::ParserRuleContext {
  public:
    LabelContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SYMBOL();
    antlr4::tree::TerminalNode *AT();
    antlr4::tree::TerminalNode *COLON();

   
  };

  LabelContext* label();

  class  AssignContext : public antlr4::ParserRuleContext {
  public:
    AssignContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SYMBOL();
    std::vector<antlr4::tree::TerminalNode *> WHITESPACE();
    antlr4::tree::TerminalNode* WHITESPACE(size_t i);
    antlr4::tree::TerminalNode *EQU();
    ExpressionContext *expression();

   
  };

  AssignContext* assign();

  class  InstructionContext : public antlr4::ParserRuleContext {
  public:
    InstructionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    NopContext *nop();
    ImplicitContext *implicit();
    AccContext *acc();
    ImmediateContext *immediate();
    X_indexContext *x_index();
    Y_indexContext *y_index();
    X_indirectContext *x_indirect();
    Indirect_yContext *indirect_y();
    AbsoluteContext *absolute();
    RelativeContext *relative();
    JumpContext *jump();
    JsrContext *jsr();

   
  };

  InstructionContext* instruction();

  class  CommentContext : public antlr4::ParserRuleContext {
  public:
    CommentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *COMMENT();

   
  };

  CommentContext* comment();

  class  NopContext : public antlr4::ParserRuleContext {
  public:
    NopContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *NOP();

   
  };

  NopContext* nop();

  class  ImplicitContext : public antlr4::ParserRuleContext {
  public:
    ImplicitContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IMPLIED();

   
  };

  ImplicitContext* implicit();

  class  AccContext : public antlr4::ParserRuleContext {
  public:
    AccContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ShiftContext *shift();
    antlr4::tree::TerminalNode *WHITESPACE();
    antlr4::tree::TerminalNode *ACC();

   
  };

  AccContext* acc();

  class  ImmediateContext : public antlr4::ParserRuleContext {
  public:
    ImmediateContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    MnemonicContext *mnemonic();
    antlr4::tree::TerminalNode *WHITESPACE();
    antlr4::tree::TerminalNode *HASH();
    ExpressionContext *expression();

   
  };

  ImmediateContext* immediate();

  class  X_indexContext : public antlr4::ParserRuleContext {
  public:
    X_indexContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *WHITESPACE();
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *X_INDEX();
    ShiftContext *shift();
    MnemonicContext *mnemonic();

   
  };

  X_indexContext* x_index();

  class  Y_indexContext : public antlr4::ParserRuleContext {
  public:
    Y_indexContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *WHITESPACE();
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *Y_INDEX();
    ShiftContext *shift();
    MnemonicContext *mnemonic();

   
  };

  Y_indexContext* y_index();

  class  X_indirectContext : public antlr4::ParserRuleContext {
  public:
    X_indirectContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LPAREN();
    antlr4::tree::TerminalNode *WHITESPACE();
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *X_INDEX();
    antlr4::tree::TerminalNode *RPAREN();
    ShiftContext *shift();
    MnemonicContext *mnemonic();

   
  };

  X_indirectContext* x_indirect();

  class  Indirect_yContext : public antlr4::ParserRuleContext {
  public:
    Indirect_yContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LPAREN();
    antlr4::tree::TerminalNode *WHITESPACE();
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *RPAREN();
    antlr4::tree::TerminalNode *Y_INDEX();
    ShiftContext *shift();
    MnemonicContext *mnemonic();

   
  };

  Indirect_yContext* indirect_y();

  class  AbsoluteContext : public antlr4::ParserRuleContext {
  public:
    AbsoluteContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *WHITESPACE();
    ExpressionContext *expression();
    ShiftContext *shift();
    MnemonicContext *mnemonic();

   
  };

  AbsoluteContext* absolute();

  class  RelativeContext : public antlr4::ParserRuleContext {
  public:
    RelativeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *BRANCH();
    antlr4::tree::TerminalNode *WHITESPACE();
    ExpressionContext *expression();

   
  };

  RelativeContext* relative();

  class  MnemonicContext : public antlr4::ParserRuleContext {
  public:
    MnemonicContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *MNEMONIC();

   
  };

  MnemonicContext* mnemonic();

  class  ShiftContext : public antlr4::ParserRuleContext {
  public:
    ShiftContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SHIFT();

   
  };

  ShiftContext* shift();

  class  JumpContext : public antlr4::ParserRuleContext {
  public:
    JumpContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *JUMP();
    antlr4::tree::TerminalNode *WHITESPACE();
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *LPAREN();
    antlr4::tree::TerminalNode *RPAREN();

   
  };

  JumpContext* jump();

  class  JsrContext : public antlr4::ParserRuleContext {
  public:
    JsrContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *JSR();
    antlr4::tree::TerminalNode *WHITESPACE();
    ExpressionContext *expression();

   
  };

  JsrContext* jsr();

  class  ExpressionContext : public antlr4::ParserRuleContext {
  public:
    ExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LBRACKET();
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    antlr4::tree::TerminalNode *RBRACKET();
    AtomContext *atom();
    Binary_opContext *binary_op();

   
  };

  ExpressionContext* expression();
  ExpressionContext* expression(int precedence);
  class  Binary_opContext : public antlr4::ParserRuleContext {
  public:
    Binary_opContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *PLUS();
    antlr4::tree::TerminalNode *MINUS();
    antlr4::tree::TerminalNode *STAR();
    antlr4::tree::TerminalNode *SLASH();

   
  };

  Binary_opContext* binary_op();

  class  Unary_opContext : public antlr4::ParserRuleContext {
  public:
    Unary_opContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LOW_BYTE_VALUE();
    antlr4::tree::TerminalNode *HIGH_BYTE_VALUE();
    antlr4::tree::TerminalNode *PLUS();
    antlr4::tree::TerminalNode *MINUS();

   
  };

  Unary_opContext* unary_op();

  class  AtomContext : public antlr4::ParserRuleContext {
  public:
    AtomContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ByteContext *byte();
    MultibyteContext *multibyte();
    CharacterContext *character();
    antlr4::tree::TerminalNode *SYMBOL();
    antlr4::tree::TerminalNode *STAR();
    Unary_opContext *unary_op();

   
  };

  AtomContext* atom();

  class  ByteContext : public antlr4::ParserRuleContext {
  public:
    ByteContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *HEX_BYTE();
    antlr4::tree::TerminalNode *DECIMAL_BYTE();
    antlr4::tree::TerminalNode *OCTAL_BYTE();
    antlr4::tree::TerminalNode *BINARY_BYTE();

   
  };

  ByteContext* byte();

  class  MultibyteContext : public antlr4::ParserRuleContext {
  public:
    MultibyteContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *HEX_NUMBER();
    antlr4::tree::TerminalNode *DECIMAL_NUMBER();
    antlr4::tree::TerminalNode *OCTAL_NUMBER();
    antlr4::tree::TerminalNode *BINARY_NUMBER();

   
  };

  MultibyteContext* multibyte();

  class  CharacterContext : public antlr4::ParserRuleContext {
  public:
    CharacterContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *CHARACTER();

   
  };

  CharacterContext* character();


  bool sempred(antlr4::RuleContext *_localctx, size_t ruleIndex, size_t predicateIndex) override;

  bool expressionSempred(ExpressionContext *_localctx, size_t predicateIndex);

  // By default the static state used to implement the parser is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:
};

