.global _start
.data
	input: .string "Enter a string: "
	output: .string "Output: "
	str: .skip 8192
	strF: .asciz "%s"
	newLine: .string "\n"
.text
_start:
	movq $1, %rax
	movq $1, %rdi
	movq $input, %rsi
	movq $16, %rdx
	syscall
	xorq %rax, %rax
	movq $0, %rdi
	movq $str, %rsi
	movq $1024, %rdx
	syscall
	movq %rax, %r8
	subq $1, %r8
	movq $0, %r9
	push str
	push %r8
	movq $str, %rbx
	callLowerCase:
	call .lowerCase
	call printText
	pop %r8
	pop str
	movq $str, %rbx
	movq $0, %r9
	push str
	push %r8
	callUpperCase:
	call .upperCase
	call printText
	pop %r8
	pop str
	movq $str, %rbx
	movq $0, %r9
	movq $0, %r15
	callCapital:
	call .capital
	call printText
end:
	movq $60, %rax
	xorq %rdi, %rdi
	syscall
printText:
	xorq %rax, %rax
	movq $output, %rdi
	call puts
	xorq %rax, %rax
	movq $strF, %rdi
	movq $str, %rsi
	call printf
	ret
.lowerCase:
	movb (%rbx, %r9), %dl
	cmp $65, %dl
	jl lElse
	cmp $90, %dl
	jg lElse
	add $32	, %dl
	cmp %r9, %r8
	je return
	movb %dl, (%rbx, %r9)
	incq %r9
	jmp .lowerCase
	lElse:
		cmp %r9, %r8
		je return
		incq %r9
		jmp .lowerCase
.upperCase:
	movb (%rbx, %r9), %dl
	cmp $97, %dl
	jl upperElse
	cmp $122, %dl
	jg upperElse
	sub $32	, %dl
	cmp %r9, %r8
	je return
	movb %dl, (%rbx, %r9)
	incq %r9
	jmp .upperCase
	upperElse:
		cmp %r9, %r8
		je return
		incq %r9
		jmp .upperCase
.capital:
	movb (%rbx, %r9), %dl
	cmp $32, %dl
	je letterSpace
	cmp $0, %r15
	je letterUpperCase
	jmp letterLowerCase
letterUpperCase:
	movq $1, %r15
	cmp $97, %dl
	jl capitalElse
	cmp $122, %dl
	jg capitalElse
	sub $32, %dl
	cmp %r9, %r8
	je return
	movb %dl, (%rbx, %r9)
	incq %r9
	jmp .capital
letterLowerCase:
	cmp $65, %dl
	jl capitalElse
	cmp $90, %dl
	jg capitalElse
	add $32, %dl
	cmp %r9, %r8
	je return
	movb %dl, (%rbx, %r9)
	incq %r9
	jmp .capital
letterSpace:
	cmp %r9, %r8
	je return	
	incq %r9
	movq $0, %r15
	jmp .capital
	capitalElse:
		cmp %r9, %r8
		je return
		incq %r9
		jmp .capital
return: 
	ret	
		
		
		
		
		
		
		
		










