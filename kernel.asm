[BITS 32]

EXTERN scrollup, print
GLOBAL _start

_start:

    push dword msg
    call print
    mov [0xB8B40],eax
    mov byte [0xB8B41],0x57  
    pop  eax


end:
    jmp end

msg  db 'un premier message', 10, 0
msg2 db 'un deuxième message', 10, 0
