EXTERN bRemoAddTest:QWORD
EXTERN bAddUnderConstructionParamMan:QWORD
EXTERN bAddUnderConstructionEmevdMan:QWORD

.data
	makeDbgMenuStaticLabel QWORD 14022E7C0h
	initDbgMenuItem QWORD 1404787F0h
	pDebugMem QWORD 141C04FA0h
	value DWORD 0
	string WORD 3010h, 25h, 30h, 32h, 64h, 3011h, 3Ch, 46h, 61h, 74h, 63h, 61h, 74h, 0
.code

fRemoAddTest PROC
	lea rsi, [value]
	mov r14, [rdi+158h]
	mov rax, 1401658B0h
	call rax
	mov rcx, rax
	mov edx, 60h
	lea r8d, [rdx-58h]
	mov rax, 140CBE4F0h
	call rax
	mov rbx, rax
	test rax, rax
	je failure
	mov rcx, rax
	call initDbgMenuItem
	mov [rbx], rbp
	lea rcx, [rbx+18h]
	mov r8, [pDebugMem]
	mov r8, [r8]
	lea rdx, [string]
	mov rax, 1400CC8C0h
	call rax
	mov [rbx+48h], rsi
	mov word ptr [rbx+50h], 6300h
	mov byte ptr [rbx+52h], 1
	movzx eax, byte ptr [rsi]
	mov [rbx+53h], al
	mov byte ptr [rbx+54h], 1
	mov dword ptr [rbx+58h], 3F800000h
	jmp continue
failure:
	xor ebx, ebx
continue:
	mov rax, [r14]
	mov r8b, 1
	mov rdx, rbx
	mov rcx, r14
	call qword ptr [rax+60h]
	mov rsi, [rdi+158h]
	jmp [bRemoAddTest]
fRemoAddTest ENDP

.data
	makeDbgMenuEmevdActionNode QWORD 1407C3EF0h
	underConstructionStr WORD 2517h, 28h, 0FF3Eh, 30h, 0FF3Eh, 29h, 2513h, 20h, 55h, 6Eh, 64h, 65h, 72h, 20h, 43h, 6Fh, 6Eh, 73h, 74h, 72h, 75h, 63h, 74h, 69h, 6Fh, 6Eh, 20h, 2517h, 28h, 0FF3Eh, 30h, 0FF3Eh, 29h, 2513h, 0
.code

fAddUnderConstructionParamMan PROC
	lea rdx, [underConstructionStr]
	mov rcx, rbx
	call makeDbgMenuStaticLabel
	mov rax, [r14]
	mov r8b, 1
	jmp [bAddUnderConstructionParamMan]
fAddUnderConstructionParamMan ENDP

fAddUnderConstructionEmevdMan PROC
	mov rcx, rdi
	mov rbx, rdx
	lea rdx, [underConstructionStr]
	call makeDbgMenuStaticLabel
	mov rdx, rbx
	mov rbx, 0AAAAAAAAAAAAAAABh
	jmp [bAddUnderConstructionEmevdMan]
fAddUnderConstructionEmevdMan ENDP

END