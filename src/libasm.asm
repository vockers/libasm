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

; Constants for ASCII characters
NULL            equ 0x00
TAB             equ 0x09
NEWLINE         equ 0x0A
VERTICAL_TAB    equ 0x0B
FORM_FEED       equ 0x0C
CARRIAGE_RETURN equ 0x0D
SPACE           equ 0x20

%endif
