extern malloc

%include "src/libasm.asm"

section .text

global ft_list_push_front
ft_list_push_front: ; rdi = **begin_list, rsi = *data
    test rdi, rdi ; check if the root pointer is null
    jz .exit      ; if it is, exit

    push rdi               ; save the root pointer (**begin_list)
    push rsi               ; save the new element pointer (*data)
    mov rdi, s_list%+_size ; use the size of the s_list structure as the argument for malloc
    call malloc wrt ..plt  ; allocate memory for the new element
    pop rsi                ; restore the new element pointer (*data)
    pop rdi                ; restore the root pointer (**begin_list)
    test rax, rax          ; check if malloc failed (rax is 0)
    jz .exit               ; if it did, exit

    mov [rax + s_list.data], rsi ; set the data of the new element
    mov rcx, [rdi]               ; load the current root pointer into rcx
    mov [rax + s_list.next], rcx ; set the next pointer of the new element to the current root
    mov [rdi], rax               ; update the root pointer to point to the new element

.exit:
    ret                   ; return
