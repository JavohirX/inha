.data
	msg1: .asciz "------------- \nn = %d\nInput something: \n"
	format1: .asciz "rdx = %d\n"
	buffer1: .skip 10
	list: .quad 1, 2, 3, 4, 5, 6
	n: .quad 6
.global _start
.text
_start:

	#printing asking user for input
	movq $msg1, %rdi
	movq n, %rsi
	call printf

	#taking user input
	movq $0, %rax
	movq $0, %rdi
	movq $buffer1, %rsi
	movq $10, %rdx
	syscall

	movq $0, %rdx
	movq $format1, %rdi
	movq %rdx, %rsi
	call printf

	movq $format1, %rdi
	movq %rdx, %rsi
	call printf

	#exit
	movq $60, %rax
	xorq %rdi, %rdi
	syscall
