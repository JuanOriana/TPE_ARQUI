GLOBAL _RTC
SECTION .text

;Param: selector de dato a obtener (segundos, min, etc..)
;Ret: retorna el dato buscado ya convertido a decimal

_RTC:
	push rbp
	mov rbp, rsp

	push rbx
	push rcx
	push rdx
	
	mov rdx,rdi
	mov rcx, 10 ;multiplicador
	mov rbx,0
	mov rax,0
	mov  al, dl ;param
	out 70h, al ;
	in al, 0x71
	mov bx,ax ; copio el resultado
	and ax,0xF0 ;guardo en ax decenas
	and bx, 0x0F ;guardo en bx unidades
	shr	 rax, 4
	mul rcx  ;Trasnformacion a decimal de verdad
	add ax,bx ;resultado total
	pop rdx
	pop rcx
	pop rbx
	leave
	ret

