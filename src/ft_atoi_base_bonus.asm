section .text

global ft_atoi_base
ft_atoi_base:
    xor rax, rax  ; Initialize result to 0
    test rdi, rdi ; check if rdi (*str) is null
    jz .exit      ; if it is, return 0
    xor rdx, rdx  ; Initialize sign to 0
    xor rcx, rcx  ; Clear tmp register

.skip_whitespaces:
    mov cl, byte [rdi]   ; Load current character into cl
    cmp cl, 0            ; Check if it's null terminator
    jz  .exit            ; If it is, exit
    cmp cl, ' '          ; Check if it's a space
    je  .skip_whitespace ; If it is, skip to next character
    cmp cl, 9
    jb  .check_sign      ; If less than 9 ('\t'), not a whitespace
    cmp cl, 13
    ja  .check_sign      ; If greater than 13 ('\r'), not a whitespace

.skip_whitespace:
    inc rdi               ; Move to the next character
    jmp .skip_whitespaces ; Repeat the loop

.check_sign:
    mov cl, byte [rdi] ; Load current character into cl
    cmp cl, '-'        ; Check if it's a minus sign
    je  .is_negative   ; If it is, toggle sign flag
    cmp cl, '+'        ; Check if it's a plus sign
    je .is_positive    ; If it is, just skip it

    jmp .parse_number ; If it's neither, parse the number

.is_negative:
    xor rdx, 1      ; Toggle sign flag
.is_positive:
    inc rdi         ; Move to the next character
    jmp .check_sign ; Repeat the loop


.parse_number:
    mov cl, byte [rdi] ; Load current character into cl
    cmp cl, 0          ; Check if it's null terminator
    jz  .parse_end     ; If it is, end parsing
    cmp cl, '0'        ; Check if it's a digit
    jb  .parse_end     ; If less than '0', exit
    cmp cl, '9'
    ja  .parse_end     ; If greater than '9', exit

    sub cl, '0'        ; Convert ASCII to integer
    imul eax, eax, 10  ; Multiply result by 10
    add eax, ecx       ; Add the digit to the result

    inc rdi           ; Move to the next character
    jmp .parse_number ; Repeat the loop

.parse_end:
    test rdx, rdx     ; Check if sign was set
    jz .exit          ; If not set, exit
    neg eax           ; If sign was set, negate the result

.exit:
    ret

