[org 0x7c00]
[bits 16]

xor ax,ax
mov es,ax

;Load os
mov ah,0x2
mov al,30
mov ch,0
mov cl,2
mov dh,0
mov bx,0x1000
int 0x13

cli ;turn off interupts
lgdt [GDT_DESC]

mov eax,cr0
or eax,0x1
mov cr0,eax

jmp CODE_SEG:INIT_PM

[bits 32]
INIT_PM:
	mov eax,DATA_SEG
	mov ds,eax
	mov ss,eax
	mov es,eax
	mov fs,eax
	mov gs,eax

	mov ebp,0x90000
	mov esp,ebp

	jmp 0x1000

GDT_START:
        GDT_NULL_DESC:
                times 8 db 0
        GDT_CODE_DESC:
                dw 0xffff
                dw 0x0 
                db 0x0 
                db 0b10011010
                db 0b11001111
                db 0x0 
        GDT_DATA_DESC:
                dw 0xffff
                dw 0x0 
                db 0x0 
                db 0b10010010
                db 0b11001111
                db 0x0 
GDT_END:

GDT_DESC:
        dw GDT_END-GDT_START-1
        dd GDT_START

CODE_SEG equ GDT_CODE_DESC - GDT_START
DATA_SEG equ GDT_DATA_DESC - GDT_START


times 510-($-$$) db 0
dw 0xaa55
