.global _start
.section .data
input_msg: .string "Enter a string of binary number (maximum 64 bits): "
error_msg: .string "Error,enter binary(max 64 bits!)\n"
format: .string "The integer value is %ld\n"
input: .skip 64
.section .bss
.lcomm input_len, 8
.section .text
_start:
	movq $input_msg, %rdi
	call puts
	movq $0, %rax
	movq $0, %rdi
	movq $input, %rsi
	movq $65, %rdx
	syscall
	movq %rax, input_len
	movq input_len, %rcx
	cmpq $65, %rcx
	jg _error
	movq $0, %rax
	movq $input, %rsi
_bin2integer:
	movb (%rsi), %cl
	cmpb $10, %cl
	je _print
	subb $'0', %cl
	shlq $1, %rax
	orq %rcx, %rax
	incq %rsi
	jmp _bin2integer
_error:
	movq $error_msg, %rdi
	call puts
	jmp _exit
_print:
	movq %rax, %rsi
	movq $format, %rdi
	movq $0, %rax
	call printf
_exit:
	movq $60, %rax
	xorq %rdi, %rdi
	syscall
