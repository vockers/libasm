%include "src/libasm.asm"

section .text

global ft_strcpy
ft_strcpy: ; rdi = *dst, rsi = *src
    mov rax, rdi ; set return value to rdi (dst)

.loop:
    cmp byte [rsi], NULL ; check if the current byte is null (end of string)
    jz .exit

    mov dl, [rsi]      ; copy the current byte from src to dst
    mov byte [rdi], dl ;
    inc rdi            ; move to the next byte in dst
    inc rsi            ; move to the next byte in src
    jmp .loop          ; repeat the loop

.exit:
    mov byte [rdi], NULL ; null-terminate the string
    ret
