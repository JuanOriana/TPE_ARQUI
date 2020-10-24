GLOBAL cpuVendor
GLOBAL intToStr
GLOBAL _inRead

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