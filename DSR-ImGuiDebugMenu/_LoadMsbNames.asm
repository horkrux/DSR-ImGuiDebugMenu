EXTERN malloc:QWORD
EXTERN free:QWORD
EXTERN bWritePlayerName:QWORD
EXTERN bContinueInitPlayer:QWORD

.data
jmpInitContinue QWORD 14031C641h
jmpDeleteContinue QWORD 14031CA1Bh
;writemodelname LABEL FAR

.code

loadEnemyMsbName PROC

	lea rcx, [r9+r8]
	movsxd r8, dword ptr [rcx]
	lea r8, [rcx+r8]
	push r11
	push r10
	push rdx
	push rax
	push rdi
	push r9
	push rcx

	mov rcx, -1
	mov r9, r8
	cmp byte ptr [r9], 0
	je endWriteModelName
	dec r9
nextchar:
	inc rcx
	inc r9
	mov dil, byte ptr [r9]
	test dil, dil
	jne nextchar
	inc rcx
	test rcx, rcx
	je endlbl
	lea r9, [rbx+4F8h]
	cmp rcx, 8
	jb write
	mov dword ptr [r9+18h], 17h
	shl ecx, 1
	add ecx, 2
	push r8
	push r9
	sub rsp, 20h
	lea rax, malloc
	call rax
	add rsp, 20h
	pop r9
	pop r8
	mov [r9], rax
	mov r9, rax
	jmp write
;writemodelname:
;	lea r8, [rbx+88h]
;	lea r9, [rbx+4F8h]
;	xor rcx, rcx
;writemodelloop:
;	mov ax, [r8+rcx]
;	mov [r9+rcx], ax
;	add rcx, 2
;	test ax, ax
;	jne writemodelloop
;	jmp endlbl
endWriteModelName:
	call writeModelName
	jmp endlbl
write:
	xor rcx, rcx
writeloop:
	movzx ax, byte ptr [r8+rcx]
	mov [r9+rcx*2], ax
	inc rcx
	test ax, ax
	jne writeloop
	;jmp endlbl

	
endlbl:
	
	pop rcx
	pop r9
	pop rdi
	pop rax
	pop rdx
	pop r10
	pop r11
	jmp [jmpInitContinue]

loadEnemyMsbName ENDP

.data

.code

writePlayerName PROC
	je writename
	jmp [bWritePlayerName]
writename:
	push rdx
	push rcx
	push r9
	push r8
	call writeModelName
	pop r8
	pop r9
	pop rcx
	pop rdx
	jmp [bContinueInitPlayer]
writePlayerName ENDP

.data

.code

writeModelName PROC
	lea r8, [rbx+88h]
	lea r9, [rbx+4F8h]
	xor rcx, rcx
writemodelloop:
	mov ax, [r8+rcx]
	mov [r9+rcx], ax
	add rcx, 2
	test ax, ax
	jne writemodelloop
	ret
writeModelName ENDP

.data

.code

freeEnemyMsbName PROC

	mov [rcx], rax
	lea rax, [rcx+4F8h]
	cmp dword ptr [rax+18h], 8
	jb endlbl
	push rdx
	push rcx
	mov rcx, [rcx+4F8h]
	push r8
	push r9
	push r10
	push r11
	sub rsp, 20h
	lea rax, free
	call rax
	add rsp, 20h
	pop r11
	pop r10
	pop r9
	pop r8
	pop rcx
	xor rdx, rdx
	mov [rcx+4F8h], rdx
	mov dword ptr [rcx+510h], 7
	pop rdx
endlbl:
	jmp [jmpDeleteContinue]

freeEnemyMsbName ENDP

END