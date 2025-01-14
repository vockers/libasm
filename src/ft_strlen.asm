global ft_strlen

section .text

ft_strlen:
    xor rax, rax
    test rdi, rdi    
    jz .exit

.loop:
    cmp byte [rdi], 0
    jz .exit 
    inc rdi
    inc rax
    jmp .loop

.exit:
    ret

