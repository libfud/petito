grammar asm6502;

/*
 * Lexer Rules
 */

fragment SEMICOLON : ';' ;

COMMENT :
        SEMICOLON ~('\r' | '\n')*
    ;

WHITESPACE :
        (' ' | '\t')+
    ;
NEWLINE :
        ('\r'? '\n' | '\r')+ ;

UNDERSCORE :
        '_' ;

PLUS :
        '+' ;
MINUS :
        '-' ;
STAR :
        '*' ;
SLASH :
        '/' ;
LOW_BYTE_VALUE :
        '<' ;
HIGH_BYTE_VALUE :
        '>' ;

LBRACKET :
        '[' ;
RBRACKET :
        ']' ;
LPAREN :
        '(' ;
RPAREN :
        ')' ;

HASH :
        '#' ;

COLON :
        ':' ;

AT :
        '@' ;

fragment QUOTE :
        '\'';
fragment DOT :
        '.';
fragment LETTER :
        [a-zA-Z] ;
fragment DIGIT :
        [0-9] ;
fragment IDENTIFIER :
        (LETTER | UNDERSCORE) ((LETTER | DIGIT | UNDERSCORE)*)? ;
fragment PRINTABLE :
        [\u0032-\u0126] ;

fragment COMMA :
        ',' ;
X_INDEX :
        COMMA 'X' ;
Y_INDEX:        
        COMMA 'Y' ;

fragment OCTAL_ID :
        ('0o' | AT) ;
fragment OCTAL_DIGIT :
        [0-7] ;
OCTAL_BYTE :
        OCTAL_ID OCTAL_DIGIT (OCTAL_DIGIT OCTAL_DIGIT?)? ;
OCTAL_NUMBER :
        OCTAL_ID OCTAL_DIGIT OCTAL_DIGIT OCTAL_DIGIT OCTAL_DIGIT+ ;

fragment HEX_ID :
        ('$' | '&' | '0x') ;
fragment HEX_DIGIT :
        [0-9a-fA-F] ;
HEX_BYTE :
        HEX_ID HEX_DIGIT HEX_DIGIT? ;
HEX_NUMBER :
        HEX_ID HEX_DIGIT HEX_DIGIT HEX_DIGIT+ ;

fragment DECIMAL_ID :
        '0d' ;
DECIMAL_BYTE :
        DECIMAL_ID? DIGIT (DIGIT DIGIT?)? ;
DECIMAL_NUMBER :
        DECIMAL_BYTE DIGIT DIGIT DIGIT DIGIT+ ;

fragment BINARY_ID :
        ('0b' | '%') ;
fragment BINARY_DIGIT :
        ('0' | '1') ;
BINARY_BYTE :
        BINARY_ID BINARY_DIGIT
        (BINARY_DIGIT
            (BINARY_DIGIT
                (BINARY_DIGIT
                    (BINARY_DIGIT
                        (BINARY_DIGIT
                            (BINARY_DIGIT BINARY_DIGIT?)
                            ?)
                        ?)
                    ?)
                ?)
            ?)?
        ;
BINARY_NUMBER :
        BINARY_ID
        BINARY_DIGIT BINARY_DIGIT BINARY_DIGIT BINARY_DIGIT
        BINARY_DIGIT BINARY_DIGIT BINARY_DIGIT BINARY_DIGIT+
    ;

CHARACTER :
        QUOTE PRINTABLE ;

ORG :
        DOT ('ORG' | 'RORG') ;

EQU :
        ('EQU' | '=') ;

NOP : 'NOP' ;

IMPLIED :
        ( 'PLA' | 'PHP' | 'PHA' | 'PLP' | 'RTI' | 'RTS'
        | 'SEC' | 'CLC' | 'CLI' | 'SEI' | 'INY' | 'DEY'
        | 'TXA' | 'TAX' | 'TAY' | 'TYA' | 'BRK' | 'CLV'
        | 'TSX' | 'TXS' | 'INX' | 'DEX' | 'SED' | 'CLD')
    ;

BRANCH :
        ( 'BPL' | 'BMI' | 'BVC' | 'BVS'
        | 'BCC' | 'BCS' | 'BNE' | 'BEQ')
    ;

