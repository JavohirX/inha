#U2210134
.global _start
.data
	print: .string "Please enter a message: \n"
	input: .string "%[^\n]s"
	denied: .skip 100
	original: .string "Entered message: %s\n"
	denied_encripted: .skip 100
	output_encripted: .string "Encrypted message: %s\n"
.text
_start:
	pushq %rbp
	subq $8, %rsp
	movq $print, %rdi
	movq $0, %rax
	call printf
	movq $input, %rdi
	movq $denied, %rsi
	movq $0, %rax
	call scanf
	movq $original, %rdi
	movq $denied, %rsi
	movq $0, %rax
	call printf
	movq $denied, %rsi
	movq $denied_encripted, %rdi
iter:	
	movb (%rsi), %al
	cmpq $0, %rax
	je enditer
	addb $10, %al
	movb %al, (%rdi)
	incq %rdi
	incq %rsi
	jmp iter
enditer:	
	movq $0, (%rdi)
	movq $output_encripted, %rdi
	movq $denied_encripted, %rsi
	movq $0, %rax
	call printf
	popq %rbp
	movq $60, %rax
	xorq %rdi, %rdi
	syscall
	
	
