	BRK
	dc.w $3412
	ORA ($12,X)
	dc.b $34
		dc.b $02, $12, $34
		dc.b $03, $12, $34
		dc.b $04, $12, $34
	ORA $12
	dc.b $34
	ASL $12
	dc.b $34
		dc.b $07, $12, $34
	PHP
	dc.w $3412
	ORA #$12
	dc.b $34
	ASL A
	dc.w $3412
		dc.b $0B, $12, $34
		dc.b $0C, $12, $34
	ORA $3412
	ASL $3412
		dc.b $0F, $12, $34
	BPL bpl_dest
	dc.b $34
	ORA ($12),Y
	dc.b $34
		dc.b $12, $12, $34
		dc.b $13, $12, $34
		dc.b $14, $12, $34
	ORA $12,X
	dc.b $34
	ASL $12,X
bpl_dest:
	dc.b $34
		dc.b $17, $12, $34
	CLC
	dc.w $3412
	ORA $3412,Y
		dc.b $1A, $12, $34
		dc.b $1B, $12, $34
		dc.b $1C, $12, $34
	ORA $3412,X
	ASL $3412,X
		dc.b $1F, $12, $34
	JSR $3412
	AND ($12,X)
	dc.b $34
		dc.b $22, $12, $34
		dc.b $23, $12, $34
	BIT $12
	dc.b $34
	AND $12
	dc.b $34
	ROL $12
	dc.b $34
		dc.b $27, $12, $34
	PLP
	dc.w $3412
	AND #$12
	dc.b $34
	ROL A
	dc.w $3412

		dc.b $2B, $12, $34
	BIT $3412
	AND $3412
	ROL $3412
		dc.b $2F, $12, $34
	BMI bmi_dest
	dc.b $34
	AND ($12),Y
	dc.b $34
		dc.b $32, $12, $34
		dc.b $33, $12, $34
		dc.b $34, $12, $34
	AND $12,X
	dc.b $34
	ROL $12,X
bmi_dest:
	dc.b $34
		dc.b $37, $12, $34
	SEC
	dc.w $3412
	AND $3412,Y
		dc.b $3A, $12, $34
		dc.b $3B, $12, $34
		dc.b $3C, $12, $34
	AND $3412,X
	ROL $3412,X
		dc.b $3F, $12, $34
	RTI
	dc.w $3412
	EOR ($12,X)
	dc.b $34
		dc.b $42, $12, $34
		dc.b $43, $12, $34
		dc.b $44, $12, $34
	EOR $12
	dc.b $34
	LSR $12
	dc.b $34
		dc.b $47, $12, $34
	PHA
	dc.w $3412
	EOR #$12
	dc.b $34
	LSR A
	dc.w $3412  
		dc.b $4B, $12, $34
	JMP $3412
	EOR $3412
	LSR $3412
		dc.b $4F, $12, $34
	BVC bvc_dest
	dc.b $34
	EOR ($12),Y
	dc.b $34
		dc.b $52, $12, $34
		dc.b $53, $12, $34
		dc.b $54, $12, $34
	EOR $12,X
	dc.b $34
	LSR $12,X
bvc_dest:
	dc.b $34
		dc.b $57, $12, $34
	CLI
	dc.w $3412
	EOR $3412,Y
		dc.b $5A, $12, $34
		dc.b $5B, $12, $34
		dc.b $5C, $12, $34
	EOR $3412,X
	LSR $3412,X
		dc.b $5F, $12, $34
	RTS
	dc.w $3412
	ADC ($12,X)
	dc.b $34
		dc.b $62, $12, $34
		dc.b $63, $12, $34
		dc.b $64, $12, $34
	ADC $12
	dc.b $34
	ROR $12
	dc.b $34
		dc.b $67, $12, $34
	PLA
	dc.w $3412
	ADC #$12
	dc.b $34
	ROR A
	dc.w $3412
		dc.b $6B, $12, $34
	JMP ($3412)
	ADC $3412
	ROR $3412
		dc.b $6F, $12, $34
	BVS bvs_dest
	dc.b $34
	ADC ($12),Y
	dc.b $34
		dc.b $72, $12, $34
		dc.b $73, $12, $34
		dc.b $74, $12, $34
	ADC $12,X
	dc.b $34
	ROR $12,X
