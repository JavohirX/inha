.data
key: .quad 32
loop: .quad 1 
counter: .quad 20 
i: .quad 0  
format1:  .string "%d  \n" 
message1: .string "The elements of the list: "
message2: .string "\nSum is:  %d\n"
message4: .string "Key %d is found at location "
message5: .string " %d in the list\n"
message7: .string "Key %d is not found in the list\n"
message6: .string "Key occurs %d times in the list\n"
message3: .string "Average is: %lf\n"
array: .quad 12, 23, 32, 84, 121, 34, 23, 32, 93, 22, 56, 32, 948, 123, 99, 23, 32, 289, 99, 34
.global _start
.text
_start:
movq $1,%rax  
movq $message1, %rdi
call printf
movq $array, %rdx
movq counter, %rcx
loop1:
pushq %rdx         
pushq %rcx         
xorq %rax,%rax 
movq $format1, %rdi 
movq (%rdx), %rsi        
call printf        
popq %rcx
popq %rdx
addq $8, %rdx       
decq %rcx  
jnz loop1
movq $0,%rbx
movq $array, %rdx       
movq counter,%rcx
loop2:
addq (%rdx), %rbx
addq $8, %rdx
decq %rcx
jne loop2
pushq %rbp
movq $message2, %rdi          
movq %rbx, %rsi              
xorq %rax, %rax               
call printf      
popq %rbp
movq counter, %rcx  
cvtsi2sd %rcx, %xmm1
cvtsi2sd %rbx, %xmm0
divsd %xmm1, %xmm0
movq $message3, %rdi
mov $1, %eax
call printf
xorq %rax, %rax
movq counter, %rcx
movq $array, %rbx 
movq key, %rsi
xorq %rax, %rax
loop3:
cmpq %rsi, (%rbx)
je _L1
jmp else
_L1:  
pushq %rcx
pushq %rbx
pushq %rsi
pushq %rax
movq $message4, %rdi
xorq %rax,%rax
call printf
movq $message5, %rdi
movq loop, %rsi
xorq %rax, %rax
call printf
popq %rax
popq %rsi
popq %rbx
popq %rcx
incq i
else:
incq loop
addq $8, %rbx
decq %rcx
jnz loop3
cmpq $0, i      
jne occurence
movq key, %rsi
movq $message7, %rdi
xorq %rax,%rax
jmp done  
occurence:
movq $message6, %rdi
movq i, %rsi
xorq %rax,%rax 
done:
call printf
call exit