EXTERN bLoadParamdefbnd:QWORD
EXTERN paramdefbndPathString:QWORD

.data
	createParamdefbndFileCap QWORD 14059E120h
.code

tLoadParamdefbnd PROC
	sub rsp, 20h
	mov rbx, rcx
	lea rdx, [rbx+28h]
	lea rcx, [paramdefbndPathString]
	call createParamdefbndFileCap
	jmp [bLoadParamdefbnd]
tLoadParamdefbnd ENDP

.data
	nodestring BYTE 5Bh, 0, 25h, 0, 73h, 0, 5Dh, 0, 28h, 0, 25h, 0, 64h, 0, 29h, 0, 0, 0 
	heapstring QWORD 1414A1BC8h
	func1 QWORD 140CC0D60h
	func2 QWORD 140D4FD10h
.code

fControlParamDebugMenu PROC
	mov [rsp+18h], rbp
	push rsi
	push rdi
	push r14
	sub rsp, 20h
	mov r14d, [rdx+14h]
	mov ebp, [rdx+10h]
	mov rax, [rcx]
	mov rsi, rdx
	mov edx, r14d
	mov rdi, rcx
	call qword ptr [rax+40h]
	mov r8, rsi
	mov rcx, rdi
	test al, al
	mov rax, [rdi]
	je loc_142368AB4 ;static check
loc_142368954:
	mov [rsp+40h], rbx
	mov ebx, [rsi+1Ch]
	mov [rsp+48h], r15
	mov r15d, 1
	shr ebx, 0Eh
	mov edx, r15d
	call qword ptr [rax+50h]
	and bl, r15b
	jne loc_142368A88
	cmp qword ptr [rdi+8], 0
	je loc_14236899C
	mov eax, [rsi+1Ch]
	shr eax, 0Dh
	test r15b, al
	je loc_14236899C
	mov rax, [rdi]
	mov edx, r14d
	mov rcx, rdi
	call qword ptr [rax+30h]
	jmp loc_142368A88 ;static check
loc_14236899C:
	mov rax, [rdi+28h]
	mov r8d, [rdi+3Ch]
	mov r9d, [rax+48h]
	test r9d, r9d
	je loc_142368A79
	mov ebx, [rsi+1Ch]
	mov ecx, ebx
	mov r10d, ebx
	mov r11d, ebx
	shr ecx, 1
	shr r10d, 5
	shr r11d, 4
	movzx eax, bl
	and cl, r15b
	and r10b, r15b
	and al, r15b
	and r11b, r15b
	cmp al, cl
	je loc_142368A79
	mov edx, ebx
	shr ebx, 0Ah
	mov eax, 6
	shr edx, 9
	and edx, r15d
	add edx, edx
	or edx, r15d
	test r15b, bl
	cmovne r15d, eax
	imul edx, r15d
	test cl, cl
	je loc_142368A3B
	lea ecx, [rdx+r8]
	cmp ebp, 4
	jnb loc_142368A12
	sub [rdi+rbp*2+18h], dx ;static check
loc_142368A12:
	cmp ecx, r9d
	jl loc_142368A6E
	test r10b, r10b
	je loc_142368A35
	lea eax, [r9-1]
	cmp r8d, eax
	jne loc_142368A35
	xor edx, edx
	mov ecx, edx
	cmp ebp, 4
	jnb loc_142368A6E
	mov [rdi+rbp*2+18h], dx
	jmp loc_142368A6E ;static check
loc_142368A35:
	lea ecx, [r9-1]
	jmp loc_142368A6E ;static check
loc_142368A3B:
	mov ecx, r8d
	sub ecx, edx
	cmp ebp, 4
	jnb loc_142368A4A
	add [rdi+rbp*2+18h], dx ;static check
loc_142368A4A:
	test ecx, ecx
	jns loc_142368A6E
	test r11b, r11b
	je loc_142368A6A
	test r8d, r8d
	jne loc_142368A6A
	lea ecx, [r9-1]
	cmp ebp, 4
	jnb loc_142368A6E
	xor edx, edx
	mov [rdi+rbp*2+18h], dx
	jmp loc_142368A6E ;static check