bvs_dest:
	dc.b $34
		dc.b $77, $12, $34
	SEI
	dc.w $3412
	ADC $3412,Y
		dc.b $7A, $12, $34
		dc.b $7B, $12, $34
		dc.b $7C, $12, $34
	ADC $3412,X
	ROR $3412,X
		dc.b $7F, $12, $34
		dc.b $80, $12, $34
	STA ($12,X)
	dc.b $34
		dc.b $82, $12, $34
		dc.b $83, $12, $34
	STY $12
	dc.b $34
	STA $12
	dc.b $34
	STX $12
	dc.b $34
		dc.b $87, $12, $34
	DEY
	dc.w $3412
		dc.b $89, $12, $34
	TXA
	dc.w $3412
		dc.b $8B, $12, $34
	STY $3412
	STA $3412
	STX $3412
		dc.b $8F, $12, $34
	BCC bcc_dest
	dc.b $34
	STA ($12),Y
	dc.b $34
		dc.b $92, $12, $34
		dc.b $93, $12, $34
	STY $12,X
	dc.b $34
	STA $12,X
	dc.b $34
	STX $12,Y
bcc_dest:
	dc.b    $34
		dc.b $97, $12, $34
	TYA
	dc.w $3412
	STA $3412,Y
	TXS
	dc.w $3412
		dc.b $9B, $12, $34
		dc.b $9C, $12, $34
	STA $3412,X
		dc.b $9E, $12, $34
		dc.b $9F, $12, $34
	LDY #$12
	dc.b $34
	LDA ($12,X)
	dc.b $34
	LDX #$12
	dc.b $34
		dc.b $A3, $12, $34
	LDY $12
	dc.b $34
	LDA $12
	dc.b $34
	LDX $12
	dc.b $34
		dc.b $A7, $12, $34
	TAY
	dc.w $3412
	LDA #$12
	dc.b $34
	TAX
	dc.w $3412
		dc.b $AB, $12, $34
	LDY $3412
	LDA $3412
	LDX $3412
		dc.b $AF, $12, $34
	BCS bcs_dest
	dc.b $34
	LDA ($12),Y
	dc.b $34
		dc.b $B2, $12, $34
		dc.b $B3, $12, $34
	LDY $12,X
	dc.b $34
	LDA $12,X
	dc.b $34
	LDX $12,Y
bcs_dest:
	dc.b $34
		dc.b $B7, $12, $34
	CLV
	dc.w $3412
	LDA $3412,Y
	TSX
	dc.w $3412
		dc.b $BB, $12, $34
	LDY $3412,X
	LDA $3412,X
	LDX $3412,Y
		dc.b $BF, $12, $34
	CPY #$12
	dc.b $34
	CMP ($12,X)
	dc.b $34
		dc.b $C2, $12, $34
		dc.b $C3, $12, $34
	CPY $12
	dc.b $34
	CMP $12
	dc.b $34
	DEC $12
	dc.b $34
		dc.b $C7, $12, $34
	INY
	dc.w $3412
	CMP #$12
	dc.b $34
	DEX
	dc.w $3412
		dc.b $CB, $12, $34
	CPY $3412
	CMP $3412
	DEC $3412
		dc.b $CF, $12, $34
	BNE bne_dest
	dc.b $34
	CMP ($12),Y
	dc.b $34
		dc.b $D2, $12, $34
		dc.b $D3, $12, $34
		dc.b $D4, $12, $34
	CMP $12,X
	dc.b $34
	DEC $12,X
bne_dest:
	dc.b $34
		dc.b $D7, $12, $34
	CLD
	dc.w $3412
	CMP $3412,Y
		dc.b $DA, $12, $34
		dc.b $DB, $12, $34
		dc.b $DC, $12, $34
	CMP $3412,X
	DEC $3412,X
		dc.b $DF, $12, $34
	CPX #$12
	dc.b $34
	SBC ($12,X)
	dc.b $34
		dc.b $E2, $12, $34
		dc.b $E3, $12, $34
	CPX $12
	dc.b $34
	SBC $12
	dc.b $34
	INC $12
	dc.b $34
		dc.b $E7, $12, $34
	INX
	dc.w $3412
	SBC #$12
	dc.b $34
	NOP
	dc.w $3412
		dc.b $EB, $12, $34
	CPX $3412
	SBC $3412
	INC $3412
		dc.b $EF, $12, $34
	BEQ beq_dest
	dc.b $34
	SBC ($12),Y
	dc.b $34
		dc.b $F2, $12, $34
		dc.b $F3, $12, $34
		dc.b $F4, $12, $34
	SBC $12,X
	dc.b $34
	INC $12,X
beq_dest:
	dc.b $34
		dc.b $F7, $12, $34
	SED
	dc.w $3412
	SBC $3412,Y
		dc.b $FA, $12, $34
		dc.b $FB, $12, $34
		dc.b $FC, $12, $34
	SBC $3412,X
	INC $3412,X
		dc.b $FF, $12, $34
