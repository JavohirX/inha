.global _start
  .data
    
        resMsg: .string "The prime numbers between 1 and %d are: 1" # include 1 beacuse it is in any set of prime numbers  
        userMsg: .string "Enter value for n: "
    
        ofrmt: .string " %d"
        sfrmt: .string "%s"
        n: .quad 0
        infrmt: .string "%d"
        input: .skip 1024
        nfrmt: .string "\n"  

  .text
_start:
    movq $0, %rax
    movq $userMsg, %rsi
    movq $sfrmt, %rdi
    call printf 

    movq $0, %rax
    movq $n, %rsi
    movq $infrmt, %rdi      # reading number
    call scanf
    movq $0, %rax
    movq n, %rsi
    movq $resMsg, %rdi
    call printf  
    movq $2, %r8      
_l1:
    movq $0, %rcx      
    movq $1, %r9  
    
_l2:
    movq $0, %rdx  
    movq %r8, %rax      
    movq %r9, %rbx      
    idivq %rbx        
    cmpq $0, %rdx  
    jne _upJ

_incCounter:
    incq %rcx

_upJ:
    cmpq %r8, %r9
    je _verI
    incq %r9  
    jmp _l2          # skipping to inner loop

_verI:
    cmpq $2, %rcx  
    jne _npCase

_pCase:
    pushq %r8
    movq %r8, %rsi
    movq $0, %rax
    movq $ofrmt, %rdi
    call printf
    popq %r8
    jmp _upI
 
_npCase:
    jmp _upI

_upI:
    cmpq n, %r8
    je exit    
    incq %r8  
    jmp _l1

_exit:
    movq $'', %rsi
    movq $0, %rax
    movq $nfrmt, %rdi
    call printf
    call exit
    
