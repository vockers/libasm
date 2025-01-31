global ft_strcpy

section .text

ft_strcpy:
    mov rax, rdi ; set return value to rdi (dst)

.loop:
    cmp byte [rsi], 0  ; check if the current byte is null (end of string)
    jz .exit           ; if it is, return rax (dst)
    mov dl, [rsi]      ; copy the current byte from src to dst
    mov byte [rdi], dl ;
    inc rdi            ; move to the next byte in dst
    inc rsi            ; move to the next byte in src
    jmp .loop          ; repeat the loop
    
.exit
    mov byte [rdi], 0 ; null-terminate the string
    ret
