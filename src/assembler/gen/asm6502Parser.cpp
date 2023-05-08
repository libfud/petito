
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
  	4,1,52,427,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,7,
  	28,2,29,7,29,2,30,7,30,2,31,7,31,2,32,7,32,2,33,7,33,2,34,7,34,2,35,7,
  	35,2,36,7,36,2,37,7,37,2,38,7,38,2,39,7,39,1,0,5,0,82,8,0,10,0,12,0,85,
  	9,0,1,0,3,0,88,8,0,1,0,1,0,4,0,92,8,0,11,0,12,0,93,1,0,3,0,97,8,0,1,0,
  	5,0,100,8,0,10,0,12,0,103,9,0,1,0,5,0,106,8,0,10,0,12,0,109,9,0,1,0,1,
  	0,1,1,1,1,1,1,1,1,3,1,117,8,1,1,1,3,1,120,8,1,1,1,1,1,3,1,124,8,1,1,1,
  	3,1,127,8,1,1,1,1,1,3,1,131,8,1,1,1,3,1,134,8,1,1,1,1,1,3,1,138,8,1,1,
  	1,3,1,141,8,1,1,1,1,1,3,1,145,8,1,1,1,3,1,148,8,1,1,1,1,1,3,1,152,8,1,
  	1,1,3,1,155,8,1,1,1,1,1,3,1,159,8,1,1,1,3,1,162,8,1,1,1,3,1,165,8,1,3,
  	1,167,8,1,1,2,3,2,170,8,2,1,2,1,2,3,2,174,8,2,1,3,1,3,1,3,1,3,1,3,1,3,
  	1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,3,4,195,8,4,1,5,1,
  	5,1,6,1,6,1,7,1,7,1,8,1,8,1,8,3,8,206,8,8,1,9,1,9,1,9,1,9,1,9,1,10,1,
  	10,3,10,215,8,10,1,10,1,10,1,10,1,10,1,10,1,10,3,10,223,8,10,1,10,1,10,
  	1,10,3,10,228,8,10,1,11,1,11,3,11,232,8,11,1,11,3,11,235,8,11,1,11,1,
  	11,1,11,1,11,1,12,1,12,3,12,243,8,12,1,12,3,12,246,8,12,1,12,1,12,1,12,
  	1,12,1,13,1,13,3,13,254,8,13,1,13,1,13,1,13,1,13,1,13,1,13,1,14,1,14,
  	3,14,264,8,14,1,14,1,14,1,14,1,14,1,14,1,14,1,15,1,15,3,15,274,8,15,1,
  	15,3,15,277,8,15,1,15,1,15,1,15,1,16,1,16,1,16,1,16,1,17,1,17,1,18,1,
  	18,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,3,19,299,8,19,1,20,1,
  	20,1,20,1,20,1,21,1,21,3,21,307,8,21,1,21,1,21,1,21,1,21,1,21,3,21,314,
  	8,21,1,21,1,21,1,21,1,21,5,21,320,8,21,10,21,12,21,323,9,21,1,22,1,22,
  	1,23,1,23,1,24,3,24,330,8,24,1,24,1,24,1,24,1,24,1,24,3,24,337,8,24,1,
  	25,1,25,1,26,1,26,1,27,1,27,1,28,1,28,1,28,1,28,3,28,349,8,28,1,28,1,
  	28,1,28,3,28,354,8,28,1,29,1,29,1,29,1,29,1,29,1,29,1,29,3,29,363,8,29,
  	1,30,1,30,1,30,1,30,3,30,369,8,30,1,30,1,30,1,31,1,31,4,31,375,8,31,11,
  	31,12,31,376,1,32,1,32,4,32,381,8,32,11,32,12,32,382,1,33,1,33,4,33,387,
  	8,33,11,33,12,33,388,1,34,1,34,1,34,1,34,1,35,1,35,1,35,1,35,1,35,3,35,
  	400,8,35,3,35,402,8,35,1,36,1,36,1,36,1,36,1,36,3,36,409,8,36,1,37,1,
  	37,1,37,3,37,414,8,37,1,38,1,38,5,38,418,8,38,10,38,12,38,421,9,38,1,
  	38,1,38,1,39,1,39,1,39,0,1,42,40,0,2,4,6,8,10,12,14,16,18,20,22,24,26,
  	28,30,32,34,36,38,40,42,44,46,48,50,52,54,56,58,60,62,64,66,68,70,72,
  	74,76,78,0,6,1,0,17,18,1,0,4,7,2,0,4,5,8,9,4,0,22,22,24,24,26,26,28,28,
  	4,0,23,23,25,25,27,27,29,29,1,0,51,52,466,0,83,1,0,0,0,2,166,1,0,0,0,
  	4,169,1,0,0,0,6,175,1,0,0,0,8,194,1,0,0,0,10,196,1,0,0,0,12,198,1,0,0,
  	0,14,200,1,0,0,0,16,202,1,0,0,0,18,207,1,0,0,0,20,227,1,0,0,0,22,231,
  	1,0,0,0,24,242,1,0,0,0,26,253,1,0,0,0,28,263,1,0,0,0,30,273,1,0,0,0,32,
  	281,1,0,0,0,34,285,1,0,0,0,36,287,1,0,0,0,38,298,1,0,0,0,40,300,1,0,0,
  	0,42,313,1,0,0,0,44,324,1,0,0,0,46,326,1,0,0,0,48,329,1,0,0,0,50,338,
  	1,0,0,0,52,340,1,0,0,0,54,342,1,0,0,0,56,344,1,0,0,0,58,362,1,0,0,0,60,
  	364,1,0,0,0,62,372,1,0,0,0,64,378,1,0,0,0,66,384,1,0,0,0,68,390,1,0,0,
  	0,70,394,1,0,0,0,72,403,1,0,0,0,74,410,1,0,0,0,76,415,1,0,0,0,78,424,
  	1,0,0,0,80,82,5,3,0,0,81,80,1,0,0,0,82,85,1,0,0,0,83,81,1,0,0,0,83,84,
  	1,0,0,0,84,87,1,0,0,0,85,83,1,0,0,0,86,88,5,2,0,0,87,86,1,0,0,0,87,88,
  	1,0,0,0,88,89,1,0,0,0,89,101,3,2,1,0,90,92,5,3,0,0,91,90,1,0,0,0,92,93,
  	1,0,0,0,93,91,1,0,0,0,93,94,1,0,0,0,94,96,1,0,0,0,95,97,5,2,0,0,96,95,
  	1,0,0,0,96,97,1,0,0,0,97,98,1,0,0,0,98,100,3,2,1,0,99,91,1,0,0,0,100,
  	103,1,0,0,0,101,99,1,0,0,0,101,102,1,0,0,0,102,107,1,0,0,0,103,101,1,
  	0,0,0,104,106,5,3,0,0,105,104,1,0,0,0,106,109,1,0,0,0,107,105,1,0,0,0,
  	107,108,1,0,0,0,108,110,1,0,0,0,109,107,1,0,0,0,110,111,5,0,0,1,111,1,
  	1,0,0,0,112,113,3,4,2,0,113,114,5,2,0,0,114,116,3,8,4,0,115,117,5,2,0,
  	0,116,115,1,0,0,0,116,117,1,0,0,0,117,119,1,0,0,0,118,120,3,10,5,0,119,
  	118,1,0,0,0,119,120,1,0,0,0,120,167,1,0,0,0,121,123,3,4,2,0,122,124,5,
  	2,0,0,123,122,1,0,0,0,123,124,1,0,0,0,124,126,1,0,0,0,125,127,3,10,5,
  	0,126,125,1,0,0,0,126,127,1,0,0,0,127,167,1,0,0,0,128,130,3,6,3,0,129,
  	131,5,2,0,0,130,129,1,0,0,0,130,131,1,0,0,0,131,133,1,0,0,0,132,134,3,
  	10,5,0,133,132,1,0,0,0,133,134,1,0,0,0,134,167,1,0,0,0,135,137,3,8,4,
  	0,136,138,5,2,0,0,137,136,1,0,0,0,137,138,1,0,0,0,138,140,1,0,0,0,139,
  	141,3,10,5,0,140,139,1,0,0,0,140,141,1,0,0,0,141,167,1,0,0,0,142,144,
  	3,6,3,0,143,145,5,2,0,0,144,143,1,0,0,0,144,145,1,0,0,0,145,147,1,0,0,
  	0,146,148,3,10,5,0,147,146,1,0,0,0,147,148,1,0,0,0,148,167,1,0,0,0,149,
  	151,3,58,29,0,150,152,5,2,0,0,151,150,1,0,0,0,151,152,1,0,0,0,152,154,
  	1,0,0,0,153,155,3,10,5,0,154,153,1,0,0,0,154,155,1,0,0,0,155,167,1,0,
  	0,0,156,158,3,56,28,0,157,159,5,2,0,0,158,157,1,0,0,0,158,159,1,0,0,0,
  	159,161,1,0,0,0,160,162,3,10,5,0,161,160,1,0,0,0,161,162,1,0,0,0,162,
  	167,1,0,0,0,163,165,3,10,5,0,164,163,1,0,0,0,164,165,1,0,0,0,165,167,
  	1,0,0,0,166,112,1,0,0,0,166,121,1,0,0,0,166,128,1,0,0,0,166,135,1,0,0,
  	0,166,142,1,0,0,0,166,149,1,0,0,0,166,156,1,0,0,0,166,164,1,0,0,0,167,
  	3,1,0,0,0,168,170,5,16,0,0,169,168,1,0,0,0,169,170,1,0,0,0,170,171,1,
  	0,0,0,171,173,5,49,0,0,172,174,5,15,0,0,173,172,1,0,0,0,173,174,1,0,0,
  	0,174,5,1,0,0,0,175,176,5,49,0,0,176,177,5,2,0,0,177,178,5,39,0,0,178,
  	179,5,2,0,0,179,180,3,42,21,0,180,7,1,0,0,0,181,195,3,12,6,0,182,195,
  	3,14,7,0,183,195,3,16,8,0,184,195,3,18,9,0,185,195,3,20,10,0,186,195,
  	3,22,11,0,187,195,3,24,12,0,188,195,3,26,13,0,189,195,3,28,14,0,190,195,
  	3,30,15,0,191,195,3,32,16,0,192,195,3,38,19,0,193,195,3,40,20,0,194,181,
  	1,0,0,0,194,182,1,0,0,0,194,183,1,0,0,0,194,184,1,0,0,0,194,185,1,0,0,
  	0,194,186,1,0,0,0,194,187,1,0,0,0,194,188,1,0,0,0,194,189,1,0,0,0,194,
  	190,1,0,0,0,194,191,1,0,0,0,194,192,1,0,0,0,194,193,1,0,0,0,195,9,1,0,
  	0,0,196,197,5,1,0,0,197,11,1,0,0,0,198,199,5,40,0,0,199,13,1,0,0,0,200,
  	201,5,41,0,0,201,15,1,0,0,0,202,205,3,36,18,0,203,204,5,2,0,0,204,206,
  	5,48,0,0,205,203,1,0,0,0,205,206,1,0,0,0,206,17,1,0,0,0,207,208,3,34,
  	17,0,208,209,5,2,0,0,209,210,5,14,0,0,210,211,3,42,21,0,211,19,1,0,0,
  	0,212,215,3,36,18,0,213,215,3,34,17,0,214,212,1,0,0,0,214,213,1,0,0,0,
  	215,216,1,0,0,0,216,217,5,17,0,0,217,218,5,2,0,0,218,219,3,42,21,0,219,
  	228,1,0,0,0,220,223,3,36,18,0,221,223,3,34,17,0,222,220,1,0,0,0,222,221,
  	1,0,0,0,223,224,1,0,0,0,224,225,5,2,0,0,225,226,3,50,25,0,226,228,1,0,
  	0,0,227,214,1,0,0,0,227,222,1,0,0,0,228,21,1,0,0,0,229,232,3,36,18,0,
  	230,232,3,34,17,0,231,229,1,0,0,0,231,230,1,0,0,0,232,234,1,0,0,0,233,
  	235,7,0,0,0,234,233,1,0,0,0,234,235,1,0,0,0,235,236,1,0,0,0,236,237,5,
  	2,0,0,237,238,3,42,21,0,238,239,5,20,0,0,239,23,1,0,0,0,240,243,3,36,
  	18,0,241,243,3,34,17,0,242,240,1,0,0,0,242,241,1,0,0,0,243,245,1,0,0,
  	0,244,246,7,0,0,0,245,244,1,0,0,0,245,246,1,0,0,0,246,247,1,0,0,0,247,
  	248,5,2,0,0,248,249,3,42,21,0,249,250,5,21,0,0,250,25,1,0,0,0,251,254,
  	3,36,18,0,252,254,3,34,17,0,253,251,1,0,0,0,253,252,1,0,0,0,254,255,1,
  	0,0,0,255,256,5,2,0,0,256,257,5,12,0,0,257,258,3,42,21,0,258,259,5,20,
  	0,0,259,260,5,13,0,0,260,27,1,0,0,0,261,264,3,36,18,0,262,264,3,34,17,
  	0,263,261,1,0,0,0,263,262,1,0,0,0,264,265,1,0,0,0,265,266,5,2,0,0,266,
  	267,5,12,0,0,267,268,3,42,21,0,268,269,5,13,0,0,269,270,5,21,0,0,270,
  	29,1,0,0,0,271,274,3,36,18,0,272,274,3,34,17,0,273,271,1,0,0,0,273,272,
  	1,0,0,0,274,276,1,0,0,0,275,277,5,18,0,0,276,275,1,0,0,0,276,277,1,0,
  	0,0,277,278,1,0,0,0,278,279,5,2,0,0,279,280,3,42,21,0,280,31,1,0,0,0,
  	281,282,5,42,0,0,282,283,5,2,0,0,283,284,3,42,21,0,284,33,1,0,0,0,285,
  	286,5,46,0,0,286,35,1,0,0,0,287,288,5,43,0,0,288,37,1,0,0,0,289,290,5,
  	44,0,0,290,291,5,2,0,0,291,299,3,42,21,0,292,293,5,44,0,0,293,294,5,2,
  	0,0,294,295,5,12,0,0,295,296,3,42,21,0,296,297,5,13,0,0,297,299,1,0,0,
  	0,298,289,1,0,0,0,298,292,1,0,0,0,299,39,1,0,0,0,300,301,5,45,0,0,301,
  	302,5,2,0,0,302,303,3,42,21,0,303,41,1,0,0,0,304,306,6,21,-1,0,305,307,
  	3,46,23,0,306,305,1,0,0,0,306,307,1,0,0,0,307,308,1,0,0,0,308,309,5,10,
  	0,0,309,310,3,42,21,0,310,311,5,11,0,0,311,314,1,0,0,0,312,314,3,48,24,
  	0,313,304,1,0,0,0,313,312,1,0,0,0,314,321,1,0,0,0,315,316,10,3,0,0,316,
  	317,3,44,22,0,317,318,3,42,21,4,318,320,1,0,0,0,319,315,1,0,0,0,320,323,
  	1,0,0,0,321,319,1,0,0,0,321,322,1,0,0,0,322,43,1,0,0,0,323,321,1,0,0,
  	0,324,325,7,1,0,0,325,45,1,0,0,0,326,327,7,2,0,0,327,47,1,0,0,0,328,330,
  	3,46,23,0,329,328,1,0,0,0,329,330,1,0,0,0,330,336,1,0,0,0,331,337,3,50,
  	25,0,332,337,3,52,26,0,333,337,3,54,27,0,334,337,5,49,0,0,335,337,5,6,
  	0,0,336,331,1,0,0,0,336,332,1,0,0,0,336,333,1,0,0,0,336,334,1,0,0,0,336,
  	335,1,0,0,0,337,49,1,0,0,0,338,339,7,3,0,0,339,51,1,0,0,0,340,341,7,4,
  	0,0,341,53,1,0,0,0,342,343,5,38,0,0,343,55,1,0,0,0,344,345,5,37,0,0,345,
  	348,5,2,0,0,346,349,3,50,25,0,347,349,3,52,26,0,348,346,1,0,0,0,348,347,
  	1,0,0,0,349,350,1,0,0,0,350,353,5,2,0,0,351,354,3,58,29,0,352,354,3,8,
  	4,0,353,351,1,0,0,0,353,352,1,0,0,0,354,57,1,0,0,0,355,363,3,60,30,0,
  	356,363,3,62,31,0,357,363,3,64,32,0,358,363,3,66,33,0,359,363,3,68,34,
  	0,360,363,3,70,35,0,361,363,3,72,36,0,362,355,1,0,0,0,362,356,1,0,0,0,
  	362,357,1,0,0,0,362,358,1,0,0,0,362,359,1,0,0,0,362,360,1,0,0,0,362,361,
  	1,0,0,0,363,59,1,0,0,0,364,365,5,30,0,0,365,368,5,2,0,0,366,367,5,39,
  	0,0,367,369,5,2,0,0,368,366,1,0,0,0,368,369,1,0,0,0,369,370,1,0,0,0,370,
  	371,3,42,21,0,371,61,1,0,0,0,372,374,5,31,0,0,373,375,3,74,37,0,374,373,
  	1,0,0,0,375,376,1,0,0,0,376,374,1,0,0,0,376,377,1,0,0,0,377,63,1,0,0,
  	0,378,380,5,32,0,0,379,381,3,74,37,0,380,379,1,0,0,0,381,382,1,0,0,0,
  	382,380,1,0,0,0,382,383,1,0,0,0,383,65,1,0,0,0,384,386,5,33,0,0,385,387,
  	3,74,37,0,386,385,1,0,0,0,387,388,1,0,0,0,388,386,1,0,0,0,388,389,1,0,
  	0,0,389,67,1,0,0,0,390,391,5,34,0,0,391,392,5,2,0,0,392,393,3,76,38,0,
  	393,69,1,0,0,0,394,401,5,35,0,0,395,396,5,2,0,0,396,399,3,42,21,0,397,
  	398,5,2,0,0,398,400,3,42,21,0,399,397,1,0,0,0,399,400,1,0,0,0,400,402,
  	1,0,0,0,401,395,1,0,0,0,401,402,1,0,0,0,402,71,1,0,0,0,403,404,5,36,0,
  	0,404,405,5,2,0,0,405,408,3,42,21,0,406,407,5,2,0,0,407,409,3,42,21,0,
  	408,406,1,0,0,0,408,409,1,0,0,0,409,73,1,0,0,0,410,411,5,2,0,0,411,413,
  	3,42,21,0,412,414,5,19,0,0,413,412,1,0,0,0,413,414,1,0,0,0,414,75,1,0,
  	0,0,415,419,5,50,0,0,416,418,3,78,39,0,417,416,1,0,0,0,418,421,1,0,0,
  	0,419,417,1,0,0,0,419,420,1,0,0,0,420,422,1,0,0,0,421,419,1,0,0,0,422,
  	423,5,50,0,0,423,77,1,0,0,0,424,425,7,5,0,0,425,79,1,0,0,0,55,83,87,93,
  	96,101,107,116,119,123,126,130,133,137,140,144,147,151,154,158,161,164,
  	166,169,173,194,205,214,222,227,231,234,242,245,253,263,273,276,298,306,
  	313,321,329,336,348,353,362,368,376,382,388,399,401,408,413,419
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

