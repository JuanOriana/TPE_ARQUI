
GLOBAL reader
GLOBAL writer
GLOBAL scClear
GLOBAL timeInfo
GLOBAL chFont
GLOBAL drawFig
GLOBAL getMem
GLOBAL getRegs
GLOBAL writeAtPos
GLOBAL timer
GLOBAL opCodeExc
GLOBAL keyBinder

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
    push rsi

    mov rdi, 2
    int 80h
    
    pop rsi
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

; getMem - recibe el valor de memoria en un vecctor
;IN- RDI - buffer
;    RSI - address
;    RDX - bytes
getMem:
    push rbp
    mov rbp,rsp;

    push rdi
    push rsi
    push rdx
    push rcx

    mov rcx ,rdx ;bytes en rdx
    mov rdx, rsi  ;address en rdx
    mov rsi,rdi   ; buff en rsi
    mov rdi,4     ; id int
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
;    RCX - x
;    R8  - y
writeAtPos:
    push rbp
    mov rbp,rsp;

    push rdi
    push rsi
    push rdx
    push rcx
    push r8
    push r9

    mov r9, r8  ;y en r9
    mov r8, rcx ;x en r8
    mov rcx ,rdx ;size en rdx
    mov rdx, rsi  ;buff en rdx
    mov rsi,rdi   ; fd en rsi
    mov rdi,8     ; id int
    int 80h

    pop r9
    pop r8
    pop rcx
    pop rdx
    pop rsi
    pop rdi

    leave
    ret


    
;getRegs - abtiene el valor de los 15 registros
;IN - RDI buffer
getRegs:

    push rbp
    mov rbp,rsp

    push rdi
    push rsi

    mov rsi,rdi
    mov rdi, 5
    int 80h

    pop rsi
    pop rdi
    
    leave
    ret

;timer: inicia o para un timer de funcion f
;IN- RDI - flag de inicio o stop
;    RSI - intervalo de tiempo
;    RDX - funcion
timer:
    push rbp
    mov rbp,rsp;

    push rdi
    push rsi
    push rdx
    push rcx

    mov rcx ,rdx ;function en rcx
    mov rdx, rsi  ;intervalo en rdx
    mov rsi,rdi   ; flag en rsi
    mov rdi,9    ; id int
    int 80h

    pop rcx
    pop rdx
    pop rsi
    pop rdi

    leave
    ret

;keyBinder: bindea una tecla de funcion (F1 o F2) a una funcion
;IN- RDI - flag de bind o unbind
;    RSI - tecla a bindear
;    RDX - funcion
keyBinder:
    push rbp
    mov rbp,rsp;

    push rdi
    push rsi
    push rdx
    push rcx

    mov rcx ,rdx ;function en rcx
    mov rdx, rsi  ;tecla en rdx
    mov rsi,rdi   ; flag en rsi
    mov rdi,10    ; id int
    int 80h

    pop rcx
    pop rdx
    pop rsi
    pop rdi

    leave
    ret

opCodeExc:
    UD2
    ret