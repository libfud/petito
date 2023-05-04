
// Generated from asm6502Parser.g4 by ANTLR 4.10.1



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

std::once_flag asm6502parserParserOnceFlag;
Asm6502ParserStaticData *asm6502parserParserStaticData = nullptr;

void asm6502parserParserInitialize() {
  assert(asm6502parserParserStaticData == nullptr);
  auto staticData = std::make_unique<Asm6502ParserStaticData>(
    std::vector<std::string>{
      "program", "line", "label", "assign", "instruction", "comment", "nop", 
      "implicit", "acc", "immediate", "zero_page", "x_index", "y_index", 
      "x_indirect", "indirect_y", "absolute", "relative", "mnemonic", "shift", 
      "jump", "jsr", "expression", "binary_op", "unary_op", "atom", "byte", 
      "multibyte", "character", "repeat_directive", "directive", "org", 
      "byte_directive", "dbyte_directive", "word_directive", "text_directive", 
      "align_directive", "fill_directive", "byte_directive_value", "string", 
      "stringContents"
    },
    std::vector<std::string>{
      "", "", "", "", "'+'", "'-'", "'*'", "'/'", "'<'", "'>'", "'['", "']'", 
      "'('", "')'", "'#'", "':'", "'@'", "", "", "','", "',X'", "',Y'", 
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
      "", "'NOP'", "", "", "", "", "", "", "", "'A'"
    },
    std::vector<std::string>{
      "", "COMMENT", "WHITESPACE", "NEWLINE", "PLUS", "MINUS", "STAR", "SLASH", 
      "LOW_BYTE_VALUE", "HIGH_BYTE_VALUE", "LBRACKET", "RBRACKET", "LPAREN", 
      "RPAREN", "HASH", "COLON", "AT", "FORCED_BYTE", "FORCED_WORD", "COMMA", 
      "X_INDEX", "Y_INDEX", "OCTAL_BYTE", "OCTAL_NUMBER", "HEX_BYTE", "HEX_NUMBER", 
      "DECIMAL_BYTE", "DECIMAL_NUMBER", "BINARY_BYTE", "BINARY_NUMBER", 
      "DORG", "DBYTE", "DDBYTE", "DWORD", "DTEXT", "DALIGN", "DFILL", "DREPEAT", 
      "CHARACTER", "EQU", "NOP", "IMPLIED", "BRANCH", "SHIFT", "JUMP", "JSR", 
      "MNEMONIC", "ILLEGAL", "ACC", "SYMBOL", "DQUOTE", "TEXT", "ESCAPE_SEQUENCE"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,52,454,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,7,
  	28,2,29,7,29,2,30,7,30,2,31,7,31,2,32,7,32,2,33,7,33,2,34,7,34,2,35,7,
  	35,2,36,7,36,2,37,7,37,2,38,7,38,2,39,7,39,1,0,4,0,82,8,0,11,0,12,0,83,
  	1,0,1,0,1,1,3,1,89,8,1,1,1,1,1,1,1,1,1,3,1,95,8,1,1,1,1,1,1,1,1,1,3,1,
  	101,8,1,1,1,1,1,1,1,1,1,3,1,107,8,1,1,1,1,1,1,1,3,1,112,8,1,1,1,1,1,3,
  	1,116,8,1,1,1,1,1,1,1,1,1,3,1,122,8,1,1,1,1,1,3,1,126,8,1,1,1,1,1,1,1,
  	3,1,131,8,1,1,1,1,1,1,1,3,1,136,8,1,1,1,1,1,1,1,1,1,3,1,142,8,1,1,1,1,
  	1,3,1,146,8,1,1,1,1,1,1,1,1,1,3,1,152,8,1,1,1,1,1,3,1,156,8,1,1,1,1,1,
  	1,1,3,1,161,8,1,1,1,1,1,3,1,165,8,1,1,1,1,1,1,1,3,1,170,8,1,1,1,1,1,3,
  	1,174,8,1,1,1,1,1,1,1,3,1,179,8,1,1,1,1,1,3,1,183,8,1,1,1,1,1,1,1,3,1,
  	188,8,1,1,1,3,1,191,8,1,1,1,3,1,194,8,1,1,2,3,2,197,8,2,1,2,1,2,3,2,201,
  	8,2,1,3,1,3,1,3,1,3,1,3,1,3,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,
  	4,1,4,1,4,3,4,222,8,4,1,5,1,5,1,6,1,6,1,7,1,7,1,8,1,8,1,8,3,8,233,8,8,
  	1,9,1,9,1,9,1,9,1,9,1,10,1,10,3,10,242,8,10,1,10,1,10,1,10,1,10,1,10,
  	1,10,3,10,250,8,10,1,10,1,10,1,10,3,10,255,8,10,1,11,1,11,3,11,259,8,
  	11,1,11,3,11,262,8,11,1,11,1,11,1,11,1,11,1,12,1,12,3,12,270,8,12,1,12,
  	3,12,273,8,12,1,12,1,12,1,12,1,12,1,13,1,13,3,13,281,8,13,1,13,1,13,1,
  	13,1,13,1,13,1,13,1,14,1,14,3,14,291,8,14,1,14,1,14,1,14,1,14,1,14,1,
  	14,1,15,1,15,3,15,301,8,15,1,15,3,15,304,8,15,1,15,1,15,1,15,1,16,1,16,
  	1,16,1,16,1,17,1,17,1,18,1,18,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,
  	1,19,3,19,326,8,19,1,20,1,20,1,20,1,20,1,21,1,21,3,21,334,8,21,1,21,1,
  	21,1,21,1,21,1,21,3,21,341,8,21,1,21,1,21,1,21,1,21,5,21,347,8,21,10,
  	21,12,21,350,9,21,1,22,1,22,1,23,1,23,1,24,3,24,357,8,24,1,24,1,24,1,
  	24,1,24,1,24,3,24,364,8,24,1,25,1,25,1,26,1,26,1,27,1,27,1,28,1,28,1,
  	28,1,28,3,28,376,8,28,1,28,1,28,1,28,3,28,381,8,28,1,29,1,29,1,29,1,29,
  	1,29,1,29,1,29,3,29,390,8,29,1,30,1,30,1,30,1,30,3,30,396,8,30,1,30,1,
  	30,1,31,1,31,4,31,402,8,31,11,31,12,31,403,1,32,1,32,4,32,408,8,32,11,
  	32,12,32,409,1,33,1,33,4,33,414,8,33,11,33,12,33,415,1,34,1,34,1,34,1,
  	34,1,35,1,35,1,35,1,35,1,35,3,35,427,8,35,3,35,429,8,35,1,36,1,36,1,36,
  	1,36,1,36,3,36,436,8,36,1,37,1,37,1,37,3,37,441,8,37,1,38,1,38,5,38,445,
  	8,38,10,38,12,38,448,9,38,1,38,1,38,1,39,1,39,1,39,0,1,42,40,0,2,4,6,
  	8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,52,54,
  	56,58,60,62,64,66,68,70,72,74,76,78,0,6,1,0,17,18,1,0,4,7,2,0,4,5,8,9,
  	4,0,22,22,24,24,26,26,28,28,4,0,23,23,25,25,27,27,29,29,1,0,51,52,498,
  	0,81,1,0,0,0,2,193,1,0,0,0,4,196,1,0,0,0,6,202,1,0,0,0,8,221,1,0,0,0,
  	10,223,1,0,0,0,12,225,1,0,0,0,14,227,1,0,0,0,16,229,1,0,0,0,18,234,1,
  	0,0,0,20,254,1,0,0,0,22,258,1,0,0,0,24,269,1,0,0,0,26,280,1,0,0,0,28,
  	290,1,0,0,0,30,300,1,0,0,0,32,308,1,0,0,0,34,312,1,0,0,0,36,314,1,0,0,
  	0,38,325,1,0,0,0,40,327,1,0,0,0,42,340,1,0,0,0,44,351,1,0,0,0,46,353,
  	1,0,0,0,48,356,1,0,0,0,50,365,1,0,0,0,52,367,1,0,0,0,54,369,1,0,0,0,56,
  	371,1,0,0,0,58,389,1,0,0,0,60,391,1,0,0,0,62,399,1,0,0,0,64,405,1,0,0,
  	0,66,411,1,0,0,0,68,417,1,0,0,0,70,421,1,0,0,0,72,430,1,0,0,0,74,437,
  	1,0,0,0,76,442,1,0,0,0,78,451,1,0,0,0,80,82,3,2,1,0,81,80,1,0,0,0,82,
  	83,1,0,0,0,83,81,1,0,0,0,83,84,1,0,0,0,84,85,1,0,0,0,85,86,5,0,0,1,86,
  	1,1,0,0,0,87,89,5,2,0,0,88,87,1,0,0,0,88,89,1,0,0,0,89,90,1,0,0,0,90,
  	91,3,4,2,0,91,92,5,2,0,0,92,94,3,8,4,0,93,95,5,2,0,0,94,93,1,0,0,0,94,
  	95,1,0,0,0,95,96,1,0,0,0,96,97,3,10,5,0,97,98,5,3,0,0,98,194,1,0,0,0,
  	99,101,5,2,0,0,100,99,1,0,0,0,100,101,1,0,0,0,101,102,1,0,0,0,102,103,
  	3,4,2,0,103,104,5,2,0,0,104,106,3,8,4,0,105,107,5,2,0,0,106,105,1,0,0,
  	0,106,107,1,0,0,0,107,108,1,0,0,0,108,109,5,3,0,0,109,194,1,0,0,0,110,
  	112,5,2,0,0,111,110,1,0,0,0,111,112,1,0,0,0,112,113,1,0,0,0,113,115,3,
  	4,2,0,114,116,5,2,0,0,115,114,1,0,0,0,115,116,1,0,0,0,116,117,1,0,0,0,
  	117,118,3,10,5,0,118,119,5,3,0,0,119,194,1,0,0,0,120,122,5,2,0,0,121,
  	120,1,0,0,0,121,122,1,0,0,0,122,123,1,0,0,0,123,125,3,4,2,0,124,126,5,
  	2,0,0,125,124,1,0,0,0,125,126,1,0,0,0,126,127,1,0,0,0,127,128,5,3,0,0,
  	128,194,1,0,0,0,129,131,5,2,0,0,130,129,1,0,0,0,130,131,1,0,0,0,131,135,
  	1,0,0,0,132,133,3,4,2,0,133,134,5,2,0,0,134,136,1,0,0,0,135,132,1,0,0,
  	0,135,136,1,0,0,0,136,137,1,0,0,0,137,138,3,6,3,0,138,139,5,3,0,0,139,
  	194,1,0,0,0,140,142,5,2,0,0,141,140,1,0,0,0,141,142,1,0,0,0,142,143,1,
  	0,0,0,143,145,3,8,4,0,144,146,5,2,0,0,145,144,1,0,0,0,145,146,1,0,0,0,
  	146,147,1,0,0,0,147,148,3,10,5,0,148,149,5,3,0,0,149,194,1,0,0,0,150,
  	152,5,2,0,0,151,150,1,0,0,0,151,152,1,0,0,0,152,153,1,0,0,0,153,155,3,
  	8,4,0,154,156,5,2,0,0,155,154,1,0,0,0,155,156,1,0,0,0,156,157,1,0,0,0,
  	157,158,5,3,0,0,158,194,1,0,0,0,159,161,5,2,0,0,160,159,1,0,0,0,160,161,
  	1,0,0,0,161,162,1,0,0,0,162,164,3,6,3,0,163,165,3,10,5,0,164,163,1,0,
  	0,0,164,165,1,0,0,0,165,166,1,0,0,0,166,167,5,3,0,0,167,194,1,0,0,0,168,
  	170,5,2,0,0,169,168,1,0,0,0,169,170,1,0,0,0,170,171,1,0,0,0,171,173,3,
  	58,29,0,172,174,3,10,5,0,173,172,1,0,0,0,173,174,1,0,0,0,174,175,1,0,
  	0,0,175,176,5,3,0,0,176,194,1,0,0,0,177,179,5,2,0,0,178,177,1,0,0,0,178,
  	179,1,0,0,0,179,180,1,0,0,0,180,182,3,56,28,0,181,183,3,10,5,0,182,181,
  	1,0,0,0,182,183,1,0,0,0,183,184,1,0,0,0,184,185,5,3,0,0,185,194,1,0,0,
  	0,186,188,5,2,0,0,187,186,1,0,0,0,187,188,1,0,0,0,188,190,1,0,0,0,189,
  	191,3,10,5,0,190,189,1,0,0,0,190,191,1,0,0,0,191,192,1,0,0,0,192,194,
  	5,3,0,0,193,88,1,0,0,0,193,100,1,0,0,0,193,111,1,0,0,0,193,121,1,0,0,
  	0,193,130,1,0,0,0,193,141,1,0,0,0,193,151,1,0,0,0,193,160,1,0,0,0,193,
  	169,1,0,0,0,193,178,1,0,0,0,193,187,1,0,0,0,194,3,1,0,0,0,195,197,5,16,
  	0,0,196,195,1,0,0,0,196,197,1,0,0,0,197,198,1,0,0,0,198,200,5,49,0,0,
  	199,201,5,15,0,0,200,199,1,0,0,0,200,201,1,0,0,0,201,5,1,0,0,0,202,203,
  	5,49,0,0,203,204,5,2,0,0,204,205,5,39,0,0,205,206,5,2,0,0,206,207,3,42,
  	21,0,207,7,1,0,0,0,208,222,3,12,6,0,209,222,3,14,7,0,210,222,3,16,8,0,
  	211,222,3,18,9,0,212,222,3,20,10,0,213,222,3,22,11,0,214,222,3,24,12,
  	0,215,222,3,26,13,0,216,222,3,28,14,0,217,222,3,30,15,0,218,222,3,32,
  	16,0,219,222,3,38,19,0,220,222,3,40,20,0,221,208,1,0,0,0,221,209,1,0,
  	0,0,221,210,1,0,0,0,221,211,1,0,0,0,221,212,1,0,0,0,221,213,1,0,0,0,221,
  	214,1,0,0,0,221,215,1,0,0,0,221,216,1,0,0,0,221,217,1,0,0,0,221,218,1,
  	0,0,0,221,219,1,0,0,0,221,220,1,0,0,0,222,9,1,0,0,0,223,224,5,1,0,0,224,
  	11,1,0,0,0,225,226,5,40,0,0,226,13,1,0,0,0,227,228,5,41,0,0,228,15,1,
  	0,0,0,229,232,3,36,18,0,230,231,5,2,0,0,231,233,5,48,0,0,232,230,1,0,
  	0,0,232,233,1,0,0,0,233,17,1,0,0,0,234,235,3,34,17,0,235,236,5,2,0,0,
  	236,237,5,14,0,0,237,238,3,42,21,0,238,19,1,0,0,0,239,242,3,36,18,0,240,
  	242,3,34,17,0,241,239,1,0,0,0,241,240,1,0,0,0,242,243,1,0,0,0,243,244,
  	5,17,0,0,244,245,5,2,0,0,245,246,3,42,21,0,246,255,1,0,0,0,247,250,3,
  	36,18,0,248,250,3,34,17,0,249,247,1,0,0,0,249,248,1,0,0,0,250,251,1,0,
  	0,0,251,252,5,2,0,0,252,253,3,50,25,0,253,255,1,0,0,0,254,241,1,0,0,0,
  	254,249,1,0,0,0,255,21,1,0,0,0,256,259,3,36,18,0,257,259,3,34,17,0,258,
  	256,1,0,0,0,258,257,1,0,0,0,259,261,1,0,0,0,260,262,7,0,0,0,261,260,1,
  	0,0,0,261,262,1,0,0,0,262,263,1,0,0,0,263,264,5,2,0,0,264,265,3,42,21,
  	0,265,266,5,20,0,0,266,23,1,0,0,0,267,270,3,36,18,0,268,270,3,34,17,0,
  	269,267,1,0,0,0,269,268,1,0,0,0,270,272,1,0,0,0,271,273,7,0,0,0,272,271,
  	1,0,0,0,272,273,1,0,0,0,273,274,1,0,0,0,274,275,5,2,0,0,275,276,3,42,
  	21,0,276,277,5,21,0,0,277,25,1,0,0,0,278,281,3,36,18,0,279,281,3,34,17,
  	0,280,278,1,0,0,0,280,279,1,0,0,0,281,282,1,0,0,0,282,283,5,2,0,0,283,
  	284,5,12,0,0,284,285,3,42,21,0,285,286,5,20,0,0,286,287,5,13,0,0,287,
  	27,1,0,0,0,288,291,3,36,18,0,289,291,3,34,17,0,290,288,1,0,0,0,290,289,
  	1,0,0,0,291,292,1,0,0,0,292,293,5,2,0,0,293,294,5,12,0,0,294,295,3,42,
  	21,0,295,296,5,13,0,0,296,297,5,21,0,0,297,29,1,0,0,0,298,301,3,36,18,
  	0,299,301,3,34,17,0,300,298,1,0,0,0,300,299,1,0,0,0,301,303,1,0,0,0,302,
  	304,5,18,0,0,303,302,1,0,0,0,303,304,1,0,0,0,304,305,1,0,0,0,305,306,
  	5,2,0,0,306,307,3,42,21,0,307,31,1,0,0,0,308,309,5,42,0,0,309,310,5,2,
  	0,0,310,311,3,42,21,0,311,33,1,0,0,0,312,313,5,46,0,0,313,35,1,0,0,0,
  	314,315,5,43,0,0,315,37,1,0,0,0,316,317,5,44,0,0,317,318,5,2,0,0,318,
  	326,3,42,21,0,319,320,5,44,0,0,320,321,5,2,0,0,321,322,5,12,0,0,322,323,
  	3,42,21,0,323,324,5,13,0,0,324,326,1,0,0,0,325,316,1,0,0,0,325,319,1,
  	0,0,0,326,39,1,0,0,0,327,328,5,45,0,0,328,329,5,2,0,0,329,330,3,42,21,
  	0,330,41,1,0,0,0,331,333,6,21,-1,0,332,334,3,46,23,0,333,332,1,0,0,0,
  	333,334,1,0,0,0,334,335,1,0,0,0,335,336,5,10,0,0,336,337,3,42,21,0,337,
  	338,5,11,0,0,338,341,1,0,0,0,339,341,3,48,24,0,340,331,1,0,0,0,340,339,
  	1,0,0,0,341,348,1,0,0,0,342,343,10,3,0,0,343,344,3,44,22,0,344,345,3,
  	42,21,4,345,347,1,0,0,0,346,342,1,0,0,0,347,350,1,0,0,0,348,346,1,0,0,
  	0,348,349,1,0,0,0,349,43,1,0,0,0,350,348,1,0,0,0,351,352,7,1,0,0,352,
  	45,1,0,0,0,353,354,7,2,0,0,354,47,1,0,0,0,355,357,3,46,23,0,356,355,1,
  	0,0,0,356,357,1,0,0,0,357,363,1,0,0,0,358,364,3,50,25,0,359,364,3,52,
  	26,0,360,364,3,54,27,0,361,364,5,49,0,0,362,364,5,6,0,0,363,358,1,0,0,
  	0,363,359,1,0,0,0,363,360,1,0,0,0,363,361,1,0,0,0,363,362,1,0,0,0,364,
  	49,1,0,0,0,365,366,7,3,0,0,366,51,1,0,0,0,367,368,7,4,0,0,368,53,1,0,
  	0,0,369,370,5,38,0,0,370,55,1,0,0,0,371,372,5,37,0,0,372,375,5,2,0,0,
  	373,376,3,50,25,0,374,376,3,52,26,0,375,373,1,0,0,0,375,374,1,0,0,0,376,
  	377,1,0,0,0,377,380,5,2,0,0,378,381,3,58,29,0,379,381,3,8,4,0,380,378,
  	1,0,0,0,380,379,1,0,0,0,381,57,1,0,0,0,382,390,3,60,30,0,383,390,3,62,
  	31,0,384,390,3,64,32,0,385,390,3,66,33,0,386,390,3,68,34,0,387,390,3,
  	70,35,0,388,390,3,72,36,0,389,382,1,0,0,0,389,383,1,0,0,0,389,384,1,0,
  	0,0,389,385,1,0,0,0,389,386,1,0,0,0,389,387,1,0,0,0,389,388,1,0,0,0,390,
  	59,1,0,0,0,391,392,5,30,0,0,392,395,5,2,0,0,393,394,5,39,0,0,394,396,
  	5,2,0,0,395,393,1,0,0,0,395,396,1,0,0,0,396,397,1,0,0,0,397,398,3,42,
  	21,0,398,61,1,0,0,0,399,401,5,31,0,0,400,402,3,74,37,0,401,400,1,0,0,
  	0,402,403,1,0,0,0,403,401,1,0,0,0,403,404,1,0,0,0,404,63,1,0,0,0,405,
  	407,5,32,0,0,406,408,3,74,37,0,407,406,1,0,0,0,408,409,1,0,0,0,409,407,
  	1,0,0,0,409,410,1,0,0,0,410,65,1,0,0,0,411,413,5,33,0,0,412,414,3,74,
  	37,0,413,412,1,0,0,0,414,415,1,0,0,0,415,413,1,0,0,0,415,416,1,0,0,0,
  	416,67,1,0,0,0,417,418,5,34,0,0,418,419,5,2,0,0,419,420,3,76,38,0,420,
  	69,1,0,0,0,421,428,5,35,0,0,422,423,5,2,0,0,423,426,3,42,21,0,424,425,
  	5,2,0,0,425,427,3,42,21,0,426,424,1,0,0,0,426,427,1,0,0,0,427,429,1,0,
  	0,0,428,422,1,0,0,0,428,429,1,0,0,0,429,71,1,0,0,0,430,431,5,36,0,0,431,
  	432,5,2,0,0,432,435,3,42,21,0,433,434,5,2,0,0,434,436,3,42,21,0,435,433,
  	1,0,0,0,435,436,1,0,0,0,436,73,1,0,0,0,437,438,5,2,0,0,438,440,3,42,21,
  	0,439,441,5,19,0,0,440,439,1,0,0,0,440,441,1,0,0,0,441,75,1,0,0,0,442,
  	446,5,50,0,0,443,445,3,78,39,0,444,443,1,0,0,0,445,448,1,0,0,0,446,444,
  	1,0,0,0,446,447,1,0,0,0,447,449,1,0,0,0,448,446,1,0,0,0,449,450,5,50,
  	0,0,450,77,1,0,0,0,451,452,7,5,0,0,452,79,1,0,0,0,57,83,88,94,100,106,
  	111,115,121,125,130,135,141,145,151,155,160,164,169,173,178,182,187,190,
  	193,196,200,221,232,241,249,254,258,261,269,272,280,290,300,303,325,333,
  	340,348,356,363,375,380,389,395,403,409,415,426,428,435,440,446
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  asm6502parserParserStaticData = staticData.release();
}

}

asm6502Parser::asm6502Parser(TokenStream *input) : asm6502Parser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

asm6502Parser::asm6502Parser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  asm6502Parser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *asm6502parserParserStaticData->atn, asm6502parserParserStaticData->decisionToDFA, asm6502parserParserStaticData->sharedContextCache, options);
}

