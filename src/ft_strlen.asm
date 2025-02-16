section .text

global ft_strlen
ft_strlen:
    xor rax, rax  ; initialize rax to 0
    test rdi, rdi ; check if rdi (*str) is null
    jz .exit      ; if it is, return 0

.loop:
    cmp byte [rdi], 0 ; check if the current byte is null (end of string)
    jz .exit          ; if it is, return rax (length of string)
    inc rdi           ; move to the next byte
    inc rax           ; increment the length of the string
    jmp .loop         ; repeat the loop

.exit:
    ret

