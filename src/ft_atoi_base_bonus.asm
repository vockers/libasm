section .text

global ft_atoi_base
ft_atoi_base:
    xor rax, rax  ; Initialize result to 0
    test rdi, rdi ; check if rdi (*str) is null
    jz .exit      ; if it is, return 0
    test rsi, rsi ; check if rsi (*base) is null
    jz .exit      ; if it is, return 0
    xor rdx, rdx  ; Initialize sign to 0
    xor r8, r8    ; Clear base length register

.check_base:
    mov cl, byte [rsi + r8] ; Load current character from base string into cl
    cmp cl, 0               ; Check if it's null terminator
    jz .check_base_end      ; If it is, end of base string
    mov r9, r8              ; Set duplicate check index to current base index

.check_base_dup:
    inc r9 
    cmp cl, byte [rsi + r9] ; Check if current character is a duplicate in the base string
    je .exit                ; If it is, exit (invalid base)
    cmp byte [rsi + r9], 0  ; Check if we've reached the end of the base string
    jnz .check_base_dup     ; If not, continue checking for duplicates

    ; check if character is a valid base character (not a whitespace or '-' or '+')
    cmp cl, ' ' ; Check if it's a space
    je .exit    ; If it is, it's invalid
    cmp cl, 9   ; Check for tab
    je .exit    ;
    cmp cl, 10  ; Check for newline
    je .exit    ;
    cmp cl, 11  ; Check for vertical tab
    je .exit    ;
    cmp cl, 12  ; Check for form feed
    je .exit    ;
    cmp cl, 13  ; Check for carriage return
    je .exit    ;
    cmp cl, '-' ; Check for minus sign
    je .exit    ;
    cmp cl, '+' ; Check for plus sign
    je .exit    ;

    inc r8             ; Increment base length
    jmp .check_base    ; Repeat the loop

.check_base_end:
    cmp r8, 2          ; Check if base length is less than 2
    jb .exit           ; If it is, exit (invalid base)

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
    
    xor r9, r9
.get_base:
    cmp cl, byte [rsi + r9] ; Compare current character with a character in the base
    je .add_digit           ; If they match, add the digit to the result
    inc r9                  ; Increment base index
    cmp byte [rsi + r9], 0  ; Check if base character is null terminator
    jnz .get_base           ; If not, continue checking
    jmp .parse_end          ; If no match found, exit parsing

.add_digit:
    imul eax, r8d     ; Multiply result by base length
    add eax, r9d      ; Add the digit to the result

    inc rdi           ; Move to the next character
    jmp .parse_number ; Repeat the loop

.parse_end:
    test rdx, rdx     ; Check if sign was set
    jz .exit          ; If not set, exit
    neg eax           ; If sign was set, negate the result

.exit:
    ret

