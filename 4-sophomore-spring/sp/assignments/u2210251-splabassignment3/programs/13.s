#U2210134
.global _start
.data
	inp_msg: .string "Encrypted message: " 
	out_msg: .ascii "Decrypted message: %s"
	new_line: .string "\n" 		
	input: .skip 1024
	output: .skip 1024
.text
_start:
	movq $1, %rax		
	movq $1, %rdi	
	movq $inp_msg, %rsi
	movq $20, %rdx
	syscall
	xorq %rax, %rax 		
	xorq %rdx, %rdx
	movq $input, %rsi 
	movq $1023, %rdx
	syscall	
	dec %rax
	movq %rax, %rcx
	movq $input, %rax
	movq $output, %rdx
decrypt:
	movb (%rax), %bl
	subb $10, %bl
	movb %bl, (%rdx)
	inc %rdx
	inc %rax
	dec %rcx
	jnz decrypt
	movq $0, %rax
	movq $out_msg, %rdi
	movq $output, %rsi
	call printf
	movq $60, %rax
	xorq %rdi, %rdi
	syscall
	
