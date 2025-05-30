%include "src/libasm.asm"

section .text

global ft_strlen
ft_strlen: ; rdi = *str
    xor rax, rax  ; initialize rax to 0
    test rdi, rdi ; check if rdi (*str) is null
    jz .exit

.loop:
    cmp byte [rdi], NULL ; check if the current byte is null terminator
    jz .exit             ; if it is, return rax (length of string)
    inc rdi              ; move to the next byte
    inc rax              ; increment the length of the string
    jmp .loop            ; repeat the loop

.exit:
    ret

