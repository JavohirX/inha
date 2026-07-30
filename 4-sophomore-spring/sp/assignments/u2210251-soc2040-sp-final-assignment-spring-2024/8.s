

.data
    #messages
    message: .asciz "Enter the value of n:"
    getNamesMsg: .asciz "Now enter a list of n=%d names(min: 15 chars, max: 1024 chars, no spaces in the name): \n"
    sortedNamesMsg: .asciz "************************************************************* \na)List of names in alphabetical order:"
    reverseSortedNamesMsg: .asciz "************************************************************* \nb)List of names in reverse alphabetical order:"
    inputNameMsg: .asciz "************************************************************* \nc)Enter the name to look for:"
    nameFoundMsg: .asciz "Name found!"
    nameOccurenceMsg: .asciz "Name occurs at position : %d \n"
    nameNotFoundMsg: .asciz "Name not found "
    upperCaseMsg: .asciz "************************************************************* \nd)Convert lowercase to uppercase: \n"
    lowerCaseMsg: .asciz "************************************************************* \ne)Convert uppercase to lowercase: \n"
    words: .asciz "************************************************************* \nf) there are %d words in this list \n"
    chars: .asciz "%d chars in this word \n"
    #formats
    scanSFormat: .asciz "%s"
    randomFormat: .asciz "%s  "
    displaySFormat: .asciz "%s\n"
    scanDFormat: .asciz "%d"
    displayDFormat: .asciz "%d\n"
    
    #vars
    n: .quad 0
    nameArr: .space 1048576
    tempArr: .space 1048576
    searchName: .space 1024
.global _start

