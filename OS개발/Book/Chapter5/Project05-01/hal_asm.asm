		.386P
		.MODEL FLAT
		PUBLIC	_WRITE_PORT_UCHAR




.DATA

.CODE
;===============================================================================
; UCHAR READ_PORT_UCHAR(IN PUCHAR Port);
;===============================================================================
_READ_PORT_UCHAR	PROC
		push	ebp
		mov		ebp, esp
		push	edx
		
		mov		edx, [ebp+8]
		in		al, dx
		
		pop		edx
		pop		ebp
		ret
_READ_PORT_UCHAR	ENDP

;===============================================================================
; VOID WRITE_PORT_UCHAR(IN PUCHAR Port, IN UCHAR Value);
;===============================================================================
_WRITE_PORT_UCHAR	PROC
        push	ebp
        mov		ebp, esp
        push	edx
        push	eax

        mov		edx, [ebp+8]
        mov		al, [ebp+12]
        out		dx, al
        
        pop		eax
        pop		edx
        pop		ebp
        ret
_WRITE_PORT_UCHAR	ENDP






        END
