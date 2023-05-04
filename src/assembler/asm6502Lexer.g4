lexer grammar asm6502Lexer;

@members {
    int nesting = 0;
}

fragment SEMICOLON : ';' ;

COMMENT : SEMICOLON ~('\r' | '\n')* ;

WHITESPACE : (' ' | '\t')+ ;
NEWLINE : ('\r'? '\n' | '\r')+ ;

fragment UNDERSCORE : '_' ;

PLUS : '+' ;
MINUS : '-' ;
STAR : '*' ;
SLASH : '/' ;
LOW_BYTE_VALUE : '<' ;
HIGH_BYTE_VALUE : '>' ;

LBRACKET : '[' ;
RBRACKET : ']' ;
LPAREN : '(' ;
RPAREN : ')' ;

HASH : '#' ;

COLON : ':' ;

AT : '@' ;

fragment QUOTE : '\'';
fragment DOT : '.';
fragment LETTER : [a-zA-Z] ;
fragment DIGIT : [0-9] ;
fragment IDENTIFIER :
        (LETTER | UNDERSCORE) ((LETTER | DIGIT | UNDERSCORE)*)? ;
fragment PRINTABLE : [\u0032-\u0126] ;

FORCED_BYTE : DOT 'b' ;
FORCED_WORD : DOT 'w' ;

COMMA : ',' ;
X_INDEX : ',X' ;
Y_INDEX: ',Y' ;

fragment OCTAL_ID : ('0o' | AT) ;
fragment OCTAL_DIGIT : [0-7] ;
OCTAL_BYTE :
        OCTAL_ID OCTAL_DIGIT (OCTAL_DIGIT OCTAL_DIGIT?)? ;
OCTAL_NUMBER :
        OCTAL_ID OCTAL_DIGIT OCTAL_DIGIT OCTAL_DIGIT OCTAL_DIGIT+ ;

fragment HEX_ID : ('$' | '&' | '0x') ;
fragment HEX_DIGIT : [0-9a-fA-F] ;
HEX_BYTE :
        HEX_ID HEX_DIGIT HEX_DIGIT? ;
HEX_NUMBER :
        HEX_ID HEX_DIGIT HEX_DIGIT HEX_DIGIT+ ;

fragment DECIMAL_ID : '0d' ;
DECIMAL_BYTE :
        DECIMAL_ID? DIGIT (DIGIT DIGIT?)? ;
DECIMAL_NUMBER :
        DECIMAL_ID? DIGIT DIGIT DIGIT DIGIT+ ;

fragment BINARY_ID : ('0b' | '%') ;
fragment BINARY_DIGIT : ('0' | '1') ;
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

DORG : DOT ('ORG' | 'RORG') ;

DBYTE : DOT 'BYTE' ;

DDBYTE : DOT 'DBYTE' ;

DWORD : DOT 'WORD' ;

DTEXT : DOT 'TEXT' ;

DALIGN : DOT 'ALIGN' ;

DFILL : DOT 'FILL' ;

DREPEAT : DOT 'REPEAT' ;

REPEAT_VAR : 'R%' ;

CHARACTER : QUOTE PRINTABLE ;

EQU : ('EQU' | '=') ;

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

fragment ILLEGAL :
        ( 'JAM' | 'SLO' | 'ANC' | 'RLA' | 'SRE'
        | 'ALR' | 'RRA' | 'ARR' | 'SAX' | 'ANE'
        | 'SHA' | 'TAS' | 'SHY' | 'SHX' | 'LAX'
        | 'LXA' | 'LAS' | 'DCP' | 'SBX' | 'ISB'
        | 'USB'
        ) ;

MNEMONIC : (LOAD | STORE | COMPARE | LOGIC | ARITH | INC) ;

ACC: 'A' ;

SYMBOL :
        IDENTIFIER ;


DQUOTE: '"' -> pushMode(IN_STRING);

mode IN_STRING;

TEXT: ~[\\"]+ ; /* " close quote sequence for syntax highlighting */
ESCAPE_SEQUENCE: '\\' . ;
DQUOTE_IN_STRING: '"' -> type(DQUOTE), popMode;
