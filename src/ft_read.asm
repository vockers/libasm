extern __errno_location

section .text

global ft_read
ft_read:
    xor rax, rax   ; set system call number to 0 (read)
    syscall        ; read call: `fd`, `buf`, `count` are in: rdi, rsi, rdx
    cmp rax, -4095 ; check if return value of syscall (rax) is between -1 and -4095
    jae .error     ; jump to .error on error (rax is between -1 and -4095)
    ret            ; return number of bytes read

.error:
    neg rax                         ; get absolute value of syscall return
    mov rdi, rax
    call __errno_location wrt ..plt ; get address of the errno global variable
    mov [rax], rdi                  ; set errno to absolute value of syscall return
    mov rax, -1                     ; set return value to -1
    ret
