section .data
stencilSumSet dq 0.0

section .text
bits 64
default rel

global daxpyAsm

daxpyAsm:
    push rsi
    push rbx
    push r14
    push r15
    push rbp 
    mov rbp, rsp
    add rbp, 16
    add rbp, 32 

    lea r14, [rcx]					;pointer to X
    lea r15, [rdx]					;pointer to Y
    mov r10, r8			                         ;stencil loop
    mov r11, 0						;counter of stencil loop
    movsd xmm0, [stencilSumSet]				;stencil window sum

initialize:
    mov rcx, 7
loopX:
    movsd xmm1, [r14]
    addsd xmm0, xmm1
    add r14, 8
    loop loopX

    movsd [r15], xmm0	;write to Y
    add r15, 8 		;inc pointer to Y

    inc r11
    cmp r10, r11
    jz tapos

    mov rcx, 6

resetLoopX:
    sub r14, 8
    loop resetLoopX
    movsd xmm0, [stencilSumSet] ;reset stencil window sum
    jmp initialize
	
tapos:
     pop rbp
     pop r14
     pop r15
     pop rbx
     pop rsi

ret 