EXTERN bGetCameraObj:QWORD
EXTERN bGetCameraObjAlt:QWORD
EXTERN bSetCameraObj:QWORD
EXTERN bLoadGameProperties:QWORD
EXTERN LoadGameProperties:QWORD

.data

camera QWORD 0

.code

fGetCameraObj PROC

	test rdx, rdx
	je Return
	mov rdi, [rdx + 158h]
	mov [camera], rdi
	xor rdi, rdi
	mov edi, [rdx+9Ch]

	Return:
	jmp [bGetCameraObj]

fGetCameraObj ENDP

.data

.code

fGetCameraObjAlt PROC

	test rdx, rdx
	je Return
	mov rsi, [rdx + 158h]
	mov [camera], rsi
	xor rsi, rsi
	mov esi, [rdx+9Ch]

	Return:
	jmp [bGetCameraObjAlt]

fGetCameraObjAlt ENDP

.data

.code

fSetCameraObj PROC

	mov rcx, [camera]
	test rcx, rcx
	je zero
	mov [rbx + 158h], rcx

	zero:
	mov rcx, [rbx + 158h]
	jmp [bSetCameraObj]
	

fSetCameraObj ENDP

tLoadGameProperties PROC
	lea rax, LoadGameProperties
	call rax
	jmp [bLoadGameProperties]
tLoadGameProperties ENDP

END
