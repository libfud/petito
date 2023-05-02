
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
      "multibyte", "character", "directive", "org", "byte_directive", "dbyte_directive", 
      "word_directive", "text_directive", "byte_directive_value", "string", 
      "stringContents", "align_directive", "fill_directive", "repeat_directive"
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
  	4,1,52,444,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
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
  	1,174,8,1,1,1,1,1,1,1,3,1,179,8,1,1,1,3,1,182,8,1,1,1,3,1,185,8,1,1,2,
  	3,2,188,8,2,1,2,1,2,3,2,192,8,2,1,3,1,3,1,3,1,3,1,3,1,3,1,4,1,4,1,4,1,
  	4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,3,4,213,8,4,1,5,1,5,1,6,1,6,1,7,
  	1,7,1,8,1,8,1,8,3,8,224,8,8,1,9,1,9,1,9,1,9,1,9,1,10,1,10,3,10,233,8,
  	10,1,10,1,10,1,10,1,10,1,10,1,10,3,10,241,8,10,1,10,1,10,1,10,3,10,246,
  	8,10,3,10,248,8,10,1,11,1,11,3,11,252,8,11,1,11,3,11,255,8,11,1,11,1,
  	11,1,11,1,11,1,12,1,12,3,12,263,8,12,1,12,3,12,266,8,12,1,12,1,12,1,12,
  	1,12,1,13,1,13,1,13,3,13,275,8,13,1,13,1,13,1,13,1,13,1,13,1,14,1,14,
  	1,14,3,14,285,8,14,1,14,1,14,1,14,1,14,1,14,1,15,1,15,3,15,294,8,15,1,
  	15,3,15,297,8,15,1,15,1,15,1,15,1,16,1,16,1,16,1,16,1,17,1,17,1,18,1,
  	18,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,3,19,319,8,19,1,20,1,
  	20,1,20,1,20,1,21,1,21,3,21,327,8,21,1,21,1,21,1,21,1,21,1,21,3,21,334,
  	8,21,1,21,1,21,1,21,1,21,5,21,340,8,21,10,21,12,21,343,9,21,1,22,1,22,
  	1,23,1,23,1,24,3,24,350,8,24,1,24,1,24,1,24,1,24,1,24,3,24,357,8,24,1,
  	25,1,25,1,26,1,26,1,27,1,27,1,28,1,28,1,28,1,28,1,28,1,28,1,28,1,28,3,
  	28,373,8,28,1,29,1,29,1,29,1,29,3,29,379,8,29,1,29,1,29,1,30,1,30,4,30,
  	385,8,30,11,30,12,30,386,1,31,1,31,4,31,391,8,31,11,31,12,31,392,1,32,
  	1,32,4,32,397,8,32,11,32,12,32,398,1,33,1,33,1,33,1,33,1,34,1,34,1,34,
  	3,34,408,8,34,1,35,1,35,5,35,412,8,35,10,35,12,35,415,9,35,1,35,1,35,
  	1,36,1,36,1,37,1,37,1,37,3,37,424,8,37,1,38,1,38,1,38,1,38,1,38,3,38,
  	431,8,38,1,39,1,39,1,39,1,39,3,39,437,8,39,1,39,1,39,1,39,3,39,442,8,
  	39,1,39,0,1,42,40,0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,
  	38,40,42,44,46,48,50,52,54,56,58,60,62,64,66,68,70,72,74,76,78,0,6,1,
  	0,17,18,1,0,4,7,2,0,4,5,8,9,4,0,22,22,24,24,26,26,28,28,4,0,23,23,25,
  	25,27,27,29,29,1,0,51,52,486,0,81,1,0,0,0,2,184,1,0,0,0,4,187,1,0,0,0,
  	6,193,1,0,0,0,8,212,1,0,0,0,10,214,1,0,0,0,12,216,1,0,0,0,14,218,1,0,
  	0,0,16,220,1,0,0,0,18,225,1,0,0,0,20,247,1,0,0,0,22,251,1,0,0,0,24,262,
  	1,0,0,0,26,271,1,0,0,0,28,281,1,0,0,0,30,293,1,0,0,0,32,301,1,0,0,0,34,
  	305,1,0,0,0,36,307,1,0,0,0,38,318,1,0,0,0,40,320,1,0,0,0,42,333,1,0,0,
  	0,44,344,1,0,0,0,46,346,1,0,0,0,48,349,1,0,0,0,50,358,1,0,0,0,52,360,
  	1,0,0,0,54,362,1,0,0,0,56,372,1,0,0,0,58,374,1,0,0,0,60,382,1,0,0,0,62,
  	388,1,0,0,0,64,394,1,0,0,0,66,400,1,0,0,0,68,404,1,0,0,0,70,409,1,0,0,
  	0,72,418,1,0,0,0,74,420,1,0,0,0,76,425,1,0,0,0,78,432,1,0,0,0,80,82,3,
  	2,1,0,81,80,1,0,0,0,82,83,1,0,0,0,83,81,1,0,0,0,83,84,1,0,0,0,84,85,1,
  	0,0,0,85,86,5,0,0,1,86,1,1,0,0,0,87,89,5,2,0,0,88,87,1,0,0,0,88,89,1,
  	0,0,0,89,90,1,0,0,0,90,91,3,4,2,0,91,92,5,2,0,0,92,94,3,8,4,0,93,95,5,
  	2,0,0,94,93,1,0,0,0,94,95,1,0,0,0,95,96,1,0,0,0,96,97,3,10,5,0,97,98,
  	5,3,0,0,98,185,1,0,0,0,99,101,5,2,0,0,100,99,1,0,0,0,100,101,1,0,0,0,
  	101,102,1,0,0,0,102,103,3,4,2,0,103,104,5,2,0,0,104,106,3,8,4,0,105,107,
  	5,2,0,0,106,105,1,0,0,0,106,107,1,0,0,0,107,108,1,0,0,0,108,109,5,3,0,
  	0,109,185,1,0,0,0,110,112,5,2,0,0,111,110,1,0,0,0,111,112,1,0,0,0,112,
  	113,1,0,0,0,113,115,3,4,2,0,114,116,5,2,0,0,115,114,1,0,0,0,115,116,1,
  	0,0,0,116,117,1,0,0,0,117,118,3,10,5,0,118,119,5,3,0,0,119,185,1,0,0,
  	0,120,122,5,2,0,0,121,120,1,0,0,0,121,122,1,0,0,0,122,123,1,0,0,0,123,
  	125,3,4,2,0,124,126,5,2,0,0,125,124,1,0,0,0,125,126,1,0,0,0,126,127,1,
  	0,0,0,127,128,5,3,0,0,128,185,1,0,0,0,129,131,5,2,0,0,130,129,1,0,0,0,
  	130,131,1,0,0,0,131,135,1,0,0,0,132,133,3,4,2,0,133,134,5,2,0,0,134,136,
  	1,0,0,0,135,132,1,0,0,0,135,136,1,0,0,0,136,137,1,0,0,0,137,138,3,6,3,
  	0,138,139,5,3,0,0,139,185,1,0,0,0,140,142,5,2,0,0,141,140,1,0,0,0,141,
  	142,1,0,0,0,142,143,1,0,0,0,143,145,3,8,4,0,144,146,5,2,0,0,145,144,1,
  	0,0,0,145,146,1,0,0,0,146,147,1,0,0,0,147,148,3,10,5,0,148,149,5,3,0,
  	0,149,185,1,0,0,0,150,152,5,2,0,0,151,150,1,0,0,0,151,152,1,0,0,0,152,
  	153,1,0,0,0,153,155,3,8,4,0,154,156,5,2,0,0,155,154,1,0,0,0,155,156,1,
  	0,0,0,156,157,1,0,0,0,157,158,5,3,0,0,158,185,1,0,0,0,159,161,5,2,0,0,
  	160,159,1,0,0,0,160,161,1,0,0,0,161,162,1,0,0,0,162,164,3,6,3,0,163,165,
  	3,10,5,0,164,163,1,0,0,0,164,165,1,0,0,0,165,166,1,0,0,0,166,167,5,3,
  	0,0,167,185,1,0,0,0,168,170,5,2,0,0,169,168,1,0,0,0,169,170,1,0,0,0,170,
  	171,1,0,0,0,171,173,3,56,28,0,172,174,3,10,5,0,173,172,1,0,0,0,173,174,
  	1,0,0,0,174,175,1,0,0,0,175,176,5,3,0,0,176,185,1,0,0,0,177,179,5,2,0,
  	0,178,177,1,0,0,0,178,179,1,0,0,0,179,181,1,0,0,0,180,182,3,10,5,0,181,
  	180,1,0,0,0,181,182,1,0,0,0,182,183,1,0,0,0,183,185,5,3,0,0,184,88,1,
  	0,0,0,184,100,1,0,0,0,184,111,1,0,0,0,184,121,1,0,0,0,184,130,1,0,0,0,
  	184,141,1,0,0,0,184,151,1,0,0,0,184,160,1,0,0,0,184,169,1,0,0,0,184,178,
  	1,0,0,0,185,3,1,0,0,0,186,188,5,16,0,0,187,186,1,0,0,0,187,188,1,0,0,
  	0,188,189,1,0,0,0,189,191,5,49,0,0,190,192,5,15,0,0,191,190,1,0,0,0,191,
  	192,1,0,0,0,192,5,1,0,0,0,193,194,5,49,0,0,194,195,5,2,0,0,195,196,5,
  	39,0,0,196,197,5,2,0,0,197,198,3,42,21,0,198,7,1,0,0,0,199,213,3,12,6,
  	0,200,213,3,14,7,0,201,213,3,16,8,0,202,213,3,18,9,0,203,213,3,20,10,
  	0,204,213,3,22,11,0,205,213,3,24,12,0,206,213,3,26,13,0,207,213,3,28,
  	14,0,208,213,3,30,15,0,209,213,3,32,16,0,210,213,3,38,19,0,211,213,3,
  	40,20,0,212,199,1,0,0,0,212,200,1,0,0,0,212,201,1,0,0,0,212,202,1,0,0,
  	0,212,203,1,0,0,0,212,204,1,0,0,0,212,205,1,0,0,0,212,206,1,0,0,0,212,
  	207,1,0,0,0,212,208,1,0,0,0,212,209,1,0,0,0,212,210,1,0,0,0,212,211,1,
  	0,0,0,213,9,1,0,0,0,214,215,5,1,0,0,215,11,1,0,0,0,216,217,5,40,0,0,217,
  	13,1,0,0,0,218,219,5,41,0,0,219,15,1,0,0,0,220,223,3,36,18,0,221,222,
  	5,2,0,0,222,224,5,48,0,0,223,221,1,0,0,0,223,224,1,0,0,0,224,17,1,0,0,
  	0,225,226,3,34,17,0,226,227,5,2,0,0,227,228,5,14,0,0,228,229,3,42,21,
  	0,229,19,1,0,0,0,230,233,3,36,18,0,231,233,3,34,17,0,232,230,1,0,0,0,
  	232,231,1,0,0,0,233,234,1,0,0,0,234,235,5,17,0,0,235,236,5,2,0,0,236,
  	237,3,42,21,0,237,248,1,0,0,0,238,241,3,36,18,0,239,241,3,34,17,0,240,
  	238,1,0,0,0,240,239,1,0,0,0,241,242,1,0,0,0,242,245,5,2,0,0,243,246,3,
  	50,25,0,244,246,3,54,27,0,245,243,1,0,0,0,245,244,1,0,0,0,246,248,1,0,
  	0,0,247,232,1,0,0,0,247,240,1,0,0,0,248,21,1,0,0,0,249,252,3,36,18,0,
  	250,252,3,34,17,0,251,249,1,0,0,0,251,250,1,0,0,0,252,254,1,0,0,0,253,
  	255,7,0,0,0,254,253,1,0,0,0,254,255,1,0,0,0,255,256,1,0,0,0,256,257,5,
  	2,0,0,257,258,3,42,21,0,258,259,5,20,0,0,259,23,1,0,0,0,260,263,3,36,
  	18,0,261,263,3,34,17,0,262,260,1,0,0,0,262,261,1,0,0,0,263,265,1,0,0,
  	0,264,266,7,0,0,0,265,264,1,0,0,0,265,266,1,0,0,0,266,267,1,0,0,0,267,
  	268,5,2,0,0,268,269,3,42,21,0,269,270,5,21,0,0,270,25,1,0,0,0,271,274,
  	5,12,0,0,272,275,3,36,18,0,273,275,3,34,17,0,274,272,1,0,0,0,274,273,
  	1,0,0,0,275,276,1,0,0,0,276,277,5,2,0,0,277,278,3,42,21,0,278,279,5,20,
  	0,0,279,280,5,13,0,0,280,27,1,0,0,0,281,284,5,12,0,0,282,285,3,36,18,
  	0,283,285,3,34,17,0,284,282,1,0,0,0,284,283,1,0,0,0,285,286,1,0,0,0,286,
  	287,5,2,0,0,287,288,3,42,21,0,288,289,5,13,0,0,289,290,5,21,0,0,290,29,
  	1,0,0,0,291,294,3,36,18,0,292,294,3,34,17,0,293,291,1,0,0,0,293,292,1,
  	0,0,0,294,296,1,0,0,0,295,297,5,18,0,0,296,295,1,0,0,0,296,297,1,0,0,
  	0,297,298,1,0,0,0,298,299,5,2,0,0,299,300,3,42,21,0,300,31,1,0,0,0,301,
  	302,5,42,0,0,302,303,5,2,0,0,303,304,3,42,21,0,304,33,1,0,0,0,305,306,
  	5,46,0,0,306,35,1,0,0,0,307,308,5,43,0,0,308,37,1,0,0,0,309,310,5,44,
  	0,0,310,311,5,2,0,0,311,319,3,42,21,0,312,313,5,44,0,0,313,314,5,2,0,
  	0,314,315,5,12,0,0,315,316,3,42,21,0,316,317,5,13,0,0,317,319,1,0,0,0,
  	318,309,1,0,0,0,318,312,1,0,0,0,319,39,1,0,0,0,320,321,5,45,0,0,321,322,
  	5,2,0,0,322,323,3,42,21,0,323,41,1,0,0,0,324,326,6,21,-1,0,325,327,3,
  	46,23,0,326,325,1,0,0,0,326,327,1,0,0,0,327,328,1,0,0,0,328,329,5,10,
  	0,0,329,330,3,42,21,0,330,331,5,11,0,0,331,334,1,0,0,0,332,334,3,48,24,
  	0,333,324,1,0,0,0,333,332,1,0,0,0,334,341,1,0,0,0,335,336,10,3,0,0,336,
  	337,3,44,22,0,337,338,3,42,21,4,338,340,1,0,0,0,339,335,1,0,0,0,340,343,
  	1,0,0,0,341,339,1,0,0,0,341,342,1,0,0,0,342,43,1,0,0,0,343,341,1,0,0,
  	0,344,345,7,1,0,0,345,45,1,0,0,0,346,347,7,2,0,0,347,47,1,0,0,0,348,350,
  	3,46,23,0,349,348,1,0,0,0,349,350,1,0,0,0,350,356,1,0,0,0,351,357,3,50,
  	25,0,352,357,3,52,26,0,353,357,3,54,27,0,354,357,5,49,0,0,355,357,5,6,
  	0,0,356,351,1,0,0,0,356,352,1,0,0,0,356,353,1,0,0,0,356,354,1,0,0,0,356,
  	355,1,0,0,0,357,49,1,0,0,0,358,359,7,3,0,0,359,51,1,0,0,0,360,361,7,4,
  	0,0,361,53,1,0,0,0,362,363,5,38,0,0,363,55,1,0,0,0,364,373,3,58,29,0,
  	365,373,3,60,30,0,366,373,3,62,31,0,367,373,3,64,32,0,368,373,3,66,33,
  	0,369,373,3,74,37,0,370,373,3,76,38,0,371,373,3,78,39,0,372,364,1,0,0,
  	0,372,365,1,0,0,0,372,366,1,0,0,0,372,367,1,0,0,0,372,368,1,0,0,0,372,
  	369,1,0,0,0,372,370,1,0,0,0,372,371,1,0,0,0,373,57,1,0,0,0,374,375,5,
  	30,0,0,375,378,5,2,0,0,376,377,5,39,0,0,377,379,5,2,0,0,378,376,1,0,0,
  	0,378,379,1,0,0,0,379,380,1,0,0,0,380,381,3,42,21,0,381,59,1,0,0,0,382,
  	384,5,31,0,0,383,385,3,68,34,0,384,383,1,0,0,0,385,386,1,0,0,0,386,384,
  	1,0,0,0,386,387,1,0,0,0,387,61,1,0,0,0,388,390,5,32,0,0,389,391,3,68,
  	34,0,390,389,1,0,0,0,391,392,1,0,0,0,392,390,1,0,0,0,392,393,1,0,0,0,
  	393,63,1,0,0,0,394,396,5,33,0,0,395,397,3,68,34,0,396,395,1,0,0,0,397,
  	398,1,0,0,0,398,396,1,0,0,0,398,399,1,0,0,0,399,65,1,0,0,0,400,401,5,
  	34,0,0,401,402,5,2,0,0,402,403,3,70,35,0,403,67,1,0,0,0,404,405,5,2,0,
  	0,405,407,3,42,21,0,406,408,5,19,0,0,407,406,1,0,0,0,407,408,1,0,0,0,
  	408,69,1,0,0,0,409,413,5,50,0,0,410,412,3,72,36,0,411,410,1,0,0,0,412,
  	415,1,0,0,0,413,411,1,0,0,0,413,414,1,0,0,0,414,416,1,0,0,0,415,413,1,
  	0,0,0,416,417,5,50,0,0,417,71,1,0,0,0,418,419,7,5,0,0,419,73,1,0,0,0,
  	420,423,5,35,0,0,421,422,5,2,0,0,422,424,3,42,21,0,423,421,1,0,0,0,423,
  	424,1,0,0,0,424,75,1,0,0,0,425,426,5,36,0,0,426,427,5,2,0,0,427,430,3,
  	42,21,0,428,429,5,2,0,0,429,431,3,42,21,0,430,428,1,0,0,0,430,431,1,0,
  	0,0,431,77,1,0,0,0,432,433,5,36,0,0,433,436,5,2,0,0,434,437,3,50,25,0,
  	435,437,3,52,26,0,436,434,1,0,0,0,436,435,1,0,0,0,437,438,1,0,0,0,438,
  	441,5,2,0,0,439,442,3,56,28,0,440,442,3,8,4,0,441,439,1,0,0,0,441,440,
  	1,0,0,0,442,79,1,0,0,0,55,83,88,94,100,106,111,115,121,125,130,135,141,
  	145,151,155,160,164,169,173,178,181,184,187,191,212,223,232,240,245,247,
  	251,254,262,265,274,284,293,296,318,326,333,341,349,356,372,378,386,392,
  	398,407,413,423,430,436,441
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
      | (1ULL << asm6502Parser::LPAREN)
      | (1ULL << asm6502Parser::AT)
      | (1ULL << asm6502Parser::DORG)
      | (1ULL << asm6502Parser::DBYTE)
      | (1ULL << asm6502Parser::DDBYTE)
      | (1ULL << asm6502Parser::DWORD)
      | (1ULL << asm6502Parser::DTEXT)
      | (1ULL << asm6502Parser::DALIGN)
      | (1ULL << asm6502Parser::DFILL)
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
    setState(184);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 21, _ctx)) {
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
      setState(181);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == asm6502Parser::COMMENT) {
        setState(180);
        comment();
      }
      setState(183);
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
    setState(187);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == asm6502Parser::AT) {
      setState(186);
      match(asm6502Parser::AT);
    }
    setState(189);
    match(asm6502Parser::SYMBOL);
    setState(191);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == asm6502Parser::COLON) {
      setState(190);
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
    setState(193);
    match(asm6502Parser::SYMBOL);
    setState(194);
    match(asm6502Parser::WHITESPACE);
    setState(195);
    match(asm6502Parser::EQU);
    setState(196);
    match(asm6502Parser::WHITESPACE);
    setState(197);
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
    setState(212);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 24, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(199);
      nop();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(200);
      implicit();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(201);
      acc();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(202);
      immediate();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(203);
      zero_page();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(204);
      x_index();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(205);
      y_index();
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(206);
      x_indirect();
      break;
    }

    case 9: {
      enterOuterAlt(_localctx, 9);
      setState(207);
      indirect_y();
      break;
    }

    case 10: {
      enterOuterAlt(_localctx, 10);
      setState(208);
      absolute();
      break;
    }

    case 11: {
      enterOuterAlt(_localctx, 11);
      setState(209);
      relative();
      break;
    }

    case 12: {
      enterOuterAlt(_localctx, 12);
      setState(210);
      jump();
      break;
    }

    case 13: {
      enterOuterAlt(_localctx, 13);
      setState(211);
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
    setState(214);
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
    setState(216);
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
    setState(218);
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
    setState(220);
    shift();
    setState(223);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 25, _ctx)) {
    case 1: {
      setState(221);
      match(asm6502Parser::WHITESPACE);
      setState(222);
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
    setState(225);
    mnemonic();
    setState(226);
    match(asm6502Parser::WHITESPACE);
    setState(227);
    match(asm6502Parser::HASH);
    setState(228);
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

asm6502Parser::CharacterContext* asm6502Parser::Zero_pageContext::character() {
  return getRuleContext<asm6502Parser::CharacterContext>(0);
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
    setState(247);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 29, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(232);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case asm6502Parser::SHIFT: {
          setState(230);
          shift();
          break;
        }

        case asm6502Parser::MNEMONIC: {
          setState(231);
          mnemonic();
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      setState(234);
      match(asm6502Parser::FORCED_BYTE);
      setState(235);
      match(asm6502Parser::WHITESPACE);
      setState(236);
      expression(0);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(240);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case asm6502Parser::SHIFT: {
          setState(238);
          shift();
          break;
        }

        case asm6502Parser::MNEMONIC: {
          setState(239);
          mnemonic();
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      setState(242);
      match(asm6502Parser::WHITESPACE);
      setState(245);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case asm6502Parser::OCTAL_BYTE:
        case asm6502Parser::HEX_BYTE:
        case asm6502Parser::DECIMAL_BYTE:
        case asm6502Parser::BINARY_BYTE: {
          setState(243);
          byte();
          break;
        }

        case asm6502Parser::CHARACTER: {
          setState(244);
          character();
          break;
        }

      default:
        throw NoViableAltException(this);
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
    setState(251);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case asm6502Parser::SHIFT: {
        setState(249);
        shift();
        break;
      }

      case asm6502Parser::MNEMONIC: {
        setState(250);
        mnemonic();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(254);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == asm6502Parser::FORCED_BYTE

    || _la == asm6502Parser::FORCED_WORD) {
      setState(253);
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
    setState(256);
    match(asm6502Parser::WHITESPACE);
    setState(257);
    expression(0);
    setState(258);
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
    setState(262);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case asm6502Parser::SHIFT: {
        setState(260);
        shift();
        break;
      }

      case asm6502Parser::MNEMONIC: {
        setState(261);
        mnemonic();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(265);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == asm6502Parser::FORCED_BYTE

    || _la == asm6502Parser::FORCED_WORD) {
      setState(264);
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
    setState(267);
    match(asm6502Parser::WHITESPACE);
    setState(268);
    expression(0);
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
    setState(271);
    match(asm6502Parser::LPAREN);
    setState(274);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case asm6502Parser::SHIFT: {
        setState(272);
        shift();
        break;
      }

      case asm6502Parser::MNEMONIC: {
        setState(273);
        mnemonic();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(276);
    match(asm6502Parser::WHITESPACE);
    setState(277);
    expression(0);
    setState(278);
    match(asm6502Parser::X_INDEX);
    setState(279);
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
    setState(281);
    match(asm6502Parser::LPAREN);
    setState(284);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case asm6502Parser::SHIFT: {
        setState(282);
        shift();
        break;
      }

      case asm6502Parser::MNEMONIC: {
        setState(283);
        mnemonic();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(286);
    match(asm6502Parser::WHITESPACE);
    setState(287);
    expression(0);
    setState(288);
    match(asm6502Parser::RPAREN);
    setState(289);
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
    setState(293);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case asm6502Parser::SHIFT: {
        setState(291);
        shift();
        break;
      }

      case asm6502Parser::MNEMONIC: {
        setState(292);
        mnemonic();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(296);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == asm6502Parser::FORCED_WORD) {
      setState(295);
      match(asm6502Parser::FORCED_WORD);
    }
    setState(298);
    match(asm6502Parser::WHITESPACE);
    setState(299);
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
    setState(301);
    match(asm6502Parser::BRANCH);
    setState(302);
    match(asm6502Parser::WHITESPACE);
    setState(303);
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
    setState(305);
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
    setState(307);
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
    setState(318);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 38, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(309);
      match(asm6502Parser::JUMP);
      setState(310);
      match(asm6502Parser::WHITESPACE);
      setState(311);
      expression(0);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(312);
      match(asm6502Parser::JUMP);
      setState(313);
      match(asm6502Parser::WHITESPACE);
      setState(314);
      match(asm6502Parser::LPAREN);
      setState(315);
      expression(0);
      setState(316);
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
    setState(320);
    match(asm6502Parser::JSR);
    setState(321);
    match(asm6502Parser::WHITESPACE);
    setState(322);
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
    setState(333);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 40, _ctx)) {
    case 1: {
      setState(326);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << asm6502Parser::PLUS)
        | (1ULL << asm6502Parser::MINUS)
        | (1ULL << asm6502Parser::LOW_BYTE_VALUE)
        | (1ULL << asm6502Parser::HIGH_BYTE_VALUE))) != 0)) {
        setState(325);
        unary_op();
      }
      setState(328);
      match(asm6502Parser::LBRACKET);
      setState(329);
      expression(0);
      setState(330);
      match(asm6502Parser::RBRACKET);
      break;
    }

    case 2: {
      setState(332);
      atom();
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(341);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 41, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<ExpressionContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleExpression);
        setState(335);

        if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
        setState(336);
        binary_op();
        setState(337);
        expression(4); 
      }
      setState(343);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 41, _ctx);
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
    setState(344);
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
    setState(346);
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
    setState(349);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << asm6502Parser::PLUS)
      | (1ULL << asm6502Parser::MINUS)
      | (1ULL << asm6502Parser::LOW_BYTE_VALUE)
      | (1ULL << asm6502Parser::HIGH_BYTE_VALUE))) != 0)) {
      setState(348);
      unary_op();
    }
    setState(356);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case asm6502Parser::OCTAL_BYTE:
      case asm6502Parser::HEX_BYTE:
      case asm6502Parser::DECIMAL_BYTE:
      case asm6502Parser::BINARY_BYTE: {
        setState(351);
        byte();
        break;
      }

      case asm6502Parser::OCTAL_NUMBER:
      case asm6502Parser::HEX_NUMBER:
      case asm6502Parser::DECIMAL_NUMBER:
      case asm6502Parser::BINARY_NUMBER: {
        setState(352);
        multibyte();
        break;
      }

      case asm6502Parser::CHARACTER: {
        setState(353);
        character();
        break;
      }

      case asm6502Parser::SYMBOL: {
        setState(354);
        match(asm6502Parser::SYMBOL);
        break;
      }

      case asm6502Parser::STAR: {
        setState(355);
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
    setState(358);
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
    setState(360);
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
    setState(362);
    match(asm6502Parser::CHARACTER);
   
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

asm6502Parser::Repeat_directiveContext* asm6502Parser::DirectiveContext::repeat_directive() {
  return getRuleContext<asm6502Parser::Repeat_directiveContext>(0);
}


size_t asm6502Parser::DirectiveContext::getRuleIndex() const {
  return asm6502Parser::RuleDirective;
}


asm6502Parser::DirectiveContext* asm6502Parser::directive() {
  DirectiveContext *_localctx = _tracker.createInstance<DirectiveContext>(_ctx, getState());
  enterRule(_localctx, 56, asm6502Parser::RuleDirective);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(372);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 44, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(364);
      org();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(365);
      byte_directive();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(366);
      dbyte_directive();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(367);
      word_directive();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(368);
      text_directive();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(369);
      align_directive();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(370);
      fill_directive();
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(371);
      repeat_directive();
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
  enterRule(_localctx, 58, asm6502Parser::RuleOrg);
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
    setState(374);
    match(asm6502Parser::DORG);
    setState(375);
    match(asm6502Parser::WHITESPACE);
    setState(378);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == asm6502Parser::EQU) {
      setState(376);
      match(asm6502Parser::EQU);
      setState(377);
      match(asm6502Parser::WHITESPACE);
    }
    setState(380);
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
  enterRule(_localctx, 60, asm6502Parser::RuleByte_directive);
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
    setState(382);
    match(asm6502Parser::DBYTE);
    setState(384); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(383);
      byte_directive_value();
      setState(386); 
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
  enterRule(_localctx, 62, asm6502Parser::RuleDbyte_directive);
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
    setState(388);
    match(asm6502Parser::DDBYTE);
    setState(390); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(389);
      byte_directive_value();
      setState(392); 
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
  enterRule(_localctx, 64, asm6502Parser::RuleWord_directive);
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
    setState(394);
    match(asm6502Parser::DWORD);
    setState(396); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(395);
      byte_directive_value();
      setState(398); 
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
  enterRule(_localctx, 66, asm6502Parser::RuleText_directive);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(400);
    match(asm6502Parser::DTEXT);
    setState(401);
    match(asm6502Parser::WHITESPACE);
    setState(402);
    string();
   
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
  enterRule(_localctx, 68, asm6502Parser::RuleByte_directive_value);
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
    setState(404);
    match(asm6502Parser::WHITESPACE);
    setState(405);
    expression(0);
    setState(407);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == asm6502Parser::COMMA) {
      setState(406);
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
  enterRule(_localctx, 70, asm6502Parser::RuleString);
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
    setState(409);
    match(asm6502Parser::DQUOTE);
    setState(413);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == asm6502Parser::TEXT

    || _la == asm6502Parser::ESCAPE_SEQUENCE) {
      setState(410);
      stringContents();
      setState(415);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(416);
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
  enterRule(_localctx, 72, asm6502Parser::RuleStringContents);
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
    setState(418);
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

//----------------- Align_directiveContext ------------------------------------------------------------------

asm6502Parser::Align_directiveContext::Align_directiveContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* asm6502Parser::Align_directiveContext::DALIGN() {
  return getToken(asm6502Parser::DALIGN, 0);
}

tree::TerminalNode* asm6502Parser::Align_directiveContext::WHITESPACE() {
  return getToken(asm6502Parser::WHITESPACE, 0);
}

asm6502Parser::ExpressionContext* asm6502Parser::Align_directiveContext::expression() {
  return getRuleContext<asm6502Parser::ExpressionContext>(0);
}


size_t asm6502Parser::Align_directiveContext::getRuleIndex() const {
  return asm6502Parser::RuleAlign_directive;
}


asm6502Parser::Align_directiveContext* asm6502Parser::align_directive() {
  Align_directiveContext *_localctx = _tracker.createInstance<Align_directiveContext>(_ctx, getState());
  enterRule(_localctx, 74, asm6502Parser::RuleAlign_directive);
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
    setState(420);
    match(asm6502Parser::DALIGN);
    setState(423);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == asm6502Parser::WHITESPACE) {
      setState(421);
      match(asm6502Parser::WHITESPACE);
      setState(422);
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
  enterRule(_localctx, 76, asm6502Parser::RuleFill_directive);
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
    setState(425);
    match(asm6502Parser::DFILL);
    setState(426);
    match(asm6502Parser::WHITESPACE);
    setState(427);
    expression(0);
    setState(430);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == asm6502Parser::WHITESPACE) {
      setState(428);
      match(asm6502Parser::WHITESPACE);
      setState(429);
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

//----------------- Repeat_directiveContext ------------------------------------------------------------------

asm6502Parser::Repeat_directiveContext::Repeat_directiveContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* asm6502Parser::Repeat_directiveContext::DFILL() {
  return getToken(asm6502Parser::DFILL, 0);
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
  enterRule(_localctx, 78, asm6502Parser::RuleRepeat_directive);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(432);
    match(asm6502Parser::DFILL);
    setState(433);
    match(asm6502Parser::WHITESPACE);
    setState(436);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case asm6502Parser::OCTAL_BYTE:
      case asm6502Parser::HEX_BYTE:
      case asm6502Parser::DECIMAL_BYTE:
      case asm6502Parser::BINARY_BYTE: {
        setState(434);
        byte();
        break;
      }

      case asm6502Parser::OCTAL_NUMBER:
      case asm6502Parser::HEX_NUMBER:
      case asm6502Parser::DECIMAL_NUMBER:
      case asm6502Parser::BINARY_NUMBER: {
        setState(435);
        multibyte();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(438);
    match(asm6502Parser::WHITESPACE);
    setState(441);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case asm6502Parser::DORG:
      case asm6502Parser::DBYTE:
      case asm6502Parser::DDBYTE:
      case asm6502Parser::DWORD:
      case asm6502Parser::DTEXT:
      case asm6502Parser::DALIGN:
      case asm6502Parser::DFILL: {
        setState(439);
        directive();
        break;
      }

      case asm6502Parser::LPAREN:
      case asm6502Parser::NOP:
      case asm6502Parser::IMPLIED:
      case asm6502Parser::BRANCH:
      case asm6502Parser::SHIFT:
      case asm6502Parser::JUMP:
      case asm6502Parser::JSR:
      case asm6502Parser::MNEMONIC: {
        setState(440);
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
