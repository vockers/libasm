%ifndef LIBASM_H
%define LIBASM_H

; struct s_list 
; {
;     void *data;
;     struct s_list *next;
; };
struc s_list
    .data resq 1 ; *data
    .next resq 1 ; *next
endstruc

%endif
