#ifndef OPCODE_TABLE
#define OPCODE_TABLE

#include <array>
#include <cstdint>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>

namespace mos6502 {

static constexpr uint8_t BRK_IMPL  = 0x00;
static constexpr uint8_t ORA_X_IND = 0x01;
static constexpr uint8_t JAM_X00   = 0x02;
static constexpr uint8_t SLO_X_IND = 0x03;
static constexpr uint8_t NOP_ZPG_0 = 0x04;
static constexpr uint8_t ORA_ZPG   = 0x05;
static constexpr uint8_t ASL_ZPG   = 0x06;
static constexpr uint8_t SLO_ZPG   = 0x07;
static constexpr uint8_t PHP_IMPL  = 0x08;
static constexpr uint8_t ORA_IMM   = 0x09;
static constexpr uint8_t ASL_A     = 0x0A;
static constexpr uint8_t ANC_IMM1  = 0x0B;
static constexpr uint8_t NOP_ABS_0 = 0x0C;
static constexpr uint8_t ORA_ABS   = 0x0D;
static constexpr uint8_t ASL_ABS   = 0x0E;
static constexpr uint8_t SLO_ABS   = 0x0F;

static constexpr uint8_t BPL_REL   = 0x10;
static constexpr uint8_t ORA_IND_Y = 0x11;
static constexpr uint8_t JAM_X01   = 0x12;
static constexpr uint8_t SLO_IND_Y = 0x13;
static constexpr uint8_t NOP_ZPX_1 = 0x14;
static constexpr uint8_t ORA_ZPG_X = 0x15;
static constexpr uint8_t ASL_ZPG_X = 0x16;
static constexpr uint8_t SLO_ZPG_X = 0x17;
static constexpr uint8_t CLC_IMPL  = 0x18;
static constexpr uint8_t ORA_ABS_Y = 0x19;
static constexpr uint8_t NOP_IMPL1 = 0x1A;
static constexpr uint8_t SLO_ABS_Y = 0x1B;
static constexpr uint8_t NOP_ABSX1 = 0x1C;
static constexpr uint8_t ORA_ABS_X = 0x1D;
static constexpr uint8_t ASL_ABS_X = 0x1E;
static constexpr uint8_t SLO_ABS_X = 0x1F;

static constexpr uint8_t JSR_ABS   = 0x20;
static constexpr uint8_t AND_X_IND = 0x21;
static constexpr uint8_t JAM_X02   = 0x22;
static constexpr uint8_t RLA_X_IND = 0x23;
static constexpr uint8_t BIT_ZPG   = 0x24;
static constexpr uint8_t AND_ZPG   = 0x25;
static constexpr uint8_t ROL_ZPG   = 0x26;
static constexpr uint8_t RLA_ZPG   = 0x27;
static constexpr uint8_t PLP_IMPL  = 0x28;
static constexpr uint8_t AND_IMM   = 0x29;
static constexpr uint8_t ROL_A     = 0x2A;
static constexpr uint8_t ANC_IMM2  = 0x2B;
static constexpr uint8_t BIT_ABS   = 0x2C;
static constexpr uint8_t AND_ABS   = 0x2D;
static constexpr uint8_t ROL_ABS   = 0x2E;
static constexpr uint8_t RLA_ABS   = 0x2F;

static constexpr uint8_t BMI_REL   = 0x30;
static constexpr uint8_t AND_IND_Y = 0x31;
static constexpr uint8_t JAM_X03   = 0x32;
static constexpr uint8_t RLA_IND_Y = 0x33;
static constexpr uint8_t NOP_ZPX_3 = 0x34;
static constexpr uint8_t AND_ZPG_X = 0x35;
static constexpr uint8_t ROL_ZPG_X = 0x36;
static constexpr uint8_t RLA_ZPG_X = 0x37;
static constexpr uint8_t SEC_IMPL  = 0x38;
static constexpr uint8_t AND_ABS_Y = 0x39;
static constexpr uint8_t NOP_IMPL3 = 0x3A;
static constexpr uint8_t RLA_ABS_Y = 0x3B;
static constexpr uint8_t NOP_ABSX3 = 0x3C;
static constexpr uint8_t AND_ABS_X = 0x3D;
static constexpr uint8_t ROL_ABS_X = 0x3E;
static constexpr uint8_t RLA_ABS_X = 0x3F;

static constexpr uint8_t RTI_IMPL  = 0x40;
static constexpr uint8_t EOR_X_IND = 0x41;
static constexpr uint8_t JAM_X04   = 0x42;
static constexpr uint8_t SRE_X_IND = 0x43;
static constexpr uint8_t NOP_ZPG_4 = 0x44;
static constexpr uint8_t EOR_ZPG   = 0x45;
static constexpr uint8_t LSR_ZPG   = 0x46;
static constexpr uint8_t SRE_ZPG   = 0x47;
static constexpr uint8_t PHA_IMPL  = 0x48;
static constexpr uint8_t EOR_IMM   = 0x49;
static constexpr uint8_t LSR_A     = 0x4A;
static constexpr uint8_t ALR_IMM   = 0x4B;
static constexpr uint8_t JMP_ABS   = 0x4C;
static constexpr uint8_t EOR_ABS   = 0x4D;
static constexpr uint8_t LSR_ABS   = 0x4E;
static constexpr uint8_t SRE_ABS   = 0x4F;

static constexpr uint8_t BVC_REL   = 0x50;
static constexpr uint8_t EOR_IND_Y = 0x51;
static constexpr uint8_t JAM_X05   = 0x52;
static constexpr uint8_t SRE_IND_Y = 0x53;
static constexpr uint8_t NOP_ZPG_5 = 0x54;
static constexpr uint8_t EOR_ZPG_X = 0x55;
static constexpr uint8_t LSR_ZPG_X = 0x56;
static constexpr uint8_t SRE_ZPG_X = 0x57;
static constexpr uint8_t CLI_IMPL  = 0x58;
static constexpr uint8_t EOR_ABS_Y = 0x59;
static constexpr uint8_t NOP_IMPL5 = 0x5A;
static constexpr uint8_t SRE_ABS_Y = 0x5B;
static constexpr uint8_t NOP_ABSX5 = 0x5C;
static constexpr uint8_t EOR_ABS_X = 0x5D;
static constexpr uint8_t LSR_ABS_X = 0x5E;
static constexpr uint8_t SRE_ABS_X = 0x5F;

static constexpr uint8_t RTS_IMPL  = 0x60;
static constexpr uint8_t ADC_X_IND = 0x61;
static constexpr uint8_t JAM_X06   = 0x62;
static constexpr uint8_t RRA_X_IND = 0x63;
static constexpr uint8_t NOP_ZPG_6 = 0x64;
static constexpr uint8_t ADC_ZPG   = 0x65;
static constexpr uint8_t ROR_ZPG   = 0x66;
static constexpr uint8_t RRA_ZPG   = 0x67;
static constexpr uint8_t PLA_IMPL  = 0x68;
static constexpr uint8_t ADC_IMM   = 0x69;
static constexpr uint8_t ROR_A     = 0x6A;
static constexpr uint8_t ARR_IMM   = 0x6B;
static constexpr uint8_t JMP_IND   = 0x6C;
static constexpr uint8_t ADC_ABS   = 0x6D;
static constexpr uint8_t ROR_ABS   = 0x6E;
static constexpr uint8_t RRA_ABS   = 0x6F;

static constexpr uint8_t BVS_REL   = 0x70;
static constexpr uint8_t ADC_IND_Y = 0x71;
static constexpr uint8_t JAM_X07   = 0x72;
static constexpr uint8_t RRA_IND_Y = 0x73;
static constexpr uint8_t NOP_ZPX_7 = 0x74;
static constexpr uint8_t ADC_ZPG_X = 0x75;
static constexpr uint8_t ROR_ZPG_X = 0x76;
static constexpr uint8_t RRA_ZPG_X = 0x77;
static constexpr uint8_t SEI_IMPL  = 0x78;
static constexpr uint8_t ADC_ABS_Y = 0x79;
static constexpr uint8_t NOP_IMPL7 = 0x7A;
static constexpr uint8_t RRA_ABS_Y = 0x7B;
static constexpr uint8_t NOP_ABSX7 = 0x7C;
static constexpr uint8_t ADC_ABS_X = 0x7D;
static constexpr uint8_t ROR_ABS_X = 0x7E;
static constexpr uint8_t RRA_ABS_X = 0x7F;

static constexpr uint8_t NOP_IMM_1 = 0x80;
static constexpr uint8_t STA_X_IND = 0x81;
static constexpr uint8_t NOP_IMM_2 = 0x82;
static constexpr uint8_t SAX_X_IND = 0x83;
static constexpr uint8_t STY_ZPG   = 0x84;
static constexpr uint8_t STA_ZPG   = 0x85;
static constexpr uint8_t STX_ZPG   = 0x86;
static constexpr uint8_t SAX_ZPG   = 0x87;
static constexpr uint8_t DEY_IMPL  = 0x88;
static constexpr uint8_t NOP_IMM_3 = 0x89;
static constexpr uint8_t TXA_IMPL  = 0x8A;
static constexpr uint8_t ANE_IMM   = 0x8B;
static constexpr uint8_t STY_ABS   = 0x8C;
static constexpr uint8_t STA_ABS   = 0x8D;
static constexpr uint8_t STX_ABS   = 0x8E;
static constexpr uint8_t SAX_ABS   = 0x8F;

static constexpr uint8_t BCC_REL   = 0x90;
static constexpr uint8_t STA_IND_Y = 0x91;
static constexpr uint8_t JAM_X09   = 0x92;
static constexpr uint8_t SHA_IND_Y = 0x93;
static constexpr uint8_t STY_ZPG_X = 0x94;
static constexpr uint8_t STA_ZPG_X = 0x95;
static constexpr uint8_t STX_ZPG_Y = 0x96;
static constexpr uint8_t SAX_ZPG_Y = 0x97;
static constexpr uint8_t TYA_IMPL  = 0x98;
static constexpr uint8_t STA_ABS_Y = 0x99;
static constexpr uint8_t TXS_IMPL  = 0x9A;
static constexpr uint8_t TAS_ABS_Y = 0x9B;
static constexpr uint8_t SHY_ABS_X = 0x9C;
static constexpr uint8_t STA_ABS_X = 0x9D;
static constexpr uint8_t SHX_ABS_Y = 0x9E;
static constexpr uint8_t SHA_ABS_Y = 0x9F;

static constexpr uint8_t LDY_IMM   = 0xA0;
static constexpr uint8_t LDA_X_IND = 0xA1;
static constexpr uint8_t LDX_IMM   = 0xA2;
static constexpr uint8_t LAX_X_IND = 0xA3;
static constexpr uint8_t LDY_ZPG   = 0xA4;
static constexpr uint8_t LDA_ZPG   = 0xA5;
static constexpr uint8_t LDX_ZPG   = 0xA6;
static constexpr uint8_t LAX_ZPG   = 0xA7;
static constexpr uint8_t TAY_IMPL  = 0xA8;
static constexpr uint8_t LDA_IMM   = 0xA9;
static constexpr uint8_t TAX_IMPL  = 0xAA;
static constexpr uint8_t LXA_IMM   = 0xAB;
static constexpr uint8_t LDY_ABS   = 0xAC;
static constexpr uint8_t LDA_ABS   = 0xAD;
static constexpr uint8_t LDX_ABS   = 0xAE;
static constexpr uint8_t LAX_ABS   = 0xAF;

static constexpr uint8_t BCS_REL   = 0xB0;
static constexpr uint8_t LDA_IND_Y = 0xB1;
static constexpr uint8_t JAM_X0B   = 0xB2;
static constexpr uint8_t LAX_IND_Y = 0xB3;
static constexpr uint8_t LDY_ZPG_X = 0xB4;
static constexpr uint8_t LDA_ZPG_X = 0xB5;
static constexpr uint8_t LDX_ZPG_Y = 0xB6;
static constexpr uint8_t LAX_ZPG_Y = 0xB7;
static constexpr uint8_t CLV_IMPL  = 0xB8;
static constexpr uint8_t LDA_ABS_Y = 0xB9;
static constexpr uint8_t TSX_IMPL  = 0xBA;
static constexpr uint8_t LAS_ABS_Y = 0xBB;
static constexpr uint8_t LDY_ABS_X = 0xBC;
static constexpr uint8_t LDA_ABS_X = 0xBD;
static constexpr uint8_t LDX_ABS_Y = 0xBE;
static constexpr uint8_t LAX_ABS_Y = 0xBF;

static constexpr uint8_t CPY_IMM   = 0xC0;
static constexpr uint8_t CMP_X_IND = 0xC1;
static constexpr uint8_t NOP_IMM_4 = 0xC2;
static constexpr uint8_t DCP_X_IND = 0xC3;
static constexpr uint8_t CPY_ZPG   = 0xC4;
static constexpr uint8_t CMP_ZPG   = 0xC5;
static constexpr uint8_t DEC_ZPG   = 0xC6;
static constexpr uint8_t DCP_ZPG   = 0xC7;
static constexpr uint8_t INY_IMPL  = 0xC8;
static constexpr uint8_t CMP_IMM   = 0xC9;
static constexpr uint8_t DEX_IMPL  = 0xCA;
static constexpr uint8_t SBX_IMM   = 0xCB;
static constexpr uint8_t CPY_ABS   = 0xCC;
static constexpr uint8_t CMP_ABS   = 0xCD;
static constexpr uint8_t DEC_ABS   = 0xCE;
static constexpr uint8_t DCP_ABS   = 0xCF;

static constexpr uint8_t BNE_REL   = 0xD0;
static constexpr uint8_t CMP_IND_Y = 0xD1;
static constexpr uint8_t JAM_X0D   = 0xD2;
static constexpr uint8_t DCP_IND_Y = 0xD3;
static constexpr uint8_t NOP_ZPX_D = 0xD4;
static constexpr uint8_t CMP_ZPG_X = 0xD5;
static constexpr uint8_t DEC_ZPG_X = 0xD6;
static constexpr uint8_t DCP_ZPG_X = 0xD7;
static constexpr uint8_t CLD_IMPL  = 0xD8;
static constexpr uint8_t CMP_ABS_Y = 0xD9;
static constexpr uint8_t NOP_IMPLD = 0xDA;
static constexpr uint8_t DCP_ABS_Y = 0xDB;
static constexpr uint8_t NOP_ABSXD = 0xDC;
static constexpr uint8_t CMP_ABS_X = 0xDD;
static constexpr uint8_t DEC_ABS_X = 0xDE;
static constexpr uint8_t DCP_ABS_X = 0xDF;

static constexpr uint8_t CPX_IMM   = 0xE0;
static constexpr uint8_t SBC_X_IND = 0xE1;
static constexpr uint8_t NOP_IMM_5 = 0xE2;
static constexpr uint8_t ISB_X_IND = 0xE3;
static constexpr uint8_t CPX_ZPG   = 0xE4;
static constexpr uint8_t SBC_ZPG   = 0xE5;
static constexpr uint8_t INC_ZPG   = 0xE6;
static constexpr uint8_t ISB_ZPG   = 0xE7;
static constexpr uint8_t INX_IMPL  = 0xE8;
static constexpr uint8_t SBC_IMM   = 0xE9;
static constexpr uint8_t NOP_IMPL  = 0xEA;
static constexpr uint8_t USBC_IMM  = 0xEB;
static constexpr uint8_t CPX_ABS   = 0xEC;
static constexpr uint8_t SBC_ABS   = 0xED;
static constexpr uint8_t INC_ABS   = 0xEE;
static constexpr uint8_t ISB_ABS   = 0xEF;

static constexpr uint8_t BEQ_REL   = 0xF0;
static constexpr uint8_t SBC_IND_Y = 0xF1;
static constexpr uint8_t JAM_X0F   = 0xF2;
static constexpr uint8_t ISB_IND_Y = 0xF3;
static constexpr uint8_t NOP_ZPX_F = 0xF4;
static constexpr uint8_t SBC_ZPG_X = 0xF5;
static constexpr uint8_t INC_ZPG_X = 0xF6;
static constexpr uint8_t ISB_ZPG_X = 0xF7;
static constexpr uint8_t SED_IMPL  = 0xF8;
static constexpr uint8_t SBC_ABS_Y = 0xF9;
static constexpr uint8_t NOP_IMPLF = 0xFA;
static constexpr uint8_t ISB_ABS_Y = 0xFB;
static constexpr uint8_t NOP_ABSXF = 0xFC;
static constexpr uint8_t SBC_ABS_X = 0xFD;
static constexpr uint8_t INC_ABS_X = 0xFE;
static constexpr uint8_t ISB_ABS_X = 0xFF;

enum class AddressMode : uint8_t
{
    NI,
    A,
    ABS,
    ABS_X,
    ABS_Y,
    IMM,
    IMPL,
    IND,
    X_IND,
    IND_Y,
    REL,
    ZPG,
    ZPG_X,
    ZPG_Y
};

enum class OpName : uint8_t
{
    BRK = 0,
    ORA,
    JAM,
    SLO,
    NOP,
    ASL,
    PHP,
    ANC,
    BPL,
    CLC,
    JSR,
    AND,
    RLA,
    BIT,
    ROL,
    PLP,
    BMI,
    SEC,
    RTI,
    EOR,
    SRE,
    LSR,
    PHA,
    ALR,
    JMP,
    BVC,
    CLI,
    RTS,
    ADC,
    RRA,
    ROR,
    PLA,
    ARR,
    BVS,
    SEI,
    STA,
    SAX,
    STY,
    STX,
    DEY,
    TXA,
    ANE,
    BCC,
    SHA,
    TYA,
    TXS,
    TAS,
    SHY,
    SHX,
    LDY,
    LDA,
    LDX,
    LAX,
    TAY,
    TAX,
    LXA,
    BCS,
    CLV,
    TSX,
    LAS,
    CPY,
    CMP,
    DCP,
    DEC,
    INY,
    DEX,
    SBX,
    BNE,
    CLD,
    CPX,
    SBC,
    ISB,
    INC,
    INX,
    USB,
    BEQ,
    SED,
};

constexpr std::array<std::string, static_cast<uint8_t>(OpName::SED) + 1> OP_NAMES
{
    "BRK",
    "ORA",
    "JAM",
    "SLO",
    "NOP",
    "ASL",
    "PHP",
    "ANC",
    "BPL",
    "CLC",
    "JSR",
    "AND",
    "RLA",
    "BIT",
    "ROL",
    "PLP",
    "BMI",
    "SEC",
    "RTI",
    "EOR",
    "SRE",
    "LSR",
    "PHA",
    "ALR",
    "JMP",
    "BVC",
    "CLI",
    "RTS",
    "ADC",
    "RRA",
    "ROR",
    "PLA",
    "ARR",
    "BVS",
    "SEI",
    "STA",
    "SAX",
    "STY",
    "STX",
    "DEY",
    "TXA",
    "ANE",
    "BCC",
    "SHA",
    "TYA",
    "TXS",
    "TAS",
    "SHY",
    "SHX",
    "LDY",
    "LDA",
    "LDX",
    "LAX",
    "TAY",
    "TAX",
    "LXA",
    "BCS",
    "CLV",
    "TSX",
    "LAS",
    "CPY",
    "CMP",
    "DCP",
    "DEC",
    "INY",
    "DEX",
    "SBX",
    "BNE",
    "CLD",
    "CPX",
    "SBC",
    "ISB",
    "INC",
    "INX",
    "USB",
    "BEQ",
    "SED",
};

const std::string& opid_to_name(OpName opid);

static const std::unordered_map<std::string, OpName> MNEMONIC_MAP{
    {"BRK", OpName::BRK},
    {"ORA", OpName::ORA},
    {"JAM", OpName::JAM},
    {"SLO", OpName::SLO},
    {"NOP", OpName::NOP},
    {"ASL", OpName::ASL},
    {"PHP", OpName::PHP},
    {"ANC", OpName::ANC},
    {"BPL", OpName::BPL},
    {"CLC", OpName::CLC},
    {"JSR", OpName::JSR},
    {"AND", OpName::AND},
    {"RLA", OpName::RLA},
    {"BIT", OpName::BIT},
    {"ROL", OpName::ROL},
    {"PLP", OpName::PLP},
    {"BMI", OpName::BMI},
    {"SEC", OpName::SEC},
    {"RTI", OpName::RTI},
    {"EOR", OpName::EOR},
    {"SRE", OpName::SRE},
    {"LSR", OpName::LSR},
    {"PHA", OpName::PHA},
    {"ALR", OpName::ALR},
    {"JMP", OpName::JMP},
    {"BVC", OpName::BVC},
    {"CLI", OpName::CLI},
    {"RTS", OpName::RTS},
    {"ADC", OpName::ADC},
    {"RRA", OpName::RRA},
    {"ROR", OpName::ROR},
    {"PLA", OpName::PLA},
    {"ARR", OpName::ARR},
    {"BVS", OpName::BVS},
    {"SEI", OpName::SEI},
    {"STA", OpName::STA},
    {"SAX", OpName::SAX},
    {"STY", OpName::STY},
    {"STX", OpName::STX},
    {"DEY", OpName::DEY},
    {"TXA", OpName::TXA},
    {"ANE", OpName::ANE},
    {"BCC", OpName::BCC},
    {"SHA", OpName::SHA},
    {"TYA", OpName::TYA},
    {"TXS", OpName::TXS},
    {"TAS", OpName::TAS},
    {"SHY", OpName::SHY},
    {"SHX", OpName::SHX},
    {"LDY", OpName::LDY},
    {"LDA", OpName::LDA},
    {"LDX", OpName::LDX},
    {"LAX", OpName::LAX},
    {"TAY", OpName::TAY},
    {"TAX", OpName::TAX},
    {"LXA", OpName::LXA},
    {"BCS", OpName::BCS},
    {"CLV", OpName::CLV},
    {"TSX", OpName::TSX},
    {"LAS", OpName::LAS},
    {"CPY", OpName::CPY},
    {"CMP", OpName::CMP},
    {"DCP", OpName::DCP},
    {"DEC", OpName::DEC},
    {"INY", OpName::INY},
    {"DEX", OpName::DEX},
    {"SBX", OpName::SBX},
    {"BNE", OpName::BNE},
    {"CLD", OpName::CLD},
    {"CPX", OpName::CPX},
    {"SBC", OpName::SBC},
    {"ISB", OpName::ISB},
    {"INC", OpName::INC},
    {"INX", OpName::INX},
    {"USB", OpName::USB},
    {"BEQ", OpName::BEQ},
    {"SED", OpName::SED},
};

struct OpcodeInfo
{
    OpName name;
    AddressMode address_type;
    uint8_t min_cycles;
};

static_assert(std::is_trivial<OpcodeInfo>::value);

static const std::array<OpcodeInfo, 256> OPCODE_INFO_TABLE = {
    /* 00 */
    OpcodeInfo{OpName::BRK, AddressMode::IMPL,  7},
    OpcodeInfo{OpName::ORA, AddressMode::X_IND, 6},
    OpcodeInfo{OpName::JAM, AddressMode::NI,    0},
    OpcodeInfo{OpName::SLO, AddressMode::X_IND, 8},
    OpcodeInfo{OpName::NOP, AddressMode::ZPG,   3},
    OpcodeInfo{OpName::ORA, AddressMode::ZPG,   3},
    OpcodeInfo{OpName::ASL, AddressMode::ZPG,   5},
    OpcodeInfo{OpName::SLO, AddressMode::ZPG,   5},
    OpcodeInfo{OpName::PHP, AddressMode::IMPL,  3},
    OpcodeInfo{OpName::ORA, AddressMode::IMM,   2},
    OpcodeInfo{OpName::ASL, AddressMode::A,     2},
    OpcodeInfo{OpName::ANC, AddressMode::IMM,   2},
    OpcodeInfo{OpName::NOP, AddressMode::ABS,   4},
    OpcodeInfo{OpName::ORA, AddressMode::ABS,   4},
    OpcodeInfo{OpName::ASL, AddressMode::ABS,   6},
    OpcodeInfo{OpName::SLO, AddressMode::ABS,   6},

    /* 10 */
    OpcodeInfo{OpName::BPL, AddressMode::REL,   2},
    OpcodeInfo{OpName::ORA, AddressMode::IND_Y, 5},
    OpcodeInfo{OpName::JAM, AddressMode::NI,    0},
    OpcodeInfo{OpName::SLO, AddressMode::IND_Y, 8},
    OpcodeInfo{OpName::NOP, AddressMode::ZPG_X, 4},
    OpcodeInfo{OpName::ORA, AddressMode::ZPG_X, 4},
    OpcodeInfo{OpName::ASL, AddressMode::ZPG_X, 6},
    OpcodeInfo{OpName::SLO, AddressMode::ZPG_X, 8},
    OpcodeInfo{OpName::CLC, AddressMode::IMPL,  2},
    OpcodeInfo{OpName::ORA, AddressMode::ABS_Y, 4},
    OpcodeInfo{OpName::NOP, AddressMode::IMPL,  2},
    OpcodeInfo{OpName::SLO, AddressMode::ABS_Y, 7},
    OpcodeInfo{OpName::NOP, AddressMode::ABS_X, 4},
    OpcodeInfo{OpName::ORA, AddressMode::ABS_X, 4},
    OpcodeInfo{OpName::ASL, AddressMode::ABS_X, 7},
    OpcodeInfo{OpName::SLO, AddressMode::ABS_X, 7},

    /* 20 */
    OpcodeInfo{OpName::JSR, AddressMode::ABS,   6},
    OpcodeInfo{OpName::AND, AddressMode::X_IND, 6},
    OpcodeInfo{OpName::JAM, AddressMode::NI,    0},
    OpcodeInfo{OpName::RLA, AddressMode::X_IND, 8},
    OpcodeInfo{OpName::BIT, AddressMode::ZPG,   3},
    OpcodeInfo{OpName::AND, AddressMode::ZPG,   3},
    OpcodeInfo{OpName::ROL, AddressMode::ZPG,   5},
    OpcodeInfo{OpName::RLA, AddressMode::ZPG,   5},
    OpcodeInfo{OpName::PLP, AddressMode::IMPL,  4},
    OpcodeInfo{OpName::AND, AddressMode::IMM,   2},
    OpcodeInfo{OpName::ROL, AddressMode::A,     2},
    OpcodeInfo{OpName::ANC, AddressMode::IMM,   2},
    OpcodeInfo{OpName::BIT, AddressMode::ABS,   4},
    OpcodeInfo{OpName::AND, AddressMode::ABS,   4},
    OpcodeInfo{OpName::ROL, AddressMode::ABS,   6},
    OpcodeInfo{OpName::RLA, AddressMode::ABS,   6},

    /* 30 */
    OpcodeInfo{OpName::BMI, AddressMode::REL,   2},
    OpcodeInfo{OpName::AND, AddressMode::IND_Y, 5},
    OpcodeInfo{OpName::JAM, AddressMode::NI,    0},
    OpcodeInfo{OpName::RLA, AddressMode::IND_Y, 8},
    OpcodeInfo{OpName::NOP, AddressMode::ZPG_X, 4},
    OpcodeInfo{OpName::AND, AddressMode::ZPG_X, 4},
    OpcodeInfo{OpName::ROL, AddressMode::ZPG_X, 6},
    OpcodeInfo{OpName::RLA, AddressMode::ZPG_X, 6},
    OpcodeInfo{OpName::SEC, AddressMode::IMPL,  2},
    OpcodeInfo{OpName::AND, AddressMode::ABS_Y, 4},
    OpcodeInfo{OpName::NOP, AddressMode::IMPL,  2},
    OpcodeInfo{OpName::RLA, AddressMode::ABS_Y, 7},
    OpcodeInfo{OpName::NOP, AddressMode::ABS_X, 4},
    OpcodeInfo{OpName::AND, AddressMode::ABS_X, 4},
    OpcodeInfo{OpName::ROL, AddressMode::ABS_X, 7},
    OpcodeInfo{OpName::RLA, AddressMode::ABS_X, 7},

    /* 40 */
    OpcodeInfo{OpName::RTI, AddressMode::IMPL,  6},
    OpcodeInfo{OpName::EOR, AddressMode::X_IND, 6},
    OpcodeInfo{OpName::JAM, AddressMode::NI,    0},
    OpcodeInfo{OpName::SRE, AddressMode::X_IND, 8},
    OpcodeInfo{OpName::NOP, AddressMode::ZPG,   3},
    OpcodeInfo{OpName::EOR, AddressMode::ZPG,   3},
    OpcodeInfo{OpName::LSR, AddressMode::ZPG,   5},
    OpcodeInfo{OpName::SRE, AddressMode::ZPG,   5},
    OpcodeInfo{OpName::PHA, AddressMode::IMPL,  3},
    OpcodeInfo{OpName::EOR, AddressMode::IMM,   2},
    OpcodeInfo{OpName::LSR, AddressMode::A,     2},
    OpcodeInfo{OpName::ALR, AddressMode::IMM,   2},
    OpcodeInfo{OpName::JMP, AddressMode::ABS,   3},
    OpcodeInfo{OpName::EOR, AddressMode::ABS,   4},
    OpcodeInfo{OpName::LSR, AddressMode::ABS,   6},
    OpcodeInfo{OpName::SRE, AddressMode::ABS,   6},

    /* 50 */
    OpcodeInfo{OpName::BVC, AddressMode::REL,   2},
    OpcodeInfo{OpName::EOR, AddressMode::IND_Y, 5},
    OpcodeInfo{OpName::JAM, AddressMode::NI,    0},
    OpcodeInfo{OpName::SRE, AddressMode::IND_Y, 8},
    OpcodeInfo{OpName::NOP, AddressMode::ZPG_X, 4},
    OpcodeInfo{OpName::EOR, AddressMode::ZPG_X, 6},
    OpcodeInfo{OpName::LSR, AddressMode::ZPG_X, 6},
    OpcodeInfo{OpName::SRE, AddressMode::ZPG_X, 6},
    OpcodeInfo{OpName::CLI, AddressMode::IMPL,  2},
    OpcodeInfo{OpName::EOR, AddressMode::ABS_Y, 4},
    OpcodeInfo{OpName::NOP, AddressMode::IMPL,  2},
    OpcodeInfo{OpName::SRE, AddressMode::ABS_Y, 7},
    OpcodeInfo{OpName::NOP, AddressMode::ABS_X, 4},
    OpcodeInfo{OpName::EOR, AddressMode::ABS_X, 4},
    OpcodeInfo{OpName::LSR, AddressMode::ABS_X, 7},
    OpcodeInfo{OpName::SRE, AddressMode::ABS_X, 7},

    /* 60 */
    OpcodeInfo{OpName::RTS, AddressMode::IMPL,  6},
    OpcodeInfo{OpName::ADC, AddressMode::X_IND, 6},
    OpcodeInfo{OpName::JAM, AddressMode::NI,    0},
    OpcodeInfo{OpName::RRA, AddressMode::X_IND, 8},
    OpcodeInfo{OpName::NOP, AddressMode::ZPG,   3},
    OpcodeInfo{OpName::ADC, AddressMode::ZPG,   3},
    OpcodeInfo{OpName::ROR, AddressMode::ZPG,   5},
    OpcodeInfo{OpName::RRA, AddressMode::ZPG,   5},
    OpcodeInfo{OpName::PLA, AddressMode::IMPL,  4},
    OpcodeInfo{OpName::ADC, AddressMode::IMM,   2},
    OpcodeInfo{OpName::ROR, AddressMode::A,     2},
    OpcodeInfo{OpName::ARR, AddressMode::IMM,   2},
    OpcodeInfo{OpName::JMP, AddressMode::IND,   5},
    OpcodeInfo{OpName::ADC, AddressMode::ABS,   4},
    OpcodeInfo{OpName::ROR, AddressMode::ABS,   6},
    OpcodeInfo{OpName::RRA, AddressMode::ABS,   6},

    /* 70 */
    OpcodeInfo{OpName::BVS, AddressMode::REL,   2},
    OpcodeInfo{OpName::ADC, AddressMode::IND_Y, 5},
    OpcodeInfo{OpName::JAM, AddressMode::NI,    0},
    OpcodeInfo{OpName::RRA, AddressMode::IND_Y, 8},
    OpcodeInfo{OpName::NOP, AddressMode::ZPG_X, 4},
    OpcodeInfo{OpName::ADC, AddressMode::ZPG_X, 4},
    OpcodeInfo{OpName::ROR, AddressMode::ZPG_X, 6},
    OpcodeInfo{OpName::RRA, AddressMode::ZPG_X, 6},
    OpcodeInfo{OpName::SEI, AddressMode::IMPL,  2},
    OpcodeInfo{OpName::ADC, AddressMode::ABS_Y, 4},
    OpcodeInfo{OpName::NOP, AddressMode::IMPL,  2},
    OpcodeInfo{OpName::RRA, AddressMode::ABS_Y, 7},
    OpcodeInfo{OpName::NOP, AddressMode::ABS_X, 4},
    OpcodeInfo{OpName::ADC, AddressMode::ABS_X, 4},
    OpcodeInfo{OpName::ROR, AddressMode::ABS_X, 7},
    OpcodeInfo{OpName::RRA, AddressMode::ABS_X, 7},

    /* 80 */
    OpcodeInfo{OpName::NOP, AddressMode::IMM,   2},
    OpcodeInfo{OpName::STA, AddressMode::X_IND, 6},
    OpcodeInfo{OpName::NOP, AddressMode::IMM,   2},
    OpcodeInfo{OpName::SAX, AddressMode::X_IND, 6},
    OpcodeInfo{OpName::STY, AddressMode::ZPG,   3},
    OpcodeInfo{OpName::STA, AddressMode::ZPG,   3},
    OpcodeInfo{OpName::STX, AddressMode::ZPG,   3},
    OpcodeInfo{OpName::SAX, AddressMode::ZPG,   3},
    OpcodeInfo{OpName::DEY, AddressMode::IMPL,  2},
    OpcodeInfo{OpName::NOP, AddressMode::IMM,   2},
    OpcodeInfo{OpName::TXA, AddressMode::IMPL,  2},
    OpcodeInfo{OpName::ANE, AddressMode::IMM,   2},
    OpcodeInfo{OpName::STY, AddressMode::ABS,   4},
    OpcodeInfo{OpName::STA, AddressMode::ABS,   4},
    OpcodeInfo{OpName::STX, AddressMode::ABS,   4},
    OpcodeInfo{OpName::SAX, AddressMode::ABS,   4},

    /* 90 */
    OpcodeInfo{OpName::BCC, AddressMode::REL,   2},
    OpcodeInfo{OpName::STA, AddressMode::IND_Y, 6},
    OpcodeInfo{OpName::JAM, AddressMode::NI,    0},
    OpcodeInfo{OpName::SHA, AddressMode::IND_Y, 6},
    OpcodeInfo{OpName::STY, AddressMode::ZPG_X, 4},
    OpcodeInfo{OpName::STA, AddressMode::ZPG_X, 4},
    OpcodeInfo{OpName::STX, AddressMode::ZPG_Y, 4},
    OpcodeInfo{OpName::SAX, AddressMode::ZPG_Y, 4},
    OpcodeInfo{OpName::TYA, AddressMode::IMPL,  2},
    OpcodeInfo{OpName::STA, AddressMode::ABS_Y, 5},
    OpcodeInfo{OpName::TXS, AddressMode::IMPL,  2},
    OpcodeInfo{OpName::TAS, AddressMode::ABS_Y, 5},
    OpcodeInfo{OpName::SHY, AddressMode::ABS_X, 5},
    OpcodeInfo{OpName::STA, AddressMode::ABS_X, 5},
    OpcodeInfo{OpName::SHX, AddressMode::ABS_Y, 5},
    OpcodeInfo{OpName::SHA, AddressMode::ABS_Y, 5},

    /* A0 */
    OpcodeInfo{OpName::LDY, AddressMode::IMM,   2},
    OpcodeInfo{OpName::LDA, AddressMode::X_IND, 6},
    OpcodeInfo{OpName::LDX, AddressMode::IMM,   2},
    OpcodeInfo{OpName::LAX, AddressMode::X_IND, 6},
    OpcodeInfo{OpName::LDY, AddressMode::ZPG,   3},
    OpcodeInfo{OpName::LDA, AddressMode::ZPG,   3},
    OpcodeInfo{OpName::LDX, AddressMode::ZPG,   3},
    OpcodeInfo{OpName::LAX, AddressMode::ZPG,   3},
    OpcodeInfo{OpName::TAY, AddressMode::IMPL,  2},
    OpcodeInfo{OpName::LDA, AddressMode::IMM,   2},
    OpcodeInfo{OpName::TAX, AddressMode::IMPL,  2},
    OpcodeInfo{OpName::LXA, AddressMode::IMM,   2},
    OpcodeInfo{OpName::LDY, AddressMode::ABS,   4},
    OpcodeInfo{OpName::LDA, AddressMode::ABS,   4},
    OpcodeInfo{OpName::LDX, AddressMode::ABS,   4},
    OpcodeInfo{OpName::LAX, AddressMode::ABS,   4},

    /* B0 */
    OpcodeInfo{OpName::BCS, AddressMode::REL,   2},
    OpcodeInfo{OpName::LDA, AddressMode::IND_Y, 5},
    OpcodeInfo{OpName::JAM, AddressMode::NI,    0},
    OpcodeInfo{OpName::LAX, AddressMode::IND_Y, 5},
    OpcodeInfo{OpName::LDY, AddressMode::ZPG_X, 4},
    OpcodeInfo{OpName::LDA, AddressMode::ZPG_X, 4},
    OpcodeInfo{OpName::LDX, AddressMode::ZPG_Y, 4},
    OpcodeInfo{OpName::LAX, AddressMode::ZPG_Y, 4},
    OpcodeInfo{OpName::CLV, AddressMode::IMPL,  2},
    OpcodeInfo{OpName::LDA, AddressMode::ABS_Y, 4},
    OpcodeInfo{OpName::TSX, AddressMode::IMPL,  2},
    OpcodeInfo{OpName::LAS, AddressMode::ABS_Y, 4},
    OpcodeInfo{OpName::LDY, AddressMode::ABS_X, 4},
    OpcodeInfo{OpName::LDA, AddressMode::ABS_X, 4},
    OpcodeInfo{OpName::LDX, AddressMode::ABS_Y, 4},
    OpcodeInfo{OpName::LAX, AddressMode::ABS_Y, 4},

    /* C0 */
    OpcodeInfo{OpName::CPY, AddressMode::IMM,   2},
    OpcodeInfo{OpName::CMP, AddressMode::X_IND, 6},
    OpcodeInfo{OpName::NOP, AddressMode::IMM,   2},
    OpcodeInfo{OpName::DCP, AddressMode::X_IND, 8},
    OpcodeInfo{OpName::CPY, AddressMode::ZPG,   3},
    OpcodeInfo{OpName::CMP, AddressMode::ZPG,   3},
    OpcodeInfo{OpName::DEC, AddressMode::ZPG,   5},
    OpcodeInfo{OpName::DCP, AddressMode::ZPG,   5},
    OpcodeInfo{OpName::INY, AddressMode::IMPL,  2},
    OpcodeInfo{OpName::CMP, AddressMode::IMM,   2},
    OpcodeInfo{OpName::DEX, AddressMode::IMPL,  2},
    OpcodeInfo{OpName::SBX, AddressMode::IMM,   2},
    OpcodeInfo{OpName::CPY, AddressMode::ABS,   4},
    OpcodeInfo{OpName::CMP, AddressMode::ABS,   4},
    OpcodeInfo{OpName::DEC, AddressMode::ABS,   6},
    OpcodeInfo{OpName::DCP, AddressMode::ABS,   6},

    /* D0 */
    OpcodeInfo{OpName::BNE, AddressMode::REL,   2},
    OpcodeInfo{OpName::CMP, AddressMode::IND_Y, 5},
    OpcodeInfo{OpName::JAM, AddressMode::NI,    0},
    OpcodeInfo{OpName::DCP, AddressMode::IND_Y, 8},
    OpcodeInfo{OpName::NOP, AddressMode::ZPG_X, 4},
    OpcodeInfo{OpName::CMP, AddressMode::ZPG_X, 4},
    OpcodeInfo{OpName::DEC, AddressMode::ZPG_X, 6},
    OpcodeInfo{OpName::DCP, AddressMode::ZPG_X, 6},
    OpcodeInfo{OpName::CLD, AddressMode::IMPL,  2},
    OpcodeInfo{OpName::CMP, AddressMode::ABS_Y, 4},
    OpcodeInfo{OpName::NOP, AddressMode::IMPL,  2},
    OpcodeInfo{OpName::DCP, AddressMode::ABS_Y, 7},
    OpcodeInfo{OpName::NOP, AddressMode::ABS_X, 4},
    OpcodeInfo{OpName::CMP, AddressMode::ABS_X, 4},
    OpcodeInfo{OpName::DEC, AddressMode::ABS_X, 7},
    OpcodeInfo{OpName::DCP, AddressMode::ABS_X, 7},

    /* E0 */
    OpcodeInfo{OpName::CPX, AddressMode::IMM,   2},
    OpcodeInfo{OpName::SBC, AddressMode::X_IND, 6},
    OpcodeInfo{OpName::NOP, AddressMode::IMM,   2},
    OpcodeInfo{OpName::ISB, AddressMode::X_IND, 7},
    OpcodeInfo{OpName::CPX, AddressMode::ZPG,   3},
    OpcodeInfo{OpName::SBC, AddressMode::ZPG,   3},
    OpcodeInfo{OpName::INC, AddressMode::ZPG,   5},
    OpcodeInfo{OpName::ISB, AddressMode::ZPG,   5},
    OpcodeInfo{OpName::INX, AddressMode::IMPL,  2},
    OpcodeInfo{OpName::SBC, AddressMode::IMM,   2},
    OpcodeInfo{OpName::NOP, AddressMode::IMPL,  2},
    OpcodeInfo{OpName::SBC, AddressMode::IMM,   2},
    OpcodeInfo{OpName::CPX, AddressMode::ABS,   4},
    OpcodeInfo{OpName::SBC, AddressMode::ABS,   4},
    OpcodeInfo{OpName::INC, AddressMode::ABS,   6},
    OpcodeInfo{OpName::ISB, AddressMode::ABS,   6},

    /* F0 */
    OpcodeInfo{OpName::BEQ, AddressMode::REL,   2},
    OpcodeInfo{OpName::SBC, AddressMode::IND_Y, 5},
    OpcodeInfo{OpName::JAM, AddressMode::NI,    0},
    OpcodeInfo{OpName::ISB, AddressMode::IND_Y, 7},
    OpcodeInfo{OpName::NOP, AddressMode::ZPG_X, 4},
    OpcodeInfo{OpName::SBC, AddressMode::ZPG_X, 4},
    OpcodeInfo{OpName::INC, AddressMode::ZPG_X, 6},
    OpcodeInfo{OpName::ISB, AddressMode::ZPG_X, 6},
    OpcodeInfo{OpName::SED, AddressMode::IMPL,  2},
    OpcodeInfo{OpName::SBC, AddressMode::ABS_Y, 4},
    OpcodeInfo{OpName::NOP, AddressMode::IMPL,  2},
    OpcodeInfo{OpName::ISB, AddressMode::ABS_Y, 7},
    OpcodeInfo{OpName::NOP, AddressMode::ABS_X, 4},
    OpcodeInfo{OpName::SBC, AddressMode::ABS_X, 4},
    OpcodeInfo{OpName::INC, AddressMode::ABS_X, 7},
    OpcodeInfo{OpName::ISB, AddressMode::ABS_X, 7},
};

constexpr auto address_mode_num_bytes(AddressMode address_type) -> uint8_t
{
    switch (address_type)
    {
    case AddressMode::A:
        return 0;
    case AddressMode::ABS:
        return 2;
    case AddressMode::ABS_X:
        return 2;
    case AddressMode::ABS_Y:
        return 2;
    case AddressMode::IMM:
        return 1;
    case AddressMode::IMPL:
        return 0;
    case AddressMode::IND:
        return 2;
    case AddressMode::X_IND:
        return 1;
    case AddressMode::IND_Y:
        return 1;
    case AddressMode::REL:
        return 1;
    case AddressMode::ZPG:
        return 1;
    case AddressMode::ZPG_X:
        return 1;
    case AddressMode::ZPG_Y:
        return 1;
    default:
        return 0;
    }
}

struct OpDecode
{
    OpcodeInfo op_info;
    uint16_t effective_address;
    uint8_t data;
    uint8_t b1;
    uint8_t b2;
    uint8_t read_bytes;
    std::string instr_fmt(uint8_t opcode, uint8_t x, uint8_t y, uint16_t pc) const;
};

static_assert(std::is_trivial<OpDecode>::value);

using OpSet = std::unordered_set<OpName>;

const OpSet ILLEGAL_OP_SET{
    OpName::JAM, OpName::SLO, OpName::ANC, OpName::RLA, OpName::SRE,
    OpName::ALR, OpName::RRA, OpName::ARR, OpName::SAX, OpName::ANE,
    OpName::SHA, OpName::TAS, OpName::SHY, OpName::SHX, OpName::LAX,
    OpName::LXA, OpName::LAS, OpName::DCP, OpName::SBX, OpName::ISB,
    OpName::USB
};

const OpSet IMPLICIT_OP_SET{
    OpName::BRK, OpName::PHP, OpName::CLC, OpName::PLP, OpName::SEC,
    OpName::RTI, OpName::PHA, OpName::CLI, OpName::RTS, OpName::PLA,
    OpName::SEI, OpName::DEY, OpName::TXA, OpName::TYA, OpName::TXS,
    OpName::TAY, OpName::TAX, OpName::CLV, OpName::TSX, OpName::INY,
    OpName::DEX, OpName::CLD, OpName::INX, OpName::SED, OpName::NOP,
};

const OpSet ACC_OP_SET{
    OpName::ASL,
    OpName::ROL,
    OpName::LSR,
    OpName::ROR,
};

const OpSet IMMEDIATE_OP_SET{
    OpName::ORA, OpName::ANC, OpName::AND, OpName::EOR, OpName::ALR,
    OpName::ADC, OpName::ARR, OpName::NOP, OpName::ANE, OpName::LDY,
    OpName::LDX, OpName::LDA, OpName::LXA, OpName::CPY, OpName::CMP,
    OpName::SBX, OpName::CPX, OpName::SBC,
};

const OpSet ABSOLUTE_OP_SET{
    OpName::NOP, OpName::ORA, OpName::ASL, OpName::SLO, OpName::JSR,
    OpName::BIT, OpName::AND, OpName::ROL, OpName::RLA, OpName::JMP,
    OpName::EOR, OpName::LSR, OpName::SRE, OpName::ADC, OpName::ROR,
    OpName::RRA, OpName::STY, OpName::STA, OpName::STX, OpName::SAX,
    OpName::LDY, OpName::LDA, OpName::LDX, OpName::LAX, OpName::CPY,
    OpName::CMP, OpName::DEC, OpName::DCP, OpName::CPX, OpName::SBC,
    OpName::INC, OpName::ISB,
};

const OpSet ABSOLUTE_X_OP_SET{
    OpName::NOP, OpName::ORA, OpName::ASL, OpName::SLO, OpName::AND,
    OpName::ROL, OpName::RLA, OpName::EOR, OpName::LSR, OpName::SRE,
    OpName::ADC, OpName::ROR, OpName::RRA, OpName::SHY, OpName::STA,
    OpName::LDY, OpName::LDA, OpName::CMP, OpName::DEC, OpName::DCP,
    OpName::SBC, OpName::INC, OpName::ISB,
};

const OpSet ABSOLUTE_Y_OP_SET{
    OpName::ORA, OpName::SLO, OpName::AND, OpName::RLA, OpName::EOR,
    OpName::SRE, OpName::ADC, OpName::RRA, OpName::STA, OpName::TAS,
    OpName::SHX, OpName::SHA, OpName::LDA, OpName::LAS, OpName::LDX,
    OpName::LAX, OpName::CMP, OpName::DCP, OpName::SBC, OpName::ISB,
};

const OpSet ZPG_OP_SET{
    OpName::NOP, OpName::ORA, OpName::ASL, OpName::SLO, OpName::BIT,
    OpName::AND, OpName::ROL, OpName::RLA, OpName::EOR, OpName::LSR,
    OpName::SRE, OpName::ADC, OpName::ROR, OpName::RRA, OpName::STY,
    OpName::STA, OpName::STX, OpName::SAX, OpName::LDY, OpName::LDA,
    OpName::LDX, OpName::LAX, OpName::CPY, OpName::CMP, OpName::DEC,
    OpName::DCP, OpName::CPX, OpName::SBC, OpName::INC, OpName::ISB,
};

const OpSet ZPG_X_OP_SET{
    OpName::NOP, OpName::ORA, OpName::ASL, OpName::SLO, OpName::AND,
    OpName::ROL, OpName::RLA, OpName::EOR, OpName::LSR, OpName::SRE,
    OpName::ADC, OpName::ROR, OpName::RRA, OpName::STY, OpName::STA,
    OpName::LDY, OpName::LDA, OpName::CMP, OpName::DEC, OpName::DCP,
    OpName::SBC, OpName::INC, OpName::ISB,
};

const OpSet ZPG_Y_OP_SET{
    OpName::STX,
    OpName::SAX,
    OpName::LDX,
    OpName::LAX,
};

const OpSet INDIRECT_OP_SET{OpName::JMP};

const OpSet X_INDIRECT_OP_SET{
    OpName::ORA, OpName::SLO, OpName::AND, OpName::RLA,
    OpName::EOR, OpName::SRE, OpName::ADC, OpName::RRA,
    OpName::STA, OpName::SAX, OpName::LDA, OpName::LAX,
    OpName::CMP, OpName::DCP, OpName::SBC, OpName::ISB,
};

const OpSet INDIRECT_Y_OP_SET{
    OpName::ORA, OpName::SLO, OpName::AND, OpName::RLA,
    OpName::EOR, OpName::SRE, OpName::ADC, OpName::RRA,
    OpName::STA, OpName::SHA, OpName::LDA, OpName::LAX,
    OpName::CMP, OpName::DCP, OpName::SBC, OpName::ISB,
};

const OpSet RELATIVE_OP_SET{
    OpName::BPL, OpName::BMI, OpName::BVC, OpName::BVS,
    OpName::BCC, OpName::BCS, OpName::BNE, OpName::BEQ,
};

const OpSet JAM_OP_SET{OpName::JAM};

const std::unordered_map<AddressMode, OpSet> ADDRESS_MODE_MAP{
    {AddressMode::IMPL, IMPLICIT_OP_SET},
    {AddressMode::A, ACC_OP_SET},
    {AddressMode::IMM, IMMEDIATE_OP_SET},
    {AddressMode::ABS, ABSOLUTE_OP_SET},
    {AddressMode::ABS_X, ABSOLUTE_X_OP_SET},
    {AddressMode::ABS_Y, ABSOLUTE_Y_OP_SET},
    {AddressMode::ZPG, ZPG_OP_SET},
    {AddressMode::ZPG_X, ZPG_X_OP_SET},
    {AddressMode::ZPG_Y, ZPG_Y_OP_SET},
    {AddressMode::IND, INDIRECT_OP_SET},
    {AddressMode::X_IND, X_INDIRECT_OP_SET},
    {AddressMode::IND_Y, INDIRECT_Y_OP_SET},
    {AddressMode::REL, RELATIVE_OP_SET},
    {AddressMode::NI, JAM_OP_SET},
};

using OpMap = std::unordered_map<OpName, uint8_t>;

const OpMap IMPLICIT_MAP{
    {OpName::BRK, BRK_IMPL}, {OpName::PHP, PHP_IMPL}, {OpName::CLC, CLC_IMPL},
    {OpName::PLP, PLP_IMPL}, {OpName::SEC, SEC_IMPL}, {OpName::RTI, RTI_IMPL},
    {OpName::PHA, PHA_IMPL}, {OpName::CLI, CLI_IMPL}, {OpName::RTS, RTS_IMPL},
    {OpName::PLA, PLA_IMPL}, {OpName::SEI, SEI_IMPL}, {OpName::DEY, DEY_IMPL},
    {OpName::TXA, TXA_IMPL}, {OpName::TYA, TYA_IMPL}, {OpName::TXS, TXS_IMPL},
    {OpName::TAY, TAY_IMPL}, {OpName::TAX, TAX_IMPL}, {OpName::CLV, CLV_IMPL},
    {OpName::TSX, TSX_IMPL}, {OpName::INY, INY_IMPL}, {OpName::DEX, DEX_IMPL},
    {OpName::CLD, CLD_IMPL}, {OpName::INX, INX_IMPL}, {OpName::SED, SED_IMPL},
    {OpName::NOP, NOP_IMPL},
};

const OpMap ACC_MAP{
    {OpName::ASL, ASL_A},
    {OpName::ROL, ROL_A},
    {OpName::LSR, LSR_A},
    {OpName::ROR, ROR_A},
};

static constexpr uint8_t ANC_IMM = ANC_IMM1;
static constexpr uint8_t NOP_IMM = NOP_IMM_1;
const OpMap IMMEDIATE_MAP{
    {OpName::ORA, ORA_IMM}, {OpName::ANC, ANC_IMM}, {OpName::AND, AND_IMM},
    {OpName::EOR, EOR_IMM}, {OpName::ALR, ALR_IMM}, {OpName::ADC, ADC_IMM},
    {OpName::ARR, ARR_IMM}, {OpName::NOP, NOP_IMM}, {OpName::ANE, ANE_IMM},
    {OpName::LDY, LDY_IMM}, {OpName::LDX, LDX_IMM}, {OpName::LDA, LDA_IMM},
    {OpName::LXA, LXA_IMM}, {OpName::CPY, CPY_IMM}, {OpName::CMP, CMP_IMM},
    {OpName::SBX, SBX_IMM}, {OpName::CPX, CPX_IMM}, {OpName::SBC, SBC_IMM},
};

static constexpr uint8_t NOP_ABS = NOP_ABS_0;
const OpMap ABSOLUTE_MAP{
    {OpName::NOP, NOP_ABS}, {OpName::ORA, ORA_ABS}, {OpName::ASL, ASL_ABS},
    {OpName::SLO, SLO_ABS}, {OpName::JSR, JSR_ABS}, {OpName::BIT, BIT_ABS},
    {OpName::AND, AND_ABS}, {OpName::ROL, ROL_ABS}, {OpName::RLA, RLA_ABS},
    {OpName::JMP, JMP_ABS}, {OpName::EOR, EOR_ABS}, {OpName::LSR, LSR_ABS},
    {OpName::SRE, SRE_ABS}, {OpName::ADC, ADC_ABS}, {OpName::ROR, ROR_ABS},
    {OpName::RRA, RRA_ABS}, {OpName::STY, STY_ABS}, {OpName::STA, STA_ABS},
    {OpName::STX, STX_ABS}, {OpName::SAX, SAX_ABS}, {OpName::LDY, LDY_ABS},
    {OpName::LDA, LDA_ABS}, {OpName::LDX, LDX_ABS}, {OpName::LAX, LAX_ABS},
    {OpName::CPY, CPY_ABS}, {OpName::CMP, CMP_ABS}, {OpName::DEC, DEC_ABS},
    {OpName::DCP, DCP_ABS}, {OpName::CPX, CPX_ABS}, {OpName::SBC, SBC_ABS},
    {OpName::INC, INC_ABS}, {OpName::ISB, ISB_ABS},
};

static constexpr uint8_t NOP_ABS_X = NOP_ABSX1;
const OpMap ABSOLUTE_X_MAP{
    {OpName::NOP, NOP_ABS_X}, {OpName::ORA, ORA_ABS_X},
    {OpName::ASL, ASL_ABS_X}, {OpName::SLO, SLO_ABS_X},
    {OpName::AND, AND_ABS_X}, {OpName::ROL, ROL_ABS_X},
    {OpName::RLA, RLA_ABS_X}, {OpName::EOR, EOR_ABS_X},
    {OpName::LSR, LSR_ABS_X}, {OpName::SRE, SRE_ABS_X},
    {OpName::ADC, ADC_ABS_X}, {OpName::ROR, ROR_ABS_X},
    {OpName::RRA, RRA_ABS_X}, {OpName::SHY, SHY_ABS_X},
    {OpName::STA, STA_ABS_X}, {OpName::LDY, LDY_ABS_X},
    {OpName::LDA, LDA_ABS_X}, {OpName::CMP, CMP_ABS_X},
    {OpName::DEC, DEC_ABS_X}, {OpName::DCP, DCP_ABS_X},
    {OpName::SBC, SBC_ABS_X}, {OpName::INC, INC_ABS_X},
    {OpName::ISB, ISB_ABS_X},
};

const OpMap ABSOLUTE_Y_MAP{
    {OpName::ORA, ORA_ABS_Y}, {OpName::SLO, SLO_ABS_Y},
    {OpName::AND, AND_ABS_Y}, {OpName::RLA, RLA_ABS_Y},
    {OpName::EOR, EOR_ABS_Y}, {OpName::SRE, SRE_ABS_Y},
    {OpName::ADC, ADC_ABS_Y}, {OpName::RRA, RRA_ABS_Y},
    {OpName::STA, STA_ABS_Y}, {OpName::TAS, TAS_ABS_Y},
    {OpName::SHX, SHX_ABS_Y}, {OpName::SHA, SHA_ABS_Y},
    {OpName::LDA, LDA_ABS_Y}, {OpName::LAS, LAS_ABS_Y},
    {OpName::LDX, LDX_ABS_Y}, {OpName::LAX, LAX_ABS_Y},
    {OpName::CMP, CMP_ABS_Y}, {OpName::DCP, DCP_ABS_Y},
    {OpName::SBC, SBC_ABS_Y}, {OpName::ISB, ISB_ABS_Y},
};

static constexpr uint8_t NOP_ZPG = NOP_ZPG_0;
const OpMap ZPG_MAP{
    {OpName::NOP, NOP_ZPG}, {OpName::ORA, ORA_ZPG}, {OpName::ASL, ASL_ZPG},
    {OpName::SLO, SLO_ZPG}, {OpName::BIT, BIT_ZPG}, {OpName::AND, AND_ZPG},
    {OpName::ROL, ROL_ZPG}, {OpName::RLA, RLA_ZPG}, {OpName::EOR, EOR_ZPG},
    {OpName::LSR, LSR_ZPG}, {OpName::SRE, SRE_ZPG}, {OpName::ADC, ADC_ZPG},
    {OpName::ROR, ROR_ZPG}, {OpName::RRA, RRA_ZPG}, {OpName::STY, STY_ZPG},
    {OpName::STA, STA_ZPG}, {OpName::STX, STX_ZPG}, {OpName::SAX, SAX_ZPG},
    {OpName::LDY, LDY_ZPG}, {OpName::LDA, LDA_ZPG}, {OpName::LDX, LDX_ZPG},
    {OpName::LAX, LAX_ZPG}, {OpName::CPY, CPY_ZPG}, {OpName::CMP, CMP_ZPG},
    {OpName::DEC, DEC_ZPG}, {OpName::DCP, DCP_ZPG}, {OpName::CPX, CPX_ZPG},
    {OpName::SBC, SBC_ZPG}, {OpName::INC, INC_ZPG}, {OpName::ISB, ISB_ZPG},
};

static constexpr uint8_t NOP_ZPG_X = NOP_ZPX_1;
const OpMap ZPG_X_MAP{
    {OpName::NOP, NOP_ZPG_X}, {OpName::ORA, ORA_ZPG_X},
    {OpName::ASL, ASL_ZPG_X}, {OpName::SLO, SLO_ZPG_X},
    {OpName::AND, AND_ZPG_X}, {OpName::ROL, ROL_ZPG_X},
    {OpName::RLA, RLA_ZPG_X}, {OpName::EOR, EOR_ZPG_X},
    {OpName::LSR, LSR_ZPG_X}, {OpName::SRE, SRE_ZPG_X},
    {OpName::ADC, ADC_ZPG_X}, {OpName::ROR, ROR_ZPG_X},
    {OpName::RRA, RRA_ZPG_X}, {OpName::STY, STY_ZPG_X},
    {OpName::STA, STA_ZPG_X}, {OpName::LDY, LDY_ZPG_X},
    {OpName::LDA, LDA_ZPG_X}, {OpName::CMP, CMP_ZPG_X},
    {OpName::DEC, DEC_ZPG_X}, {OpName::DCP, DCP_ZPG_X},
    {OpName::SBC, SBC_ZPG_X}, {OpName::INC, INC_ZPG_X},
    {OpName::ISB, ISB_ZPG_X},
};

const OpMap ZPG_Y_MAP{
    {OpName::STX, STX_ZPG_Y},
    {OpName::SAX, SAX_ZPG_Y},
    {OpName::LDX, LDX_ZPG_Y},
    {OpName::LAX, LAX_ZPG_Y},
};

const OpMap INDIRECT_MAP{{OpName::JMP, JMP_IND}};

const OpMap X_INDIRECT_MAP{
    {OpName::ORA, ORA_X_IND}, {OpName::SLO, SLO_X_IND},
    {OpName::AND, AND_X_IND}, {OpName::RLA, RLA_X_IND},
    {OpName::EOR, EOR_X_IND}, {OpName::SRE, SRE_X_IND},
    {OpName::ADC, ADC_X_IND}, {OpName::RRA, RRA_X_IND},
    {OpName::STA, STA_X_IND}, {OpName::SAX, SAX_X_IND},
    {OpName::LDA, LDA_X_IND}, {OpName::LAX, LAX_X_IND},
    {OpName::CMP, CMP_X_IND}, {OpName::DCP, DCP_X_IND},
    {OpName::SBC, SBC_X_IND}, {OpName::ISB, ISB_X_IND},
};

const OpMap INDIRECT_Y_MAP{
    {OpName::ORA, ORA_IND_Y}, {OpName::SLO, SLO_IND_Y},
    {OpName::AND, AND_IND_Y}, {OpName::RLA, RLA_IND_Y},
    {OpName::EOR, EOR_IND_Y}, {OpName::SRE, SRE_IND_Y},
    {OpName::ADC, ADC_IND_Y}, {OpName::RRA, RRA_IND_Y},
    {OpName::STA, STA_IND_Y}, {OpName::SHA, SHA_IND_Y},
    {OpName::LDA, LDA_IND_Y}, {OpName::LAX, LAX_IND_Y},
    {OpName::CMP, CMP_IND_Y}, {OpName::DCP, DCP_IND_Y},
    {OpName::SBC, SBC_IND_Y}, {OpName::ISB, ISB_IND_Y},
};

const OpMap RELATIVE_MAP{
    {OpName::BPL, BPL_REL}, {OpName::BMI, BMI_REL}, {OpName::BVC, BVC_REL},
    {OpName::BVS, BVS_REL}, {OpName::BCC, BCC_REL}, {OpName::BCS, BCS_REL},
    {OpName::BNE, BNE_REL}, {OpName::BEQ, BEQ_REL},
};

const OpMap JAM_MAP{
    {OpName::JAM, JAM_X00}
};

const std::unordered_map<AddressMode, OpMap> OPCODE_MAP{
    {AddressMode::IMPL, IMPLICIT_MAP},
    {AddressMode::A, ACC_MAP},
    {AddressMode::IMM, IMMEDIATE_MAP},
    {AddressMode::ABS, ABSOLUTE_MAP},
    {AddressMode::ABS_X, ABSOLUTE_X_MAP},
    {AddressMode::ABS_Y, ABSOLUTE_Y_MAP},
    {AddressMode::ZPG, ZPG_MAP},
    {AddressMode::ZPG_X, ZPG_X_MAP},
    {AddressMode::ZPG_Y, ZPG_Y_MAP},
    {AddressMode::IND, INDIRECT_MAP},
    {AddressMode::X_IND, X_INDIRECT_MAP},
    {AddressMode::IND_Y, INDIRECT_Y_MAP},
    {AddressMode::REL, RELATIVE_MAP},
    {AddressMode::NI, JAM_MAP},
};


} // namespace mos6502

#endif
