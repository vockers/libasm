extern __errno_location
global ft_read

section .text

ft_read:
    xor rax, rax ; set system call number to 0 (read)
    syscall      ; read call: `fd`, `buf`, `count` are in: rdi, rsi, rdx
    cmp rax, 0   ; check if return value of syscall (rax) is negative
    jl .error    ; jump to .error on error (rax is negative)
    ret          ; return number of bytes read

.error:
    neg rax                         ; get absolute value of syscall return
    mov rdi, rax
    call __errno_location wrt ..plt ; get address of the errno global variable
    mov [rax], rdi                  ; set errno to absolute value of syscall return
    mov rax, -1                     ; set return value to -1
    ret
