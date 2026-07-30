;
; AssemblerApplication1.asm
;
; Author : hjeong
;

;Stack pointer
.ORG 0
	LDI R16, HIGH(RAMEND)
	OUT SPH, R16
	LDI R16, LOW(RAMEND)
	OUT SPL, R16

MAIN:
	;Set PORTB output
	SBI DDRB, 4
	SBI DDRB, 5

;Loop
L3: 
	SBI PORTB,4
	CBI PORTB,5
	CALL DELAY
	CBI PORTB,4
	SBI PORTB,5
	CALL DELAY
	RJMP L3

;Function
DELAY:
	LDI R20, 20
	D0: LDI R21, 200
		D1: LDI R22, 250
			D2: NOP
				NOP
				DEC R22
				BRNE D2
			DEC R21
			BRNE D1
		DEC R20
		BRNE D0
	RET

;MC = 1 + ((5x250 + 4)x200 + 3)x20 + 4