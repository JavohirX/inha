.data
        format: .asciz "%s"
        format2: .asciz "%s%ld\n"
        buffer1: .skip 12

.global _start

.text
   	messageForInput: .asciz "Input: \n     Enter the value for n = "
   	messageForOutput: .asciz "Output : \n\t n! = "

    _start:
    									#print
    		movq $1, %rax
            movq $1, %rdi 
            movq $messageForInput, %rsi
            movq $37, %rdx 
            syscall
            							#input

            movq $0, %rax
            movq $0, %rdi
            movq $buffer1, %rsi
            movq $12, %rdx
            syscall
            							#transferring buffer1
            movq $buffer1, %rax 		#rax = string of nums
            movq $1, %r11 				#r11 will be incremented by 10 every time
            xorq %r10, %r10
            xorq %rdx, %rdx
    	digitCounter: 
            movzbl (%rax), %ebx			#if char == 0xa, then it is the end
            movq $0xa, %rcx
            subq %rbx, %rcx
            je obnulenie				#updating indexes
            imulq $10, %r11
            addq $1, %rax
            jmp digitCounter		#end of the loop
    	obnulenie:							#initializing
            movq $buffer1, %rax 		#rax = string of nums
            movq %rax, %r13
            movq $48, %r12
            neg %r12 					#%r12 now has -48
            xorq %r10, %r10
            xorq %rbx, %rbx
            xorq %rcx, %rcx
            movq $10, %r14
            movq %r11, %rax 			#%rax now has a 1000000...
            idivq %r14
    	calculator:
            movzbl (%r13), %ebx
            #if char == 0xa, then it is the end
            movq $0xa, %rcx
            subq %rbx, %rcx
            je _factorialCalc
            							#turning the chars into nums, store in r10
            addq %r12, %rbx
            imulq %rax, %rbx
            addq %rbx, %r10
            							#updating indexes
            idivq %r14
            addq $1, %r13
            jmp calculator			#end of the loop

   	_factorialCalc:
        addq $0, %r10
        jne continueZ1 #if ZF is 0, then this number is 1
        movq $1, %r10
        jmp _done
        continueZ1:
   		movq %r10,  %rdx
   		movq $1, %rcx
		negq %rcx #%rcx now has -1
	   	miniFactorial:
	   		cmpq $1, %r10
	   		je _done
			addq %rcx, %r10	#%r10 contains n-1
			imulq %r10, %rdx #%rdx now contains n(n-1)
			jmp miniFactorial

    _done:	

            movq $format2, %rdi
            movq $messageForOutput, %rsi
            #movq %r10, %rdx 			
            call printf
    		
    _exit:

            movq $60, %rax
            xorq %rdi, %rdi
            syscall
