#Program asmddd.s for debugging with ddd global_start
.global _start
.text
_start: movq $0x01289AB76EF34567, %rax
movb $-1, %al
movw $-1, %ax
movl $-1, %eax
movq $-1, %rax
movq $0x01289AB76EF34567, %rbx
movb $0xBB, %dl
movb %dl, %bl
movsbq %dl, %rbx
movzbq %dl, %rbx
movq $65535, %rbx
addq %rbx, %rax
subq %rax, %rbx
negq %rbx
subq %rbx, %rax
movq $60000, %rsi
movq $65535, %rdx
movq %rsi, %rax
imulq %rdx
cqto
idivq %rsi
testq %rsi,%rdi
jnz downl
upl: cmpq %rsi,%rdi
setl %al
movzbq %al, %rax
jmp down2
down2: xorq %rax, %rbx
xorq %rbx, %rax
xorq %rax, %rbx
andq %rsi, %rax
orq %rsi, %rax
xorq %rax, %rax
notq %rax
negq %rax
incq %rax
decq %rax
addq $99,%rax
leaq (%rax, %rax, 8), %rax
leaq (%rax, %rax, 4), %rax
salq $3, %rax
negq %rax
sarq %rax
ret