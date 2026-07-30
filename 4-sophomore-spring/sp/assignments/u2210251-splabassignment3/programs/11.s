	.global _start
	.data

		message: .asciz "Enter a string: "
		notpal: .asciz "The given string is not a Palindrome"
		pal: .asciz "The given string is a Palindrome"
		string: .skip 1024
	.text
_start:
	movq $message, %rdi
	call puts
	movq $0, %rdi
	movq $string, %rsi
	movq $1024, %rdx
	movq $0, %rax
	syscall
	movq $string, %rbx
	xorq %rcx, %rcx
	xorq %rdx, %rdx
	movb (%rbx), %cl
	decq %rax
	decq %rax
	movb (%rbx, %rax), %dl
	movq %rax, %r14
	decq %r14
	incq %rax
	movq $1, %r15
	shrq $1, %rax
_find:
	decq %rax
	cmpb %cl, %dl
	jne _statenot

	movb (%rbx, %r15), %cl
	movb (%rbx, %r14), %dl
	incq %r15
	decq %r14
	cmpq $0, %rax
	jne _find

_stateyes:
	movq $pal, %rdi
	call puts
	jmp _end

_statenot:
	movq $notpal, %rdi
	call puts

_end:
	movq $60, %rax
	xorq %rdi, %rdi
	syscall
