.global _start
  .data
    x:  .space 10,0
    ostr: .asciz "%ld\n"
    eltext: .asciz "Enter an element:  " 
    msg: .asciz "Number of integers: "
    f: .asciz "%ld"
    format: .asciz "%ld\n"
    input: .skip 1024
  .text
  
_numtext: 
  movq $1 , %rax
  movq $1 , %rdi
  movq $msg , %rsi
  movq $21, %rdx
  syscall
  ret

_exit:
  movq $60, %rax
  xorq %rdi ,%rdi
  syscall
  ret


_start:
  
  call _numtext

  xorq %rax, %rax
  movq $f, %rdi
  movq $x, %rsi
  call scanf 
  
  movq $x, %r11
  movq $0, %r9
  movq (%r11) , %r8

_tIntergers:
  pushq %r8
  pushq %r9
  movq $1 , %rax
  movq $1 , %rdi
  movq $eltext , %rsi
  movq $18, %rdx
  syscall  
  movq $0, %rax
  movq $f, %rdi
  leaq input(,%r9,8), %rsi
  call scanf  
  popq %r9
  popq %r8
  incq %r9
  decq %r8

jnz _tIntergers
  movq x, %rdx
  movq %rdx,%r8
  movq %r8, %r9 
  xorq %rsi, %rsi
  xorq %rdi , %rdi

_l1:
  movq %rdx ,%r9
  movq input(,%rdi,8), %rax
  movq %rdi , %rsi
  incq %rsi
  subq %rsi , %r9
  jz _r
_l2:
  movq input(,%rsi,8), %rcx
  cmpq %rcx, %rax
  jl _ns
  movq %rcx , input(,%rdi,8)
  movq %rax , input(,%rsi,8)
  movq input(,%rdi,8), %rax
  movq input(,%rsi,8), %rcx
_ns: 
  incq %rsi
  decq %r9
  jnz _l2
  incq %rdi
  decq %r8
  jnz _l1
_r:
  movq x, %rcx
  movq $0,%r8
_rint:
  pushq %rcx
  pushq %r8  
  movq $ostr, %rdi
  movq input(,%r8,8), %rsi
  xorq %rax, %rax
  call printf  
  popq %r8
  popq %rcx  
  incq %r8
  decq %rcx
  jnz _rint
  
  call _exit
