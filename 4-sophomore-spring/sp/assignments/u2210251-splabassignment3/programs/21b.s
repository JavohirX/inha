.data
msg9: .string "The key %d is not found in the list \n"
msg10: .string "The key occurs %d times in the list\n"
msg8: .string "The key %d is found at location "
msg1: .string "Enter the size of the list: "
msg3:.string "Enter elements of the list:\n"
msg4: .string "The elements of the list: "
msg7: .string "Average is: %f\n"
msg2: .string "%d in the list\n"
msg5:.string "Enter the key: "
msg6: .string "\nSum is: %d\n"
format1: .string "%d"
format2: .string "%d "
list: .space 1024
key: .quad 0
j: .quad 1
n: .quad 0
i: .quad   
.global _start
.text
_start:
movq $msg1, %rdi 
xorq %rax, %rax
call printf
movq $format1, %rdi           
movq $i, %rsi   
xorq %rax, %rax
call scanf
movq $msg3, %rdi
xorq %rax, %rax
call printf
movq $list, %rdx
movq i, %r8
loop1:  
pushq %rdx 
pushq %r8
movq $format1, %rdi
movq %rdx, %rsi
xorq %rax, %rax
call scanf
popq %r8
popq %rdx
addq $8, %rdx
decq %r8
jnz loop1
movq $msg4, %rdi       
xorq %rax, %rax
call printf
movq $list, %rdx
movq i, %r8
loop2:
pushq %rdx
pushq %r8
xorq %rax, %rax
movq $format2, %rdi      
movq  (%rdx), %rsi    
call printf      
popq %r8
popq %rdx
addq $8, %rdx
decq %r8
jnz loop2
movq $list, %rdx
movq i, %r8
movq $0,%rbx
loop3:
addq (%rdx), %rbx
addq $8, %rdx
decq %r8           
jnz loop3
movq $msg6, %rdi           
movq %rbx, %rsi             
xorq %rax, %rax             
call printf    
movq i, %rcx  
cvtsi2sd %rcx, %xmm1
cvtsi2sd %rbx, %xmm0
divsd %xmm1, %xmm0
movq $msg7, %rdi
mov $1, %eax      
call printf
movq $0,%rax
movq $msg5, %rdi
xorq %rax, %rax
call printf
movq $format1, %rdi
movq $key, %rsi
xorq %rax, %rax
call scanf   
movq $list, %rbx 
movq i, %r8
movq key, %r9
xorq %rax, %rax
movq $0, n
finder:
cmpq %r9, (%rbx)
je continue1
jmp else
continue1:  
pushq %r8
pushq %rbx
pushq %r9
pushq %rax
movq $msg8, %rdi
movq %r9, %rsi
xorq %rax, %rax
call printf
movq $msg2, %rdi
movq j, %rsi
xorq %rax, %rax
call printf
popq %rax
popq %r9
popq %rbx
popq %r8
incq n
else:
incq j 
addq $8, %rbx   
decq %r8  
jnz finder  
cmpq $0, n
jne occured
movq key, %rsi
movq $msg9, %rdi
xorq %rax, %rax
jmp done  
occured:
movq $msg10, %rdi
movq n, %rsi
movq $0,%rax
done:
call printf
movq $60, %rax #exit
xorq %rdi, %rdi
syscall