asm6502Parser::~asm6502Parser() {
  delete _interpreter;
}

const atn::ATN& asm6502Parser::getATN() const {
  return *asm6502parserParserStaticData->atn;
}

std::string asm6502Parser::getGrammarFileName() const {
  return "asm6502Parser.g4";
}

const std::vector<std::string>& asm6502Parser::getRuleNames() const {
  return asm6502parserParserStaticData->ruleNames;
}

const dfa::Vocabulary& asm6502Parser::getVocabulary() const {
  return asm6502parserParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView asm6502Parser::getSerializedATN() const {
  return asm6502parserParserStaticData->serializedATN;
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
    setState(81); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(80);
      line();
      setState(83); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << asm6502Parser::COMMENT)
      | (1ULL << asm6502Parser::WHITESPACE)
      | (1ULL << asm6502Parser::NEWLINE)
      | (1ULL << asm6502Parser::AT)
      | (1ULL << asm6502Parser::DORG)
      | (1ULL << asm6502Parser::DBYTE)
      | (1ULL << asm6502Parser::DDBYTE)
      | (1ULL << asm6502Parser::DWORD)
      | (1ULL << asm6502Parser::DTEXT)
      | (1ULL << asm6502Parser::DALIGN)
      | (1ULL << asm6502Parser::DFILL)
      | (1ULL << asm6502Parser::DREPEAT)
      | (1ULL << asm6502Parser::NOP)
      | (1ULL << asm6502Parser::IMPLIED)
      | (1ULL << asm6502Parser::BRANCH)
      | (1ULL << asm6502Parser::SHIFT)
      | (1ULL << asm6502Parser::JUMP)
      | (1ULL << asm6502Parser::JSR)
      | (1ULL << asm6502Parser::MNEMONIC)
      | (1ULL << asm6502Parser::SYMBOL))) != 0));
    setState(85);
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

