.global _start
  .data
    input: .skip 1024
    n: .quad 0
    fmsg: .string "Enter number= "
    line: .string "\n"
    nnum: .string "%ld\n"
    inum: .string "%d"
    sNum: .string "%s"
    resMsg: .string "Number of 1s in given number: %d\n"
  .text
_start:
  	movq $0, %rax
  	movq $fmsg, %rsi
  	movq $sNum, %rdi
  	call printf        
 
	xorq %rax, %rax
	movq $n, %rsi  
  	movq $inum, %rdi
  	call scanf  
  	
  	movq n, %rdi  
  	xorq %rcx, %rcx    
  	call _countfnc
  
  	xorq %rax, %rax
  	movq %rcx, %rsi
  	movq $resMsg, %rdi
  	call printf  
  	  
  	jmp _exit

_countfnc:
  	movq $0, %rax
  	testq %rdi, %rdi      
  	je _rt
  	pushq %rbx
  	movq %rdi, %rbx
  	andq $1, %rbx  
 	shrq %rdi    
  	call _countfnc
  
  	addq %rbx, %rcx  
  	popq %rbx  
_rt:
  	ret  
_exit:
  	call exit
