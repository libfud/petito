parser grammar asm6502Parser;

options {
    tokenVocab = 'asm6502Lexer';
}

program : line+ EOF ;

line :
        WHITESPACE? label WHITESPACE instruction WHITESPACE? comment NEWLINE |
        WHITESPACE? label WHITESPACE instruction WHITESPACE? NEWLINE |
        WHITESPACE? label WHITESPACE? comment NEWLINE |
        WHITESPACE? label WHITESPACE? NEWLINE |
        WHITESPACE? (label WHITESPACE)? assign NEWLINE |
        WHITESPACE? instruction WHITESPACE? comment NEWLINE |
        WHITESPACE? instruction WHITESPACE? NEWLINE |
        WHITESPACE? assign comment? NEWLINE |
        WHITESPACE? directive comment? NEWLINE |
        WHITESPACE? comment? NEWLINE
    ;

label :
        AT? SYMBOL COLON?
    ;

assign :
        SYMBOL WHITESPACE EQU WHITESPACE expression
    ;

instruction : nop
    | implicit
    | acc
    | immediate
    | zero_page
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

immediate : mnemonic WHITESPACE HASH expression ;

zero_page :
        (shift | mnemonic) FORCED_BYTE WHITESPACE expression |
        (shift | mnemonic) WHITESPACE byte ;

x_index :
        (shift | mnemonic) (FORCED_BYTE | FORCED_WORD)? WHITESPACE expression X_INDEX
    ;

y_index :
        (shift | mnemonic) (FORCED_BYTE | FORCED_WORD)? WHITESPACE expression Y_INDEX
    ;

x_indirect :
        (shift | mnemonic) WHITESPACE LPAREN expression X_INDEX RPAREN
    ;

indirect_y :
        (shift | mnemonic) WHITESPACE LPAREN expression RPAREN Y_INDEX
    ;

absolute :
        (shift | mnemonic) FORCED_WORD? WHITESPACE expression
    ;

relative : BRANCH WHITESPACE expression ;

mnemonic : MNEMONIC ;

shift : SHIFT ;

jump :
        JUMP WHITESPACE expression |
        JUMP WHITESPACE LPAREN expression RPAREN
    ;

jsr :
        JSR WHITESPACE expression ;

expression :
        expression binary_op expression
    |   unary_op? LBRACKET expression RBRACKET
    |   atom
    ;

binary_op : (PLUS | MINUS | STAR | SLASH) ;

unary_op : (LOW_BYTE_VALUE | HIGH_BYTE_VALUE | PLUS | MINUS) ;

atom : unary_op? (byte | multibyte | character | SYMBOL | STAR) ;
byte : (HEX_BYTE | DECIMAL_BYTE | OCTAL_BYTE | BINARY_BYTE) ;
multibyte : (HEX_NUMBER | DECIMAL_NUMBER | OCTAL_NUMBER | BINARY_NUMBER) ;
character : CHARACTER ;

directive :
        org |
        byte_directive |
        dbyte_directive |
        word_directive |
        text_directive |
        align_directive |
        fill_directive |
        repeat_directive
    ;

org : DORG WHITESPACE (EQU WHITESPACE)? expression ;

byte_directive : DBYTE byte_directive_value+ ;

dbyte_directive : DDBYTE byte_directive_value+ ;

word_directive : DWORD byte_directive_value+ ;

text_directive : DTEXT WHITESPACE string ;

byte_directive_value :  WHITESPACE expression COMMA? ;

string : DQUOTE stringContents* DQUOTE ;

stringContents : TEXT | ESCAPE_SEQUENCE ;

align_directive : DALIGN (WHITESPACE expression)? ;

fill_directive : DFILL WHITESPACE expression (WHITESPACE expression)? ;

repeat_directive :
        DFILL WHITESPACE (byte | multibyte) WHITESPACE (directive | instruction) ;
