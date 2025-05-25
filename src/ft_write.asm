extern __errno_location

section .text

global ft_write
ft_write: ; rdi = fd, rsi = buf, rdx = count
    mov rax, 1     ; set system call number to 1 (write)
    syscall        ; write call: `fd`, `buf`, `count` are in: rdi, rsi, rdx
    cmp rax, -4095 ; check if return value of syscall (rax) is between -1 and -4095
    jae .error
    ret            ; return number of bytes written

.error:
    neg rax                         ; get absolute value of syscall return
    mov rdi, rax
    call __errno_location wrt ..plt ; get address of the errno global variable
    mov [rax], rdi                  ; set errno to absolute value of syscall return
    mov rax, -1                     ; set return value to -1
    ret
