;assembly part using x86-64
section .text
    bits 64
    default rel
    global daxpyAsm

daxpyAsm:
   push rdi 
   push r8  
   push rbp 
   mov rbp, rsp 
   add rbp, 16
        xor rbx, rbx    ; initialize for int i in for loop 
        xor r12, r12    ; for vectorX indexing
        xor r13, r13    ; for vectorY indexing (yIndex)
        xor r11, r11    ; for vectorZ indexing (zIndex)
   
        mov r10, 10     ; i = 10
        
   
        ; Function body
        movsd xmm1, xmm0 ; Load the scalar A into XMM1
        mov r12, rdx ; Load the address of vector X into R12
        mov r13, r8 ; Load the address of vector Y into R13
        mov r11, r9  ; Load the address of vector Z into R15

        
perform:
    CMP RBX, R10
    JE END
    movsd xmm2, [r12] ; Load the current element of X into XMM1
    mulsd xmm2, xmm1 ; Multiply the current element of X by the scalar A
    movsd xmm3, [r13] ; Load the current element of Y into XMM2
    addsd xmm2, xmm3 ; Add the result to the current element of Y
    movsd [r11], xmm2 ; Store the result in Z

    add r12, 8 ; Move to the next element in X
    add r13, 8 ; Move to the next element in Y
    add r11, 8 ; Move to the next element in Z
   
    INC RBX
    JMP perform
    
END:
    pop rbp
    pop r8
    pop rdi
    ret


