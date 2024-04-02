section .data

section .text
bits 64
default rel

global daxpyAsm

; Z = RCX
; X = RDX
; Y = R8
; A = XMM3
; size = 5th param (SET TO R10)

daxpyAsm:
    PUSH RBP
    MOV RBP, RSP
    ADD RBP, 16
    MOV R10, qword[RBP+32]  ; R10 will hold the loop counter

    DEC R10     ; Adjust R10 for zero-based indexing

    LOOP:
        MOVSD XMM0, QWORD [RDX + R10*8]  ; Load X[i]
        MULSD XMM0, XMM3                 ; Multiply by A
        ADDSD XMM0, QWORD [R8 + R10*8]    ; Add Y[i]
        MOVSD QWORD [RCX + R10*8], XMM0   ; Store result in Z[i]

        DEC R10
        CMP R10, -1
        JNE LOOP

    POP RBP
    RET
