extern __errno_location
global ft_write

section .text

ft_write:
    mov rax, 1 ; set system call number to 1 (write)
    syscall    ; write call: `fd`, `buf`, `count` are in: rdi, rsi, rdx
    cmp rax, 0 ; check if return value of syscall (rax) is negative
    jl .error  ; jump to .error on error (rax is negative)
    ret        ; return number of bytes written

.error:
    neg rax                         ; get absolute value of syscall return
    mov rdi, rax
    call __errno_location wrt ..plt ; get address of the errno global variable
    mov [rax], rdi                  ; set errno to absolute value of syscall return
    mov rax, -1                     ; set return value to -1
    ret
