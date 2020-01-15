[BITS 32]

EXTERN foo
GLOBAL _start

_start:

    mov eax,10
    push eax
    call foo
    mov [0xB8B40], eax
    mov byte [0xB8B41], 0x57

end:
    jmp end

msg  db 'un premier message', 10, 0
msg2 db 'un deuxième message', 10, 0