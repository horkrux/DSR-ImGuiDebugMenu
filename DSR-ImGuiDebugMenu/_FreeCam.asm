EXTERN bFreeCam:QWORD
EXTERN bGetFreeCamMode1:QWORD
EXTERN bGetFreeCamMode2:QWORD
EXTERN bGetFreeCamMode3:QWORD
EXTERN bGetFreeCamMode4:QWORD

.data

freeCamMode DWORD 0
pHgMan QWORD 141C04ED8h
DbgCamPadFunc QWORD 1402424A0h
PadStuff QWORD 0, 0, 0, 0
getPadDevice QWORD 1401ADBA0h
checkButton QWORD 1401A43B0h

.code

fFreeCam PROC
	push rbx
	push rcx
	push rdx
	push r8
	push r9
	sub rsp, 8
	movaps [rsp], xmm0
	xor ecx, ecx
	call getPadDevice
	lea rbx, [PadStuff]
	xor rdx, rdx
	mov rdx, 1412DA5B8h
	mov [rbx], rdx
	xor rdx, rdx
	mov [rbx+8], rax
	mov [rbx+0Ch], rdx
	mov rcx, [rbx+8]
	mov edx, 64h
	call checkButton
	test al, al
	je pastCheck
	mov rcx, [rbx+8]
	mov edx, 46h
	call checkButton
	test al, al
	je pastCheck
	inc [freeCamMode]
	cmp dword ptr [freeCamMode], 4
	jb pastCheck
	mov dword ptr [freeCamMode], 0
pastCheck:
	mov ecx, [freeCamMode]
	mov rdx, [pHgMan]
	mov rdx, [rdx]
	mov rdx, [rdx+738h]
	mov [rdx+328h], rcx
	cmp ecx, 1
	je freeCamMode1
	cmp ecx, 2
	je freeCamMode2
	cmp ecx, 3
	je freeCamMode3
freeCamMode0:
	mov r8, [rdx+330h]
	mov r9, [rdx+20h]
	movaps xmm0, [r9+10h]
	movaps [r8+10h], xmm0
	movaps xmm0, [r9+20h]
	movaps [r8+20h], xmm0
	movaps xmm0, [r9+30h]
	movaps [r8+30h], xmm0
	movaps xmm0, [r9+40h]
	movaps [r8+40h], xmm0
	mov byte ptr [rsi+90h], 0
	mov byte ptr [rsi+91h], 0
	jmp freeCamFinish
freeCamMode1:
	mov rcx, [rbx+8]
	mov edx, 0Ah
	call checkButton
	mov rdx, [pHgMan]
	mov rdx, [rdx]
	mov rdx, [rdx+738h]
	test al, al
	je frozen
	jmp freeCamMode2
frozen:
	mov byte ptr [rsi+90h], 1
	mov byte ptr [rsi+91h], 1
	jmp freeCamUpdateMotion
freeCamMode2:
	mov byte ptr [rsi+90h], 0
	mov byte ptr [rsi+91h], 0
	jmp freeCamUpdateMotion
freeCamMode3:
	mov r8, [rdx+50h]
	mov r9, [rdx+330h]
	movaps xmm0, [r9+10h]
	movaps [r8+10h], xmm0
	movaps xmm0, [r9+20h]
	movaps [r8+20h], xmm0
	movaps xmm0, [r9+30h]
	movaps [r8+30h], xmm0
	movaps xmm0, [r9+40h]
	movaps [r8+40h], xmm0
	mov byte ptr [rsi+90h], 0
	mov byte ptr [rsi+91h], 0
	jmp freeCamFinish
freeCamUpdateMotion:
	mov rcx, [pHgMan]
	mov rcx, [rcx]
	mov rcx, [rcx+738h]
	mov byte ptr [rsi+70h], 1
	mov r8, [rdx+50h]
	mov r9, [rdx+330h]
	movaps xmm0, [r9+10h]
	movaps [r8+10h], xmm0
	movaps xmm0, [r9+20h]
	movaps [r8+20h], xmm0
	movaps xmm0, [r9+30h]
	movaps [r8+30h], xmm0
	movaps xmm0, [r9+40h]
	movaps [r8+40h], xmm0
	mov rcx, [rcx+330h]
	mov rdx, r13
	mov r8, 0
	mov r9, 0
	call DbgCamPadFunc
freeCamFinish:
	movaps xmm0, [rsp]
	add rsp, 8
	pop r9
	pop r8
	pop rdx
	pop rcx
	pop rbx
	mov rax, r13
	mov [rbp+70h], rax
	mov ecx, [rsi+70h]
	jmp bFreeCam
fFreeCam ENDP

tGetFreeCamMode1 PROC
	call getFreeCamMode
	jmp bGetFreeCamMode1
tGetFreeCamMode1 ENDP

tGetFreeCamMode2 PROC
	call getFreeCamMode
	jmp bGetFreeCamMode2
tGetFreeCamMode2 ENDP

tGetFreeCamMode3 PROC
	call getFreeCamMode
	jmp bGetFreeCamMode3
tGetFreeCamMode3 ENDP

tGetFreeCamMode4 PROC
	call getFreeCamMode
	jmp bGetFreeCamMode4
tGetFreeCamMode4 ENDP

getFreeCamMode PROC
	mov eax, dword ptr [freeCamMode]
	ret
getFreeCamMode ENDP

END