loc_142368A6A:
	xor edx, edx
	mov ecx, edx
loc_142368A6E:
	cmp ecx, r8d
	je loc_142368A79
	mov r8d, ecx
	mov [rdi+3Ch], ecx
loc_142368A79:
	mov rax, [rdi]
	mov rdx, rsi
	mov rcx, rdi
	call qword ptr [rax+80h] ;static check
loc_142368A88:
	mov rax, [rdi]
	mov r8, rsi
	mov edx, 2
	call qword ptr [rax+50h]
	mov r15, [rsp+48h]
	mov rbx, [rsp+40h]
	inc dword ptr [rsi+18h]
	mov rbp, [rsp+50h]
	add rsp, 20h
	pop r14
	pop rdi
	pop rsi
	ret ;static check
loc_142368AB4:
	mov edx, 10h
	call qword ptr [rax+50h]
	mov eax, [rsi+1Ch]
	shr eax, 0Ch
	test al, 1
	je loc_142368AD2
	mov rax, [rdi]
	mov edx, r14d
	mov rcx, rdi
	call qword ptr [rax+28h] ;static check
loc_142368AD2:
	mov rax, [rdi]
	mov r8, rsi
	mov edx, 20h
	mov rcx, rdi
	call qword ptr [rax+50h]
	inc dword ptr [rsi+18h]
	mov rbp, [rsp+50h]
	add rsp, 20h
	pop r14
	pop rdi
	pop rsi
	ret ;static check
fControlParamDebugMenu ENDP

.data
	;nodestring BYTE 5Bh, 0, 25h, 0, 73h, 0, 5Dh, 0, 28h, 0, 25h, 0, 64h, 0, 29h, 0, 0, 0 
	;heapstring QWORD 1414A1BC8h
	;func1 QWORD 140CC0D60h
	;func2 QWORD 140D4FD10h
.code

fShowParamDebugMenu PROC
	push rbp
	push rsi
	push rdi
	push r12
	push r13
	push r14
	push r15
	mov rbp, rsp
	sub rsp, 70h
	mov qword ptr [rbp-40h], -2
	mov [rsp+0C0h], rbx
	movzx r12d, r8b
	mov rdi, rdx
	mov rsi, rcx
	mov rax, [rcx+28h]
	mov r13d, [rax+48h]
	mov [rbp-4Ch], r13d
	mov r14d, [rdx+10h]
	mov rax, [rcx]
	mov edx, [rdx+14h]
	call qword ptr [rax+40h]
	test al, al
	je loc_142368DB5
	mov eax, [rsi+3Ch]
	mov [rbp-48h], eax
	mov rax, [rsi]
	mov r8, rdi
	mov edx, 1
	mov rcx, rsi
	call qword ptr [rax+58h]
	call func1
	mov rbx, rax
	mov rax, [rax]
	xor r8d, r8d
	lea rdx, [rbp-50h]
	mov rcx, rbx
	call qword ptr [rax+18h]
	mov ecx, [rax]
	shr ecx, 5
	test cl, 1
	jne loc_142368BAC
	mov r8, heapstring
	mov edx, 3Eh
	xor ecx, ecx
	call func2
	int 3
loc_142368BAC:
	xor r15d, r15d
	mov [rbp-20h], r15 ;-> -20h
	mov [rbp-18h], r15 ;-> -18h
	mov [rbp-30h], rbx ;-> -30h
	mov qword ptr [rbp-10h], 7 ;-> -10h
	mov [rbp-20h], r15 ;-> -20h
	mov word ptr [rbp-28h], r15w ;-> -28h
	mov byte ptr [rbp-8], 1 ;-> -8h
