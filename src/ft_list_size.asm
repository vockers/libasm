%include "src/libasm.asm"

section .text

global ft_list_size
ft_list_size: ; rdi = *begin_list
    xor rax, rax       ; initialize size to 0

.loop:
    test rdi, rdi      ; check if the list pointer is null
    jz .exit           ; if it is, return 0

    mov rdi, [rdi + s_list.next] ; move to the next element in the list
    inc rax                      ; increment the size counter
    jmp .loop                    ; repeat the loop

.exit:
    ret ; return the size (rax)
