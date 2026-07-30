.global _start
	.data
		inputMessage: .string "Enter a string (max: 1024 chars): "
		numberMessage: .string "Numbers: %d\n"
		alphabetMessage: .string "Alphabets: %d\n"
		specialCharactersMessage: .string "Special characters: %d\n"
		totalCharactersMessage: .string "Total Characters: %d\n"
		totalWordMessage: .string "Total Words: %d\n"
		newLine: .string "\n"
		stringFormat: .string "%s\n"
		numberFormat: .string "%d\n"
		skip: .skip 1024
		numberCount: .quad 0
		alphabetCount: .quad 0
		specialCharactersCount: .quad 0
		charactersCount: .quad 0
		wordCount: .quad 0
.text
_start:
	xorq %rax, %rax
	movq $inputMessage, %rsi
	movq $stringFormat, %rdi
	call printf
	xorq %rax, %rax
	movq $0, %rdi
	movq $skip, %rsi
	movq $1025, %rdx
	syscall
	decq %rax
	decq %rax
	movq %rax, %rcx
	movq $0, %r8
	movq $0, %r9
	movq $0, %r10
	movq $0, %r11
	movq $1, %r12
_loop:
	xorq %rax, %rax
	movb (%rsi), %al
_lowerCase:
	cmpb $97, %al
	jl _upperCase
	cmpb $122, %al
	jg _specialCharacter
	jmp _incrementAlphabet
_upperCase:
	cmpb $65, %al
	jl _number
	cmpb $90, %al
	jg _specialCharacter
	jmp _incrementAlphabet
_number:
	cmpb $48, %al
	jl _specialCharacter
	cmpb $57, %al
	jg _specialCharacter
	jmp _incrementNumber
_specialCharacter:
	incq %r10
	incq %r11
	cmpb $32, %al
	jne _updateCharacter
_incrementWord:
	incq %r12
	jmp _updateCharacter
_incrementNumber:
	incq %r9
	incq %r11
	jmp _updateCharacter
_incrementAlphabet:
	incq %r8
	incq %r11
	jmp _updateCharacter
_updateCharacter:
	cmpq $0, %rcx
	je _printResults
	incq %rsi
	decq %rcx
	jmp _loop
_printResults:
	movq %r8, alphabetCount
	movq %r9, numberCount
	movq %r10, specialCharactersCount
	movq %r11, charactersCount
	movq %r12, wordCount
	xorq %rax, %rax
	movq alphabetCount, %rsi
	movq $alphabetMessage, %rdi
	call printf
	xorq %rax, %rax
	movq specialCharactersCount, %rsi
	movq $specialCharactersMessage, %rdi
	call printf
	xorq %rax, %rax
	movq numberCount, %rsi
	movq $numberMessage, %rdi
	call printf
	xorq %rax, %rax
	movq charactersCount, %rsi
	movq $totalCharactersMessage, %rdi
	call printf
	xorq %rax, %rax
	movq wordCount, %rsi
	movq $totalWordMessage, %rdi
	call printf
_exit:
	call exit
	
	
		
	
	
