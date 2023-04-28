
// Generated from asm6502.g4 by ANTLR 4.10.1



#include "asm6502Parser.h"


using namespace antlrcpp;

using namespace antlr4;

namespace {

struct Asm6502ParserStaticData final {
  Asm6502ParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  Asm6502ParserStaticData(const Asm6502ParserStaticData&) = delete;
  Asm6502ParserStaticData(Asm6502ParserStaticData&&) = delete;
  Asm6502ParserStaticData& operator=(const Asm6502ParserStaticData&) = delete;
  Asm6502ParserStaticData& operator=(Asm6502ParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

std::once_flag asm6502ParserOnceFlag;
Asm6502ParserStaticData *asm6502ParserStaticData = nullptr;

void asm6502ParserInitialize() {
  assert(asm6502ParserStaticData == nullptr);
  auto staticData = std::make_unique<Asm6502ParserStaticData>(
    std::vector<std::string>{
      "program", "line", "label", "assign", "instruction", "comment", "nop", 
      "implicit", "acc", "immediate", "x_index", "y_index", "x_indirect", 
      "indirect_y", "absolute", "relative", "mnemonic", "shift", "jump", 
      "jsr", "expression", "binary_op", "unary_op", "atom", "byte", "multibyte", 
      "character"
    },
    std::vector<std::string>{
      "", "", "", "", "'_'", "'+'", "'-'", "'*'", "'/'", "'<'", "'>'", "'['", 
      "']'", "'('", "')'", "'#'", "':'", "'@'", "", "", "", "", "", "", 
      "", "", "", "", "", "", "", "'NOP'", "", "", "", "", "", "", "", "'A'"
    },
    std::vector<std::string>{
      "", "COMMENT", "WHITESPACE", "NEWLINE", "UNDERSCORE", "PLUS", "MINUS", 
      "STAR", "SLASH", "LOW_BYTE_VALUE", "HIGH_BYTE_VALUE", "LBRACKET", 
      "RBRACKET", "LPAREN", "RPAREN", "HASH", "COLON", "AT", "X_INDEX", 
      "Y_INDEX", "OCTAL_BYTE", "OCTAL_NUMBER", "HEX_BYTE", "HEX_NUMBER", 
      "DECIMAL_BYTE", "DECIMAL_NUMBER", "BINARY_BYTE", "BINARY_NUMBER", 
      "CHARACTER", "ORG", "EQU", "NOP", "IMPLIED", "BRANCH", "SHIFT", "JUMP", 
      "JSR", "MNEMONIC", "ILLEGAL", "ACC", "SYMBOL"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,40,296,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,1,0,4,0,56,8,0,11,
  	0,12,0,57,1,0,1,0,1,1,3,1,63,8,1,1,1,1,1,1,1,1,1,3,1,69,8,1,1,1,1,1,1,
  	1,1,1,3,1,75,8,1,1,1,1,1,1,1,1,1,3,1,81,8,1,1,1,1,1,1,1,3,1,86,8,1,1,
  	1,1,1,3,1,90,8,1,1,1,1,1,1,1,1,1,3,1,96,8,1,1,1,1,1,3,1,100,8,1,1,1,1,
  	1,1,1,3,1,105,8,1,1,1,1,1,1,1,3,1,110,8,1,1,1,1,1,3,1,114,8,1,1,1,1,1,
  	3,1,118,8,1,1,1,1,1,1,1,1,1,3,1,124,8,1,1,1,1,1,3,1,128,8,1,1,1,1,1,1,
  	1,3,1,133,8,1,1,1,3,1,136,8,1,1,1,1,1,3,1,140,8,1,1,1,1,1,3,1,144,8,1,
  	1,1,1,1,3,1,148,8,1,1,2,3,2,151,8,2,1,2,1,2,3,2,155,8,2,1,3,1,3,1,3,1,
  	3,1,3,1,3,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,3,4,175,8,4,
  	1,5,1,5,1,6,1,6,1,7,1,7,1,8,1,8,1,8,3,8,186,8,8,1,9,1,9,1,9,1,9,1,9,1,
  	10,1,10,3,10,195,8,10,1,10,1,10,1,10,1,10,1,11,1,11,3,11,203,8,11,1,11,
  	1,11,1,11,1,11,1,12,1,12,1,12,3,12,212,8,12,1,12,1,12,1,12,1,12,1,12,
  	1,13,1,13,1,13,3,13,222,8,13,1,13,1,13,1,13,1,13,1,13,1,14,1,14,3,14,
  	231,8,14,1,14,1,14,1,14,1,15,1,15,1,15,1,15,1,16,1,16,1,17,1,17,1,18,
  	1,18,1,18,1,18,1,18,1,18,1,18,1,18,1,18,3,18,253,8,18,1,19,1,19,1,19,
  	1,19,1,20,1,20,1,20,1,20,1,20,1,20,3,20,265,8,20,1,20,1,20,1,20,1,20,
  	5,20,271,8,20,10,20,12,20,274,9,20,1,21,1,21,1,22,1,22,1,23,3,23,281,
  	8,23,1,23,1,23,1,23,1,23,1,23,3,23,288,8,23,1,24,1,24,1,25,1,25,1,26,
  	1,26,1,26,0,1,40,27,0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,
  	36,38,40,42,44,46,48,50,52,0,4,1,0,5,8,2,0,5,6,9,10,4,0,20,20,22,22,24,
  	24,26,26,4,0,21,21,23,23,25,25,27,27,322,0,55,1,0,0,0,2,147,1,0,0,0,4,
  	150,1,0,0,0,6,156,1,0,0,0,8,174,1,0,0,0,10,176,1,0,0,0,12,178,1,0,0,0,
  	14,180,1,0,0,0,16,182,1,0,0,0,18,187,1,0,0,0,20,194,1,0,0,0,22,202,1,
  	0,0,0,24,208,1,0,0,0,26,218,1,0,0,0,28,230,1,0,0,0,30,235,1,0,0,0,32,
  	239,1,0,0,0,34,241,1,0,0,0,36,252,1,0,0,0,38,254,1,0,0,0,40,264,1,0,0,
  	0,42,275,1,0,0,0,44,277,1,0,0,0,46,280,1,0,0,0,48,289,1,0,0,0,50,291,
  	1,0,0,0,52,293,1,0,0,0,54,56,3,2,1,0,55,54,1,0,0,0,56,57,1,0,0,0,57,55,
  	1,0,0,0,57,58,1,0,0,0,58,59,1,0,0,0,59,60,5,0,0,1,60,1,1,0,0,0,61,63,
  	5,2,0,0,62,61,1,0,0,0,62,63,1,0,0,0,63,64,1,0,0,0,64,65,3,4,2,0,65,66,
  	5,2,0,0,66,68,3,8,4,0,67,69,5,2,0,0,68,67,1,0,0,0,68,69,1,0,0,0,69,70,
  	1,0,0,0,70,71,3,10,5,0,71,72,5,3,0,0,72,148,1,0,0,0,73,75,5,2,0,0,74,
  	73,1,0,0,0,74,75,1,0,0,0,75,76,1,0,0,0,76,77,3,4,2,0,77,78,5,2,0,0,78,
  	80,3,8,4,0,79,81,5,2,0,0,80,79,1,0,0,0,80,81,1,0,0,0,81,82,1,0,0,0,82,
  	83,5,3,0,0,83,148,1,0,0,0,84,86,5,2,0,0,85,84,1,0,0,0,85,86,1,0,0,0,86,
  	87,1,0,0,0,87,89,3,4,2,0,88,90,5,2,0,0,89,88,1,0,0,0,89,90,1,0,0,0,90,
  	91,1,0,0,0,91,92,3,10,5,0,92,93,5,3,0,0,93,148,1,0,0,0,94,96,5,2,0,0,
  	95,94,1,0,0,0,95,96,1,0,0,0,96,97,1,0,0,0,97,99,3,4,2,0,98,100,5,2,0,
  	0,99,98,1,0,0,0,99,100,1,0,0,0,100,101,1,0,0,0,101,102,5,3,0,0,102,148,
  	1,0,0,0,103,105,5,2,0,0,104,103,1,0,0,0,104,105,1,0,0,0,105,109,1,0,0,
  	0,106,107,3,4,2,0,107,108,5,2,0,0,108,110,1,0,0,0,109,106,1,0,0,0,109,
  	110,1,0,0,0,110,111,1,0,0,0,111,148,3,6,3,0,112,114,5,2,0,0,113,112,1,
  	0,0,0,113,114,1,0,0,0,114,115,1,0,0,0,115,117,3,8,4,0,116,118,5,2,0,0,
  	117,116,1,0,0,0,117,118,1,0,0,0,118,119,1,0,0,0,119,120,3,10,5,0,120,
  	121,5,3,0,0,121,148,1,0,0,0,122,124,5,2,0,0,123,122,1,0,0,0,123,124,1,
  	0,0,0,124,125,1,0,0,0,125,127,3,8,4,0,126,128,5,2,0,0,127,126,1,0,0,0,
  	127,128,1,0,0,0,128,129,1,0,0,0,129,130,5,3,0,0,130,148,1,0,0,0,131,133,
  	5,2,0,0,132,131,1,0,0,0,132,133,1,0,0,0,133,135,1,0,0,0,134,136,3,10,
  	5,0,135,134,1,0,0,0,135,136,1,0,0,0,136,137,1,0,0,0,137,148,5,3,0,0,138,
  	140,5,2,0,0,139,138,1,0,0,0,139,140,1,0,0,0,140,141,1,0,0,0,141,143,3,
  	6,3,0,142,144,3,10,5,0,143,142,1,0,0,0,143,144,1,0,0,0,144,145,1,0,0,
  	0,145,146,5,3,0,0,146,148,1,0,0,0,147,62,1,0,0,0,147,74,1,0,0,0,147,85,
  	1,0,0,0,147,95,1,0,0,0,147,104,1,0,0,0,147,113,1,0,0,0,147,123,1,0,0,
  	0,147,132,1,0,0,0,147,139,1,0,0,0,148,3,1,0,0,0,149,151,5,17,0,0,150,
  	149,1,0,0,0,150,151,1,0,0,0,151,152,1,0,0,0,152,154,5,40,0,0,153,155,
  	5,16,0,0,154,153,1,0,0,0,154,155,1,0,0,0,155,5,1,0,0,0,156,157,5,40,0,
  	0,157,158,5,2,0,0,158,159,5,30,0,0,159,160,5,2,0,0,160,161,3,40,20,0,
  	161,7,1,0,0,0,162,175,3,12,6,0,163,175,3,14,7,0,164,175,3,16,8,0,165,
  	175,3,18,9,0,166,175,3,20,10,0,167,175,3,22,11,0,168,175,3,24,12,0,169,
  	175,3,26,13,0,170,175,3,28,14,0,171,175,3,30,15,0,172,175,3,36,18,0,173,
  	175,3,38,19,0,174,162,1,0,0,0,174,163,1,0,0,0,174,164,1,0,0,0,174,165,
  	1,0,0,0,174,166,1,0,0,0,174,167,1,0,0,0,174,168,1,0,0,0,174,169,1,0,0,
  	0,174,170,1,0,0,0,174,171,1,0,0,0,174,172,1,0,0,0,174,173,1,0,0,0,175,
  	9,1,0,0,0,176,177,5,1,0,0,177,11,1,0,0,0,178,179,5,31,0,0,179,13,1,0,
  	0,0,180,181,5,32,0,0,181,15,1,0,0,0,182,185,3,34,17,0,183,184,5,2,0,0,
  	184,186,5,39,0,0,185,183,1,0,0,0,185,186,1,0,0,0,186,17,1,0,0,0,187,188,
  	3,32,16,0,188,189,5,2,0,0,189,190,5,15,0,0,190,191,3,40,20,0,191,19,1,
  	0,0,0,192,195,3,34,17,0,193,195,3,32,16,0,194,192,1,0,0,0,194,193,1,0,
  	0,0,195,196,1,0,0,0,196,197,5,2,0,0,197,198,3,40,20,0,198,199,5,18,0,
  	0,199,21,1,0,0,0,200,203,3,34,17,0,201,203,3,32,16,0,202,200,1,0,0,0,
  	202,201,1,0,0,0,203,204,1,0,0,0,204,205,5,2,0,0,205,206,3,40,20,0,206,
  	207,5,19,0,0,207,23,1,0,0,0,208,211,5,13,0,0,209,212,3,34,17,0,210,212,
  	3,32,16,0,211,209,1,0,0,0,211,210,1,0,0,0,212,213,1,0,0,0,213,214,5,2,
  	0,0,214,215,3,40,20,0,215,216,5,18,0,0,216,217,5,14,0,0,217,25,1,0,0,
  	0,218,221,5,13,0,0,219,222,3,34,17,0,220,222,3,32,16,0,221,219,1,0,0,
  	0,221,220,1,0,0,0,222,223,1,0,0,0,223,224,5,2,0,0,224,225,3,40,20,0,225,
  	226,5,14,0,0,226,227,5,19,0,0,227,27,1,0,0,0,228,231,3,34,17,0,229,231,
  	3,32,16,0,230,228,1,0,0,0,230,229,1,0,0,0,231,232,1,0,0,0,232,233,5,2,
  	0,0,233,234,3,40,20,0,234,29,1,0,0,0,235,236,5,33,0,0,236,237,5,2,0,0,
  	237,238,3,40,20,0,238,31,1,0,0,0,239,240,5,37,0,0,240,33,1,0,0,0,241,
  	242,5,34,0,0,242,35,1,0,0,0,243,244,5,35,0,0,244,245,5,2,0,0,245,253,
  	3,40,20,0,246,247,5,35,0,0,247,248,5,2,0,0,248,249,5,13,0,0,249,250,3,
  	40,20,0,250,251,5,14,0,0,251,253,1,0,0,0,252,243,1,0,0,0,252,246,1,0,
  	0,0,253,37,1,0,0,0,254,255,5,36,0,0,255,256,5,2,0,0,256,257,3,40,20,0,
  	257,39,1,0,0,0,258,259,6,20,-1,0,259,260,5,11,0,0,260,261,3,40,20,0,261,
  	262,5,12,0,0,262,265,1,0,0,0,263,265,3,46,23,0,264,258,1,0,0,0,264,263,
  	1,0,0,0,265,272,1,0,0,0,266,267,10,3,0,0,267,268,3,42,21,0,268,269,3,
  	40,20,4,269,271,1,0,0,0,270,266,1,0,0,0,271,274,1,0,0,0,272,270,1,0,0,
  	0,272,273,1,0,0,0,273,41,1,0,0,0,274,272,1,0,0,0,275,276,7,0,0,0,276,
  	43,1,0,0,0,277,278,7,1,0,0,278,45,1,0,0,0,279,281,3,44,22,0,280,279,1,
  	0,0,0,280,281,1,0,0,0,281,287,1,0,0,0,282,288,3,48,24,0,283,288,3,50,
  	25,0,284,288,3,52,26,0,285,288,5,40,0,0,286,288,5,7,0,0,287,282,1,0,0,
  	0,287,283,1,0,0,0,287,284,1,0,0,0,287,285,1,0,0,0,287,286,1,0,0,0,288,
  	47,1,0,0,0,289,290,7,2,0,0,290,49,1,0,0,0,291,292,7,3,0,0,292,51,1,0,
  	0,0,293,294,5,28,0,0,294,53,1,0,0,0,34,57,62,68,74,80,85,89,95,99,104,
  	109,113,117,123,127,132,135,139,143,147,150,154,174,185,194,202,211,221,
  	230,252,264,272,280,287
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  asm6502ParserStaticData = staticData.release();
}

}

asm6502Parser::asm6502Parser(TokenStream *input) : asm6502Parser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

asm6502Parser::asm6502Parser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  asm6502Parser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *asm6502ParserStaticData->atn, asm6502ParserStaticData->decisionToDFA, asm6502ParserStaticData->sharedContextCache, options);
}

asm6502Parser::~asm6502Parser() {
  delete _interpreter;
}

const atn::ATN& asm6502Parser::getATN() const {
  return *asm6502ParserStaticData->atn;
}

std::string asm6502Parser::getGrammarFileName() const {
  return "asm6502.g4";
}

const std::vector<std::string>& asm6502Parser::getRuleNames() const {
  return asm6502ParserStaticData->ruleNames;
}

const dfa::Vocabulary& asm6502Parser::getVocabulary() const {
  return asm6502ParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView asm6502Parser::getSerializedATN() const {
  return asm6502ParserStaticData->serializedATN;
}


//----------------- ProgramContext ------------------------------------------------------------------

asm6502Parser::ProgramContext::ProgramContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* asm6502Parser::ProgramContext::EOF() {
  return getToken(asm6502Parser::EOF, 0);
}

std::vector<asm6502Parser::LineContext *> asm6502Parser::ProgramContext::line() {
  return getRuleContexts<asm6502Parser::LineContext>();
}

asm6502Parser::LineContext* asm6502Parser::ProgramContext::line(size_t i) {
  return getRuleContext<asm6502Parser::LineContext>(i);
}


size_t asm6502Parser::ProgramContext::getRuleIndex() const {
  return asm6502Parser::RuleProgram;
}


asm6502Parser::ProgramContext* asm6502Parser::program() {
  ProgramContext *_localctx = _tracker.createInstance<ProgramContext>(_ctx, getState());
  enterRule(_localctx, 0, asm6502Parser::RuleProgram);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(55); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(54);
      line();
      setState(57); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << asm6502Parser::COMMENT)
      | (1ULL << asm6502Parser::WHITESPACE)
      | (1ULL << asm6502Parser::NEWLINE)
      | (1ULL << asm6502Parser::LPAREN)
      | (1ULL << asm6502Parser::AT)
      | (1ULL << asm6502Parser::NOP)
      | (1ULL << asm6502Parser::IMPLIED)
      | (1ULL << asm6502Parser::BRANCH)
      | (1ULL << asm6502Parser::SHIFT)
      | (1ULL << asm6502Parser::JUMP)
      | (1ULL << asm6502Parser::JSR)
      | (1ULL << asm6502Parser::MNEMONIC)
      | (1ULL << asm6502Parser::SYMBOL))) != 0));
    setState(59);
    match(asm6502Parser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LineContext ------------------------------------------------------------------

asm6502Parser::LineContext::LineContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

asm6502Parser::LabelContext* asm6502Parser::LineContext::label() {
  return getRuleContext<asm6502Parser::LabelContext>(0);
}

std::vector<tree::TerminalNode *> asm6502Parser::LineContext::WHITESPACE() {
  return getTokens(asm6502Parser::WHITESPACE);
}

tree::TerminalNode* asm6502Parser::LineContext::WHITESPACE(size_t i) {
  return getToken(asm6502Parser::WHITESPACE, i);
}

asm6502Parser::InstructionContext* asm6502Parser::LineContext::instruction() {
  return getRuleContext<asm6502Parser::InstructionContext>(0);
}

asm6502Parser::CommentContext* asm6502Parser::LineContext::comment() {
  return getRuleContext<asm6502Parser::CommentContext>(0);
}

tree::TerminalNode* asm6502Parser::LineContext::NEWLINE() {
  return getToken(asm6502Parser::NEWLINE, 0);
}

asm6502Parser::AssignContext* asm6502Parser::LineContext::assign() {
  return getRuleContext<asm6502Parser::AssignContext>(0);
}


size_t asm6502Parser::LineContext::getRuleIndex() const {
  return asm6502Parser::RuleLine;
}


asm6502Parser::LineContext* asm6502Parser::line() {
  LineContext *_localctx = _tracker.createInstance<LineContext>(_ctx, getState());
  enterRule(_localctx, 2, asm6502Parser::RuleLine);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(147);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 19, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(62);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == asm6502Parser::WHITESPACE) {
        setState(61);
        match(asm6502Parser::WHITESPACE);
      }
      setState(64);
      label();
      setState(65);
      match(asm6502Parser::WHITESPACE);
      setState(66);
      instruction();
      setState(68);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == asm6502Parser::WHITESPACE) {
        setState(67);
        match(asm6502Parser::WHITESPACE);
      }
      setState(70);
      comment();
      setState(71);
      match(asm6502Parser::NEWLINE);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(74);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == asm6502Parser::WHITESPACE) {
        setState(73);
        match(asm6502Parser::WHITESPACE);
      }
      setState(76);
      label();
      setState(77);
      match(asm6502Parser::WHITESPACE);
      setState(78);
      instruction();
      setState(80);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == asm6502Parser::WHITESPACE) {
        setState(79);
        match(asm6502Parser::WHITESPACE);
      }
      setState(82);
      match(asm6502Parser::NEWLINE);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(85);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == asm6502Parser::WHITESPACE) {
        setState(84);
        match(asm6502Parser::WHITESPACE);
      }
      setState(87);
      label();
      setState(89);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == asm6502Parser::WHITESPACE) {
        setState(88);
        match(asm6502Parser::WHITESPACE);
      }
      setState(91);
      comment();
      setState(92);
      match(asm6502Parser::NEWLINE);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(95);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == asm6502Parser::WHITESPACE) {
        setState(94);
        match(asm6502Parser::WHITESPACE);
      }
      setState(97);
      label();
      setState(99);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == asm6502Parser::WHITESPACE) {
        setState(98);
        match(asm6502Parser::WHITESPACE);
      }
      setState(101);
      match(asm6502Parser::NEWLINE);
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(104);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == asm6502Parser::WHITESPACE) {
        setState(103);
        match(asm6502Parser::WHITESPACE);
      }
      setState(109);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 10, _ctx)) {
      case 1: {
        setState(106);
        label();
        setState(107);
        match(asm6502Parser::WHITESPACE);
        break;
      }

      default:
        break;
      }
      setState(111);
      assign();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(113);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == asm6502Parser::WHITESPACE) {
        setState(112);
        match(asm6502Parser::WHITESPACE);
      }
      setState(115);
      instruction();
      setState(117);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == asm6502Parser::WHITESPACE) {
        setState(116);
        match(asm6502Parser::WHITESPACE);
      }
      setState(119);
      comment();
      setState(120);
      match(asm6502Parser::NEWLINE);
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(123);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == asm6502Parser::WHITESPACE) {
        setState(122);
        match(asm6502Parser::WHITESPACE);
      }
      setState(125);
      instruction();
      setState(127);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == asm6502Parser::WHITESPACE) {
        setState(126);
        match(asm6502Parser::WHITESPACE);
      }
      setState(129);
      match(asm6502Parser::NEWLINE);
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(132);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == asm6502Parser::WHITESPACE) {
        setState(131);
        match(asm6502Parser::WHITESPACE);
      }
      setState(135);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == asm6502Parser::COMMENT) {
        setState(134);
        comment();
      }
      setState(137);
      match(asm6502Parser::NEWLINE);
      break;
    }

    case 9: {
      enterOuterAlt(_localctx, 9);
      setState(139);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == asm6502Parser::WHITESPACE) {
        setState(138);
        match(asm6502Parser::WHITESPACE);
      }
      setState(141);
      assign();
      setState(143);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == asm6502Parser::COMMENT) {
        setState(142);
        comment();
      }
      setState(145);
      match(asm6502Parser::NEWLINE);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LabelContext ------------------------------------------------------------------

