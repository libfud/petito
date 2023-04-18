#ifndef OPCODE_TABLE
#define OPCODE_TABLE

#include <array>
#include <fmt/core.h>
#include <cstdint>
#include <string>
#include <type_traits>

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

static constexpr std::array<char, 4> FUG{"BRK"};

enum class AddressType : uint8_t
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

struct OpcodeInfo
{
    std::array<char, 4> name;
    AddressType address_type;
    uint8_t min_cycles;
};

static_assert(std::is_trivial<OpcodeInfo>::value);

static const std::array<OpcodeInfo, 256> OPCODE_INFO_TABLE = {
    /* 00 */
    OpcodeInfo{{"BRK"}, AddressType::IMPL,  7}, OpcodeInfo{{"ORA"}, AddressType::X_IND, 6}, OpcodeInfo{{"JAM"}, AddressType::NI,    0}, OpcodeInfo{{"SLO"}, AddressType::X_IND, 8},
    OpcodeInfo{{"NOP"}, AddressType::ZPG,   3}, OpcodeInfo{{"ORA"}, AddressType::ZPG,   3}, OpcodeInfo{{"ASL"}, AddressType::ZPG,   5}, OpcodeInfo{{"SLO"}, AddressType::ZPG,   5},
    OpcodeInfo{{"PHP"}, AddressType::IMPL,  3}, OpcodeInfo{{"ORA"}, AddressType::IMM,   2}, OpcodeInfo{{"ASL"}, AddressType::A,     2}, OpcodeInfo{{"ANC"}, AddressType::IMM,   2},
    OpcodeInfo{{"NOP"}, AddressType::ABS,   4}, OpcodeInfo{{"ORA"}, AddressType::ABS,   4}, OpcodeInfo{{"ASL"}, AddressType::ABS,   6}, OpcodeInfo{{"SLO"}, AddressType::ABS,   6},

    /* 10 */
    OpcodeInfo{{"BPL"}, AddressType::REL,   2}, OpcodeInfo{{"ORA"}, AddressType::IND_Y, 5}, OpcodeInfo{{"JAM"}, AddressType::NI,    0}, OpcodeInfo{{"SLO"}, AddressType::IND_Y, 8},
    OpcodeInfo{{"NOP"}, AddressType::ZPG_X, 4}, OpcodeInfo{{"ORA"}, AddressType::ZPG_X, 4}, OpcodeInfo{{"ASL"}, AddressType::ZPG_X, 6}, OpcodeInfo{{"SLO"}, AddressType::ZPG_X, 8},
    OpcodeInfo{{"CLC"}, AddressType::IMPL,  2}, OpcodeInfo{{"ORA"}, AddressType::ABS_Y, 4}, OpcodeInfo{{"NOP"}, AddressType::IMPL,  2}, OpcodeInfo{{"SLO"}, AddressType::ABS_Y, 7},
    OpcodeInfo{{"NOP"}, AddressType::ABS_X, 4}, OpcodeInfo{{"ORA"}, AddressType::ABS_X, 4}, OpcodeInfo{{"ASL"}, AddressType::ABS_X, 7}, OpcodeInfo{{"SLO"}, AddressType::ABS_X, 7},

    /* 20 */
    OpcodeInfo{{"JSR"}, AddressType::ABS,   6}, OpcodeInfo{{"AND"}, AddressType::X_IND, 6}, OpcodeInfo{{"JAM"}, AddressType::NI,    0}, OpcodeInfo{{"RLA"}, AddressType::X_IND, 8},
    OpcodeInfo{{"BIT"}, AddressType::ZPG,   3}, OpcodeInfo{{"AND"}, AddressType::ZPG,   3}, OpcodeInfo{{"ROL"}, AddressType::ZPG,   5}, OpcodeInfo{{"RLA"}, AddressType::ZPG,   5},
    OpcodeInfo{{"PLP"}, AddressType::IMPL,  4}, OpcodeInfo{{"AND"}, AddressType::IMM,   2}, OpcodeInfo{{"ROL"}, AddressType::A,     2}, OpcodeInfo{{"ANC"}, AddressType::IMM,   2},
    OpcodeInfo{{"BIT"}, AddressType::ABS,   4}, OpcodeInfo{{"AND"}, AddressType::ABS,   4}, OpcodeInfo{{"ROL"}, AddressType::ABS,   6}, OpcodeInfo{{"RLA"}, AddressType::ABS,   6},

    /* 30 */
    OpcodeInfo{{"BMI"}, AddressType::REL,   2}, OpcodeInfo{{"AND"}, AddressType::IND_Y, 5}, OpcodeInfo{{"JAM"}, AddressType::NI,    0}, OpcodeInfo{{"RLA"}, AddressType::IND_Y, 8},
    OpcodeInfo{{"NOP"}, AddressType::ZPG_X, 4}, OpcodeInfo{{"AND"}, AddressType::ZPG_X, 4}, OpcodeInfo{{"ROL"}, AddressType::ZPG_X, 6}, OpcodeInfo{{"RLA"}, AddressType::ZPG_X, 6},
    OpcodeInfo{{"SEC"}, AddressType::IMPL,  2}, OpcodeInfo{{"AND"}, AddressType::ABS_Y, 4}, OpcodeInfo{{"NOP"}, AddressType::IMPL,  2}, OpcodeInfo{{"RLA"}, AddressType::ABS_Y, 7},
    OpcodeInfo{{"NOP"}, AddressType::ABS_X, 4}, OpcodeInfo{{"AND"}, AddressType::ABS_X, 4}, OpcodeInfo{{"ROL"}, AddressType::ABS_X, 7}, OpcodeInfo{{"RLA"}, AddressType::ABS_X, 7},

    /* 40 */
    OpcodeInfo{{"RTI"}, AddressType::IMPL,  6}, OpcodeInfo{{"EOR"}, AddressType::X_IND, 6}, OpcodeInfo{{"JAM"}, AddressType::NI,    0}, OpcodeInfo{{"SRE"}, AddressType::X_IND, 8},
    OpcodeInfo{{"NOP"}, AddressType::ZPG,   3}, OpcodeInfo{{"EOR"}, AddressType::ZPG,   3}, OpcodeInfo{{"LSR"}, AddressType::ZPG,   5}, OpcodeInfo{{"SRE"}, AddressType::ZPG,   5},
    OpcodeInfo{{"PHA"}, AddressType::IMPL,  3}, OpcodeInfo{{"EOR"}, AddressType::IMM,   2}, OpcodeInfo{{"LSR"}, AddressType::A,     2}, OpcodeInfo{{"ALR"}, AddressType::IMM,   2},
    OpcodeInfo{{"JMP"}, AddressType::ABS,   3}, OpcodeInfo{{"EOR"}, AddressType::ABS,   4}, OpcodeInfo{{"LSR"}, AddressType::ABS,   6}, OpcodeInfo{{"SRE"}, AddressType::ABS,   6},

    /* 50 */
    OpcodeInfo{{"BVC"}, AddressType::REL,   2}, OpcodeInfo{{"EOR"}, AddressType::IND_Y, 5}, OpcodeInfo{{"JAM"}, AddressType::NI,    0}, OpcodeInfo{{"SRE"}, AddressType::IND_Y, 8},
    OpcodeInfo{{"NOP"}, AddressType::ZPG_X, 4}, OpcodeInfo{{"EOR"}, AddressType::ZPG_X, 6}, OpcodeInfo{{"LSR"}, AddressType::ZPG_X, 6}, OpcodeInfo{{"SRE"}, AddressType::ZPG_X, 6},
    OpcodeInfo{{"CLI"}, AddressType::IMPL,  2}, OpcodeInfo{{"EOR"}, AddressType::ABS_Y, 4}, OpcodeInfo{{"NOP"}, AddressType::IMPL,  2}, OpcodeInfo{{"SRE"}, AddressType::ABS_Y, 7},
    OpcodeInfo{{"NOP"}, AddressType::ABS_X, 4}, OpcodeInfo{{"EOR"}, AddressType::ABS_X, 4}, OpcodeInfo{{"LSR"}, AddressType::ABS_X, 7}, OpcodeInfo{{"SRE"}, AddressType::ABS_X, 7},

    /* 60 */
    OpcodeInfo{{"RTS"}, AddressType::IMPL,  6}, OpcodeInfo{{"ADC"}, AddressType::X_IND, 6}, OpcodeInfo{{"JAM"}, AddressType::NI,    0}, OpcodeInfo{{"RRA"}, AddressType::X_IND, 8},
    OpcodeInfo{{"NOP"}, AddressType::ZPG,   3}, OpcodeInfo{{"ADC"}, AddressType::ZPG,   3}, OpcodeInfo{{"ROR"}, AddressType::ZPG,   5}, OpcodeInfo{{"RRA"}, AddressType::ZPG,   5},
    OpcodeInfo{{"PLA"}, AddressType::IMPL,  4}, OpcodeInfo{{"ADC"}, AddressType::IMM,   2}, OpcodeInfo{{"ROR"}, AddressType::A,     2}, OpcodeInfo{{"ARR"}, AddressType::IMM,   2},
    OpcodeInfo{{"JMP"}, AddressType::IND,   5}, OpcodeInfo{{"ADC"}, AddressType::ABS,   4}, OpcodeInfo{{"ROR"}, AddressType::ABS,   6}, OpcodeInfo{{"RRA"}, AddressType::ABS,   6},

    /* 70 */
    OpcodeInfo{{"BVS"}, AddressType::REL,   2}, OpcodeInfo{{"ADC"}, AddressType::IND_Y, 5}, OpcodeInfo{{"JAM"}, AddressType::NI,    0}, OpcodeInfo{{"RRA"}, AddressType::IND_Y, 8},
    OpcodeInfo{{"NOP"}, AddressType::ZPG_X, 4}, OpcodeInfo{{"ADC"}, AddressType::ZPG_X, 4}, OpcodeInfo{{"ROR"}, AddressType::ZPG_X, 6}, OpcodeInfo{{"RRA"}, AddressType::ZPG_X, 6},
    OpcodeInfo{{"SEI"}, AddressType::IMPL,  2}, OpcodeInfo{{"ADC"}, AddressType::ABS_Y, 4}, OpcodeInfo{{"NOP"}, AddressType::IMPL,  2}, OpcodeInfo{{"RRA"}, AddressType::ABS_Y, 7},
    OpcodeInfo{{"NOP"}, AddressType::ABS_X, 4}, OpcodeInfo{{"ADC"}, AddressType::ABS_X, 4}, OpcodeInfo{{"ROR"}, AddressType::ABS_X, 7}, OpcodeInfo{{"RRA"}, AddressType::ABS_X, 7},

    /* 80 */
    OpcodeInfo{{"NOP"}, AddressType::IMM,   2}, OpcodeInfo{{"STA"}, AddressType::X_IND, 6}, OpcodeInfo{{"NOP"}, AddressType::IMM,   2}, OpcodeInfo{{"SAX"}, AddressType::X_IND, 6},
    OpcodeInfo{{"STY"}, AddressType::ZPG,   3}, OpcodeInfo{{"STA"}, AddressType::ZPG,   3}, OpcodeInfo{{"STX"}, AddressType::ZPG,   3}, OpcodeInfo{{"SAX"}, AddressType::ZPG,   3},
    OpcodeInfo{{"DEY"}, AddressType::IMPL,  2}, OpcodeInfo{{"NOP"}, AddressType::IMM,   2}, OpcodeInfo{{"TXA"}, AddressType::IMPL,  2}, OpcodeInfo{{"ANE"}, AddressType::IMM,   2},
    OpcodeInfo{{"STY"}, AddressType::ABS,   4}, OpcodeInfo{{"STA"}, AddressType::ABS,   4}, OpcodeInfo{{"STX"}, AddressType::ABS,   4}, OpcodeInfo{{"SAX"}, AddressType::ABS,   4},

    /* 90 */
    OpcodeInfo{{"BCC"}, AddressType::REL,   2}, OpcodeInfo{{"STA"}, AddressType::IND_Y, 6}, OpcodeInfo{{"JAM"}, AddressType::NI,    0}, OpcodeInfo{{"SHA"}, AddressType::IND_Y, 6},
    OpcodeInfo{{"STY"}, AddressType::ZPG_X, 4}, OpcodeInfo{{"STA"}, AddressType::ZPG_X, 4}, OpcodeInfo{{"STX"}, AddressType::ZPG_Y, 4}, OpcodeInfo{{"SAX"}, AddressType::ZPG_Y, 4},
    OpcodeInfo{{"TYA"}, AddressType::IMPL,  2}, OpcodeInfo{{"STA"}, AddressType::ABS_Y, 5}, OpcodeInfo{{"TXS"}, AddressType::IMPL,  2}, OpcodeInfo{{"TAS"}, AddressType::ABS_Y, 5},
    OpcodeInfo{{"SHY"}, AddressType::ABS_X, 5}, OpcodeInfo{{"STA"}, AddressType::ABS_X, 5}, OpcodeInfo{{"SHX"}, AddressType::ABS_Y, 5}, OpcodeInfo{{"SHA"}, AddressType::ABS_Y, 5},

    /* A0 */
    OpcodeInfo{{"LDY"}, AddressType::IMM,   2}, OpcodeInfo{{"LDA"}, AddressType::X_IND, 6}, OpcodeInfo{{"LDX"}, AddressType::IMM,   2}, OpcodeInfo{{"LAX"}, AddressType::X_IND, 6},
    OpcodeInfo{{"LDY"}, AddressType::ZPG,   3}, OpcodeInfo{{"LDA"}, AddressType::ZPG,   3}, OpcodeInfo{{"LDX"}, AddressType::ZPG,   3}, OpcodeInfo{{"LAX"}, AddressType::ZPG,   3},
    OpcodeInfo{{"TAY"}, AddressType::IMPL,  2}, OpcodeInfo{{"LDA"}, AddressType::IMM,   2}, OpcodeInfo{{"TAX"}, AddressType::IMPL,  2}, OpcodeInfo{{"LXA"}, AddressType::IMM,   2},
    OpcodeInfo{{"LDY"}, AddressType::ABS,   4}, OpcodeInfo{{"LDA"}, AddressType::ABS,   4}, OpcodeInfo{{"LDX"}, AddressType::ABS,   4}, OpcodeInfo{{"LAX"}, AddressType::ABS,   4},

    /* B0 */
    OpcodeInfo{{"BCS"}, AddressType::REL,   2}, OpcodeInfo{{"LDA"}, AddressType::IND_Y, 5}, OpcodeInfo{{"JAM"}, AddressType::NI,    0}, OpcodeInfo{{"LAX"}, AddressType::IND_Y, 5},
    OpcodeInfo{{"LDY"}, AddressType::ZPG_X, 4}, OpcodeInfo{{"LDA"}, AddressType::ZPG_X, 4}, OpcodeInfo{{"LDX"}, AddressType::ZPG_Y, 4}, OpcodeInfo{{"LAX"}, AddressType::ZPG_Y, 4},
    OpcodeInfo{{"CLV"}, AddressType::IMPL,  2}, OpcodeInfo{{"LDA"}, AddressType::ABS_Y, 4}, OpcodeInfo{{"TSX"}, AddressType::IMPL,  2}, OpcodeInfo{{"LAS"}, AddressType::ABS_Y, 4},
    OpcodeInfo{{"LDY"}, AddressType::ABS_X, 4}, OpcodeInfo{{"LDA"}, AddressType::ABS_X, 4}, OpcodeInfo{{"LDX"}, AddressType::ABS_Y, 4}, OpcodeInfo{{"LAX"}, AddressType::ABS_Y, 4},

    /* C0 */
    OpcodeInfo{{"CPY"}, AddressType::IMM,   2}, OpcodeInfo{{"CMP"}, AddressType::X_IND, 6}, OpcodeInfo{{"NOP"}, AddressType::IMM,   2}, OpcodeInfo{{"DCP"}, AddressType::X_IND, 8},
    OpcodeInfo{{"CPY"}, AddressType::ZPG,   3}, OpcodeInfo{{"CMP"}, AddressType::ZPG,   3}, OpcodeInfo{{"DEC"}, AddressType::ZPG,   5}, OpcodeInfo{{"DCP"}, AddressType::ZPG,   5},
    OpcodeInfo{{"INY"}, AddressType::IMPL,  2}, OpcodeInfo{{"CMP"}, AddressType::IMM,   2}, OpcodeInfo{{"DEX"}, AddressType::IMPL,  2}, OpcodeInfo{{"SBX"}, AddressType::IMM,   2},
    OpcodeInfo{{"CPY"}, AddressType::ABS,   4}, OpcodeInfo{{"CMP"}, AddressType::ABS,   4}, OpcodeInfo{{"DEC"}, AddressType::ABS,   6}, OpcodeInfo{{"DCP"}, AddressType::ABS,   6},

    /* D0 */
    OpcodeInfo{{"BNE"}, AddressType::REL,   2}, OpcodeInfo{{"CMP"}, AddressType::IND_Y, 5}, OpcodeInfo{{"JAM"}, AddressType::NI,    0}, OpcodeInfo{{"DCP"}, AddressType::IND_Y, 8},
    OpcodeInfo{{"NOP"}, AddressType::ZPG_X, 4}, OpcodeInfo{{"CMP"}, AddressType::ZPG_X, 4}, OpcodeInfo{{"DEC"}, AddressType::ZPG_X, 6}, OpcodeInfo{{"DCP"}, AddressType::ZPG_X, 6},
    OpcodeInfo{{"CLD"}, AddressType::IMPL,  2}, OpcodeInfo{{"CMP"}, AddressType::ABS_Y, 4}, OpcodeInfo{{"NOP"}, AddressType::IMPL,  2}, OpcodeInfo{{"DCP"}, AddressType::ABS_Y, 7},
    OpcodeInfo{{"NOP"}, AddressType::ABS_X, 4}, OpcodeInfo{{"CMP"}, AddressType::ABS_X, 4}, OpcodeInfo{{"DEC"}, AddressType::ABS_X, 7}, OpcodeInfo{{"DCP"}, AddressType::ABS_X, 7},

    /* E0 */
    OpcodeInfo{{"CPX"}, AddressType::IMM,   2}, OpcodeInfo{{"SBC"}, AddressType::X_IND, 6}, OpcodeInfo{{"NOP"}, AddressType::IMM,   2}, OpcodeInfo{{"ISB"}, AddressType::X_IND, 7},
    OpcodeInfo{{"CPX"}, AddressType::ZPG,   3}, OpcodeInfo{{"SBC"}, AddressType::ZPG,   3}, OpcodeInfo{{"INC"}, AddressType::ZPG,   5}, OpcodeInfo{{"ISB"}, AddressType::ZPG,   5},
    OpcodeInfo{{"INX"}, AddressType::IMPL,  2}, OpcodeInfo{{"SBC"}, AddressType::IMM,   2}, OpcodeInfo{{"NOP"}, AddressType::IMPL,  2}, OpcodeInfo{{"SBC"}, AddressType::IMM,   2},
    OpcodeInfo{{"CPX"}, AddressType::ABS,   4}, OpcodeInfo{{"SBC"}, AddressType::ABS,   4}, OpcodeInfo{{"INC"}, AddressType::ABS,   6}, OpcodeInfo{{"ISB"}, AddressType::ABS,   6},

    /* F0 */
    OpcodeInfo{{"BEQ"}, AddressType::REL,   2}, OpcodeInfo{{"SBC"}, AddressType::IND_Y, 5}, OpcodeInfo{{"JAM"}, AddressType::NI,    0}, OpcodeInfo{{"ISB"}, AddressType::IND_Y, 7},
    OpcodeInfo{{"NOP"}, AddressType::ZPG_X, 4}, OpcodeInfo{{"SBC"}, AddressType::ZPG_X, 4}, OpcodeInfo{{"INC"}, AddressType::ZPG_X, 6}, OpcodeInfo{{"ISB"}, AddressType::ZPG_X, 6},
    OpcodeInfo{{"SED"}, AddressType::IMPL,  2}, OpcodeInfo{{"SBC"}, AddressType::ABS_Y, 4}, OpcodeInfo{{"NOP"}, AddressType::IMPL,  2}, OpcodeInfo{{"ISB"}, AddressType::ABS_Y, 7},
    OpcodeInfo{{"NOP"}, AddressType::ABS_X, 4}, OpcodeInfo{{"SBC"}, AddressType::ABS_X, 4}, OpcodeInfo{{"INC"}, AddressType::ABS_X, 7}, OpcodeInfo{{"ISB"}, AddressType::ABS_X, 7},
};

// clang warns OPCODE_INFO_TABLE is unused but that is very wrong.
static_assert(OPCODE_INFO_TABLE.size() == 256);

uint8_t address_mode_num_bytes(AddressType address_type);

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

constexpr size_t foo_size = sizeof(OPCODE_INFO_TABLE);

}

#endif
