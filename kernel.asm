[BITS 32]

EXTERN scrollup, print
GLOBAL _start

	section .text
_start:
	
    mov eax, msg
    push eax
    call print
    pop  eax

    mov eax, msg2
    push eax
    call print
    pop  eax

    mov eax,2
    push eax
    call scrollup


end:
    jmp end

	section .data

msg:  db 'un premier message', 10, 0
msg2: db 'un autre message', 10, 0