asm6502Parser::DirectiveContext* asm6502Parser::LineContext::directive() {
  return getRuleContext<asm6502Parser::DirectiveContext>(0);
}

asm6502Parser::Repeat_directiveContext* asm6502Parser::LineContext::repeat_directive() {
  return getRuleContext<asm6502Parser::Repeat_directiveContext>(0);
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
    setState(193);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 23, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(88);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == asm6502Parser::WHITESPACE) {
        setState(87);
        match(asm6502Parser::WHITESPACE);
      }
      setState(90);
      label();
      setState(91);
      match(asm6502Parser::WHITESPACE);
      setState(92);
      instruction();
      setState(94);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == asm6502Parser::WHITESPACE) {
        setState(93);
        match(asm6502Parser::WHITESPACE);
      }
      setState(96);
      comment();
      setState(97);
      match(asm6502Parser::NEWLINE);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(100);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == asm6502Parser::WHITESPACE) {
        setState(99);
        match(asm6502Parser::WHITESPACE);
      }
      setState(102);
      label();
      setState(103);
      match(asm6502Parser::WHITESPACE);
      setState(104);
      instruction();
      setState(106);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == asm6502Parser::WHITESPACE) {
        setState(105);
        match(asm6502Parser::WHITESPACE);
      }
      setState(108);
      match(asm6502Parser::NEWLINE);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(111);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == asm6502Parser::WHITESPACE) {
        setState(110);
        match(asm6502Parser::WHITESPACE);
      }
      setState(113);
      label();
      setState(115);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == asm6502Parser::WHITESPACE) {
        setState(114);
        match(asm6502Parser::WHITESPACE);
      }
      setState(117);
      comment();
      setState(118);
      match(asm6502Parser::NEWLINE);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(121);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == asm6502Parser::WHITESPACE) {
        setState(120);
        match(asm6502Parser::WHITESPACE);
      }
      setState(123);
      label();
      setState(125);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == asm6502Parser::WHITESPACE) {
        setState(124);
        match(asm6502Parser::WHITESPACE);
      }
      setState(127);
      match(asm6502Parser::NEWLINE);
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(130);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == asm6502Parser::WHITESPACE) {
        setState(129);
        match(asm6502Parser::WHITESPACE);
      }
      setState(135);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 10, _ctx)) {
      case 1: {
        setState(132);
        label();
        setState(133);
        match(asm6502Parser::WHITESPACE);
        break;
      }

      default:
        break;
      }
      setState(137);
      assign();
      setState(138);
      match(asm6502Parser::NEWLINE);
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(141);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == asm6502Parser::WHITESPACE) {
        setState(140);
        match(asm6502Parser::WHITESPACE);
      }
      setState(143);
      instruction();
      setState(145);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == asm6502Parser::WHITESPACE) {
        setState(144);
        match(asm6502Parser::WHITESPACE);
      }
      setState(147);
      comment();
      setState(148);
      match(asm6502Parser::NEWLINE);
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(151);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == asm6502Parser::WHITESPACE) {
        setState(150);
        match(asm6502Parser::WHITESPACE);
      }
      setState(153);
      instruction();
      setState(155);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == asm6502Parser::WHITESPACE) {
        setState(154);
        match(asm6502Parser::WHITESPACE);
      }
      setState(157);
      match(asm6502Parser::NEWLINE);
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(160);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == asm6502Parser::WHITESPACE) {
        setState(159);
        match(asm6502Parser::WHITESPACE);
      }
      setState(162);
      assign();
      setState(164);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == asm6502Parser::COMMENT) {
        setState(163);
        comment();
      }
      setState(166);
      match(asm6502Parser::NEWLINE);
      break;
    }

    case 9: {
      enterOuterAlt(_localctx, 9);
      setState(169);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == asm6502Parser::WHITESPACE) {
        setState(168);
        match(asm6502Parser::WHITESPACE);
      }
      setState(171);
      directive();
      setState(173);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == asm6502Parser::COMMENT) {
        setState(172);
        comment();
      }
      setState(175);
      match(asm6502Parser::NEWLINE);
      break;
    }

    case 10: {
      enterOuterAlt(_localctx, 10);
      setState(178);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == asm6502Parser::WHITESPACE) {
        setState(177);
        match(asm6502Parser::WHITESPACE);
      }
      setState(180);
      repeat_directive();
      setState(182);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == asm6502Parser::COMMENT) {
        setState(181);
        comment();
      }
      setState(184);
      match(asm6502Parser::NEWLINE);
      break;
    }

    case 11: {
      enterOuterAlt(_localctx, 11);
      setState(187);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == asm6502Parser::WHITESPACE) {
        setState(186);
        match(asm6502Parser::WHITESPACE);
      }
      setState(190);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == asm6502Parser::COMMENT) {
        setState(189);
        comment();
      }
      setState(192);
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
    setState(196);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == asm6502Parser::AT) {
      setState(195);
      match(asm6502Parser::AT);
    }
    setState(198);
    match(asm6502Parser::SYMBOL);
    setState(200);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == asm6502Parser::COLON) {
      setState(199);
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
    setState(202);
    match(asm6502Parser::SYMBOL);
    setState(203);
    match(asm6502Parser::WHITESPACE);
    setState(204);
    match(asm6502Parser::EQU);
    setState(205);
    match(asm6502Parser::WHITESPACE);
    setState(206);
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

asm6502Parser::Zero_pageContext* asm6502Parser::InstructionContext::zero_page() {
  return getRuleContext<asm6502Parser::Zero_pageContext>(0);
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
    setState(221);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 26, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(208);
      nop();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(209);
      implicit();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(210);
      acc();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(211);
      immediate();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(212);
      zero_page();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(213);
      x_index();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(214);
      y_index();
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(215);
      x_indirect();
      break;
    }

    case 9: {
      enterOuterAlt(_localctx, 9);
      setState(216);
      indirect_y();
      break;
    }

    case 10: {
      enterOuterAlt(_localctx, 10);
      setState(217);
      absolute();
      break;
    }

    case 11: {
      enterOuterAlt(_localctx, 11);
      setState(218);
      relative();
      break;
    }

    case 12: {
      enterOuterAlt(_localctx, 12);
      setState(219);
      jump();
      break;
    }

    case 13: {
      enterOuterAlt(_localctx, 13);
      setState(220);
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
    setState(223);
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
    setState(225);
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
    setState(227);
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
    setState(229);
    shift();
    setState(232);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 27, _ctx)) {
    case 1: {
      setState(230);
      match(asm6502Parser::WHITESPACE);
      setState(231);
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
    setState(234);
    mnemonic();
    setState(235);
    match(asm6502Parser::WHITESPACE);
    setState(236);
    match(asm6502Parser::HASH);
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

//----------------- Zero_pageContext ------------------------------------------------------------------

asm6502Parser::Zero_pageContext::Zero_pageContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* asm6502Parser::Zero_pageContext::FORCED_BYTE() {
  return getToken(asm6502Parser::FORCED_BYTE, 0);
}

tree::TerminalNode* asm6502Parser::Zero_pageContext::WHITESPACE() {
  return getToken(asm6502Parser::WHITESPACE, 0);
}

asm6502Parser::ExpressionContext* asm6502Parser::Zero_pageContext::expression() {
  return getRuleContext<asm6502Parser::ExpressionContext>(0);
}

asm6502Parser::ShiftContext* asm6502Parser::Zero_pageContext::shift() {
  return getRuleContext<asm6502Parser::ShiftContext>(0);
}

asm6502Parser::MnemonicContext* asm6502Parser::Zero_pageContext::mnemonic() {
  return getRuleContext<asm6502Parser::MnemonicContext>(0);
}

asm6502Parser::ByteContext* asm6502Parser::Zero_pageContext::byte() {
  return getRuleContext<asm6502Parser::ByteContext>(0);
}


size_t asm6502Parser::Zero_pageContext::getRuleIndex() const {
  return asm6502Parser::RuleZero_page;
}


asm6502Parser::Zero_pageContext* asm6502Parser::zero_page() {
  Zero_pageContext *_localctx = _tracker.createInstance<Zero_pageContext>(_ctx, getState());
  enterRule(_localctx, 20, asm6502Parser::RuleZero_page);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(254);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 30, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(241);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case asm6502Parser::SHIFT: {
          setState(239);
          shift();
          break;
        }

        case asm6502Parser::MNEMONIC: {
          setState(240);
          mnemonic();
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      setState(243);
      match(asm6502Parser::FORCED_BYTE);
      setState(244);
      match(asm6502Parser::WHITESPACE);
      setState(245);
      expression(0);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(249);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case asm6502Parser::SHIFT: {
          setState(247);
          shift();
          break;
        }

        case asm6502Parser::MNEMONIC: {
          setState(248);
          mnemonic();
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      setState(251);
      match(asm6502Parser::WHITESPACE);
      setState(252);
      byte();
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

tree::TerminalNode* asm6502Parser::X_indexContext::FORCED_BYTE() {
  return getToken(asm6502Parser::FORCED_BYTE, 0);
}

tree::TerminalNode* asm6502Parser::X_indexContext::FORCED_WORD() {
  return getToken(asm6502Parser::FORCED_WORD, 0);
}


size_t asm6502Parser::X_indexContext::getRuleIndex() const {
  return asm6502Parser::RuleX_index;
}


asm6502Parser::X_indexContext* asm6502Parser::x_index() {
  X_indexContext *_localctx = _tracker.createInstance<X_indexContext>(_ctx, getState());
  enterRule(_localctx, 22, asm6502Parser::RuleX_index);
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
    setState(258);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case asm6502Parser::SHIFT: {
        setState(256);
        shift();
        break;
      }

      case asm6502Parser::MNEMONIC: {
        setState(257);
        mnemonic();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(261);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == asm6502Parser::FORCED_BYTE

    || _la == asm6502Parser::FORCED_WORD) {
      setState(260);
      _la = _input->LA(1);
      if (!(_la == asm6502Parser::FORCED_BYTE

      || _la == asm6502Parser::FORCED_WORD)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
    }
    setState(263);
    match(asm6502Parser::WHITESPACE);
    setState(264);
    expression(0);
    setState(265);
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

tree::TerminalNode* asm6502Parser::Y_indexContext::FORCED_BYTE() {
  return getToken(asm6502Parser::FORCED_BYTE, 0);
}

tree::TerminalNode* asm6502Parser::Y_indexContext::FORCED_WORD() {
  return getToken(asm6502Parser::FORCED_WORD, 0);
}


size_t asm6502Parser::Y_indexContext::getRuleIndex() const {
  return asm6502Parser::RuleY_index;
}


asm6502Parser::Y_indexContext* asm6502Parser::y_index() {
  Y_indexContext *_localctx = _tracker.createInstance<Y_indexContext>(_ctx, getState());
  enterRule(_localctx, 24, asm6502Parser::RuleY_index);
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
    setState(269);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case asm6502Parser::SHIFT: {
        setState(267);
        shift();
        break;
      }

      case asm6502Parser::MNEMONIC: {
        setState(268);
        mnemonic();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(272);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == asm6502Parser::FORCED_BYTE

    || _la == asm6502Parser::FORCED_WORD) {
      setState(271);
      _la = _input->LA(1);
      if (!(_la == asm6502Parser::FORCED_BYTE

      || _la == asm6502Parser::FORCED_WORD)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
    }
    setState(274);
    match(asm6502Parser::WHITESPACE);
    setState(275);
    expression(0);
    setState(276);
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

tree::TerminalNode* asm6502Parser::X_indirectContext::WHITESPACE() {
  return getToken(asm6502Parser::WHITESPACE, 0);
}

tree::TerminalNode* asm6502Parser::X_indirectContext::LPAREN() {
  return getToken(asm6502Parser::LPAREN, 0);
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
  enterRule(_localctx, 26, asm6502Parser::RuleX_indirect);

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
    switch (_input->LA(1)) {
      case asm6502Parser::SHIFT: {
        setState(278);
        shift();
        break;
      }

      case asm6502Parser::MNEMONIC: {
        setState(279);
        mnemonic();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(282);
    match(asm6502Parser::WHITESPACE);
    setState(283);
    match(asm6502Parser::LPAREN);
    setState(284);
    expression(0);
    setState(285);
    match(asm6502Parser::X_INDEX);
    setState(286);
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

tree::TerminalNode* asm6502Parser::Indirect_yContext::WHITESPACE() {
  return getToken(asm6502Parser::WHITESPACE, 0);
}

tree::TerminalNode* asm6502Parser::Indirect_yContext::LPAREN() {
  return getToken(asm6502Parser::LPAREN, 0);
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
  enterRule(_localctx, 28, asm6502Parser::RuleIndirect_y);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(290);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case asm6502Parser::SHIFT: {
        setState(288);
        shift();
        break;
      }

      case asm6502Parser::MNEMONIC: {
        setState(289);
        mnemonic();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(292);
    match(asm6502Parser::WHITESPACE);
    setState(293);
    match(asm6502Parser::LPAREN);
    setState(294);
    expression(0);
    setState(295);
    match(asm6502Parser::RPAREN);
    setState(296);
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

tree::TerminalNode* asm6502Parser::AbsoluteContext::FORCED_WORD() {
  return getToken(asm6502Parser::FORCED_WORD, 0);
}


size_t asm6502Parser::AbsoluteContext::getRuleIndex() const {
  return asm6502Parser::RuleAbsolute;
}


asm6502Parser::AbsoluteContext* asm6502Parser::absolute() {
  AbsoluteContext *_localctx = _tracker.createInstance<AbsoluteContext>(_ctx, getState());
  enterRule(_localctx, 30, asm6502Parser::RuleAbsolute);
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
    setState(300);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case asm6502Parser::SHIFT: {
        setState(298);
        shift();
        break;
      }

      case asm6502Parser::MNEMONIC: {
        setState(299);
        mnemonic();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(303);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == asm6502Parser::FORCED_WORD) {
      setState(302);
      match(asm6502Parser::FORCED_WORD);
    }
    setState(305);
    match(asm6502Parser::WHITESPACE);
    setState(306);
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
  enterRule(_localctx, 32, asm6502Parser::RuleRelative);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(308);
    match(asm6502Parser::BRANCH);
    setState(309);
    match(asm6502Parser::WHITESPACE);
    setState(310);
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
  enterRule(_localctx, 34, asm6502Parser::RuleMnemonic);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(312);
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
  enterRule(_localctx, 36, asm6502Parser::RuleShift);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(314);
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
  enterRule(_localctx, 38, asm6502Parser::RuleJump);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(325);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 39, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(316);
      match(asm6502Parser::JUMP);
      setState(317);
      match(asm6502Parser::WHITESPACE);
      setState(318);
      expression(0);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(319);
      match(asm6502Parser::JUMP);
      setState(320);
      match(asm6502Parser::WHITESPACE);
      setState(321);
      match(asm6502Parser::LPAREN);
      setState(322);
      expression(0);
      setState(323);
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
  enterRule(_localctx, 40, asm6502Parser::RuleJsr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(327);
    match(asm6502Parser::JSR);
    setState(328);
    match(asm6502Parser::WHITESPACE);
    setState(329);
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

asm6502Parser::Unary_opContext* asm6502Parser::ExpressionContext::unary_op() {
  return getRuleContext<asm6502Parser::Unary_opContext>(0);
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
  size_t startState = 42;
  enterRecursionRule(_localctx, 42, asm6502Parser::RuleExpression, precedence);

    size_t _la = 0;

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
    setState(340);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 41, _ctx)) {
    case 1: {
      setState(333);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << asm6502Parser::PLUS)
        | (1ULL << asm6502Parser::MINUS)
        | (1ULL << asm6502Parser::LOW_BYTE_VALUE)
        | (1ULL << asm6502Parser::HIGH_BYTE_VALUE))) != 0)) {
        setState(332);
        unary_op();
      }
      setState(335);
      match(asm6502Parser::LBRACKET);
      setState(336);
      expression(0);
      setState(337);
      match(asm6502Parser::RBRACKET);
      break;
    }

    case 2: {
      setState(339);
      atom();
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(348);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 42, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<ExpressionContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleExpression);
        setState(342);

        if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
        setState(343);
        binary_op();
        setState(344);
        expression(4); 
      }
      setState(350);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 42, _ctx);
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
  enterRule(_localctx, 44, asm6502Parser::RuleBinary_op);
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
    setState(351);
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
  enterRule(_localctx, 46, asm6502Parser::RuleUnary_op);
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
    setState(353);
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
  enterRule(_localctx, 48, asm6502Parser::RuleAtom);
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
    setState(356);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << asm6502Parser::PLUS)
      | (1ULL << asm6502Parser::MINUS)
      | (1ULL << asm6502Parser::LOW_BYTE_VALUE)
      | (1ULL << asm6502Parser::HIGH_BYTE_VALUE))) != 0)) {
      setState(355);
      unary_op();
    }
    setState(363);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case asm6502Parser::OCTAL_BYTE:
      case asm6502Parser::HEX_BYTE:
      case asm6502Parser::DECIMAL_BYTE:
      case asm6502Parser::BINARY_BYTE: {
        setState(358);
        byte();
        break;
      }

      case asm6502Parser::OCTAL_NUMBER:
      case asm6502Parser::HEX_NUMBER:
      case asm6502Parser::DECIMAL_NUMBER:
      case asm6502Parser::BINARY_NUMBER: {
        setState(359);
        multibyte();
        break;
      }

      case asm6502Parser::CHARACTER: {
        setState(360);
        character();
        break;
      }

      case asm6502Parser::SYMBOL: {
        setState(361);
        match(asm6502Parser::SYMBOL);
        break;
      }

      case asm6502Parser::STAR: {
        setState(362);
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
  enterRule(_localctx, 50, asm6502Parser::RuleByte);
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
    setState(365);
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
  enterRule(_localctx, 52, asm6502Parser::RuleMultibyte);
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
    setState(367);
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
  enterRule(_localctx, 54, asm6502Parser::RuleCharacter);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(369);
    match(asm6502Parser::CHARACTER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Repeat_directiveContext ------------------------------------------------------------------

asm6502Parser::Repeat_directiveContext::Repeat_directiveContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* asm6502Parser::Repeat_directiveContext::DREPEAT() {
  return getToken(asm6502Parser::DREPEAT, 0);
}

std::vector<tree::TerminalNode *> asm6502Parser::Repeat_directiveContext::WHITESPACE() {
  return getTokens(asm6502Parser::WHITESPACE);
}

tree::TerminalNode* asm6502Parser::Repeat_directiveContext::WHITESPACE(size_t i) {
  return getToken(asm6502Parser::WHITESPACE, i);
}

asm6502Parser::ByteContext* asm6502Parser::Repeat_directiveContext::byte() {
  return getRuleContext<asm6502Parser::ByteContext>(0);
}

asm6502Parser::MultibyteContext* asm6502Parser::Repeat_directiveContext::multibyte() {
  return getRuleContext<asm6502Parser::MultibyteContext>(0);
}

asm6502Parser::DirectiveContext* asm6502Parser::Repeat_directiveContext::directive() {
  return getRuleContext<asm6502Parser::DirectiveContext>(0);
}

asm6502Parser::InstructionContext* asm6502Parser::Repeat_directiveContext::instruction() {
  return getRuleContext<asm6502Parser::InstructionContext>(0);
}


size_t asm6502Parser::Repeat_directiveContext::getRuleIndex() const {
  return asm6502Parser::RuleRepeat_directive;
}


asm6502Parser::Repeat_directiveContext* asm6502Parser::repeat_directive() {
  Repeat_directiveContext *_localctx = _tracker.createInstance<Repeat_directiveContext>(_ctx, getState());
  enterRule(_localctx, 56, asm6502Parser::RuleRepeat_directive);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(371);
    match(asm6502Parser::DREPEAT);
    setState(372);
    match(asm6502Parser::WHITESPACE);
    setState(375);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case asm6502Parser::OCTAL_BYTE:
      case asm6502Parser::HEX_BYTE:
      case asm6502Parser::DECIMAL_BYTE:
      case asm6502Parser::BINARY_BYTE: {
        setState(373);
        byte();
        break;
      }

      case asm6502Parser::OCTAL_NUMBER:
      case asm6502Parser::HEX_NUMBER:
      case asm6502Parser::DECIMAL_NUMBER:
      case asm6502Parser::BINARY_NUMBER: {
        setState(374);
        multibyte();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(377);
    match(asm6502Parser::WHITESPACE);
    setState(380);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case asm6502Parser::DORG:
      case asm6502Parser::DBYTE:
      case asm6502Parser::DDBYTE:
      case asm6502Parser::DWORD:
      case asm6502Parser::DTEXT:
      case asm6502Parser::DALIGN:
      case asm6502Parser::DFILL: {
        setState(378);
        directive();
        break;
      }

      case asm6502Parser::NOP:
      case asm6502Parser::IMPLIED:
      case asm6502Parser::BRANCH:
      case asm6502Parser::SHIFT:
      case asm6502Parser::JUMP:
      case asm6502Parser::JSR:
      case asm6502Parser::MNEMONIC: {
        setState(379);
        instruction();
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

//----------------- DirectiveContext ------------------------------------------------------------------

asm6502Parser::DirectiveContext::DirectiveContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

asm6502Parser::OrgContext* asm6502Parser::DirectiveContext::org() {
  return getRuleContext<asm6502Parser::OrgContext>(0);
}

asm6502Parser::Byte_directiveContext* asm6502Parser::DirectiveContext::byte_directive() {
  return getRuleContext<asm6502Parser::Byte_directiveContext>(0);
}

asm6502Parser::Dbyte_directiveContext* asm6502Parser::DirectiveContext::dbyte_directive() {
  return getRuleContext<asm6502Parser::Dbyte_directiveContext>(0);
}

asm6502Parser::Word_directiveContext* asm6502Parser::DirectiveContext::word_directive() {
  return getRuleContext<asm6502Parser::Word_directiveContext>(0);
}

asm6502Parser::Text_directiveContext* asm6502Parser::DirectiveContext::text_directive() {
  return getRuleContext<asm6502Parser::Text_directiveContext>(0);
}

asm6502Parser::Align_directiveContext* asm6502Parser::DirectiveContext::align_directive() {
  return getRuleContext<asm6502Parser::Align_directiveContext>(0);
}

asm6502Parser::Fill_directiveContext* asm6502Parser::DirectiveContext::fill_directive() {
  return getRuleContext<asm6502Parser::Fill_directiveContext>(0);
}


size_t asm6502Parser::DirectiveContext::getRuleIndex() const {
  return asm6502Parser::RuleDirective;
}


asm6502Parser::DirectiveContext* asm6502Parser::directive() {
  DirectiveContext *_localctx = _tracker.createInstance<DirectiveContext>(_ctx, getState());
  enterRule(_localctx, 58, asm6502Parser::RuleDirective);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(389);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case asm6502Parser::DORG: {
        enterOuterAlt(_localctx, 1);
        setState(382);
        org();
        break;
      }

      case asm6502Parser::DBYTE: {
        enterOuterAlt(_localctx, 2);
        setState(383);
        byte_directive();
        break;
      }

      case asm6502Parser::DDBYTE: {
        enterOuterAlt(_localctx, 3);
        setState(384);
        dbyte_directive();
        break;
      }

      case asm6502Parser::DWORD: {
        enterOuterAlt(_localctx, 4);
        setState(385);
        word_directive();
        break;
      }

      case asm6502Parser::DTEXT: {
        enterOuterAlt(_localctx, 5);
        setState(386);
        text_directive();
        break;
      }

      case asm6502Parser::DALIGN: {
        enterOuterAlt(_localctx, 6);
        setState(387);
        align_directive();
        break;
      }

      case asm6502Parser::DFILL: {
        enterOuterAlt(_localctx, 7);
        setState(388);
        fill_directive();
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

//----------------- OrgContext ------------------------------------------------------------------

asm6502Parser::OrgContext::OrgContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* asm6502Parser::OrgContext::DORG() {
  return getToken(asm6502Parser::DORG, 0);
}

std::vector<tree::TerminalNode *> asm6502Parser::OrgContext::WHITESPACE() {
  return getTokens(asm6502Parser::WHITESPACE);
}

tree::TerminalNode* asm6502Parser::OrgContext::WHITESPACE(size_t i) {
  return getToken(asm6502Parser::WHITESPACE, i);
}

asm6502Parser::ExpressionContext* asm6502Parser::OrgContext::expression() {
  return getRuleContext<asm6502Parser::ExpressionContext>(0);
}

tree::TerminalNode* asm6502Parser::OrgContext::EQU() {
  return getToken(asm6502Parser::EQU, 0);
}


size_t asm6502Parser::OrgContext::getRuleIndex() const {
  return asm6502Parser::RuleOrg;
}


asm6502Parser::OrgContext* asm6502Parser::org() {
  OrgContext *_localctx = _tracker.createInstance<OrgContext>(_ctx, getState());
  enterRule(_localctx, 60, asm6502Parser::RuleOrg);
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
    setState(391);
    match(asm6502Parser::DORG);
    setState(392);
    match(asm6502Parser::WHITESPACE);
    setState(395);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == asm6502Parser::EQU) {
      setState(393);
      match(asm6502Parser::EQU);
      setState(394);
      match(asm6502Parser::WHITESPACE);
    }
    setState(397);
    expression(0);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Byte_directiveContext ------------------------------------------------------------------

asm6502Parser::Byte_directiveContext::Byte_directiveContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* asm6502Parser::Byte_directiveContext::DBYTE() {
  return getToken(asm6502Parser::DBYTE, 0);
}

std::vector<asm6502Parser::Byte_directive_valueContext *> asm6502Parser::Byte_directiveContext::byte_directive_value() {
  return getRuleContexts<asm6502Parser::Byte_directive_valueContext>();
}

asm6502Parser::Byte_directive_valueContext* asm6502Parser::Byte_directiveContext::byte_directive_value(size_t i) {
  return getRuleContext<asm6502Parser::Byte_directive_valueContext>(i);
}


size_t asm6502Parser::Byte_directiveContext::getRuleIndex() const {
  return asm6502Parser::RuleByte_directive;
}


asm6502Parser::Byte_directiveContext* asm6502Parser::byte_directive() {
  Byte_directiveContext *_localctx = _tracker.createInstance<Byte_directiveContext>(_ctx, getState());
  enterRule(_localctx, 62, asm6502Parser::RuleByte_directive);
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
    setState(399);
    match(asm6502Parser::DBYTE);
    setState(401); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(400);
      byte_directive_value();
      setState(403); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (_la == asm6502Parser::WHITESPACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Dbyte_directiveContext ------------------------------------------------------------------

asm6502Parser::Dbyte_directiveContext::Dbyte_directiveContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* asm6502Parser::Dbyte_directiveContext::DDBYTE() {
  return getToken(asm6502Parser::DDBYTE, 0);
}

std::vector<asm6502Parser::Byte_directive_valueContext *> asm6502Parser::Dbyte_directiveContext::byte_directive_value() {
  return getRuleContexts<asm6502Parser::Byte_directive_valueContext>();
}

asm6502Parser::Byte_directive_valueContext* asm6502Parser::Dbyte_directiveContext::byte_directive_value(size_t i) {
  return getRuleContext<asm6502Parser::Byte_directive_valueContext>(i);
}


size_t asm6502Parser::Dbyte_directiveContext::getRuleIndex() const {
  return asm6502Parser::RuleDbyte_directive;
}


asm6502Parser::Dbyte_directiveContext* asm6502Parser::dbyte_directive() {
  Dbyte_directiveContext *_localctx = _tracker.createInstance<Dbyte_directiveContext>(_ctx, getState());
  enterRule(_localctx, 64, asm6502Parser::RuleDbyte_directive);
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
    setState(405);
    match(asm6502Parser::DDBYTE);
    setState(407); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(406);
      byte_directive_value();
      setState(409); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (_la == asm6502Parser::WHITESPACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Word_directiveContext ------------------------------------------------------------------

asm6502Parser::Word_directiveContext::Word_directiveContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* asm6502Parser::Word_directiveContext::DWORD() {
  return getToken(asm6502Parser::DWORD, 0);
}

std::vector<asm6502Parser::Byte_directive_valueContext *> asm6502Parser::Word_directiveContext::byte_directive_value() {
  return getRuleContexts<asm6502Parser::Byte_directive_valueContext>();
}

asm6502Parser::Byte_directive_valueContext* asm6502Parser::Word_directiveContext::byte_directive_value(size_t i) {
  return getRuleContext<asm6502Parser::Byte_directive_valueContext>(i);
}


size_t asm6502Parser::Word_directiveContext::getRuleIndex() const {
  return asm6502Parser::RuleWord_directive;
}


asm6502Parser::Word_directiveContext* asm6502Parser::word_directive() {
  Word_directiveContext *_localctx = _tracker.createInstance<Word_directiveContext>(_ctx, getState());
  enterRule(_localctx, 66, asm6502Parser::RuleWord_directive);
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
    setState(411);
    match(asm6502Parser::DWORD);
    setState(413); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(412);
      byte_directive_value();
      setState(415); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (_la == asm6502Parser::WHITESPACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Text_directiveContext ------------------------------------------------------------------

asm6502Parser::Text_directiveContext::Text_directiveContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* asm6502Parser::Text_directiveContext::DTEXT() {
  return getToken(asm6502Parser::DTEXT, 0);
}

tree::TerminalNode* asm6502Parser::Text_directiveContext::WHITESPACE() {
  return getToken(asm6502Parser::WHITESPACE, 0);
}

asm6502Parser::StringContext* asm6502Parser::Text_directiveContext::string() {
  return getRuleContext<asm6502Parser::StringContext>(0);
}


size_t asm6502Parser::Text_directiveContext::getRuleIndex() const {
  return asm6502Parser::RuleText_directive;
}


asm6502Parser::Text_directiveContext* asm6502Parser::text_directive() {
  Text_directiveContext *_localctx = _tracker.createInstance<Text_directiveContext>(_ctx, getState());
  enterRule(_localctx, 68, asm6502Parser::RuleText_directive);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(417);
    match(asm6502Parser::DTEXT);
    setState(418);
    match(asm6502Parser::WHITESPACE);
    setState(419);
    string();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Align_directiveContext ------------------------------------------------------------------

asm6502Parser::Align_directiveContext::Align_directiveContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* asm6502Parser::Align_directiveContext::DALIGN() {
  return getToken(asm6502Parser::DALIGN, 0);
}

std::vector<tree::TerminalNode *> asm6502Parser::Align_directiveContext::WHITESPACE() {
  return getTokens(asm6502Parser::WHITESPACE);
}

tree::TerminalNode* asm6502Parser::Align_directiveContext::WHITESPACE(size_t i) {
  return getToken(asm6502Parser::WHITESPACE, i);
}

std::vector<asm6502Parser::ExpressionContext *> asm6502Parser::Align_directiveContext::expression() {
  return getRuleContexts<asm6502Parser::ExpressionContext>();
}

asm6502Parser::ExpressionContext* asm6502Parser::Align_directiveContext::expression(size_t i) {
  return getRuleContext<asm6502Parser::ExpressionContext>(i);
}


size_t asm6502Parser::Align_directiveContext::getRuleIndex() const {
  return asm6502Parser::RuleAlign_directive;
}


asm6502Parser::Align_directiveContext* asm6502Parser::align_directive() {
  Align_directiveContext *_localctx = _tracker.createInstance<Align_directiveContext>(_ctx, getState());
  enterRule(_localctx, 70, asm6502Parser::RuleAlign_directive);
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
    setState(421);
    match(asm6502Parser::DALIGN);
    setState(428);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == asm6502Parser::WHITESPACE) {
      setState(422);
      match(asm6502Parser::WHITESPACE);
      setState(423);
      expression(0);
      setState(426);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == asm6502Parser::WHITESPACE) {
        setState(424);
        match(asm6502Parser::WHITESPACE);
        setState(425);
        expression(0);
      }
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Fill_directiveContext ------------------------------------------------------------------

asm6502Parser::Fill_directiveContext::Fill_directiveContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* asm6502Parser::Fill_directiveContext::DFILL() {
  return getToken(asm6502Parser::DFILL, 0);
}

std::vector<tree::TerminalNode *> asm6502Parser::Fill_directiveContext::WHITESPACE() {
  return getTokens(asm6502Parser::WHITESPACE);
}

tree::TerminalNode* asm6502Parser::Fill_directiveContext::WHITESPACE(size_t i) {
  return getToken(asm6502Parser::WHITESPACE, i);
}

std::vector<asm6502Parser::ExpressionContext *> asm6502Parser::Fill_directiveContext::expression() {
  return getRuleContexts<asm6502Parser::ExpressionContext>();
}

asm6502Parser::ExpressionContext* asm6502Parser::Fill_directiveContext::expression(size_t i) {
  return getRuleContext<asm6502Parser::ExpressionContext>(i);
}


size_t asm6502Parser::Fill_directiveContext::getRuleIndex() const {
  return asm6502Parser::RuleFill_directive;
}


asm6502Parser::Fill_directiveContext* asm6502Parser::fill_directive() {
  Fill_directiveContext *_localctx = _tracker.createInstance<Fill_directiveContext>(_ctx, getState());
  enterRule(_localctx, 72, asm6502Parser::RuleFill_directive);
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
    setState(430);
    match(asm6502Parser::DFILL);
    setState(431);
    match(asm6502Parser::WHITESPACE);
    setState(432);
    expression(0);
    setState(435);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == asm6502Parser::WHITESPACE) {
      setState(433);
      match(asm6502Parser::WHITESPACE);
      setState(434);
      expression(0);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Byte_directive_valueContext ------------------------------------------------------------------

asm6502Parser::Byte_directive_valueContext::Byte_directive_valueContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* asm6502Parser::Byte_directive_valueContext::WHITESPACE() {
  return getToken(asm6502Parser::WHITESPACE, 0);
}

asm6502Parser::ExpressionContext* asm6502Parser::Byte_directive_valueContext::expression() {
  return getRuleContext<asm6502Parser::ExpressionContext>(0);
}

tree::TerminalNode* asm6502Parser::Byte_directive_valueContext::COMMA() {
  return getToken(asm6502Parser::COMMA, 0);
}


size_t asm6502Parser::Byte_directive_valueContext::getRuleIndex() const {
  return asm6502Parser::RuleByte_directive_value;
}


asm6502Parser::Byte_directive_valueContext* asm6502Parser::byte_directive_value() {
  Byte_directive_valueContext *_localctx = _tracker.createInstance<Byte_directive_valueContext>(_ctx, getState());
  enterRule(_localctx, 74, asm6502Parser::RuleByte_directive_value);
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
    setState(437);
    match(asm6502Parser::WHITESPACE);
    setState(438);
    expression(0);
    setState(440);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == asm6502Parser::COMMA) {
      setState(439);
      match(asm6502Parser::COMMA);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StringContext ------------------------------------------------------------------

asm6502Parser::StringContext::StringContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> asm6502Parser::StringContext::DQUOTE() {
  return getTokens(asm6502Parser::DQUOTE);
}

tree::TerminalNode* asm6502Parser::StringContext::DQUOTE(size_t i) {
  return getToken(asm6502Parser::DQUOTE, i);
}

std::vector<asm6502Parser::StringContentsContext *> asm6502Parser::StringContext::stringContents() {
  return getRuleContexts<asm6502Parser::StringContentsContext>();
}

asm6502Parser::StringContentsContext* asm6502Parser::StringContext::stringContents(size_t i) {
  return getRuleContext<asm6502Parser::StringContentsContext>(i);
}


size_t asm6502Parser::StringContext::getRuleIndex() const {
  return asm6502Parser::RuleString;
}


asm6502Parser::StringContext* asm6502Parser::string() {
  StringContext *_localctx = _tracker.createInstance<StringContext>(_ctx, getState());
  enterRule(_localctx, 76, asm6502Parser::RuleString);
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
    setState(442);
    match(asm6502Parser::DQUOTE);
    setState(446);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == asm6502Parser::TEXT

    || _la == asm6502Parser::ESCAPE_SEQUENCE) {
      setState(443);
      stringContents();
      setState(448);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(449);
    match(asm6502Parser::DQUOTE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StringContentsContext ------------------------------------------------------------------

asm6502Parser::StringContentsContext::StringContentsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* asm6502Parser::StringContentsContext::TEXT() {
  return getToken(asm6502Parser::TEXT, 0);
}

tree::TerminalNode* asm6502Parser::StringContentsContext::ESCAPE_SEQUENCE() {
  return getToken(asm6502Parser::ESCAPE_SEQUENCE, 0);
}


size_t asm6502Parser::StringContentsContext::getRuleIndex() const {
  return asm6502Parser::RuleStringContents;
}


asm6502Parser::StringContentsContext* asm6502Parser::stringContents() {
  StringContentsContext *_localctx = _tracker.createInstance<StringContentsContext>(_ctx, getState());
  enterRule(_localctx, 78, asm6502Parser::RuleStringContents);
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
    setState(451);
    _la = _input->LA(1);
    if (!(_la == asm6502Parser::TEXT

    || _la == asm6502Parser::ESCAPE_SEQUENCE)) {
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

bool asm6502Parser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 21: return expressionSempred(antlrcpp::downCast<ExpressionContext *>(context), predicateIndex);

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
  std::call_once(asm6502parserParserOnceFlag, asm6502parserParserInitialize);
}
