	.global _start
	.data
	  noError: .string "No error          "
		ch1: .string "Check bit 1 (C1)  "
		ch2: .string "Check bit 2 (C2)  "
		ch4: .string "Check bit 4 (C4)  "
		ch8: .string "Check bit 8 (C8)  "
		ch16: .string "Check bit 16 (C16)"
		db1: .string "Data bit 1 (D1)   "
		db2: .string "Data bit 2 (D2)   "
		db3: .string "Data bit 3 (D3)   "
		db4: .string "Data bit 4 (D4)   "
		db5: .string "Data bit 5 (D5)   "
		db6: .string "Data bit 6 (D6)   "
		db7: .string "Data bit 7 (D7)   "
		db8: .string "Data bit 8 (D8)   "
		db9: .string "Data bit 9 (D9)   "
		db10: .string "Data bit 10 (D10) "
		db11: .string "Data bit 11 (D11) "
		db12: .string "Data bit 12 (D12) "
		db13: .string "Data bit 13 (D13) "
		db14: .string "Data bit 14 (D14) "
		db15: .string "Data bit 15 (D15) "
		db16: .string "Data bit 16 (D16) "
		errorString: .quad noError, ch1, ch2, db1, ch4, db2, db3, db4, ch8, db5, db6, db7, db8, db9, db10, db11, ch16, db12, db13, db14, db15, db16
		inLengthM: .string "Enter the length of data M = "
		inString: .string "%d"
		inQuad: .quad 0
		inMBits: .string "Enter %d bit data M = "
		inStrBits: .string "%s"
		inSpace: .space 17
		inQuad_bits: .quad 0
		outMBits: .string "\nGiven data bits M:"
		outMLabel: .string "D%02d "
		outBits: .string " %d  "
		outK: .string "Check bits required K = %d\n"
		outQuad: .quad 4
		outString: .string "Check bits (Hamming Code) K:"
		outKLabel: .string "C%02d "
		outQuadBits: .quad 0
		outMKBits: .string "Data stored in the memory along with check bits (M + K):"
		outQuadZ: .quad 0
		bNumber: .string "Enter bit number: "
		bString: .string "%d"
		bQuad: .quad 0
		nbValue: .string "Bit %d new value (0/1): "
		nbString: .string "%d"
		nbQuad: .quad 0
		outMKBitsError: .string "M + K bits with single bit error:"
		outStringBitsK: .string "Recomputed check bits K:"
		outQuadBitsK: .quad 0
		outSyndrome: .string "Syndrome word:"
		outQuadSyndrome: .quad 0
		bError: .string "Error in bit position "
		bErrorbit: .string "%d"
		outError: .string " - %d: %s\n"
		nextLine: .string "\n"
		nextLineDouble: .string "\n\n"
	.text
displayBits:
	bitsIteration:	
		pushq %rcx
		pushq %rax
		pushq %rdx
		movq %rdx, %rdi
		movq $1, %rsi
		subq $1, %rcx
		shlq %cl, %rsi
		andq %rax, %rsi
		jnz else1
		movq $0, %rsi
		jmp endif1
	else1:	movq $1, %rsi
	endif1:	xorq %rax, %rax
		call printf
		popq %rdx
		popq %rax
		popq %rcx
		decq %rcx
		jnz bitsIteration
		ret
displayKLabels:
	pushq %rcx
	subq $1, %rcx		
	movq $1, %rax		
	shlq %cl,%rax
	popq %rcx
lLabels2:
	pushq %rax
	pushq %rcx
	movq $outKLabel, %rdi
	movq %rax, %rsi
	xorq %rax, %rax
	call printf
	popq %rcx
	pop %rax
	shrq $1, %rax
	decq %rcx
	jnz lLabels2
	movq $nextLine, %rdi
	xorq %rax, %rax
	call printf
	ret
displayLabels:
	pushq %r8
	movq %rbx, %rcx		
	subq $1, %rcx		
	movq $1, %r8		
	shlq %cl, %r8		
	movq %rax, %rcx		
	addq %rbx, %rcx		
lLabels3:
	movq %rcx, %rdx		
	subq $1, %rdx		
	andq %rcx, %rdx		
	jnz else5
	movq $outKLabel, %rdi
	movq %r8, %rsi		
	shrq $1, %r8		
	jmp endif5
