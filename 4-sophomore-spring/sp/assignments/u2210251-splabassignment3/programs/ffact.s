.global _start
.data
n: .quad 0x0000000000000008
nfact: .quad 0x0000000000000000
.text
_start:
movq n, %rbx
movq %rbx,%rax
call ffact
movq $nfact, %rdi
movq %rax, (%rdi)
movq $60, %rax # system call 60 for exit
xorq %rdi, %rdi # return code 0 syscall
syscall
ffact: cmpq $1, %rbx
je L1
decq %rbx
pushq %rbx
call ffact
popq %rbx
mulq %rbx
L1: ret
