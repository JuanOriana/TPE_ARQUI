GLOBAL cpuVendor
GLOBAL intToStr
GLOBAL _inRead
GLOBAL _getReg
GLOBAL _getMem

section .text
	
cpuVendor:
	push rbp
	mov rbp, rsp

	push rbx

	mov rax, 0
	cpuid


	mov [rdi], ebx
	mov [rdi + 4], edx
	mov [rdi + 8], ecx

	mov byte [rdi+13], 0

	mov rax, rdi

	pop rbx

	mov rsp, rbp
	pop rbp
	ret

; -----------------------------------------------------------------------------
; intToStr -- Convert a binary interger into an string
;  IN:   RSI = binary integer
;   RDI = location to store string
; OUT:   RAX = points to end of string
;   All other registers preserved
; Min return value is 0 and max return value is 18446744073709551615 so your
; string needs to be able to store at least 21 characters (20 for the digits
; and 1 for the string terminator).
; Adapted from http://www.cs.usfca.edu/~cruse/cs210s09/rax2uint.s
intToStr:
	push rbp
	mov rbp, rsp
	push rdx
	push rcx
	push rbx
	push rdi
	push rsi

	mov rax,rsi
	mov rbx, 10               ; base of the decimal system
	xor ecx, ecx               ; number of digits generated
	intToStr_next_divide:
	xor edx, edx               ; RAX extended to (RDX,RAX)
	div rbx                  ; divide by the number-base
	push rdx               ; save remainder on the stack
	inc rcx                  ; and count this remainder
	cmp rax, 0               ; was the quotient zero?
	jne intToStr_next_divide      ; no, do another division

	intToStr_next_digit:
	pop rax                  ; else pop recent remainder
	add al, '0'               ; and convert to a numeral
	stosb                  ; store to memory-buffer
	loop intToStr_next_digit      ; again for other remainders
	xor al, al
	stosb                  ; Store the null terminator at the end of the string

	mov rax,rdi
	pop rsi
	pop rdi
	pop rbx
	pop rcx
	pop rdx
	leave
	ret

_inRead:
	push rbp
	mov rbp, rsp
	push rdx
	mov rax, 0
	mov rdx, rdi
	in al, dx
	pop rdx
	leave
	ret

_getReg:
    push rbp
    mov rbp, rsp
   
    cmp rdi, 0
    je .getRAX

    cmp rdi, 1
    je .getRBX

    cmp rdi, 2
    je .getRCX

    cmp rdi, 3
    je .getRDX

    cmp rdi, 4
    je .getRBP

    cmp rdi, 5
    je .getRDI

    cmp rdi, 6
    je .getRSI

    cmp rdi, 7
    je .getR8

    cmp rdi, 8
    je .getR9

    cmp rdi, 9
    je .getR10

    cmp rdi, 10
    je .getR11

    cmp rdi, 11
    je .getR12

    cmp rdi, 12
    je .getR13

    cmp rdi, 13
    je .getR14

    cmp rdi, 14
    je .getR15
  

    .exit:
        mov rsp, rbp
        pop rbp
        ret

    .getRAX:
        jmp .exit
	
    .getRBX:
        mov rax, rbx
        jmp .exit

   .getRCX:
        mov rax, rcx
        jmp .exit

   .getRDX:
        mov rax, rdx
        jmp .exit

    .getRBP:
        mov rax,rbp
         jmp .exit

    .getRDI:
        mov rax, rdi
        jmp .exit

   .getRSI:
        mov rax, rsi
        jmp .exit

    .getR8:
        mov rax, r8
        jmp .exit
    .getR9:
        mov rax, r9
        jmp .exit

    .getR10:
        mov rax, r10
        jmp .exit

    .getR11:
        mov rax, r11
        jmp .exit
    .getR12:
        mov rax, r12
        jmp .exit

    .getR13:
        mov rax, r13
        jmp .exit

    .getR14:
        mov rax, r14
        jmp .exit
    
    .getR15:
        mov rax, 255
        jmp .exit

_getMem;
    push rbp
	mov rbp,rsp

	mov al, byte[rdi]

	mov rsp,rbp
	pop rbp
	ret