.text
    _start:
        movq $displaySFormat, %rdi
        movq $message, %rsi
        call printf

        #taking the value of n
        movq $scanDFormat, %rdi
        movq $n, %rsi
        call scanf 

        #taking n number of names
        movq $getNamesMsg, %rdi
        movq n, %rsi
        call printf

        #start namesInputLoop
        movq $n, %r14
        movq (%r14), %r12
        movq $nameArr, %r13

        namesInputLoop:

        movq $scanSFormat, %rdi
        movq %r13, %rsi
        call scanf

        subq $1, %r12
        addq $1024, %r13

        #check
        addq $0, %r12
        jne namesInputLoop
        #end namesInputLoop

        sorting:
            movq $1000, %rdx
            sortIterationLoop:
                
                pushq %rdx
                pushq %rax

                movq $n, %r12
                movq (%r12), %r14 # r14 = n
                leaq nameArr, %r10 #loading adress
                leaq nameArr, %r11 #loading adress
                addq $1024, %r11
                sortLoop:
                    
                    call swapper
                    
                    addq $1024, %r10
                    addq $1024, %r11
                    subq $1, %r14
                    cmpq $1, %r14
                    jne sortLoop
                
                popq %rax
                popq %rdx
                subq $1, %rdx
                jne sortIterationLoop

        namesDisplay:
            #sorted list:
            movq $displaySFormat, %rdi
            movq $sortedNamesMsg, %rsi
            call printf

            #start namesOutputLoop
            movq $n, %r14
            movq (%r14), %r12
            movq $nameArr, %r13

            namesOutputLoop:

            movq $displaySFormat, %rdi
            movq %r13, %rsi
            call printf

            subq $1, %r12
            addq $1024, %r13

            #check
            addq $0, %r12
            jne namesOutputLoop
            #end namesOutputLoop
        
        
        reverseSorting:
            #reverseSorted list:
            movq $displaySFormat, %rdi
            movq $reverseSortedNamesMsg, %rsi
            call printf

            #values
            movq $n, %r14
            movq (%r14), %r12
            subq $1024, %r13
            reverseNamesLoop:

            movq $displaySFormat, %rdi
            movq %r13, %rsi
            call printf

            subq $1, %r12
            subq $1024, %r13

            #check
            addq $0, %r12
            jne reverseNamesLoop
            #end namesOutputLoop
        
        
        #continue the main
        movq $displaySFormat, %rdi
        movq $inputNameMsg, %rsi
        call printf #told the user to make an input

        movq $scanSFormat, %rdi
        movq $searchName, %rsi
        call scanf #took as an input the name to search

        movq $n, %r14
        movq (%r14), %r12
        movq $nameArr, %r13
        movq $0, %r14
        findNameLoop:

            movq %r13, %rdi
            movq $searchName, %rsi
            call strcmp
            cmpq $0, %rax
            jne next3
            nameFound:
                movq $displaySFormat ,%rdi
                movq $nameFoundMsg ,%rsi
                call printf

                movq $nameOccurenceMsg , %rdi
                movq %r12, %rsi
                call printf
                inc %r14
            next3:

            subq $1, %r12
            addq $1024, %r13

            #check
            addq $0, %r12
            jne findNameLoop
            #end findNameLoop
            
        cmpq $0, %r14
        jne next6
        nameNotFound:
            movq $displaySFormat, %rdi
            movq $nameNotFoundMsg, %rsi
            call printf
        next6:

        
        movq $n, %r14
        movq $30720, %r12
        movq $nameArr, %r13
        

        l2uLoop:
        movq (%r13), %rbx
        movzbl %bl, %rdi
        call toupper

        mov %al, (%r13)

        continue:
        subq $1, %r12
        addq $1, %r13

        #check
        addq $0, %r12
        jne l2uLoop
        #end l2uLoop

        movq $upperCaseMsg, %rdi
        call printf

        upperCaselistPrint:

            #start namesOutputLoop
            movq $n, %r14
            movq (%r14), %r12
            movq $nameArr, %r13

            upperCase:

            movq $displaySFormat, %rdi
            movq %r13, %rsi
            call printf

            subq $1, %r12
            addq $1024, %r13

            #check
            addq $0, %r12
            jne upperCase
            #end upperCase

        

        
        movq $n, %r14
        movq $30720, %r12
        movq $nameArr, %r13
        

        u2lLoop:
        movq (%r13), %rbx
        movzbl %bl, %rdi
        call tolower

        mov %al, (%r13)

        continue2:
        subq $1, %r12
        addq $1, %r13

        #check
        addq $0, %r12
        jne u2lLoop
        #end u2lLoop

        movq $lowerCaseMsg, %rdi
        call printf

        lowerCaselistPrint:

            #start namesOutputLoop
            movq $n, %r14
            movq (%r14), %r12
            movq $nameArr, %r13

            lowerCase:

            movq $displaySFormat, %rdi
            movq %r13, %rsi
            call printf

            subq $1, %r12
            addq $1024, %r13

            #check
            addq $0, %r12
            jne lowerCase
            #end upperCase

        ############################
        
        charCount:

            #start namesOutputLoop
            movq $n, %r14
            movq (%r14), %r12
            movq $nameArr, %r13

            movq $words, %rdi
            movq %r12, %rsi
            call printf

            charCountLoop:

            movq $randomFormat, %rdi
            movq %r13, %rsi
            call printf

            movq %r13, %rdi
            call strlen

            movq $chars, %rdi
            movq %rax, %rsi
            call printf

            subq $1, %r12
            addq $1024, %r13

            #check
            addq $0, %r12
            jne charCountLoop
            #end upperCase
        
        ###############################
        call exit

    swapper:
        pushq %rcx
        pushq %rax
        pushq %rbx
        pushq %rdx
        pushq %r12
        pushq %r13
        pushq %r10
        pushq %r11

        movq %r10, %rbx #loading adress
        movq %r11, %rdx #loading adress

        movq (%rbx), %rax #loading the value
        movq (%rdx), %rcx #loading the value

        cmp $91, %al
        js continue4
        addb $32, %al

        cmp $91, %cl
        js continue4
        addb $32, %cl

        continue4:
        cmpb %al,%cl #next char - char
        js swapProcess
        jg end1
        cmpb %ah,%ch #next char - char
        js swapProcess
        jg end1
        shl $16, %rax
        shl $16, %rcx
        cmpb %al,%cl
        js swapProcess
        end1:

        popq %r11
        popq %r10
        popq %r13
        popq %r12
        popq %rdx
        popq %rbx
        popq %rax
        popq %rcx
        
        ret
        swapProcess:
        movq %r10, %r12
        movq %r11, %r13
        leaq tempArr, %rdi
        movq %r12, %rsi
        call strcpy

        movq %r12, %rdi
        movq %r13, %rsi
        call strcpy

        movq %r13, %rdi
        leaq tempArr, %rsi
        call strcpy

        jmp end1
