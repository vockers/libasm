%include "src/libasm.asm"

section .text

global ft_list_remove_if
extern free
ft_list_remove_if: ; rdi = **begin_list, rsi = *data_ref, rdx = *cmp(), rcx = *free_fct()
    test rdi, rdi ; check if rdi (**begin_list) is null
    jz .exit
    test rsi, rsi ; check if rsi (data_ref) is null
    jz .exit
    test rdx, rdx ; check if rdx (cmp function pointer) is null
    jz .exit
    test rcx, rcx ; check if rcx (free function pointer) is null
    jz .exit

    push rbx ; begin_list
    push rbp ; data_ref
    push r12 ; cmp function pointer
    push r13 ; free function pointer
    push r14 ; current node
    push r15 ; next node

    mov rbx, rdi   ; save the address of begin_list
    mov rbp, rsi   ; rbp = data_ref
    mov r12, rdx   ; r12 = cmp function pointer
    mov r13, rcx   ; r13 = free function pointer
    mov r14, [rdi] ; current = *begin_list

    xor rdi, rdi   ; previous = NULL

.loop:
    test r14, r14  ; check if current node is NULL
    jz .exit_cleanup
    mov r15, [r14 + s_list.next] ; next = current->next

    push rdi
    mov rdi, [r14 + s_list.data] ; set first argument to current node data
    mov rsi, rbp                 ; set second argument to data_ref
    call r12                     ; cmp(current->data, data_ref)
    pop rdi

    test eax, eax ; if the data matches, remove the node
    jnz .next     ; else, go to next node

    push rdi
    mov rdi, [r14 + s_list.data] ; set first argument to current node data
    call r13                     ; free_fct(current->data)
    pop rdi

    test rdi, rdi  ; check if previous node is NULL
    jz .first_node

    ; if previous is not NULL, link it to the next node
    mov [rdi + s_list.next], r15 ; previous->next = next
    jmp .delete_node

.first_node:
    mov [rbx], r15 ; update the begin_list to point to the next node

.delete_node:
    push rdi
    mov rdi, r14        ; set first argument to current node
    call free wrt ..plt ; free the current node
    pop rdi

    mov r14, r15 ; current = next
    jmp .loop    ; continue loop

.next:
    mov rdi, r14 ; previous = current
    mov r14, r15 ; current = next
    jmp .loop

.exit_cleanup:
    pop r15
    pop r14
    pop r13
    pop r12
    pop rbp
    pop rbx
.exit:
    ret