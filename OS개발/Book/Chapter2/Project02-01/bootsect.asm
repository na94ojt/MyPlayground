;===============================================================================
; bootsect.asm - for FAT12 disk filesystem.
;
; First written = Aug 5th, 2003.
; Writer = Yeori (alphamcu@hanmail.net, http://www.zap.pe.kr)
;===============================================================================

	[BITS 16]
	ORG	0

	%include "c16.mac"
    
;===============================================================================
; boot records (FAT12 compatible)
;===============================================================================
	db		0ebh, 3ch				; jmp entry
	db		90h						; nop		- for assembler independence
		
	db		'Chobits '				; 8 bytes
	dw		512						; bytes per sector
	db		1						; sectors per cluster
	dw		1						; reserved sectors
	db		2						; numbers of FAT
	dw		224						; entries of root directory
	dw		2880					; total sectors
	db		0f0h
	dw		9						; sectors per FAT
	dw		18						; sectors per track
	dw		2						; heads
	dw		0						; numbers of hidden sectors
	dw		0
	dd		0
	db		0						; disk driver number (A:0, C:2)
	db		0
	db		029h
	dd		0
	db		'CHOBITS BIN'
	db		'FAT12   '
		

;===============================================================================
; main
;
; * description - read carefully - *
; Only "conventional memory" area(00000h~9ffffh) is available freely. First 1k
; memory(from 000h~3ffh) is set aside for the "interrupt vector table". The area
; from 400h to 4ffh(a total of 256 bytes) is set aside for the "BIOS data" area.
; Memory from 500h to 5ffh(256 bytes) is set aside to be used for "DOS" parameters.
; Locations 700h to 9ffffh are available to "ANY OS".
;
; But, we only use the area from 1000h to 9ffffh area(a total of 650kbytes).
; first 512bytes(1000h~11ffh) is used for a copy of "boot sector". Next 4k memory
; from(1200h~23ffh) is used for a copy of "FAT" table. The area from 2400h to
; 3fffh(7kbytes) is used for "Directory Entry" table. Memory from 10000h to 1ffffh
; (64kbytes) is used for the "stack" area. Finally, the area from 20000h to 9ffffh
; (588kbytes) is set aside to be used for launching "CHOBITS OS" image file.
;===============================================================================
%define BOOTSEG		07c0h		; 7c00h
%define INITSEG		0100h		; 1000h
%define INITSS		01000h		; 10000h
%define INITSP		0ffffh

%define	FATSEG		0120h		; 1200h
%define DIRSEG		0240h		; 2400h
%define LDRSEG		02000h		; 20000h ~ 9ffffh

entry:
		cli
		mov		ax, INITSS
		mov		ss, ax
		mov		sp, INITSP
		sti
		
		; re-load
		cld
		mov		ax, INITSEG
		mov		es, ax
		xor		di, di
		mov		ax, BOOTSEG
		mov		ds, ax
		xor		si, si
		mov		cx, 100h				; 256 * 2bytes(movsw) = 512 bytes
		repz	movsw
		
		jmp		INITSEG:main
		

;===============================================================================
; main procedure
;===============================================================================
main:
		mov		ax, INITSEG
		mov		ds, ax
		
		; init video
		mov		ax, 0600h
		mov		bh, 07h
		xor		cx, cx
		mov		dx, 1850h		; row:24, column:80
		int		10h				; reset window
		mov		ah, 02h
		xor		bh, bh
		xor		dx, dx
		int		10h				; set cursor position onto the top-left
		
		; loading msg
		push	msg_loading
		call	msgout
		add		sp, 2
		
.infinate:
		jmp		.infinate

;===============================================================================
; msgout
;
; type : void msgout(word ptMsg);  // ptMsg is an word-size address.
;===============================================================================
proc	msgout
		pusha
		
		mov		si, WORD [bp+4]
.print:
		lodsb
		or		al, al
		jz		.out
		mov		ah, 0eh					; teletype output function
		mov		bx, 08h					; back/fore ground color
		int		10h
		jmp		.print
		
.out:
		popa
endproc


;===============================================================================
; datas used by boot procedure
;===============================================================================
msg_loading	db	'Loading', 00h


;===============================================================================
; boot signature
;===============================================================================
times	1feh-($-$$)	db	00h
		dw		0aa55h