else5:	movq $outMLabel, %rdi	
	movq %rax, %rsi		
	decq %rax		
endif5:	pushq %r8
	pushq %rax
	pushq %rcx
	xorq %rax, %rax
	call printf
	popq %rcx
	popq %rax
	popq %r8
	decq %rcx
	jnz lLabels3
	popq %r8
	movq $nextLine, %rdi
	xorq %rax, %rax
	call printf
	ret
_start:
	movq $inLengthM, %rdi
	xorq %rax, %rax
	call printf
	movq $inString, %rdi
	movq $inQuad, %rsi
	xorq %rax, %rax
	call scanf
	movq $inMBits, %rdi
	movq inQuad, %rsi
	xorq %rax, %rax
	call printf
	movq $inStrBits, %rdi
	movq $inSpace, %rsi
	xorq %rax, %rax
	call scanf
	movq $0, %rsi		
	movq $inSpace, %rax	
	movq $0, %rdi		
	movq $1, %rdx		
	movq inQuad, %rcx		
	subq $1, %rcx		
	shlq %cl, %rdx		
	addq $1, %rcx	
lLengthMStr:
	movb (%rax, %rsi), %bl	
	cmpq $48, %rbx		
	je endif8		
	orq %rdx, %rdi		
endif8:	shrq $1, %rdx
	incq %rsi
	decq %rcx
	jnz lLengthMStr
	movq %rdi, inQuad_bits
	movq $outMBits, %rdi
	xorq %rax, %rax
	call puts
	movq inQuad, %rcx
lLabels1:
	pushq %rcx
	movq $outMLabel, %rdi
	movq %rcx, %rsi
	xorq %rax, %rax
	call printf
	popq %rcx
	decq %rcx
	cmp $0, %rcx
	jne lLabels1
	movq $nextLine, %rdi
	xorq %rax, %rax
	call printf
	movq inQuad, %rcx
	movq inQuad_bits, %rax
	movq $outBits, %rdx
	call displayBits
	movq $nextLineDouble, %rdi
	xorq %rax, %rax
	call printf
	movq inQuad, %rax
	cmp $11, %rax
	jle endif2
	movq $5, outQuad
endif2:	
	movq $outK, %rdi
	movq outQuad, %rsi
	xorq %rax, %rax
	call printf
	movq $outString, %rdi
	xorq %rax, %rax
	call puts
	movq inQuad_bits, %r8	
	movq $0, %r9		
	movq inQuad, %rcx		
	addq outQuad, %rcx		
	movq %rcx, outQuadZ	
	movq $1, %rbx		
	movq $1, %rax		
	movq $1, %rsi		
l1:	movq %rsi, %rdx		
	subq $1, %rdx		
	andq %rsi, %rdx		
	jz endif3
	movq %r8, %rdx		
	andq %rbx, %rdx		
	shlq $1, %rbx		
	cmp $0, %rdx	
	je endif3
	orq %rax, %r9
endif3:	shlq $1, %rax
	incq %rsi
	decq %rcx
	jnz l1
	movq %r9, %r10		
	movq $1, %rbx		 
	movq outQuadZ, %r8		
	movq outQuad, %r11		
	movq $0, %r12		
	movq $0, %r14
lPar1:
	movq $0, %r9		
	movq %rbx, %rax		
	movq %rax, %rcx	
	subq $1, %rcx	
	movq $1, %r13	
	shlq %cl, %r13		
	movq %r8, %rcx		
	addq $1, %rcx		
	subq %rbx, %rcx	
lPar2:
	movq %rax, %rdx		
	andq %rbx, %rdx		
	jz endif4		
	movq %r13, %rdx	
	andq %r10, %rdx		
	jz endif4		
	xorq $1, %r9	