std::vector<tree::TerminalNode *> asm6502Parser::ProgramContext::NEWLINE() {
  return getTokens(asm6502Parser::NEWLINE);
}

tree::TerminalNode* asm6502Parser::ProgramContext::NEWLINE(size_t i) {
  return getToken(asm6502Parser::NEWLINE, i);
}

std::vector<tree::TerminalNode *> asm6502Parser::ProgramContext::WHITESPACE() {
  return getTokens(asm6502Parser::WHITESPACE);
}

tree::TerminalNode* asm6502Parser::ProgramContext::WHITESPACE(size_t i) {
  return getToken(asm6502Parser::WHITESPACE, i);
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
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(83);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 0, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(80);
        match(asm6502Parser::NEWLINE); 
      }
      setState(85);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 0, _ctx);
    }

    setState(87);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == asm6502Parser::WHITESPACE) {
      setState(86);
      match(asm6502Parser::WHITESPACE);
    }
    setState(89);
    line();
    setState(101);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(91); 
        _errHandler->sync(this);
        alt = 1;
        do {
          switch (alt) {
            case 1: {
                  setState(90);
                  match(asm6502Parser::NEWLINE);
                  break;
                }

          default:
            throw NoViableAltException(this);
          }
          setState(93); 
          _errHandler->sync(this);
          alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx);
        } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER);
        setState(96);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == asm6502Parser::WHITESPACE) {
          setState(95);
          match(asm6502Parser::WHITESPACE);
        }
        setState(98);
        line(); 
      }
      setState(103);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx);
    }
    setState(107);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == asm6502Parser::NEWLINE) {
      setState(104);
      match(asm6502Parser::NEWLINE);
      setState(109);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(110);
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
    setState(166);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 21, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(112);
      label();
      setState(113);
      match(asm6502Parser::WHITESPACE);
      setState(114);
      instruction();
      setState(116);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == asm6502Parser::WHITESPACE) {
        setState(115);
        match(asm6502Parser::WHITESPACE);
      }
      setState(119);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == asm6502Parser::COMMENT) {
        setState(118);
        comment();
      }
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(121);
      label();
      setState(123);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == asm6502Parser::WHITESPACE) {
        setState(122);
        match(asm6502Parser::WHITESPACE);
      }
      setState(126);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == asm6502Parser::COMMENT) {
        setState(125);
        comment();
      }
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(128);
      assign();
      setState(130);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == asm6502Parser::WHITESPACE) {
        setState(129);
        match(asm6502Parser::WHITESPACE);
      }
      setState(133);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == asm6502Parser::COMMENT) {
        setState(132);
        comment();
      }
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(135);
      instruction();
      setState(137);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == asm6502Parser::WHITESPACE) {
        setState(136);
        match(asm6502Parser::WHITESPACE);
      }
      setState(140);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == asm6502Parser::COMMENT) {
        setState(139);
        comment();
      }
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(142);
      assign();
      setState(144);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == asm6502Parser::WHITESPACE) {
        setState(143);
        match(asm6502Parser::WHITESPACE);
      }
      setState(147);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == asm6502Parser::COMMENT) {
        setState(146);
        comment();
      }
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(149);
      directive();
      setState(151);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == asm6502Parser::WHITESPACE) {
        setState(150);
        match(asm6502Parser::WHITESPACE);
      }
      setState(154);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == asm6502Parser::COMMENT) {
        setState(153);
        comment();
      }
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(156);
      repeat_directive();
      setState(158);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == asm6502Parser::WHITESPACE) {
        setState(157);
        match(asm6502Parser::WHITESPACE);
      }
      setState(161);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == asm6502Parser::COMMENT) {
        setState(160);
        comment();
      }
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(164);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == asm6502Parser::COMMENT) {
        setState(163);
        comment();
      }
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
    setState(169);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == asm6502Parser::AT) {
      setState(168);
      match(asm6502Parser::AT);
    }
    setState(171);
    match(asm6502Parser::SYMBOL);
    setState(173);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == asm6502Parser::COLON) {
      setState(172);
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
    setState(175);
    match(asm6502Parser::SYMBOL);
    setState(176);
    match(asm6502Parser::WHITESPACE);
    setState(177);
    match(asm6502Parser::EQU);
    setState(178);
    match(asm6502Parser::WHITESPACE);
    setState(179);
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
    setState(194);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 24, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(181);
      nop();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(182);
      implicit();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(183);
      acc();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(184);
      immediate();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(185);
      zero_page();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(186);
      x_index();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(187);
      y_index();
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(188);
      x_indirect();
      break;
    }

    case 9: {
      enterOuterAlt(_localctx, 9);
      setState(189);
      indirect_y();
      break;
    }

    case 10: {
      enterOuterAlt(_localctx, 10);
      setState(190);
      absolute();
      break;
    }

    case 11: {
      enterOuterAlt(_localctx, 11);
      setState(191);
      relative();
      break;
    }

    case 12: {
      enterOuterAlt(_localctx, 12);
      setState(192);
      jump();
      break;
    }

    case 13: {
      enterOuterAlt(_localctx, 13);
      setState(193);
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
    setState(196);
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
    setState(198);
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
    setState(200);
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
    setState(202);
    shift();
    setState(205);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 25, _ctx)) {
    case 1: {
      setState(203);
      match(asm6502Parser::WHITESPACE);
      setState(204);
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
    setState(207);
    mnemonic();
    setState(208);
    match(asm6502Parser::WHITESPACE);
    setState(209);
    match(asm6502Parser::HASH);
    setState(210);
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
    setState(227);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 28, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(214);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case asm6502Parser::SHIFT: {
          setState(212);
          shift();
          break;
        }

        case asm6502Parser::MNEMONIC: {
          setState(213);
          mnemonic();
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      setState(216);
      match(asm6502Parser::FORCED_BYTE);
      setState(217);
      match(asm6502Parser::WHITESPACE);
      setState(218);
      expression(0);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(222);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case asm6502Parser::SHIFT: {
          setState(220);
          shift();
          break;
        }

        case asm6502Parser::MNEMONIC: {
          setState(221);
          mnemonic();
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      setState(224);
      match(asm6502Parser::WHITESPACE);
      setState(225);
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
    setState(231);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case asm6502Parser::SHIFT: {
        setState(229);
        shift();
        break;
      }

      case asm6502Parser::MNEMONIC: {
        setState(230);
        mnemonic();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(234);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == asm6502Parser::FORCED_BYTE

    || _la == asm6502Parser::FORCED_WORD) {
      setState(233);
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
    setState(236);
    match(asm6502Parser::WHITESPACE);
    setState(237);
    expression(0);
    setState(238);
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
    setState(242);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case asm6502Parser::SHIFT: {
        setState(240);
        shift();
        break;
      }

      case asm6502Parser::MNEMONIC: {
        setState(241);
        mnemonic();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(245);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == asm6502Parser::FORCED_BYTE

    || _la == asm6502Parser::FORCED_WORD) {
      setState(244);
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
    setState(247);
    match(asm6502Parser::WHITESPACE);
    setState(248);
    expression(0);
    setState(249);
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
    setState(253);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case asm6502Parser::SHIFT: {
        setState(251);
        shift();
        break;
      }

      case asm6502Parser::MNEMONIC: {
        setState(252);
        mnemonic();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(255);
    match(asm6502Parser::WHITESPACE);
    setState(256);
    match(asm6502Parser::LPAREN);
    setState(257);
    expression(0);
    setState(258);
    match(asm6502Parser::X_INDEX);
    setState(259);
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
    setState(263);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case asm6502Parser::SHIFT: {
        setState(261);
        shift();
        break;
      }

      case asm6502Parser::MNEMONIC: {
        setState(262);
        mnemonic();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(265);
    match(asm6502Parser::WHITESPACE);
    setState(266);
    match(asm6502Parser::LPAREN);
    setState(267);
    expression(0);
    setState(268);
    match(asm6502Parser::RPAREN);
    setState(269);
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
    setState(273);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case asm6502Parser::SHIFT: {
        setState(271);
        shift();
        break;
      }

      case asm6502Parser::MNEMONIC: {
        setState(272);
        mnemonic();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(276);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == asm6502Parser::FORCED_WORD) {
      setState(275);
      match(asm6502Parser::FORCED_WORD);
    }
    setState(278);
    match(asm6502Parser::WHITESPACE);
    setState(279);
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
    setState(281);
    match(asm6502Parser::BRANCH);
    setState(282);
    match(asm6502Parser::WHITESPACE);
    setState(283);
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
    setState(285);
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
    setState(287);
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
    setState(298);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 37, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(289);
      match(asm6502Parser::JUMP);
      setState(290);
      match(asm6502Parser::WHITESPACE);
      setState(291);
      expression(0);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(292);
      match(asm6502Parser::JUMP);
      setState(293);
      match(asm6502Parser::WHITESPACE);
      setState(294);
      match(asm6502Parser::LPAREN);
      setState(295);
      expression(0);
      setState(296);
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
    setState(300);
    match(asm6502Parser::JSR);
    setState(301);
    match(asm6502Parser::WHITESPACE);
    setState(302);
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
    setState(313);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 39, _ctx)) {
    case 1: {
      setState(306);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << asm6502Parser::PLUS)
        | (1ULL << asm6502Parser::MINUS)
        | (1ULL << asm6502Parser::LOW_BYTE_VALUE)
        | (1ULL << asm6502Parser::HIGH_BYTE_VALUE))) != 0)) {
        setState(305);
        unary_op();
      }
      setState(308);
      match(asm6502Parser::LBRACKET);
      setState(309);
      expression(0);
      setState(310);
      match(asm6502Parser::RBRACKET);
      break;
    }

    case 2: {
      setState(312);
      atom();
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(321);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 40, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<ExpressionContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleExpression);
        setState(315);

        if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
        setState(316);
        binary_op();
        setState(317);
        expression(4); 
      }
      setState(323);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 40, _ctx);
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
    setState(324);
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
    setState(326);
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
    setState(329);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << asm6502Parser::PLUS)
      | (1ULL << asm6502Parser::MINUS)
      | (1ULL << asm6502Parser::LOW_BYTE_VALUE)
      | (1ULL << asm6502Parser::HIGH_BYTE_VALUE))) != 0)) {
      setState(328);
      unary_op();
    }
    setState(336);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case asm6502Parser::OCTAL_BYTE:
      case asm6502Parser::HEX_BYTE:
      case asm6502Parser::DECIMAL_BYTE:
      case asm6502Parser::BINARY_BYTE: {
        setState(331);
        byte();
        break;
      }

      case asm6502Parser::OCTAL_NUMBER:
      case asm6502Parser::HEX_NUMBER:
      case asm6502Parser::DECIMAL_NUMBER:
      case asm6502Parser::BINARY_NUMBER: {
        setState(332);
        multibyte();
        break;
      }

      case asm6502Parser::CHARACTER: {
        setState(333);
        character();
        break;
      }

      case asm6502Parser::SYMBOL: {
        setState(334);
        match(asm6502Parser::SYMBOL);
        break;
      }

      case asm6502Parser::STAR: {
        setState(335);
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
    setState(338);
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
    setState(340);
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
    setState(342);
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
    setState(344);
    match(asm6502Parser::DREPEAT);
    setState(345);
    match(asm6502Parser::WHITESPACE);
    setState(348);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case asm6502Parser::OCTAL_BYTE:
      case asm6502Parser::HEX_BYTE:
      case asm6502Parser::DECIMAL_BYTE:
      case asm6502Parser::BINARY_BYTE: {
        setState(346);
        byte();
        break;
      }

      case asm6502Parser::OCTAL_NUMBER:
      case asm6502Parser::HEX_NUMBER:
      case asm6502Parser::DECIMAL_NUMBER:
      case asm6502Parser::BINARY_NUMBER: {
        setState(347);
        multibyte();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(350);
    match(asm6502Parser::WHITESPACE);
    setState(353);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case asm6502Parser::DORG:
      case asm6502Parser::DBYTE:
      case asm6502Parser::DDBYTE:
      case asm6502Parser::DWORD:
      case asm6502Parser::DTEXT:
      case asm6502Parser::DALIGN:
      case asm6502Parser::DFILL: {
        setState(351);
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
        setState(352);
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
    setState(362);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case asm6502Parser::DORG: {
        enterOuterAlt(_localctx, 1);
        setState(355);
        org();
        break;
      }

      case asm6502Parser::DBYTE: {
        enterOuterAlt(_localctx, 2);
        setState(356);
        byte_directive();
        break;
      }

      case asm6502Parser::DDBYTE: {
        enterOuterAlt(_localctx, 3);
        setState(357);
        dbyte_directive();
        break;
      }

      case asm6502Parser::DWORD: {
        enterOuterAlt(_localctx, 4);
        setState(358);
        word_directive();
        break;
      }

      case asm6502Parser::DTEXT: {
        enterOuterAlt(_localctx, 5);
        setState(359);
        text_directive();
        break;
      }

      case asm6502Parser::DALIGN: {
        enterOuterAlt(_localctx, 6);
        setState(360);
        align_directive();
        break;
      }

      case asm6502Parser::DFILL: {
        enterOuterAlt(_localctx, 7);
        setState(361);
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
    setState(364);
    match(asm6502Parser::DORG);
    setState(365);
    match(asm6502Parser::WHITESPACE);
    setState(368);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == asm6502Parser::EQU) {
      setState(366);
      match(asm6502Parser::EQU);
      setState(367);
      match(asm6502Parser::WHITESPACE);
    }
    setState(370);
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

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(372);
    match(asm6502Parser::DBYTE);
    setState(374); 
    _errHandler->sync(this);
    alt = 1;
    do {
      switch (alt) {
        case 1: {
              setState(373);
              byte_directive_value();
              break;
            }

      default:
        throw NoViableAltException(this);
      }
      setState(376); 
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 47, _ctx);
    } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER);
   
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

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(378);
    match(asm6502Parser::DDBYTE);
    setState(380); 
    _errHandler->sync(this);
    alt = 1;
    do {
      switch (alt) {
        case 1: {
              setState(379);
              byte_directive_value();
              break;
            }

      default:
        throw NoViableAltException(this);
      }
      setState(382); 
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 48, _ctx);
    } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER);
   
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

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(384);
    match(asm6502Parser::DWORD);
    setState(386); 
    _errHandler->sync(this);
    alt = 1;
    do {
      switch (alt) {
        case 1: {
              setState(385);
              byte_directive_value();
              break;
            }

      default:
        throw NoViableAltException(this);
      }
      setState(388); 
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 49, _ctx);
    } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER);
   
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
    setState(390);
    match(asm6502Parser::DTEXT);
    setState(391);
    match(asm6502Parser::WHITESPACE);
    setState(392);
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

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(394);
    match(asm6502Parser::DALIGN);
    setState(401);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 51, _ctx)) {
    case 1: {
      setState(395);
      match(asm6502Parser::WHITESPACE);
      setState(396);
      expression(0);
      setState(399);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 50, _ctx)) {
      case 1: {
        setState(397);
        match(asm6502Parser::WHITESPACE);
        setState(398);
        expression(0);
        break;
      }

      default:
        break;
      }
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

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(403);
    match(asm6502Parser::DFILL);
    setState(404);
    match(asm6502Parser::WHITESPACE);
    setState(405);
    expression(0);
    setState(408);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 52, _ctx)) {
    case 1: {
      setState(406);
      match(asm6502Parser::WHITESPACE);
      setState(407);
      expression(0);
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
    setState(410);
    match(asm6502Parser::WHITESPACE);
    setState(411);
    expression(0);
    setState(413);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == asm6502Parser::COMMA) {
      setState(412);
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
    setState(415);
    match(asm6502Parser::DQUOTE);
    setState(419);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == asm6502Parser::TEXT

    || _la == asm6502Parser::ESCAPE_SEQUENCE) {
      setState(416);
      stringContents();
      setState(421);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(422);
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
    setState(424);
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
