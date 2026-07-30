.data
        format: .asciz "%s\n"
        format2: .asciz "%ld\n"
        buffer1: .skip 12
.global _start

.text
        message: .asciz "input, please"
        _start:
                movq $format, %rdi 
                movq $message, %rsi 
                call printf

                movq $0, %rax
                movq $0, %rdi
                movq $buffer1, %rsi
                movq $12, %rdx
                syscall
                #in buffer1 we have the number
                movq $buffer1, %rax #rax = string of nums
                movq $1, %r11 #r11 will be incremented by 10 every time
                movq $48, %r12
                neg %r12 # %r12 now has -48
                xorq %r10, %r10
                xorq %rdx, %rdx

        iterator1:
                movzbl (%rax), %ebx
                #if char == 0xa, then it is the end
                movq $0xa, %rcx
                subq %rbx, %rcx
                je continue1
                
                xorq %rcx, %rcx
                #if char == (-), then continue
                movl $0x2d, %ecx
                subq %rbx, %rcx
                jne continuex1
                addq $1, %rax
                jmp iterator1
                continuex1:

                xorq %rcx, %rcx
                #if char == (+), then continue
                movl $0x2b, %ecx
                subq %rbx, %rcx
                jne continuex2
                addq $1, %rax
                jmp iterator1
                continuex2:
                #turning the chars into nums, store in r10

                addq %r12, %rbx
                imulq %r11, %rbx
                addq %rbx, %r10

                #updating indexes
                imulq $10, %r11
                addq $1, %rax
                jmp iterator1                    #end of the loop
        continue1:
                #initializing
                movq $buffer1, %rax #rax = string of nums
                movq %rax, %r13
                movq $48, %r12
                neg %r12 # %r12 now has -48
                xorq %r10, %r10
                xorq %rbx, %rbx
                xorq %rcx, %rcx
                movq $10, %r14
                movq %r11, %rax #%rax now has a 1000000...
                idivq %r14
        iterator:
                movzbl (%r13), %ebx
                #if char == 0xa, then it is the end
                movq $0xa, %rcx
                subq %rbx, %rcx
                je done

                xorq %rcx, %rcx
                #if char == (-), then %r15 is 1
                movl $0x2d, %ecx
                subq %rbx, %rcx
                jne continue
                movq $1, %r15 # value of r15 decides whether the number is positive or negative
                addq $1, %r13
                jmp iterator
                continue:

                xorq %rcx, %rcx
                #if char == (+), then %r15 is 1
                movl $0x2b, %ecx
                subq %rbx, %rcx
                jne continue2
                addq $1, %r13
                jmp iterator
                continue2:

                #turning the chars into nums, store in r10

                addq %r12, %rbx
                imulq %rax, %rbx
                addq %rbx, %r10
                #updating indexes
                idivq %r14
                addq $1, %r13
                jmp iterator                    #end of the loop

        done:
                movl $1, %ebx
                subq %r15, %rbx
                jne continueF1
                neg %r10
                continueF1:
                movq %r10, %rax
                #we have sign in r15 and the result in r10    
                movq $format2, %rdi
                movq %rax, %rsi
                call printf
        
        _exit:
                movq $60, %rax #exit
                xorq %rdi, %rdi
                syscall
        printE:
                movq $format2, %rdi
                movq %r10, %rsi
                call printf
                jmp _exit
