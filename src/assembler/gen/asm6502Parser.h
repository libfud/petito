
// Generated from asm6502Parser.g4 by ANTLR 4.10.1

#pragma once


#include "antlr4-runtime.h"




class  asm6502Parser : public antlr4::Parser {
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
    RuleProgram = 0, RuleLine = 1, RuleLabel = 2, RuleAssign = 3, RuleInstruction = 4, 
    RuleComment = 5, RuleNop = 6, RuleImplicit = 7, RuleAcc = 8, RuleImmediate = 9, 
    RuleZero_page = 10, RuleX_index = 11, RuleY_index = 12, RuleX_indirect = 13, 
    RuleIndirect_y = 14, RuleAbsolute = 15, RuleRelative = 16, RuleMnemonic = 17, 
    RuleShift = 18, RuleJump = 19, RuleJsr = 20, RuleExpression = 21, RuleBinary_op = 22, 
    RuleUnary_op = 23, RuleAtom = 24, RuleByte = 25, RuleMultibyte = 26, 
    RuleCharacter = 27, RuleDirective = 28, RuleOrg = 29, RuleByte_directive = 30, 
    RuleDbyte_directive = 31, RuleWord_directive = 32, RuleText_directive = 33, 
    RuleByte_directive_value = 34, RuleString = 35, RuleStringContents = 36, 
    RuleAlign_directive = 37, RuleFill_directive = 38, RuleRepeat_directive = 39
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
  class Zero_pageContext;
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
  class DirectiveContext;
  class OrgContext;
  class Byte_directiveContext;
  class Dbyte_directiveContext;
  class Word_directiveContext;
  class Text_directiveContext;
  class Byte_directive_valueContext;
  class StringContext;
  class StringContentsContext;
  class Align_directiveContext;
  class Fill_directiveContext;
  class Repeat_directiveContext; 

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
    DirectiveContext *directive();

   
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
    Zero_pageContext *zero_page();
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

  class  Zero_pageContext : public antlr4::ParserRuleContext {
  public:
    Zero_pageContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *FORCED_BYTE();
    antlr4::tree::TerminalNode *WHITESPACE();
    ExpressionContext *expression();
    ShiftContext *shift();
    MnemonicContext *mnemonic();
    ByteContext *byte();
    CharacterContext *character();

   
  };

  Zero_pageContext* zero_page();

  class  X_indexContext : public antlr4::ParserRuleContext {
  public:
    X_indexContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *WHITESPACE();
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *X_INDEX();
    ShiftContext *shift();
    MnemonicContext *mnemonic();
    antlr4::tree::TerminalNode *FORCED_BYTE();
    antlr4::tree::TerminalNode *FORCED_WORD();

   
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
    antlr4::tree::TerminalNode *FORCED_BYTE();
    antlr4::tree::TerminalNode *FORCED_WORD();

   
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
    antlr4::tree::TerminalNode *FORCED_WORD();

   
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
    Unary_opContext *unary_op();
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

  class  DirectiveContext : public antlr4::ParserRuleContext {
  public:
    DirectiveContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    OrgContext *org();
    Byte_directiveContext *byte_directive();
    Dbyte_directiveContext *dbyte_directive();
    Word_directiveContext *word_directive();
    Text_directiveContext *text_directive();
    Align_directiveContext *align_directive();
    Fill_directiveContext *fill_directive();
    Repeat_directiveContext *repeat_directive();

   
  };

  DirectiveContext* directive();

  class  OrgContext : public antlr4::ParserRuleContext {
  public:
    OrgContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *DORG();
    std::vector<antlr4::tree::TerminalNode *> WHITESPACE();
    antlr4::tree::TerminalNode* WHITESPACE(size_t i);
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *EQU();

   
  };

  OrgContext* org();

  class  Byte_directiveContext : public antlr4::ParserRuleContext {
  public:
    Byte_directiveContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *DBYTE();
    std::vector<Byte_directive_valueContext *> byte_directive_value();
    Byte_directive_valueContext* byte_directive_value(size_t i);

   
  };

  Byte_directiveContext* byte_directive();

  class  Dbyte_directiveContext : public antlr4::ParserRuleContext {
  public:
    Dbyte_directiveContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *DDBYTE();
    std::vector<Byte_directive_valueContext *> byte_directive_value();
    Byte_directive_valueContext* byte_directive_value(size_t i);

   
  };

  Dbyte_directiveContext* dbyte_directive();

  class  Word_directiveContext : public antlr4::ParserRuleContext {
  public:
    Word_directiveContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *DWORD();
    std::vector<Byte_directive_valueContext *> byte_directive_value();
    Byte_directive_valueContext* byte_directive_value(size_t i);

   
  };

  Word_directiveContext* word_directive();

  class  Text_directiveContext : public antlr4::ParserRuleContext {
  public:
    Text_directiveContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *DTEXT();
    antlr4::tree::TerminalNode *WHITESPACE();
    StringContext *string();

   
  };

  Text_directiveContext* text_directive();

  class  Byte_directive_valueContext : public antlr4::ParserRuleContext {
  public:
    Byte_directive_valueContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *WHITESPACE();
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *COMMA();

   
  };

  Byte_directive_valueContext* byte_directive_value();

  class  StringContext : public antlr4::ParserRuleContext {
  public:
    StringContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> DQUOTE();
    antlr4::tree::TerminalNode* DQUOTE(size_t i);
    std::vector<StringContentsContext *> stringContents();
    StringContentsContext* stringContents(size_t i);

   
  };

  StringContext* string();

  class  StringContentsContext : public antlr4::ParserRuleContext {
  public:
    StringContentsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *TEXT();
    antlr4::tree::TerminalNode *ESCAPE_SEQUENCE();

   
  };

  StringContentsContext* stringContents();

  class  Align_directiveContext : public antlr4::ParserRuleContext {
  public:
    Align_directiveContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *DALIGN();
    antlr4::tree::TerminalNode *WHITESPACE();
    ExpressionContext *expression();

   
  };

  Align_directiveContext* align_directive();

  class  Fill_directiveContext : public antlr4::ParserRuleContext {
  public:
    Fill_directiveContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *DFILL();
    std::vector<antlr4::tree::TerminalNode *> WHITESPACE();
    antlr4::tree::TerminalNode* WHITESPACE(size_t i);
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);

   
  };

  Fill_directiveContext* fill_directive();

  class  Repeat_directiveContext : public antlr4::ParserRuleContext {
  public:
    Repeat_directiveContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *DFILL();
    std::vector<antlr4::tree::TerminalNode *> WHITESPACE();
    antlr4::tree::TerminalNode* WHITESPACE(size_t i);
    ByteContext *byte();
    MultibyteContext *multibyte();
    DirectiveContext *directive();
    InstructionContext *instruction();

   
  };

  Repeat_directiveContext* repeat_directive();


  bool sempred(antlr4::RuleContext *_localctx, size_t ruleIndex, size_t predicateIndex) override;

  bool expressionSempred(ExpressionContext *_localctx, size_t predicateIndex);

  // By default the static state used to implement the parser is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:
};