asm6502Parser::LabelContext::LabelContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* asm6502Parser::LabelContext::SYMBOL() {
  return getToken(asm6502Parser::SYMBOL, 0);
}

tree::TerminalNode* asm6502Parser::LabelContext::AT() {
  return getToken(asm6502Parser::AT, 0);
}

tree::TerminalNode* asm6502Parser::LabelContext::COLON() {
  return getToken(asm6502Parser::COLON, 0);
}


size_t asm6502Parser::LabelContext::getRuleIndex() const {
  return asm6502Parser::RuleLabel;
}


asm6502Parser::LabelContext* asm6502Parser::label() {
  LabelContext *_localctx = _tracker.createInstance<LabelContext>(_ctx, getState());
  enterRule(_localctx, 4, asm6502Parser::RuleLabel);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(150);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == asm6502Parser::AT) {
      setState(149);
      match(asm6502Parser::AT);
    }
    setState(152);
    match(asm6502Parser::SYMBOL);
    setState(154);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == asm6502Parser::COLON) {
      setState(153);
      match(asm6502Parser::COLON);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AssignContext ------------------------------------------------------------------

asm6502Parser::AssignContext::AssignContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* asm6502Parser::AssignContext::SYMBOL() {
  return getToken(asm6502Parser::SYMBOL, 0);
}

std::vector<tree::TerminalNode *> asm6502Parser::AssignContext::WHITESPACE() {
  return getTokens(asm6502Parser::WHITESPACE);
}

tree::TerminalNode* asm6502Parser::AssignContext::WHITESPACE(size_t i) {
  return getToken(asm6502Parser::WHITESPACE, i);
}

tree::TerminalNode* asm6502Parser::AssignContext::EQU() {
  return getToken(asm6502Parser::EQU, 0);
}

asm6502Parser::ExpressionContext* asm6502Parser::AssignContext::expression() {
  return getRuleContext<asm6502Parser::ExpressionContext>(0);
}


size_t asm6502Parser::AssignContext::getRuleIndex() const {
  return asm6502Parser::RuleAssign;
}


asm6502Parser::AssignContext* asm6502Parser::assign() {
  AssignContext *_localctx = _tracker.createInstance<AssignContext>(_ctx, getState());
  enterRule(_localctx, 6, asm6502Parser::RuleAssign);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(156);
    match(asm6502Parser::SYMBOL);
    setState(157);
    match(asm6502Parser::WHITESPACE);
    setState(158);
    match(asm6502Parser::EQU);
    setState(159);
    match(asm6502Parser::WHITESPACE);
    setState(160);
    expression(0);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- InstructionContext ------------------------------------------------------------------

asm6502Parser::InstructionContext::InstructionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

asm6502Parser::NopContext* asm6502Parser::InstructionContext::nop() {
  return getRuleContext<asm6502Parser::NopContext>(0);
}

asm6502Parser::ImplicitContext* asm6502Parser::InstructionContext::implicit() {
  return getRuleContext<asm6502Parser::ImplicitContext>(0);
}

asm6502Parser::AccContext* asm6502Parser::InstructionContext::acc() {
  return getRuleContext<asm6502Parser::AccContext>(0);
}

asm6502Parser::ImmediateContext* asm6502Parser::InstructionContext::immediate() {
  return getRuleContext<asm6502Parser::ImmediateContext>(0);
}

asm6502Parser::X_indexContext* asm6502Parser::InstructionContext::x_index() {
  return getRuleContext<asm6502Parser::X_indexContext>(0);
}

asm6502Parser::Y_indexContext* asm6502Parser::InstructionContext::y_index() {
  return getRuleContext<asm6502Parser::Y_indexContext>(0);
}

asm6502Parser::X_indirectContext* asm6502Parser::InstructionContext::x_indirect() {
  return getRuleContext<asm6502Parser::X_indirectContext>(0);
}

asm6502Parser::Indirect_yContext* asm6502Parser::InstructionContext::indirect_y() {
  return getRuleContext<asm6502Parser::Indirect_yContext>(0);
}

asm6502Parser::AbsoluteContext* asm6502Parser::InstructionContext::absolute() {
  return getRuleContext<asm6502Parser::AbsoluteContext>(0);
}

asm6502Parser::RelativeContext* asm6502Parser::InstructionContext::relative() {
  return getRuleContext<asm6502Parser::RelativeContext>(0);
}

asm6502Parser::JumpContext* asm6502Parser::InstructionContext::jump() {
  return getRuleContext<asm6502Parser::JumpContext>(0);
}

asm6502Parser::JsrContext* asm6502Parser::InstructionContext::jsr() {
  return getRuleContext<asm6502Parser::JsrContext>(0);
}


size_t asm6502Parser::InstructionContext::getRuleIndex() const {
  return asm6502Parser::RuleInstruction;
}


asm6502Parser::InstructionContext* asm6502Parser::instruction() {
  InstructionContext *_localctx = _tracker.createInstance<InstructionContext>(_ctx, getState());
  enterRule(_localctx, 8, asm6502Parser::RuleInstruction);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(174);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 22, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(162);
      nop();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(163);
      implicit();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(164);
      acc();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(165);
      immediate();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(166);
      x_index();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(167);
      y_index();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(168);
      x_indirect();
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(169);
      indirect_y();
      break;
    }

    case 9: {
      enterOuterAlt(_localctx, 9);
      setState(170);
      absolute();
      break;
    }

    case 10: {
      enterOuterAlt(_localctx, 10);
      setState(171);
      relative();
      break;
    }

    case 11: {
      enterOuterAlt(_localctx, 11);
      setState(172);
      jump();
      break;
    }

    case 12: {
      enterOuterAlt(_localctx, 12);
      setState(173);
      jsr();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CommentContext ------------------------------------------------------------------

asm6502Parser::CommentContext::CommentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* asm6502Parser::CommentContext::COMMENT() {
  return getToken(asm6502Parser::COMMENT, 0);
}


size_t asm6502Parser::CommentContext::getRuleIndex() const {
  return asm6502Parser::RuleComment;
}


asm6502Parser::CommentContext* asm6502Parser::comment() {
  CommentContext *_localctx = _tracker.createInstance<CommentContext>(_ctx, getState());
  enterRule(_localctx, 10, asm6502Parser::RuleComment);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(176);
    match(asm6502Parser::COMMENT);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NopContext ------------------------------------------------------------------

asm6502Parser::NopContext::NopContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* asm6502Parser::NopContext::NOP() {
  return getToken(asm6502Parser::NOP, 0);
}


size_t asm6502Parser::NopContext::getRuleIndex() const {
  return asm6502Parser::RuleNop;
}


asm6502Parser::NopContext* asm6502Parser::nop() {
  NopContext *_localctx = _tracker.createInstance<NopContext>(_ctx, getState());
  enterRule(_localctx, 12, asm6502Parser::RuleNop);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(178);
    match(asm6502Parser::NOP);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ImplicitContext ------------------------------------------------------------------

asm6502Parser::ImplicitContext::ImplicitContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* asm6502Parser::ImplicitContext::IMPLIED() {
  return getToken(asm6502Parser::IMPLIED, 0);
}


size_t asm6502Parser::ImplicitContext::getRuleIndex() const {
  return asm6502Parser::RuleImplicit;
}


asm6502Parser::ImplicitContext* asm6502Parser::implicit() {
  ImplicitContext *_localctx = _tracker.createInstance<ImplicitContext>(_ctx, getState());
  enterRule(_localctx, 14, asm6502Parser::RuleImplicit);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(180);
    match(asm6502Parser::IMPLIED);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AccContext ------------------------------------------------------------------

asm6502Parser::AccContext::AccContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

asm6502Parser::ShiftContext* asm6502Parser::AccContext::shift() {
  return getRuleContext<asm6502Parser::ShiftContext>(0);
}

tree::TerminalNode* asm6502Parser::AccContext::WHITESPACE() {
  return getToken(asm6502Parser::WHITESPACE, 0);
}

tree::TerminalNode* asm6502Parser::AccContext::ACC() {
  return getToken(asm6502Parser::ACC, 0);
}


size_t asm6502Parser::AccContext::getRuleIndex() const {
  return asm6502Parser::RuleAcc;
}


asm6502Parser::AccContext* asm6502Parser::acc() {
  AccContext *_localctx = _tracker.createInstance<AccContext>(_ctx, getState());
  enterRule(_localctx, 16, asm6502Parser::RuleAcc);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(182);
    shift();
    setState(185);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 23, _ctx)) {
    case 1: {
      setState(183);
      match(asm6502Parser::WHITESPACE);
      setState(184);
      match(asm6502Parser::ACC);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ImmediateContext ------------------------------------------------------------------

asm6502Parser::ImmediateContext::ImmediateContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

asm6502Parser::MnemonicContext* asm6502Parser::ImmediateContext::mnemonic() {
  return getRuleContext<asm6502Parser::MnemonicContext>(0);
}

tree::TerminalNode* asm6502Parser::ImmediateContext::WHITESPACE() {
  return getToken(asm6502Parser::WHITESPACE, 0);
}

tree::TerminalNode* asm6502Parser::ImmediateContext::HASH() {
  return getToken(asm6502Parser::HASH, 0);
}

asm6502Parser::ExpressionContext* asm6502Parser::ImmediateContext::expression() {
  return getRuleContext<asm6502Parser::ExpressionContext>(0);
}


size_t asm6502Parser::ImmediateContext::getRuleIndex() const {
  return asm6502Parser::RuleImmediate;
}


asm6502Parser::ImmediateContext* asm6502Parser::immediate() {
  ImmediateContext *_localctx = _tracker.createInstance<ImmediateContext>(_ctx, getState());
  enterRule(_localctx, 18, asm6502Parser::RuleImmediate);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(187);
    mnemonic();
    setState(188);
    match(asm6502Parser::WHITESPACE);
    setState(189);
    match(asm6502Parser::HASH);
    setState(190);
    expression(0);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- X_indexContext ------------------------------------------------------------------

asm6502Parser::X_indexContext::X_indexContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* asm6502Parser::X_indexContext::WHITESPACE() {
  return getToken(asm6502Parser::WHITESPACE, 0);
}

asm6502Parser::ExpressionContext* asm6502Parser::X_indexContext::expression() {
  return getRuleContext<asm6502Parser::ExpressionContext>(0);
}

tree::TerminalNode* asm6502Parser::X_indexContext::X_INDEX() {
  return getToken(asm6502Parser::X_INDEX, 0);
}

asm6502Parser::ShiftContext* asm6502Parser::X_indexContext::shift() {
  return getRuleContext<asm6502Parser::ShiftContext>(0);
}

asm6502Parser::MnemonicContext* asm6502Parser::X_indexContext::mnemonic() {
  return getRuleContext<asm6502Parser::MnemonicContext>(0);
}


size_t asm6502Parser::X_indexContext::getRuleIndex() const {
  return asm6502Parser::RuleX_index;
}


asm6502Parser::X_indexContext* asm6502Parser::x_index() {
  X_indexContext *_localctx = _tracker.createInstance<X_indexContext>(_ctx, getState());
  enterRule(_localctx, 20, asm6502Parser::RuleX_index);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(194);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case asm6502Parser::SHIFT: {
        setState(192);
        shift();
        break;
      }

      case asm6502Parser::MNEMONIC: {
        setState(193);
        mnemonic();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(196);
    match(asm6502Parser::WHITESPACE);
    setState(197);
    expression(0);
    setState(198);
    match(asm6502Parser::X_INDEX);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Y_indexContext ------------------------------------------------------------------

asm6502Parser::Y_indexContext::Y_indexContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* asm6502Parser::Y_indexContext::WHITESPACE() {
  return getToken(asm6502Parser::WHITESPACE, 0);
}

asm6502Parser::ExpressionContext* asm6502Parser::Y_indexContext::expression() {
  return getRuleContext<asm6502Parser::ExpressionContext>(0);
}

tree::TerminalNode* asm6502Parser::Y_indexContext::Y_INDEX() {
  return getToken(asm6502Parser::Y_INDEX, 0);
}

asm6502Parser::ShiftContext* asm6502Parser::Y_indexContext::shift() {
  return getRuleContext<asm6502Parser::ShiftContext>(0);
}

asm6502Parser::MnemonicContext* asm6502Parser::Y_indexContext::mnemonic() {
  return getRuleContext<asm6502Parser::MnemonicContext>(0);
}


size_t asm6502Parser::Y_indexContext::getRuleIndex() const {
  return asm6502Parser::RuleY_index;
}


asm6502Parser::Y_indexContext* asm6502Parser::y_index() {
  Y_indexContext *_localctx = _tracker.createInstance<Y_indexContext>(_ctx, getState());
  enterRule(_localctx, 22, asm6502Parser::RuleY_index);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(202);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case asm6502Parser::SHIFT: {
        setState(200);
        shift();
        break;
      }

      case asm6502Parser::MNEMONIC: {
        setState(201);
        mnemonic();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(204);
    match(asm6502Parser::WHITESPACE);
    setState(205);
    expression(0);
    setState(206);
    match(asm6502Parser::Y_INDEX);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- X_indirectContext ------------------------------------------------------------------

asm6502Parser::X_indirectContext::X_indirectContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* asm6502Parser::X_indirectContext::LPAREN() {
  return getToken(asm6502Parser::LPAREN, 0);
}

tree::TerminalNode* asm6502Parser::X_indirectContext::WHITESPACE() {
  return getToken(asm6502Parser::WHITESPACE, 0);
}

asm6502Parser::ExpressionContext* asm6502Parser::X_indirectContext::expression() {
  return getRuleContext<asm6502Parser::ExpressionContext>(0);
}

tree::TerminalNode* asm6502Parser::X_indirectContext::X_INDEX() {
  return getToken(asm6502Parser::X_INDEX, 0);
}

tree::TerminalNode* asm6502Parser::X_indirectContext::RPAREN() {
  return getToken(asm6502Parser::RPAREN, 0);
}

asm6502Parser::ShiftContext* asm6502Parser::X_indirectContext::shift() {
  return getRuleContext<asm6502Parser::ShiftContext>(0);
}

asm6502Parser::MnemonicContext* asm6502Parser::X_indirectContext::mnemonic() {
  return getRuleContext<asm6502Parser::MnemonicContext>(0);
}


size_t asm6502Parser::X_indirectContext::getRuleIndex() const {
  return asm6502Parser::RuleX_indirect;
}


asm6502Parser::X_indirectContext* asm6502Parser::x_indirect() {
  X_indirectContext *_localctx = _tracker.createInstance<X_indirectContext>(_ctx, getState());
  enterRule(_localctx, 24, asm6502Parser::RuleX_indirect);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(208);
    match(asm6502Parser::LPAREN);
    setState(211);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case asm6502Parser::SHIFT: {
        setState(209);
        shift();
        break;
      }

      case asm6502Parser::MNEMONIC: {
        setState(210);
        mnemonic();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(213);
    match(asm6502Parser::WHITESPACE);
    setState(214);
    expression(0);
    setState(215);
    match(asm6502Parser::X_INDEX);
    setState(216);
    match(asm6502Parser::RPAREN);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Indirect_yContext ------------------------------------------------------------------

asm6502Parser::Indirect_yContext::Indirect_yContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* asm6502Parser::Indirect_yContext::LPAREN() {
  return getToken(asm6502Parser::LPAREN, 0);
}

tree::TerminalNode* asm6502Parser::Indirect_yContext::WHITESPACE() {
  return getToken(asm6502Parser::WHITESPACE, 0);
}

asm6502Parser::ExpressionContext* asm6502Parser::Indirect_yContext::expression() {
  return getRuleContext<asm6502Parser::ExpressionContext>(0);
}

tree::TerminalNode* asm6502Parser::Indirect_yContext::RPAREN() {
  return getToken(asm6502Parser::RPAREN, 0);
}

tree::TerminalNode* asm6502Parser::Indirect_yContext::Y_INDEX() {
  return getToken(asm6502Parser::Y_INDEX, 0);
}

asm6502Parser::ShiftContext* asm6502Parser::Indirect_yContext::shift() {
  return getRuleContext<asm6502Parser::ShiftContext>(0);
}

asm6502Parser::MnemonicContext* asm6502Parser::Indirect_yContext::mnemonic() {
  return getRuleContext<asm6502Parser::MnemonicContext>(0);
}


size_t asm6502Parser::Indirect_yContext::getRuleIndex() const {
  return asm6502Parser::RuleIndirect_y;
}


asm6502Parser::Indirect_yContext* asm6502Parser::indirect_y() {
  Indirect_yContext *_localctx = _tracker.createInstance<Indirect_yContext>(_ctx, getState());
  enterRule(_localctx, 26, asm6502Parser::RuleIndirect_y);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(218);
    match(asm6502Parser::LPAREN);
    setState(221);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case asm6502Parser::SHIFT: {
        setState(219);
        shift();
        break;
      }

      case asm6502Parser::MNEMONIC: {
        setState(220);
        mnemonic();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(223);
    match(asm6502Parser::WHITESPACE);
    setState(224);
    expression(0);
    setState(225);
    match(asm6502Parser::RPAREN);
    setState(226);
    match(asm6502Parser::Y_INDEX);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AbsoluteContext ------------------------------------------------------------------

asm6502Parser::AbsoluteContext::AbsoluteContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* asm6502Parser::AbsoluteContext::WHITESPACE() {
  return getToken(asm6502Parser::WHITESPACE, 0);
}

asm6502Parser::ExpressionContext* asm6502Parser::AbsoluteContext::expression() {
  return getRuleContext<asm6502Parser::ExpressionContext>(0);
}

asm6502Parser::ShiftContext* asm6502Parser::AbsoluteContext::shift() {
  return getRuleContext<asm6502Parser::ShiftContext>(0);
}

asm6502Parser::MnemonicContext* asm6502Parser::AbsoluteContext::mnemonic() {
  return getRuleContext<asm6502Parser::MnemonicContext>(0);
}


size_t asm6502Parser::AbsoluteContext::getRuleIndex() const {
  return asm6502Parser::RuleAbsolute;
}


asm6502Parser::AbsoluteContext* asm6502Parser::absolute() {
  AbsoluteContext *_localctx = _tracker.createInstance<AbsoluteContext>(_ctx, getState());
  enterRule(_localctx, 28, asm6502Parser::RuleAbsolute);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(230);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case asm6502Parser::SHIFT: {
        setState(228);
        shift();
        break;
      }

      case asm6502Parser::MNEMONIC: {
        setState(229);
        mnemonic();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(232);
    match(asm6502Parser::WHITESPACE);
    setState(233);
    expression(0);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- RelativeContext ------------------------------------------------------------------

asm6502Parser::RelativeContext::RelativeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* asm6502Parser::RelativeContext::BRANCH() {
  return getToken(asm6502Parser::BRANCH, 0);
}

tree::TerminalNode* asm6502Parser::RelativeContext::WHITESPACE() {
  return getToken(asm6502Parser::WHITESPACE, 0);
}

asm6502Parser::ExpressionContext* asm6502Parser::RelativeContext::expression() {
  return getRuleContext<asm6502Parser::ExpressionContext>(0);
}


size_t asm6502Parser::RelativeContext::getRuleIndex() const {
  return asm6502Parser::RuleRelative;
}


asm6502Parser::RelativeContext* asm6502Parser::relative() {
  RelativeContext *_localctx = _tracker.createInstance<RelativeContext>(_ctx, getState());
  enterRule(_localctx, 30, asm6502Parser::RuleRelative);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(235);
    match(asm6502Parser::BRANCH);
    setState(236);
    match(asm6502Parser::WHITESPACE);
    setState(237);
    expression(0);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- MnemonicContext ------------------------------------------------------------------

asm6502Parser::MnemonicContext::MnemonicContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* asm6502Parser::MnemonicContext::MNEMONIC() {
  return getToken(asm6502Parser::MNEMONIC, 0);
}


size_t asm6502Parser::MnemonicContext::getRuleIndex() const {
  return asm6502Parser::RuleMnemonic;
}


asm6502Parser::MnemonicContext* asm6502Parser::mnemonic() {
  MnemonicContext *_localctx = _tracker.createInstance<MnemonicContext>(_ctx, getState());
  enterRule(_localctx, 32, asm6502Parser::RuleMnemonic);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(239);
    match(asm6502Parser::MNEMONIC);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ShiftContext ------------------------------------------------------------------

asm6502Parser::ShiftContext::ShiftContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* asm6502Parser::ShiftContext::SHIFT() {
  return getToken(asm6502Parser::SHIFT, 0);
}


size_t asm6502Parser::ShiftContext::getRuleIndex() const {
  return asm6502Parser::RuleShift;
}


asm6502Parser::ShiftContext* asm6502Parser::shift() {
  ShiftContext *_localctx = _tracker.createInstance<ShiftContext>(_ctx, getState());
  enterRule(_localctx, 34, asm6502Parser::RuleShift);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(241);
    match(asm6502Parser::SHIFT);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- JumpContext ------------------------------------------------------------------

asm6502Parser::JumpContext::JumpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* asm6502Parser::JumpContext::JUMP() {
  return getToken(asm6502Parser::JUMP, 0);
}

tree::TerminalNode* asm6502Parser::JumpContext::WHITESPACE() {
  return getToken(asm6502Parser::WHITESPACE, 0);
}

asm6502Parser::ExpressionContext* asm6502Parser::JumpContext::expression() {
  return getRuleContext<asm6502Parser::ExpressionContext>(0);
}

tree::TerminalNode* asm6502Parser::JumpContext::LPAREN() {
  return getToken(asm6502Parser::LPAREN, 0);
}

tree::TerminalNode* asm6502Parser::JumpContext::RPAREN() {
  return getToken(asm6502Parser::RPAREN, 0);
}


size_t asm6502Parser::JumpContext::getRuleIndex() const {
  return asm6502Parser::RuleJump;
}


asm6502Parser::JumpContext* asm6502Parser::jump() {
  JumpContext *_localctx = _tracker.createInstance<JumpContext>(_ctx, getState());
  enterRule(_localctx, 36, asm6502Parser::RuleJump);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(252);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 29, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(243);
      match(asm6502Parser::JUMP);
      setState(244);
      match(asm6502Parser::WHITESPACE);
      setState(245);
      expression(0);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(246);
      match(asm6502Parser::JUMP);
      setState(247);
      match(asm6502Parser::WHITESPACE);
      setState(248);
      match(asm6502Parser::LPAREN);
      setState(249);
      expression(0);
      setState(250);
      match(asm6502Parser::RPAREN);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- JsrContext ------------------------------------------------------------------

asm6502Parser::JsrContext::JsrContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* asm6502Parser::JsrContext::JSR() {
  return getToken(asm6502Parser::JSR, 0);
}

tree::TerminalNode* asm6502Parser::JsrContext::WHITESPACE() {
  return getToken(asm6502Parser::WHITESPACE, 0);
}

asm6502Parser::ExpressionContext* asm6502Parser::JsrContext::expression() {
  return getRuleContext<asm6502Parser::ExpressionContext>(0);
}


size_t asm6502Parser::JsrContext::getRuleIndex() const {
  return asm6502Parser::RuleJsr;
}


asm6502Parser::JsrContext* asm6502Parser::jsr() {
  JsrContext *_localctx = _tracker.createInstance<JsrContext>(_ctx, getState());
  enterRule(_localctx, 38, asm6502Parser::RuleJsr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(254);
    match(asm6502Parser::JSR);
    setState(255);
    match(asm6502Parser::WHITESPACE);
    setState(256);
    expression(0);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExpressionContext ------------------------------------------------------------------

asm6502Parser::ExpressionContext::ExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* asm6502Parser::ExpressionContext::LBRACKET() {
  return getToken(asm6502Parser::LBRACKET, 0);
}

std::vector<asm6502Parser::ExpressionContext *> asm6502Parser::ExpressionContext::expression() {
  return getRuleContexts<asm6502Parser::ExpressionContext>();
}

asm6502Parser::ExpressionContext* asm6502Parser::ExpressionContext::expression(size_t i) {
  return getRuleContext<asm6502Parser::ExpressionContext>(i);
}

tree::TerminalNode* asm6502Parser::ExpressionContext::RBRACKET() {
  return getToken(asm6502Parser::RBRACKET, 0);
}

asm6502Parser::AtomContext* asm6502Parser::ExpressionContext::atom() {
  return getRuleContext<asm6502Parser::AtomContext>(0);
}

asm6502Parser::Binary_opContext* asm6502Parser::ExpressionContext::binary_op() {
  return getRuleContext<asm6502Parser::Binary_opContext>(0);
}


size_t asm6502Parser::ExpressionContext::getRuleIndex() const {
  return asm6502Parser::RuleExpression;
}



asm6502Parser::ExpressionContext* asm6502Parser::expression() {
   return expression(0);
}

asm6502Parser::ExpressionContext* asm6502Parser::expression(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  asm6502Parser::ExpressionContext *_localctx = _tracker.createInstance<ExpressionContext>(_ctx, parentState);
  asm6502Parser::ExpressionContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 40;
  enterRecursionRule(_localctx, 40, asm6502Parser::RuleExpression, precedence);

    

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(264);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case asm6502Parser::LBRACKET: {
        setState(259);
        match(asm6502Parser::LBRACKET);
        setState(260);
        expression(0);
        setState(261);
        match(asm6502Parser::RBRACKET);
        break;
      }

      case asm6502Parser::PLUS:
      case asm6502Parser::MINUS:
      case asm6502Parser::STAR:
      case asm6502Parser::LOW_BYTE_VALUE:
      case asm6502Parser::HIGH_BYTE_VALUE:
      case asm6502Parser::OCTAL_BYTE:
      case asm6502Parser::OCTAL_NUMBER:
      case asm6502Parser::HEX_BYTE:
      case asm6502Parser::HEX_NUMBER:
      case asm6502Parser::DECIMAL_BYTE:
      case asm6502Parser::DECIMAL_NUMBER:
      case asm6502Parser::BINARY_BYTE:
      case asm6502Parser::BINARY_NUMBER:
      case asm6502Parser::CHARACTER:
      case asm6502Parser::SYMBOL: {
        setState(263);
        atom();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    _ctx->stop = _input->LT(-1);
    setState(272);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 31, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<ExpressionContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleExpression);
        setState(266);

        if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
        setState(267);
        binary_op();
        setState(268);
        expression(4); 
      }
      setState(274);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 31, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- Binary_opContext ------------------------------------------------------------------

asm6502Parser::Binary_opContext::Binary_opContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* asm6502Parser::Binary_opContext::PLUS() {
  return getToken(asm6502Parser::PLUS, 0);
}

tree::TerminalNode* asm6502Parser::Binary_opContext::MINUS() {
  return getToken(asm6502Parser::MINUS, 0);
}

tree::TerminalNode* asm6502Parser::Binary_opContext::STAR() {
  return getToken(asm6502Parser::STAR, 0);
}

tree::TerminalNode* asm6502Parser::Binary_opContext::SLASH() {
  return getToken(asm6502Parser::SLASH, 0);
}


size_t asm6502Parser::Binary_opContext::getRuleIndex() const {
  return asm6502Parser::RuleBinary_op;
}


asm6502Parser::Binary_opContext* asm6502Parser::binary_op() {
  Binary_opContext *_localctx = _tracker.createInstance<Binary_opContext>(_ctx, getState());
  enterRule(_localctx, 42, asm6502Parser::RuleBinary_op);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(275);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << asm6502Parser::PLUS)
      | (1ULL << asm6502Parser::MINUS)
      | (1ULL << asm6502Parser::STAR)
      | (1ULL << asm6502Parser::SLASH))) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Unary_opContext ------------------------------------------------------------------

asm6502Parser::Unary_opContext::Unary_opContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* asm6502Parser::Unary_opContext::LOW_BYTE_VALUE() {
  return getToken(asm6502Parser::LOW_BYTE_VALUE, 0);
}

tree::TerminalNode* asm6502Parser::Unary_opContext::HIGH_BYTE_VALUE() {
  return getToken(asm6502Parser::HIGH_BYTE_VALUE, 0);
}

tree::TerminalNode* asm6502Parser::Unary_opContext::PLUS() {
  return getToken(asm6502Parser::PLUS, 0);
}

tree::TerminalNode* asm6502Parser::Unary_opContext::MINUS() {
  return getToken(asm6502Parser::MINUS, 0);
}


size_t asm6502Parser::Unary_opContext::getRuleIndex() const {
  return asm6502Parser::RuleUnary_op;
}


asm6502Parser::Unary_opContext* asm6502Parser::unary_op() {
  Unary_opContext *_localctx = _tracker.createInstance<Unary_opContext>(_ctx, getState());
  enterRule(_localctx, 44, asm6502Parser::RuleUnary_op);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(277);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << asm6502Parser::PLUS)
      | (1ULL << asm6502Parser::MINUS)
      | (1ULL << asm6502Parser::LOW_BYTE_VALUE)
      | (1ULL << asm6502Parser::HIGH_BYTE_VALUE))) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AtomContext ------------------------------------------------------------------

asm6502Parser::AtomContext::AtomContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

asm6502Parser::ByteContext* asm6502Parser::AtomContext::byte() {
  return getRuleContext<asm6502Parser::ByteContext>(0);
}

asm6502Parser::MultibyteContext* asm6502Parser::AtomContext::multibyte() {
  return getRuleContext<asm6502Parser::MultibyteContext>(0);
}

asm6502Parser::CharacterContext* asm6502Parser::AtomContext::character() {
  return getRuleContext<asm6502Parser::CharacterContext>(0);
}

tree::TerminalNode* asm6502Parser::AtomContext::SYMBOL() {
  return getToken(asm6502Parser::SYMBOL, 0);
}

tree::TerminalNode* asm6502Parser::AtomContext::STAR() {
  return getToken(asm6502Parser::STAR, 0);
}

asm6502Parser::Unary_opContext* asm6502Parser::AtomContext::unary_op() {
  return getRuleContext<asm6502Parser::Unary_opContext>(0);
}


size_t asm6502Parser::AtomContext::getRuleIndex() const {
  return asm6502Parser::RuleAtom;
}


asm6502Parser::AtomContext* asm6502Parser::atom() {
  AtomContext *_localctx = _tracker.createInstance<AtomContext>(_ctx, getState());
  enterRule(_localctx, 46, asm6502Parser::RuleAtom);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(280);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << asm6502Parser::PLUS)
      | (1ULL << asm6502Parser::MINUS)
      | (1ULL << asm6502Parser::LOW_BYTE_VALUE)
      | (1ULL << asm6502Parser::HIGH_BYTE_VALUE))) != 0)) {
      setState(279);
      unary_op();
    }
    setState(287);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case asm6502Parser::OCTAL_BYTE:
      case asm6502Parser::HEX_BYTE:
      case asm6502Parser::DECIMAL_BYTE:
      case asm6502Parser::BINARY_BYTE: {
        setState(282);
        byte();
        break;
      }

      case asm6502Parser::OCTAL_NUMBER:
      case asm6502Parser::HEX_NUMBER:
      case asm6502Parser::DECIMAL_NUMBER:
      case asm6502Parser::BINARY_NUMBER: {
        setState(283);
        multibyte();
        break;
      }

      case asm6502Parser::CHARACTER: {
        setState(284);
        character();
        break;
      }

      case asm6502Parser::SYMBOL: {
        setState(285);
        match(asm6502Parser::SYMBOL);
        break;
      }

      case asm6502Parser::STAR: {
        setState(286);
        match(asm6502Parser::STAR);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ByteContext ------------------------------------------------------------------

asm6502Parser::ByteContext::ByteContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* asm6502Parser::ByteContext::HEX_BYTE() {
  return getToken(asm6502Parser::HEX_BYTE, 0);
}

tree::TerminalNode* asm6502Parser::ByteContext::DECIMAL_BYTE() {
  return getToken(asm6502Parser::DECIMAL_BYTE, 0);
}

tree::TerminalNode* asm6502Parser::ByteContext::OCTAL_BYTE() {
  return getToken(asm6502Parser::OCTAL_BYTE, 0);
}

tree::TerminalNode* asm6502Parser::ByteContext::BINARY_BYTE() {
  return getToken(asm6502Parser::BINARY_BYTE, 0);
}


size_t asm6502Parser::ByteContext::getRuleIndex() const {
  return asm6502Parser::RuleByte;
}


asm6502Parser::ByteContext* asm6502Parser::byte() {
  ByteContext *_localctx = _tracker.createInstance<ByteContext>(_ctx, getState());
  enterRule(_localctx, 48, asm6502Parser::RuleByte);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(289);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << asm6502Parser::OCTAL_BYTE)
      | (1ULL << asm6502Parser::HEX_BYTE)
      | (1ULL << asm6502Parser::DECIMAL_BYTE)
      | (1ULL << asm6502Parser::BINARY_BYTE))) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- MultibyteContext ------------------------------------------------------------------

asm6502Parser::MultibyteContext::MultibyteContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* asm6502Parser::MultibyteContext::HEX_NUMBER() {
  return getToken(asm6502Parser::HEX_NUMBER, 0);
}

tree::TerminalNode* asm6502Parser::MultibyteContext::DECIMAL_NUMBER() {
  return getToken(asm6502Parser::DECIMAL_NUMBER, 0);
}

tree::TerminalNode* asm6502Parser::MultibyteContext::OCTAL_NUMBER() {
  return getToken(asm6502Parser::OCTAL_NUMBER, 0);
}

tree::TerminalNode* asm6502Parser::MultibyteContext::BINARY_NUMBER() {
  return getToken(asm6502Parser::BINARY_NUMBER, 0);
}


size_t asm6502Parser::MultibyteContext::getRuleIndex() const {
  return asm6502Parser::RuleMultibyte;
}


asm6502Parser::MultibyteContext* asm6502Parser::multibyte() {
  MultibyteContext *_localctx = _tracker.createInstance<MultibyteContext>(_ctx, getState());
  enterRule(_localctx, 50, asm6502Parser::RuleMultibyte);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(291);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << asm6502Parser::OCTAL_NUMBER)
      | (1ULL << asm6502Parser::HEX_NUMBER)
      | (1ULL << asm6502Parser::DECIMAL_NUMBER)
      | (1ULL << asm6502Parser::BINARY_NUMBER))) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CharacterContext ------------------------------------------------------------------

asm6502Parser::CharacterContext::CharacterContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* asm6502Parser::CharacterContext::CHARACTER() {
  return getToken(asm6502Parser::CHARACTER, 0);
}


size_t asm6502Parser::CharacterContext::getRuleIndex() const {
  return asm6502Parser::RuleCharacter;
}


asm6502Parser::CharacterContext* asm6502Parser::character() {
  CharacterContext *_localctx = _tracker.createInstance<CharacterContext>(_ctx, getState());
  enterRule(_localctx, 52, asm6502Parser::RuleCharacter);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(293);
    match(asm6502Parser::CHARACTER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

bool asm6502Parser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 20: return expressionSempred(antlrcpp::downCast<ExpressionContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool asm6502Parser::expressionSempred(ExpressionContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 3);

  default:
    break;
  }
  return true;
}

void asm6502Parser::initialize() {
  std::call_once(asm6502ParserOnceFlag, asm6502ParserInitialize);
}
