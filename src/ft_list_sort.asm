%include "src/libasm.asm"

section .text

global ft_list_sort
ft_list_sort: ; rdi = **begin_list, rsi = (*cmp)()
    test rdi, rdi ; check if rdi (**begin_list) is null
    jz .exit
    test rsi, rsi ; check if rsi (cmp function pointer) is null
    jz .exit

    push rbx ; root node
    push rbp ; cmp function pointer
    push r12 ; current node
    push r13 ; count node
    push r14 ; next node

    mov rbx, [rdi] ; rbx = *begin_list
    test rbx, rbx  ; check if the list is empty
    jz .exit_cleanup

    mov rbp, rsi ; rbp = cmp function pointer
    mov r13, rbx ; set count node to the root node

.swap_loop_start:
    mov r12, rbx ; set current node to the root node
.swap_loop:
    mov r14, [r12 + s_list.next] ; next = current->next
    test r14, r14                ; check if next is null
    jz .next_pass                ; if next is null, go to next pass

    mov rdi, [r12 + s_list.data] ; set first argument to current node data
    mov rsi, [r14 + s_list.data] ; set second argument to next node data
    call rbp                     ; cmp(current->data, next->data)
    test eax, eax                ; move to next node if cmp returns <= 0
    jle .next

    ; Swap the node's data if cmp returns > 0
    mov rcx, [r12 + s_list.data] ; save current node data
    mov rdx, [r14 + s_list.data] ; save next node data
    mov [r12 + s_list.data], rdx ; current->data = next->data
    mov [r14 + s_list.data], rcx ; next->data = current->data

.next:
    mov r12, r14   ; current = next
    jmp .swap_loop ; repeat the loop

.next_pass:
    mov r13, [r13 + s_list.next] ; move to the next node in the list
    test r13, r13                ; check if we reached the end of the list
    jz .exit_cleanup

    jmp .swap_loop_start ; start a new pass through the list

.exit_cleanup:
    pop r14
    pop r13
    pop r12
    pop rbp
    pop rbx
.exit:
    ret