%include "src/libasm.asm"

section .text

global ft_strcmp
ft_strcmp: ; rdi = *s1, rsi = *s2
    xor rax, rax ; initialize rax to 0

.start_loop:
    cmp byte [rdi], NULL ; check if the current byte in rdi (*s1) is null (end of string)
    jnz .continue_loop   ; if it is not, continue the loop
    cmp byte [rsi], NULL ; check if the current byte in rsi (*s2) is null (end of string)
    jz .exit

.continue_loop:
    mov al, [rdi]   ; subtract the current byte in rsi (*s2) from the current byte in rdi (*s1)
    sub al, [rsi]   ;
    jne .exit       ; if the bytes are not equal, return the difference
    inc rdi         ; move to the next byte in s1
    inc rsi         ; move to the next byte in s2
    jmp .start_loop ; repeat the loop

.exit:
    movsx eax, al   ; sign-extend al (8-bit) to eax (32-bit)
    ret
