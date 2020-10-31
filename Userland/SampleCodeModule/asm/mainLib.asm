GLOBAL intToStr
GLOBAL read
GLOBAL write
GLOBAL scClear
GLOBAL timeInfo


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

; read - lee de un fd determinado
; IN- RDI - FD
;    RSI - Buffer
;    RDX - size
read:
    push rbp
    mov rbp,rsp;

    push rdi
    push rsi
    push rdx
    push rcx

    mov rcx ,rdx ;len en rdx
    mov rdx, rsi  ;buff en rdx
    mov rsi,rdi   ; fd en rsi
    mov rdi,0    ; id int
    int 80h

    pop rcx
    pop rdx
    pop rsi
    pop rdi

    leave
    ret


; write - escribe en un fd determinado
;IN- RDI - FD
;    RSI - Buffer
;    RDX - size
write:
    push rbp
    mov rbp,rsp;

    push rdi
    push rsi
    push rdx
    push rcx

    mov rcx ,rdx ;len en rdx
    mov rdx, rsi  ;buff en rdx
    mov rsi,rdi   ; fd en rsi
    mov rdi,1     ; id int
    int 80h

    pop rcx
    pop rdx
    pop rsi
    pop rdi

    leave
    ret

;scClear - Limpia la pantalla
scClear:
    push rbp
    mov rbp,rsp
    push rdi

    mov rdi, 2
    int 80h
    
    pop rdi
    leave
    ret

;chColor - cambia el color de escritura
;IN - RDI - color
chFont:

    push rbp
    mov rbp,rsp
    push rdi
    push rsi

    mov rsi,rdi
    mov rdi, 3
    int 80h
    
    mov rdi

    pop rsi
    pop rdi
    leave
    ret

;timeInfo - obtiene info del tiempo
;IN - RDI selector de data
timeInfo:

    push rbp
    mov rbp,rsp
    push rdi
    push rsi

    mov rsi,rdi
    mov rdi, 6
    int 80h
    
    mov rdi

    pop rsi
    pop rdi
    leave
    ret