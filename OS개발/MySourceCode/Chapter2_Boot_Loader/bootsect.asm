	[BITS 16]
	ORG	0

	%include 'c16.mac'

;===============================================================================================
;boot records (FAT12 compatible)
;===============================================================================================
	db		0ebh, 3ch		; jmp entry
	db		90h				; nop - for assembler indepence

	db		'chobits '		; 8bytes
	dw		512				; bytes per sector
	db		1				; sectors per cluster
	dw		1				; reserved sectors
	db		2				; numbers of FAT
	dw		224				; entries of root directory
	dw		2880			; total sectors;
	db		0f0h
	dw		9				; sectors per FAT
	dw		18				; sectors per track
	dw		2				; heads
	dw		0 				; numbers of hidden sectors
	dw		0 
	dd		0
	db		0 				; disk driver number (A:0, C:2)
	db		0
	db		029h
	dd		0
	db		'CHOBITS IN'
	db		'FAT12   '