loc_142368BD0:
	mov rax, [rsi]
	lea rdx, [rbp-30h] ;-> -30h
	mov rcx, rsi
	call qword ptr [rax+48h]
	lea r8, [rbp-28h] ;-> -28h
	cmp qword ptr [rbp-10h], 8 ;-> -10h
	cmovnb r8, [rbp-28h] ;-> -28h
	mov rax, [rdi]
	mov r9d, r13d
	lea rdx, nodestring
	mov rcx, rdi
	call qword ptr [rax+58h]
	nop
loc_142368BFF:
	cmp qword ptr [rbp-10h], 8 ;-> -10h
	jb loc_142368C14
	mov rcx, [rbp-30h] ;-> -30h
	mov rax, [rcx]
	mov rdx, [rbp-28h] ;-> -28h
	call qword ptr [rax+68h]
loc_142368C14:
	mov qword ptr [rbp-10h], 7 ;-> -10h
	mov [rbp-20h], r15 ;-> -20h
	mov word ptr [rbp-28h], r15w ;-> -28h
	mov rax, [rdi]
	mov rcx, rdi
	call qword ptr [rax+80h]
	mov r8d, eax
	mov [rbp-50h], eax
	mov ebx, r15d
	lea rcx, [rbp-4Ch]
	lea rax, [rbp-50h]
	cmp r13d, r8d
	cmovge rcx, rax
	mov r12d, [rcx]
	jle loc_142368D08
	mov eax, r8d
	cdq
	and edx, 7
	add edx, eax
	sar edx, 3
	inc edx
	cmp r14d, 4
	jnb loc_142368C6E
	movsx r9d, word ptr [rsi+r14*2+18h]
	jmp loc_142368C71 ;static check
loc_142368C6E:
	mov r9d, r15d
loc_142368C71:
	mov eax, edx
	sub eax, r8d
	inc eax
	cmp r9d, eax
	jge loc_142368C93
	cmp r14d, 4
	jnb loc_142368CA1
	movzx ecx, dx
	sub cx, r8w
	inc cx
	mov [rsi+r14*2+18h], cx
loc_142368C93:
	cmp r14d, 4
	jnb loc_142368CA1
	movsx ecx, word ptr [rsi+r14*2+18h]
	jmp loc_142368CA4
loc_142368CA1:
	mov ecx, r15d
loc_142368CA4:
	mov eax, edx
	neg eax
	cmp ecx, eax
	jle loc_142368CBB
	cmp r14d, 4
	jnb loc_142368CC9
	neg dx
	mov [rsi+r14*2+18h], dx
loc_142368CBB:
	cmp r14d, 4
	jnb loc_142368CC9
	movsx ecx, word ptr [rsi+r14*2+18h]
	jmp loc_142368CCC
loc_142368CC9:
	mov ecx, r15d
loc_142368CCC:
	mov ebx, [rbp-48h]
	add ebx, ecx
	lea ecx, [rbx+r8]
	mov [rbp-50h], ecx
	cmp ecx, r13d
	jle loc_142368CE9
	mov ecx, r13d
	mov [rbp-50h], ecx
	mov ebx, r13d
	sub ebx, r8d
loc_142368CE9:
	test ebx, ebx
	jns loc_142368CF6
	mov ebx, r15d
	mov ecx, r8d
	mov [rbp-50h], ecx
loc_142368CF6:
	lea rax, [rbp-50h]
	lea rdx, [rbp-4Ch]
	cmp ecx, r13d
	cmovge rax, rdx
	mov r12d, [rax]
loc_142368D08:
	mov r15d, [rbp-48h]
	cmp r14d, 4
	jnb loc_142368D1F
	movzx ecx, bx
	sub cx, r15w
	mov [rsi+r14*2+18h], cx
loc_142368D1F:
	mov rax, [rdi]
	cmp r12d, r13d
	setl r8b
	test ebx, ebx
	setnle dl
	mov rcx, rdi
	call qword ptr [rax+48h]
	mov rax, [rdi]
	mov r9d, r12d
	sub r9d, ebx
	mov r8d, ebx
	mov edx, r13d
	mov rcx, rdi
	call qword ptr [rax+50h]
	cmp ebx, r12d
	jge loc_142368DAB
	xchg ax, ax