SHIFT : ('ASL' | 'LSR' | 'ROL' | 'ROR') ;

JUMP : ('JMP') ;

JSR : ('JSR') ;

fragment LOAD : ('LDY' | 'LDA' | 'LDX') ;

fragment STORE : ('STA' | 'STY' | 'STX') ;

fragment COMPARE : ('CPY' | 'CPX' | 'CMP') ;

fragment LOGIC : ('AND' | 'ORA' | 'EOR' | 'BIT') ;

fragment ARITH : ('ADC' | 'SBC') ;

fragment INC : ('INC' | 'DEC') ;

MNEMONIC : (LOAD | STORE | COMPARE | LOGIC | ARITH | INC) ;

ILLEGAL :
        ( 'JAM' | 'SLO' | 'ANC' | 'RLA' | 'SRE'
        | 'ALR' | 'RRA' | 'ARR' | 'SAX' | 'ANE'
        | 'SHA' | 'TAS' | 'SHY' | 'SHX' | 'LAX'
        | 'LXA' | 'LAS' | 'DCP' | 'SBX' | 'ISB'
        | 'USB'
        ) ;

ACC: 'A' ;

SYMBOL :
        IDENTIFIER ;

/*
 * Parser Rules
 */

program : line+ EOF ;

line :
        WHITESPACE? label WHITESPACE instruction WHITESPACE? comment NEWLINE |
        WHITESPACE? label WHITESPACE instruction WHITESPACE? NEWLINE |
        WHITESPACE? label WHITESPACE? comment NEWLINE |
        WHITESPACE? label WHITESPACE? NEWLINE |
        WHITESPACE? (label WHITESPACE)? assign |
        WHITESPACE? instruction WHITESPACE? comment NEWLINE |
        WHITESPACE? instruction WHITESPACE? NEWLINE |
        WHITESPACE? comment? NEWLINE |
        WHITESPACE? assign comment? NEWLINE
    ;

label :
        AT? SYMBOL COLON?
    ;

assign :
        SYMBOL WHITESPACE EQU WHITESPACE arithmetic
    ;

instruction : nop
    | implicit
    | acc
    | immediate
    | x_index
    | y_index
    | x_indirect
    | indirect_y
    | absolute
    | relative
    | jump
    | jsr
    ;

comment : COMMENT ;

nop : NOP ;

implicit : IMPLIED ;

acc : shift (WHITESPACE ACC)? ;

immediate :
        mnemonic WHITESPACE HASH arithmetic
    ;

x_index :
        (shift | mnemonic) WHITESPACE arithmetic X_INDEX
    ;

y_index :
        (shift | mnemonic) WHITESPACE arithmetic Y_INDEX
    ;

x_indirect :
        LPAREN (shift | mnemonic) WHITESPACE arithmetic X_INDEX RPAREN
    ;

indirect_y :
        LPAREN (shift | mnemonic) WHITESPACE arithmetic RPAREN Y_INDEX
    ;

absolute :
        (shift | mnemonic) WHITESPACE arithmetic
    ;

relative : BRANCH WHITESPACE arithmetic ;

mnemonic : MNEMONIC ;

shift : SHIFT ;

jump :
        JUMP WHITESPACE arithmetic |
        JUMP WHITESPACE LPAREN arithmetic RPAREN
    ;

jsr :
        JSR WHITESPACE arithmetic ;

arithmetic :
        LBRACKET arithmetic+ RBRACKET
    |   number binary_expression*
    ;

binary_expression :
        binary_op number
    ;

binary_op : (PLUS | MINUS | STAR | SLASH) ;

unary_op :
        (LOW_BYTE_VALUE | HIGH_BYTE_VALUE | PLUS | MINUS | STAR) ;

// byte_op :
//         (LOW_BYTE_VALUE | HIGH_BYTE_VALUE) ;

number :
        unary_op? (byte | multibyte | character | SYMBOL)
    ;
byte :
        (HEX_BYTE | DECIMAL_BYTE | OCTAL_BYTE | BINARY_BYTE)
    ;
multibyte :
        (HEX_NUMBER | DECIMAL_NUMBER | OCTAL_NUMBER | BINARY_NUMBER)
    ;
character :
        CHARACTER
    ;
