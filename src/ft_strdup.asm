extern ft_strlen
extern ft_strcpy
extern malloc

section .text

global ft_strdup
ft_strdup: ; rdi = *src
    push rdi              ; save source string
    call ft_strlen        ; get length of source string, `str` is in rdi
    inc rax               ; add 1 to length for null terminator

    mov rdi, rax          ; set size to length + 1
    call malloc wrt ..plt ; allocate memory for new string
    pop rsi               ; restore source string
    test rax, rax         ; check if malloc failed (rax is 0)
    jz .exit

    mov rdi, rax          ; set destination string to allocated memory
    call ft_strcpy        ; copy source string to destination string

.exit:
    ret