loc_142368D50:
	cmp ebx, r15d
	jne loc_142368D92
	mov rax, [rdi]
	mov rcx, rdi
	cmp byte ptr [rdi+18h], 0
	je loc_142368D8F
	mov edx, 0FFC0FF80h
	call qword ptr [rax+28h]
	mov rax, [rdi]
	mov rcx, rdi
	call qword ptr [rax+40h]
	mov rax, [rsi]
	mov r8d, ebx
	mov rdx, rdi
	mov rcx, rsi
	call qword ptr [rax+88h]
	mov rax, [rdi]
	mov rcx, rdi
	call qword ptr [rax+30h]
	jmp loc_142368DA4
loc_142368D8F:
	call qword ptr [rax+40h]
loc_142368D92:
	mov rax, [rsi]
	mov r8d, ebx
	mov rdx, rdi
	mov rcx, rsi
	call qword ptr [rax+88h]
loc_142368DA4:
	inc ebx
	cmp ebx, r12d
	jl loc_142368D50
loc_142368DAB:
	mov edx, 2
	jmp loc_142368E87
loc_142368DB5:
	test r12b, r12b
	je loc_142368DCB
	mov rax, [rsi]
	mov r8, rdi
	mov edx, 10h
	mov rcx, rsi
	call qword ptr [rax+58h]
loc_142368DCB:
	call func1
	mov rbx, rax
	mov rax, [rax]
	xor r8d, r8d
	lea rdx, [rbp-4Ch]
	mov rcx, rbx
	call qword ptr [rax+18h]
	mov ecx, [rax]
	shr ecx, 5
	test cl, 1
	jne loc_142368E01
	lea r8, heapstring
	mov edx, 3Eh
	xor ecx, ecx
	call func2
	int 3
loc_142368E01:
	xor r15d, r15d
	mov [rbp-1Ch], r15			;-> -1Ch
	mov [rbp-14h], r15			;-> -14h
	mov [rbp-2Ch], rbx			;-> -2Ch
	mov qword ptr [rbp-0Ch], 7	;-> -0Ch
	mov [rbp-1Ch], r15			;-> -1Ch
	mov word ptr [rbp-24h], r15w ;-> -24h
	mov byte ptr [rbp-4], 1	;-> -4h
loc_142368E25:
	mov rax, [rsi]
	lea rdx, [rbp-2Ch]			;-> -2Ch
	mov rcx, rsi
	call qword ptr [rax+48h]
	lea r8, [rbp-24h]			;-> -24h
	cmp qword ptr [rbp-0Ch], 8	;-> -0Ch
	cmovnb r8, [rbp-24h]		;-> -24h
	mov rax, [rdi]
	mov r9d, r13d
	lea rdx, nodestring
	mov rcx, rdi
	call qword ptr [rax+78h]
	nop
loc_142368E57:
	cmp qword ptr [rbp-0Ch], 8	;-> -0Ch
	jb loc_142368E6C
	mov rcx, [rbp-2Ch]			;-> -2Ch
	mov rax, [rcx]
	mov rdx, [rbp-24h]			;-> -24h
	call qword ptr [rax+68h]
loc_142368E6C:
	mov qword ptr [rbp-0Ch], 7	;-> -0Ch
	mov [rbp-1Ch], r15			;-> -1Ch
	mov word ptr [rbp-24h], r15w ;-> -24h
	test r12b, r12b
	je loc_142368E93
	mov edx, 20h
loc_142368E87:
	mov rax, [rsi]
	mov r8, rdi
	mov rcx, rsi
	call qword ptr [rax+58h]
loc_142368E93:
	mov rbx, [rsp+0C0h]
	add rsp, 70h
	pop r15
	pop r14
	pop r13
	pop r12
	pop rdi
	pop rsi
	pop rbp
	ret
fShowParamDebugMenu ENDP

END