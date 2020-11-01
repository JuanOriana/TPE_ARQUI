
GLOBAL reader
GLOBAL writer
GLOBAL scClear
GLOBAL timeInfo
GLOBAL chFont
GLOBAL drawFig


; read - lee de un fd determinado
; IN- RDI - FD
;    RSI - Buffer
;    RDX - size
reader:
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
writer:
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


; write - escribe en un fd determinado
;IN- RDI - FD
;    RSI - fig
drawFig:
    push rbp
    mov rbp,rsp;

    push rdi
    push rsi
    push rdx

    mov rdx, rsi  ;fig en rdx
    mov rsi,rdi   ; fd en rsi
    mov rdi,7     ; id int
    int 80h

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

    pop rsi
    pop rdi
    leave
    ret