endif4:	
    incq %rax
	shlq $1, %r13
	decq %rcx
	jnz lPar2
	movq %r9, %r15		
	movq %rbx, %rcx		
	subq $1, %rcx		
	shlq %cl, %r15		
	orq %r15, %r10		
	movq %r14, %rcx		
	shlq %cl, %r9	
	orq %r9, %r12		
	incq %r14
	shlq $1, %rbx
	decq %r11
	jnz lPar1
	movq %r10, outQuadBits
	movq %r12, outQuadBits
	movq outQuad, %rcx
	call displayKLabels
	movq outQuad, %rcx
	movq outQuadBits, %rax
	movq $outBits, %rdx
	call displayBits
	movq $nextLineDouble, %rdi
	xorq %rax, %rax
	call printf
	movq $outMKBits, %rdi
	xorq %rax, %rax
	call puts
	movq inQuad, %rax
	movq outQuad, %rbx
	call displayLabels
	movq outQuadZ, %rcx
	movq outQuadBits, %rax
	movq $outBits, %rdx
	call displayBits
	movq $nextLineDouble, %rdi
	xorq %rax, %rax
	call printf
	movq $bNumber, %rdi
	xorq %rax, %rax
	call printf
	movq $bString, %rdi
	movq $bQuad, %rsi
	xorq %rax, %rax
	call scanf
	movq $nbValue, %rdi
	movq bQuad, %rsi
	xorq %rax, %rax
	call printf
	movq $nbString, %rdi
	movq $nbQuad, %rsi
	xorq %rax, %rax
	call scanf
	movq outQuadBits, %rdx
	movq bQuad, %rcx
	subq $1, %rcx
	movq $1, %rax
	shlq %cl, %rax
	movq nbQuad, %rbx
	cmpq $0, %rbx
	je else6
	orq %rax, %rdx
	jmp endif6
else6:	
  notq %rax
	andq %rax, %rdx
endif6:	
  movq %rdx, outQuadBits
	movq $outMKBitsError, %rdi
	xorq %rax, %rax
	call puts
	movq inQuad, %rax
	movq outQuad, %rbx
	call displayLabels
	movq outQuadZ, %rcx
	movq outQuadBits, %rax
	movq $outBits, %rdx
	call displayBits
	movq $nextLineDouble, %rdi
	xorq %rax, %rax
	call printf
	movq outQuadBits, %r10	
	movq $1, %rbx		
	movq outQuadZ, %r8		
	movq outQuad, %r11		
	movq $0, %r12		
	movq $0, %r14	
lPar3:
	movq $0, %r9		
	movq %rbx, %rax		
	movq %rax, %rcx		
	subq $1, %rcx		
	movq $1, %r13		
	shlq %cl, %r13		
	movq %r8, %rcx		
	addq $1, %rcx		
	subq %rbx, %rcx	
lPar4:
	movq %rax, %rdx		
	andq %rbx, %rdx		
	jz endif7		
	movq %r13, %rdx		
	andq %r10, %rdx		
	jz endif7		
	xorq $1, %r9
endif7:	
  incq %rax
	shlq $1, %r13
	decq %rcx
	jnz lPar4
	movq %r14, %rcx		
	shlq %cl, %r9		
	orq %r9, %r12		
	incq %r14
	shlq $1, %rbx
	decq %r11
	jnz lPar3
	movq %r12, outQuadSyndrome
	movq outQuadBits, %rax
	movq %rax, %rdx
	xorq %r12, %rdx
	movq %r12, %rbx
	decq %rbx
	andq %r12, %rbx
	jnz endif9
	movq %rax, %rdx
endif9:	
  movq %rdx, outQuadBitsK
	movq $outStringBitsK, %rdi
	xorq %rax, %rax
	call puts
	movq outQuad, %rcx
	call displayKLabels
	movq outQuad, %rcx
	movq outQuadBitsK, %rax
	movq $outBits, %rdx
	call displayBits
	movq $nextLineDouble, %rdi
	xorq %rax, %rax
	call printf
	movq $outSyndrome, %rdi
	xorq %rax, %rax
	call puts
	movq outQuad, %rcx
	call displayKLabels
	movq outQuad, %rcx
	movq outQuadSyndrome, %rax
	movq $outBits, %rdx
	call displayBits
	movq $nextLineDouble, %rdi
	xorq %rax, %rax
	call printf
	movq $bError, %rdi
	xorq %rax, %rax
	call printf
	movq outQuad, %rcx
	movq outQuadSyndrome, %rax
	movq $bErrorbit, %rdx
	call displayBits
	movq outQuadSyndrome, %rax
	movq $errorString, %rbx
	movq (%rbx, %rax, 8), %rdx
	movq $outError, %rdi
	movq outQuadSyndrome, %rsi
	xorq %rax, %rax
	call printf
	movq $60, %rax
	movq $0, %rdi
	syscall
