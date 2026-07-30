# program helloworld.s
.global _start
.data
message: .ascii "Hello World\n"
.text
_start: movq $1, %rax #system call 1 is write
movq $1, %rdi #file handle 1 is stdout
movq $message, %rsi #address of string in memory to output
movq $13, %rdx #number of bytes
syscall #invoke operating system to print
movq $60, %rax #system call 60 is exit
xorq %rdi, %rdi #return code 0
syscall #invoke operating system to exit








