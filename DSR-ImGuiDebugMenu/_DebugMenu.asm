EXTERN bDrawDebugMenuGOGOGO:QWORD
EXTERN bOpenLogConsole:QWORD
EXTERN textHighlightColor:DWORD
EXTERN g_isOpenConsole:BYTE
EXTERN bExitButtonComboCheck1:QWORD
EXTERN bExitButtonComboCheck2:QWORD
EXTERN bExitButtonComboCheck3:QWORD
EXTERN rootString:QWORD

.data
	AllocDebugMem QWORD 1401687F0h
	DebugMemAddress1 QWORD 140168891h
	DebugMemAddress2 QWORD 1401688B8h
	DebugMemAddress3 QWORD 1401688FEh
	AllocDebugMemAddress QWORD 14017651Bh
	origBytes BYTE 0E8h, 0D0h, 022h, 0FFh, 0FFh
.code


.data
	pDbgMenuMan QWORD 141C04CC8h

.code

fGetDebugMenuLabelNode PROC
	mov rax, pDbgMenuMan
	mov rax, [rax]
	test rax, rax
	je ende
	mov rax, [rax+8]
ende:
	ret
fGetDebugMenuLabelNode ENDP

.data
	
.code

tDrawDebugMenuGOGOGO PROC
	call fDrawDebugMenuGOGOGO
	jmp [bDrawDebugMenuGOGOGO]
tDrawDebugMenuGOGOGO ENDP

.data
	pHgMan QWORD 141C04ED8h
	pDbgMenuLabelNode QWORD 0
	getDbgMenuLabelNode QWORD 140152AF0h
	timeStepValue DWORD 3C888889h
	dbgMenuCtrl QWORD 0
	windowCount DWORD 0
	GetAsyncKeyState QWORD 1420B59E0h
.code

fDrawDebugMenuGOGOGO PROC
	;sub rsp, 28h
	push rbx
	push rbp
	push rsi
	push rdi
	sub rsp, 28h
	mov rsi, pDbgMenuMan
	mov rsi, [rsi]
	cmp qword ptr [rsi+8], 0
	lea rax, [rsi+8]
	mov rbx, rsi
	mov [pDbgMenuLabelNode], rax
	je loc_F96FD0
	mov rax, [rsi+18h]
	lea rdi, [rsi+18h]
	test rax, rax
	je loc_F96FD0
control:
	mov rcx, [rax+18h]
	mov rbp, [rax+20h]
	mov [dbgMenuCtrl], rcx
	test rcx, rcx
	je loc_F96FD0
	mov rax, rcx
	call fPassInputToDbgCtrl
	mov ecx, [rax+1Ch]
	shr ecx, 0Fh
	test cl, 1
	je checkMenuState
	mov eax, [rsi+28h]
	mov cl, 1
	cmp eax, 1
	je loc_F96E4E
	xor cl, cl
loc_F96E4E:
	add eax, 4
	cdq
	mov ebx, 3
	idiv ebx
	mov al, 1
	mov [rsi+28h], edx
	cmp edx, 1
	je loc_F96E65
	xor al, al
loc_F96E65:
	cmp cl, al
	je loc_F96E9F
	test al, al
	je loc_F96E87
	xor rcx, rcx
	call fDbgMenuControlFocus
	mov rcx, 1
	call fDbgMenuControlFocus
	mov rcx, rbx
	call fDbgMenuControlFocus
	jmp loc_F96E9F
loc_F96E87:
	xor rdx, rdx
	call fDbgMenuControlDefocus
	mov rdx, 1
	call fDbgMenuControlDefocus
	mov rdx, rbx
	call fDbgMenuControlDefocus
loc_F96E9F:
	mov rbx, rsi
checkMenuState:
	mov eax, [rbx+28h]
	sub eax, 1
	jne loc_F96FD0
	mov rsi, [pDbgMenuLabelNode]
	mov rcx, [rsi]
	mov rax, [rcx]
	mov rdx, [dbgMenuCtrl]
	call qword ptr [rax+18h]
	test rbp, rbp
	je loc_F96ED4
	mov rdx, [dbgMenuCtrl]
	mov rax, [rbp]
	mov rcx, rbp
	call qword ptr [rax+18h]
loc_F96ED4:
	mov rbp, [dbgMenuCtrl]
	test byte ptr [rbp+1Eh], 1
	je loc_F96F4A
	mov rax, [rbx+20h]
	test rax, rax
	je loc_F96F4A
	mov rcx, [rsi]
	mov rsi, [rdi]
	;mov r8, [rsi]
	mov r8d, [rsi+4]
	;mov rdx, [rax]
	mov edx, [rax+4]
	mov rax, [rcx]
	call qword ptr [rax+8]
	mov rcx, [rbx+20h]
	mov rdx, [rcx+10h]
	mov rax, rdx
	sub rax, rcx
	neg rax
	sbb rax, rax
	and rax, rdx
	mov [rbx+20h], rax
	mov rax, [rcx+8]
	test rax, rax
	je loc_F96F16
	mov rdx, [rcx+10h]
	mov [rax+10h], rdx
loc_F96F16:
	mov rax, [rcx+10h]
	test rax, rax
	je loc_F96F23
	mov rdx, [rcx+8]
	mov [rax+8], rdx
loc_F96F23:
	mov rax, [rdi]
	test rax, rax
	je loc_F96F42
	mov [rcx+10h], rax
	mov rax, [rdi]
	mov rdx, [rax+8]
	mov rax, [rcx+10h]
	mov [rcx+8], rdx
	mov [rax+8], rcx
	mov rdx, [rcx+8]
	mov [rdx+10h], rcx
	jmp loc_F96F48
loc_F96F42:
	mov [rcx+10h], rcx
	mov [rcx+8], rcx
loc_F96F48:
	mov [rdi], rcx
loc_F96F4A:
	mov eax, dword ptr [rbp+1Ch]
	shr eax, 11h
	test al, 1
	je loc_F96FAE
	mov rax, [rdi]
	cmp [rax+10h], rax
	je loc_F96FAE
	mov rdx, [rax+10h]
	mov rcx, rdx
	sub rcx, rax
	neg rcx
	sbb rcx, rcx
	and rcx, rdx
	mov [rdi], rcx
	mov rcx, [rax+8]
	test rcx, rcx
	je loc_F96F77
	mov rdx, [rax+10h]
	mov [rcx+10h], rdx
loc_F96F77:
	mov rcx, [rax+10h]
	test rcx, rcx
	je loc_F96F84
	mov rdx, [rax+8]
	mov [rcx+8], rdx
loc_F96F84:
	mov rcx, [rbx+20h]
	test rcx, rcx
	je loc_F96FA5
	mov [rax+10h], rcx
	mov rcx, [rbx+20h]
	mov rdx, [rcx+8]
	mov rcx, [rax+10h]
	mov [rax+8], rdx
	mov [rcx+8], rax
	mov rdx, [rax+8]
	mov [rdx+10h], rax
	jmp loc_F96FAB
loc_F96FA5:
	mov [rax+10h], rax
	mov [rax+8], rax
loc_F96FAB:
	mov [rbx+20h], rax
loc_F96FAE:
	mov eax, [rbp+1Ch]
	shr eax, 13h
	test al, 1
	je loc_F96FBF
	mov rcx, [rdi]
	mov rdx, [rcx+10h]
	mov [rdi], rdx
loc_F96FBF:
	mov eax, [rbp+1Ch]
	shr eax, 12h
	test al, 1
	je loc_F96FD0
	mov rcx, [rdi]
	mov rdx, [rcx+8]
	mov [rdi], rdx
loc_F96FD0:
	mov rax, [pDbgMenuLabelNode]
	cmp qword ptr [rax], 0
	je nonode
	mov rax, [rbx+18h]
	test rax, rax
	je lbl1
	mov rdi, [rax+8]
	jmp lbl2
lbl1:
	xor rdi, rdi
lbl2:
	mov [windowCount], 0
	test rdi, rdi
	je nonode
	mov rbp, 70h
loopstart:
	mov rsi, [rdi+20h]
	test rsi, rsi			;DbgMenuHgDraw
	je loc_F97074
	cmp [windowCount], 4
	jnb loc_F97074
	mov rcx, pHgMan
	mov rcx, [rcx]
	mov rax, [rcx+rbp]
	test rax, rax
	je loc_F97074
	mov rdx, [rsi]
	inc [windowCount]
	mov [rsi+20h], rax
	add rbp, 8
	mov byte ptr [rsi+18h], 0
	mov rcx, rsi
	call qword ptr [rdx+20h]
	movss xmm1, dword ptr [timeStepValue]
	mov rdx, [rsi]
	mov rcx, rsi
	call qword ptr [rdx+10h]
	mov eax, [rbx+28h]
	sub eax,  1
	je loc_F97052
	sub eax, 1
	jnz loc_F97074
	jmp loc_F9705B
loc_F97052:
	cmp rdi, [rbx+18h]
	jne loc_F9705B
	mov byte ptr [rsi+18h], 1
loc_F9705B:
	mov rdx, [rsi]
	mov rcx, rsi
	call qword ptr [rdx+38h]
	mov rcx, pDbgMenuLabelNode
	mov rcx, [rcx]
	mov rax, [rcx]
	mov r8, 1
	mov rdx, rsi
	call qword ptr [rax+20h]
loc_F97074:
	cmp rdi, [rbx+18h]
	je nonode
	mov rdi, [rdi+8]
	test rdi, rdi
	jne loopstart
nonode:
	add rsp, 28h
	pop rdi
	pop rsi
	pop rbp
	pop rbx
	;add rsp, 28h
	ret

fDrawDebugMenuGOGOGO ENDP

.data 
	nodestring BYTE 5Bh, 0, 25h, 0, 73h, 0, 5Dh, 0, 28h, 0, 25h, 0, 64h, 0, 29h, 0, 0, 0 
	heapstring QWORD 1414A1BC8h
	func1 QWORD 140CC0D60h
	func2 QWORD 140D4FD10h
	funcSpecial QWORD 1400BCC60h

.code

fDrawDebugMenu PROC

	push rbp
	push rsi
	push rdi
	push r12
	push r13
	push r14
	push r15
	lea rbp, [rsp-27h]
	sub rsp, 90h
	;mov rax, 0					;REMOVE LATER
	;mov rax, [rax]				;
	mov qword ptr [rbp-21h], -2
	mov [rsp+0E0h], rbx
	movzx r13d, r8b
	mov rdi, rdx
	mov rsi, rcx
	mov r15, [rcx+30h]
	sub r15, [rcx+28h]
	sar r15, 3
	mov [rbp-3Dh], r15d
	mov r12d, [rdx+10h]
	mov ebx, [rdx+14h]
	mov rax, [rcx]
	mov edx, ebx
	call qword ptr [rax+40h]
	test al, al
	je loc_142334CD6
	mov dword ptr [rbp-41h], -1
	xor r14d, r14d
	mov [rbp-39h], r14
	test r15d, r15d
	jle loc_142334A4F
	mov rcx, [rdi+8]
	test rcx, rcx
	je loc_142334879
	mov r8d, r12d
	mov rdx, rsi
	call fAdditionalDbgFunc
	test eax, eax
	js loc_142334879
	cmp eax, r15d
	jge loc_142334879
	movsxd r8, eax
	mov rcx, [rsi+28h]
	mov r13, [rcx+r8*8]
	mov ecx, [r13+10h]
	and ecx, ebx
	test cl, 0Fh
	je loc_142334879
	mov [rbp-41h], eax
	jmp loc_142334960
loc_142334879:
	mov rax, [rdi]
	mov rcx, [rdi]
	call qword ptr [rax+80h]
	cmp r12d, 4
	jnb loc_142334893
	movsx edx, word ptr [rsi+r12*2+18h]
	jmp loc_142334896
loc_142334893:
	mov edx, r14d
loc_142334896:
	mov [rbp-49h], edx
	lea ecx, [r15-1]
	mov [rbp-25h], ecx
	mov [rbp-2Dh], r14d
	mov [rbp-29h], ecx
	mov [rbp-31h], r14d
	lea r9d, [rdx+rax]
	mov [rbp-45h], r9d
	test edx, edx
	jns loc_1423348BD
	lea r8, [rbp-2Dh]
	jmp loc_1423348CB
loc_1423348BD:
	lea r8, [rbp-25h]
	lea rax, [rbp-49h]
	cmp edx, ecx
	cmovle r8, rax
loc_1423348CB:
	test r9d, r9d
	jns loc_1423348D6
	lea rax, [rbp-31h]
	jmp loc_1423348E5
loc_1423348D6:
	lea rax, [rbp-29h]
	lea rdx, [rbp-45h]
	cmp r9d, ecx
	cmovle rax, rdx
loc_1423348E5:
	mov eax, [rax]
	add eax, [r8]
	cdq
	sub eax, edx
	sar eax, 1
	movsxd r10, eax
	lea edx, [r10+1]
	mov r8, r10
	movsxd rcx, edx
	lea r9, [rcx*8]
loc_142334904:
	test r8, r8
	jns loc_142334914
	cmp edx, r15d
	jge loc_142334A4F
	jmp loc_14233492A
loc_142334914:
	mov rax, [rsi+28h]
	mov rcx, [rax+r8*8]
	mov eax, [rcx+10h]
	and eax, ebx
	test al, 0Fh
	jne loc_142334951
	cmp edx, r15d
	jge loc_14233493B
loc_14233492A:
	mov rax, [rsi+28h]
	mov rcx, [r9+rax]
	mov eax, [rcx+10h]
	and eax, ebx
	test al, 0Fh
	jne loc_142334949
loc_14233493B:
	dec r10d
	dec r8
	inc edx
	add r9, 8
	jmp loc_142334904
loc_142334949:
	mov [rbp-41h], edx
	movsxd rcx, edx
	jmp loc_142334958
loc_142334951:
	mov [rbp-41h], r10d
	movsxd rcx, r10d
loc_142334958:
	mov rax, [rsi+28h]
	mov r13, [rax+rcx*8]
loc_142334960:
	mov [rbp-39h], r13
	mov rax, [r13+0]
	mov edx, ebx
	mov rcx, r13
	call qword ptr [rax+40h]
	test al, al
	je loc_142334A4F
	mov rax, [rsi]
	mov r8, rdi
	mov edx, 4
	mov rcx, rsi
	call qword ptr [rax+58h]
	mov rax, [r13+0]
	mov r8b, 1
	mov rdx, rdi
	mov rcx, r13
	;call fDrawDebugMenu
	call qword ptr [rax+20h]
	call func1
	mov rbx, rax
	mov rax, [rax]
	xor r8d, r8d
	lea rdx, [rbp-45h]
	mov rcx, rbx
	call qword ptr [rax+18h]
	mov ecx, [rax]
	shr ecx, 5
	test cl, 1
	jne loc_1423349CF
	mov r8, heapstring
	mov edx, 3Eh
	xor ecx, ecx
	call func2
	int 3
loc_1423349CF:
	mov [rbp-15h], r14
	mov [rbp-0Dh], r14
	;mov [rbp+7], rbx
	mov [rbp-25h], rbx
	mov qword ptr [rbp-5], 7
	mov [rbp-15h], r14
	mov word ptr [rbp-1Dh], r14w
	mov byte ptr [rbp+3], 1
loc_1423349F0:
	mov rax, [rsi]
	lea rdx, [rbp-25h]
	mov rcx, rsi
	call qword ptr [rax+48h]
	lea r8, [rbp-1Dh]
	cmp qword ptr [rbp-5], 8
	cmovnb r8, [rbp-1Dh]
	mov rax, [rdi]
	mov r9d, r15d
	lea rdx, nodestring
	mov rcx, rdi
	call qword ptr [rax+58h]
loc_142334A1F:
	cmp qword ptr [rbp-5], 8
	jb loc_142334A34
	;mov rcx, [rbp+7]
	mov rcx, [rbp-25h]
	mov rax, [rcx]
	mov rdx, [rbp-1Dh]
	call qword ptr [rax+68h]
loc_142334A34:
	mov qword ptr [rbp-5], 7
	mov [rbp-15h], r14
	mov word ptr [rbp-25h], r14w
	mov edx, 8
	jmp loc_142334DA8
loc_142334A4F:
	mov rax, [rsi]
	mov r8, rdi
	mov edx, 1
	mov rcx, rsi
	call qword ptr [rax+58h]
	call func1
	mov rbx, rax
	mov rax, [rax]
	xor r8d, r8d
	lea rdx, [rbp-45h]
	mov rcx, rbx
	call qword ptr [rax+18h]
	mov ecx, [rax]
	shr ecx, 5
	test cl, 1
	jne loc_142334A96
	mov r8, heapstring
	mov edx, 3Eh
	xor ecx, ecx
	call func2
	int 3
loc_142334A96:
	mov [rbp-15h], r14
	mov [rbp-0Dh], r14
	mov [rbp-25h], rbx
	mov qword ptr [rbp-5], 7
	mov [rbp-15h], r14
	mov word ptr [rbp-1Dh], r14w
	mov byte ptr [rbp+3], 1
loc_142334AB7:
	mov rax, [rsi]
	lea rdx, [rbp-25h]
	mov rcx, rsi
	call qword ptr [rax+48h]
	lea r8, [rbp-1Dh]
	cmp qword ptr [rbp-5], 8
	cmovnb r8, [rbp-1Dh]
	mov rax, [rdi]
	mov r9d, r15d
	lea rdx, nodestring
	mov rcx, rdi
	call qword ptr [rax+58h]
loc_142334AE6:
	cmp qword ptr [rbp-5], 8
	jb loc_142334AFB
	mov rcx, [rbp-25h]
	mov rax, [rcx]
	mov rdx, [rbp-1Dh]
	call qword ptr [rax+68h]
loc_142334AFB:
	mov qword ptr [rbp-5], 7
	mov [rbp-15h], r14
	mov word ptr [rbp-1Dh], r14w
	mov rax, [rdi]
	mov rcx, rdi
	call qword ptr [rax+80h]
	mov r8d, eax
	mov [rbp-45h], eax
	mov ebx, r14d
	lea rcx, [rbp-3Dh]
	lea rax, [rbp-45h]
	cmp r15d, r8d
	cmovge rcx, rax
	mov r13d, [rcx]
	cmp [rbp-39h], rbx
	je loc_142334C16
	cmp r15d, r8d
	jle loc_142334BFF
	mov eax, r8d
	cdq
	and edx, 7
	add edx, eax
	sar edx, 3
	inc edx
	cmp r12d, 4
	jnb loc_142334B62
	movsx r9d, word ptr [rsi+r12*2+18h]
	jmp loc_142334B65
loc_142334B62:
	mov r9d, r14d
loc_142334B65:
	mov eax, edx
	sub eax, r8d
	inc eax
	cmp r9d, eax
	jge loc_142334B87
	cmp r12d, 4
	jnb loc_142334B95
	movzx ecx, dx
	sub cx, r8w
	inc cx
	mov [rsi+r12*2+18h], cx
loc_142334B87:
	cmp r12d, 4
	jnb loc_142334B95
	movsx ecx, word ptr [rsi+r12*2+18h]
	jmp loc_142334B98
loc_142334B95:
	mov ecx, r14d
loc_142334B98:
	mov eax, edx
	neg eax
	cmp ecx, eax
	jle loc_142334BAF
	cmp r12d, 4
	jnb loc_142334BBD
	neg dx
	mov [rsi+r12*2+18h], dx
loc_142334BAF:
	cmp r12d, 4
	jnb loc_142334BBD
	movsx ecx, word ptr [rsi+r12*2+18h]
	jmp loc_142334BC0
loc_142334BBD:
	mov ecx, r14d
loc_142334BC0:
	mov edx, [rbp-41h]
	lea ebx, [rcx+rdx]
	lea ecx, [rbx+r8]
	mov [rbp-49h], ecx
	cmp ecx, r15d
	jle loc_142334BDE
	mov ecx, r15d
	mov [rbp-49h], ecx
	mov ebx, r15d
	sub ebx, r8d
loc_142334BDE:
	test ebx, ebx
	jns loc_142334BEB
	mov ebx, r14d
	mov ecx, r8d
	mov [rbp-49h], ecx
loc_142334BEB:
	lea rax, [rbp-49h]
	lea r8, [rbp-3Dh]
	cmp ecx, r15d
	cmovge rax, r8
	mov r13d, [rax]
	jmp loc_142334C02
loc_142334BFF:
	mov edx, [rbp-41h]
loc_142334C02:
	cmp r12d, 4
	jnb loc_142334C22
	movzx ecx, bx
	sub cx, dx
	mov [rsi+r12*2+18h], cx
	jmp loc_142334C22
loc_142334C16:
	cmp r12d, 4
	jnb loc_142334C22
	mov [rsi+r12*2+18h], r14w
loc_142334C22:
	mov rax, [rdi]
	cmp r13d, r15d
	setl r8b
	test ebx, ebx
	setnle dl
	mov rcx, rdi
	call qword ptr [rax+48h]
	mov rax, [rdi]
	mov r9d, r13d
	sub r9d, ebx
	mov r8d, ebx
	mov edx, r15d
	mov rcx, rdi
	call qword ptr [rax+50h]
	movsxd r14, ebx
	cmp ebx, r13d
	jge loc_142334CCC
	lea r14, [r14*8]
	mov r15d, [rbp-41h]
loc_142334C64:
	cmp ebx, r15d
	jne loc_142334CAD
	mov rax, [rdi]
	mov rcx, rdi
	cmp byte ptr [rdi+18h], 0
	je loc_142334CA5
	;mov edx, 0FFC0FF80h
	mov edx, [textHighlightColor]
	call qword ptr [rax+28h]	;changeEzDrawStateColor
	mov rax, [rdi]
	mov rcx, rdi
	call qword ptr [rax+40h]
	mov rax, [rsi+28h]
	mov rcx, [r14+rax]
	mov rax, [rcx]
	mov r8b, 1
	mov rdx, rdi
	call qword ptr [rax+20h]
	mov rax, [rdi]
	mov rcx, rdi
	call qword ptr [rax+30h]
	jmp loc_142334CC1
loc_142334CA5:
	call qword ptr [rax+40h]
	mov r8b, 1
	jmp loc_142334CB0
loc_142334CAD:
	xor r8d, r8d
loc_142334CB0:
	mov rax, [rsi+28h]
	mov rcx, [r14+rax]
	mov rax, [rcx]
	mov rdx, rdi
	call qword ptr [rax+20h]
loc_142334CC1:
	inc ebx
	add r14, 8
	cmp ebx, r13d
	jl loc_142334C64
loc_142334CCC:
	mov edx, 2
	jmp loc_142334DA8
loc_142334CD6:
	test r13b, r13b
	je loc_142334CEC
	mov rax, [rsi]
	mov r8, rdi
	mov edx, 10h
	mov rcx, rsi
	call qword ptr [rax+58h]
loc_142334CEC:
	call func1
	mov rbx, rax
	mov rax, [rax]
	xor r8d, r8d
	lea rdx, [rbp-45h]
	mov rcx, rbx
	call qword ptr [rax+18h]
	mov ecx, [rax]
	shr ecx, 5
	test cl, 1
	jne loc_142334D22
	mov r8, heapstring
	mov edx, 3Eh
	xor ecx, ecx
	call func2
	int 3
loc_142334D22:
	xor r14d, r14d
	mov [rbp-15h], r14
	mov [rbp-0Dh], r14
	;mov [rbp+7], rbx
	mov [rbp-25h], rbx
	mov qword ptr [rbp-5], 7
	mov [rbp-15h], r14
	mov word ptr [rbp-1Dh], r14w
	mov byte ptr [rbp+3], 1
loc_142334D46:
	mov rax, [rsi]
	lea rdx, [rbp-25h]
	mov rcx, rsi
	call qword ptr [rax+48h]
	lea r8, [rbp-1Dh]
	cmp qword ptr [rbp-5], 8
	cmovnb r8, [rbp-1Dh]
	mov rax, [rdi]
	mov r9d, r15d
	lea rdx, nodestring
	mov rcx, rdi
	call qword ptr [rax+78h]
loc_142334D78:
	cmp qword ptr [rbp-5], 8
	jb loc_142334D8D
	;mov rcx, [rbp+7]
	mov rcx, [rbp-25h]
	mov rax, [rcx]
	mov rdx, [rbp-1Dh]
	call qword ptr [rax+68h]
loc_142334D8D:
	mov qword ptr [rbp-5], 7
	mov [rbp-15h], r14
	mov word ptr [rbp-1Dh], r14w
	test r13b, r13b
	je loc_142334DB4
loc_142334DA8:
	mov rax, [rsi]
	mov r8, rdi
	mov rcx, rsi
	call qword ptr [rax+58h]
loc_142334DB4:
	mov rbx, [rsp+0E0h]
	add rsp, 90h
	pop r15
	pop r14
	pop r13
	pop r12
	pop rdi
	pop rsi
	pop rbp
	ret

fDrawDebugMenu ENDP

.data
	
.code

fAdditionalDbgFunc PROC
	mov r11, [rcx+8]
	test r11, r11
	je returno
	mov r10d, [rcx+10h]
	mov r9d, r10d
loopbegin:
	movsxd rax, r9d
	add rax, rax
	cmp [r11+rax*8], rdx
	jne branch1
	movsx ecx, word ptr [r11+rax*8+8]
	cmp ecx, r8d
	je branch2
branch1:
	movsx r9d, word ptr [r11+rax*8+0Eh]
	cmp r9d, r10d
	jne loopbegin
returno:
	or eax, -1
	ret
branch2:
	test r9d, r9d
	js returno
	movsxd rax, r9d
	add rax, rax
	movsx eax, word ptr [r11+rax*8+0Ah]
	ret
fAdditionalDbgFunc ENDP

.data
funcCreateSyncSth QWORD 140CBEDE0h

.code

fControlDebugMenu PROC

	mov rax, rsp
	push rbp
	push rdi
	push r14
	sub rsp, 60h
	mov r10, [rcx+28h]
	mov ebp, [rdx+10h]
loc_142334062:
	mov [rax+18h], rbx
	mov [rax-20h], rsi
	mov [rax-28h], r12
	mov r12d, [rdx+14h]
	mov [rax-30h], r13
	mov [rax-38h], r15
	mov r15, [rcx+30h]
	sub r15, r10
	or r13d, -1
	mov r14, rdx
	xor edx, edx
	sar r15, 3
	mov rdi, rcx
	mov [rsp+80h], r13d
	mov esi, edx
	mov [rsp+30h], rdx
	test r15d, r15d
	jle loc_1423341DC
	mov rax, [r14+8]
	test rax, rax
	je loc_1423340E5
	mov r8, [rax+8]
	test r8, r8
	je loc_1423340E5
	mov r9d, [rax+10h]
	mov edx, r9d
loc_1423340C2:
	movsxd rcx, edx
	add rcx, rcx
	cmp [r8+rcx*8], rdi
	jne loc_1423340D8
	movsx eax, word ptr [r8+rcx*8+8]
	cmp eax, ebp
	je loc_1423340F8
loc_1423340D8:
	movsx edx, word ptr [r8+rcx*8+0Eh]
	cmp edx, r9d
	jne loc_1423340C2
loc_1423340E3:
	xor edx, edx
loc_1423340E5:
	cmp ebp, 4
	jnb loc_142334134
	movsx ecx, word ptr [rdi+rbp*2+18h]
	mov dword ptr [rsp+88h], ecx
	jmp loc_14233413D
loc_1423340F8:
	test edx, edx
	js loc_1423340E3
	movsxd rax, edx
	add rax, rax
	movsx rcx, word ptr [r8+rax*8+0Ah]
	test ecx, ecx
	js loc_1423340E3
	cmp ecx, r15d
	jge loc_1423340E3
	mov rdx, [r10+rcx*8]
	mov eax, [rdx+10h]
	and eax, r12d
	test al, 0Fh
	je loc_1423340E3
	mov rax, [rdx]
	mov r13d, ecx
	mov [rsp+80h], ecx
	mov rsi, rdx
	jmp loc_14233443E
loc_142334134:
	mov ecx, edx
	mov dword ptr [rsp+88h], edx
loc_14233413D:
	lea eax, [r15-1]
	mov dword ptr [rsp+98h], edx
	mov [rsp+24h], edx
	lea edx, [rcx+10h]
	mov [rsp+20h], eax
	mov [rsp+28h], eax
	mov [rsp+2Ch], edx
	test ecx, ecx
	jns loc_142334169
	lea r8, [rsp+98h]
	jmp loc_14233417C
loc_142334169:
	lea r8, [rsp+20h]
	lea r9, [rsp+88h]
	cmp ecx, eax
	cmovle r8, r9
loc_14233417C:
	test edx, edx
	jns loc_142334187
	lea rcx, [rsp+24h]
	jmp loc_142334197
loc_142334187:
	lea rcx, [rsp+28h]
	lea r9, [rsp+2Ch]
	cmp edx, eax
	cmovle rcx, r9
loc_142334197:
	mov eax, [r8]
	add eax, [rcx]
	cdq
	sub eax, edx
	sar eax, 1
	movsxd r11, eax
	movsxd rax, r15d
	lea ebx, [r11+1]
	mov r8, r11
	mov [rsp+88h], rax
	movsxd rdx, ebx
	lea r9, [r10+rdx*8]
	lea r10, [r10+r11*8]
loc_1423341C1:
	test r8, r8
	jns loc_1423343DD
	cmp rdx, rax
	jl loc_1423343F8
	mov r10, [rdi+28h]
	xor edx, edx
	test r15d, r15d
loc_1423341DC:
	je loc_1423341F4
	mov rsi, [r10]
	mov eax, r12d
	mov r13d, edx
	and eax, 0Fh
	mov [rsp+80h], edx
	or [rsi+10h], eax
loc_1423341F4:
	mov rax, [rdi]
	mov edx, r12d
	mov rcx, rdi
	call qword ptr [rax+40h]
	mov r8, r14
	mov rcx, rdi
	test al, al
	mov rax, [rdi]
	je loc_142334716
	mov ebx, [r14+1Ch]
	shr ebx, 0Eh
	and bl, 1
	cmp qword ptr [rsp+30h], 0
	mov dword ptr [rsp+88h], ebx
	je loc_142334519
	mov edx, 4
	call qword ptr [rax+50h]
	mov rcx, [rsp+30h]
	mov r8b, 1
	mov rax, [rcx]
	mov rdx, r14
	call qword ptr [rax+10h]
	mov rcx, [rsp+30h]
	mov r13, rax
	test rax, rax
	je loc_14233430C
	cmp rax, rcx
	je loc_14233430C
	mov edx, [rsi+10h]
	mov rbx, [rax]
	mov rcx, rsi
	and edx, 0Fh
	or [rax+10h], edx
	mov rdx, [rsi]
	call qword ptr [rdx+38h]
	mov rcx, r13
	mov edx, eax
	call qword ptr [rbx+28h]
	movsxd rax, dword ptr [rsp+80h]
	lea rsi, [rax*8]
	mov rax, [rdi+28h]
	mov rcx, [rsi+rax]
	xor eax, eax
	mov [rcx+8], rax
	mov rax, [rdi+28h]
	mov rax, [rsi+rax]
	mov [rsp+98h], rax
	test rax, rax
	je loc_1423342EB
	mov rcx, rax
	;call 140CBEDE0h
	call funcCreateSyncSth
	xor edx, edx
	mov rbx, rax
	mov rax, [rsp+98h]
	mov r8, [rax]
	mov rcx, rax
	call qword ptr [r8]
	mov r8, [rbx]
	mov rdx, [rsp+98h]
	mov rcx, rbx
	call qword ptr [r8+58h]
	mov rax, [rdi+28h]
	xor edx, edx
	mov [rsi+rax], rdx
loc_1423342EB:
	mov rax, [rdi+28h]
	mov ebx, dword ptr [rsp+88h]
	mov rcx, r13
	mov [rsi+rax], r13
	or dword ptr [r13+10h], 100h
	mov rsi, r13
	mov [r13+8], rdi
loc_14233430C:
	mov rax, [rcx]
	mov r8b, 1
	mov rdx, r14
	call qword ptr [rax+18h]
	cmp dword ptr [r14+18h], 1
	jne loc_14233450F
	test bl, bl
	je loc_14233450F
	test r15d, r15d
	je loc_14233450F
	mov r8d, [r14+1Ch]
	mov edx, r8d
	mov r9d, r8d
	mov r10d, r8d
	shr edx, 1
	shr r9d, 5
	shr r10d, 4
	movzx eax, r8b
	and dl, 1
	and r9b, 1
	and al, 1
	and r10b, 1
	cmp al, dl
	je loc_14233450F
	mov ecx, r8d
	shr r8d, 0Ah
	mov eax, 1
	shr ecx, 9
	and ecx, 1
	add ecx, ecx
	or ecx, 1
	test r8b, 1
	mov r8d, 6
	cmovnz eax, r8d
	imul ecx, eax
	test dl, dl
	je loc_142334493
	mov edx, [rsp+80h]
	lea ebx, [rcx+rdx]
	cmp ebp, 4
	jnb loc_1423343A8
	sub [rdi+rbp*2+18h], cx
loc_1423343A8:
	cmp ebx, r15d
	jl loc_1423344CB
	test r9b, r9b
	je loc_14233448D
	lea eax, [r15-1]
	cmp edx, eax
	jne loc_14233448D
	xor ecx, ecx
	mov ebx, ecx
	cmp ebp, 4
	jnb loc_1423344CB
	mov [rdi+rbp*2+18h], cx
	jmp loc_1423344CB
loc_1423343DD:
	mov rax, [r10]
	mov ecx, [rax+10h]
	and ecx, r12d
	test cl, 0Fh
	jne loc_142334459
	mov rax, [rsp+88h]
	cmp rdx, rax
	jge loc_14233440E
loc_1423343F8:
	mov rax, [r9]
	mov ecx, [rax+10h]
	and ecx, r12d
	test cl, 0Fh
	jne loc_142334426
	mov rax, [rsp+88h]
loc_14233440E:
	dec r11d
	dec r8
	sub r10, 8
	inc ebx
	inc rdx
	add r9, 8
	jmp loc_1423341C1
loc_142334426:
	mov rsi, [rdi+28h]
	movsxd rax, ebx
	mov r13d, ebx
	mov rsi, [rsi+rax*8]
	mov [rsp+80h], ebx
	mov rax, [rsi]
loc_14233443E:
	mov edx, r12d
	mov rcx, rsi
	call qword ptr [rax+40h]
	test al, al
	je loc_1423341F4
	mov [rsp+30h], rsi
	jmp loc_1423341F4
loc_142334459:
	mov rsi, [rdi+28h]
	movsxd rax, r11d
	mov edx, r12d
	mov rsi, [rsi+rax*8]
	mov r13d, r11d
	mov [rsp+80h], r11d
	mov rax, [rsi]
	mov rcx, rsi
	call qword ptr [rax+40h]
	test al, al
	je loc_1423341F4
	mov [rsp+30h], rsi
	jmp loc_1423341F4
loc_14233448D:
	lea ebx, [r15-1]
	jmp loc_1423344CB
loc_142334493:
	mov eax, [rsp+80h]
	mov ebx, eax
	sub ebx, ecx
	cmp ebp, 4
	jnb loc_1423344A8
	add [rdi+rbp*2+18h], cx
loc_1423344A8:
	test ebx, ebx
	jns loc_1423344CB
	test r10b, r10b
	je loc_1423344C7
	test eax, eax
	jne loc_1423344C7
	lea ebx, [r15-1]
	cmp ebp, 4
	jnb loc_1423344CB
	xor ecx, ecx
	mov [rdi+rbp*2+18h], cx
	jmp loc_1423344CB
loc_1423344C7:
	xor eax, eax
	mov ebx, eax
loc_1423344CB:
	cmp ebx, [rsp+80h]
	je loc_14233450F
	mov eax, r12d
	mov edx, r12d
	mov rcx, rsi
	not eax
	or eax, 0FFFFFFF0h
	and [rsi+10h], eax
	mov rax, [rsi]
	call qword ptr [rax+30h]
	mov rax, [rdi+28h]
	movsxd rcx, ebx
	mov rcx, [rax+rcx*8]
	mov eax, r12d
	mov edx, r12d
	and eax, 0Fh
	mov [rsp+80h], ebx
	or [rcx+10h], eax
	mov rax, [rcx]
	call qword ptr [rax+28h]
loc_14233450F:
	mov edx, 8
	jmp loc_142334766
loc_142334519:
	mov edx, 1
	call qword ptr [rax+50h]
	test bl, bl
	jne loc_14233470F
	cmp qword ptr [rdi+8], 0
	je loc_142334551
	mov eax, [r14+1Ch]
	shr eax, 0Dh
	test al, 1
	je loc_142334551
	mov rax, [rdi]
	mov edx, r12d
	mov rcx, rdi
	call qword ptr [rax+30h]
	mov edx, 2
	jmp loc_142334766
loc_142334551:
	test r15d, r15d
	je loc_14233464D
	mov r8d, [r14+1Ch]
	mov ecx, r8d
	mov r9d, r8d
	mov r10d, r8d
	shr ecx, 1
	shr r9d, 5
	shr r10d, 4
	movzx eax, r8b
	and cl, 1
	and r9b, 1
	and al, 1
	and r10b, 1
	cmp al, cl
	je loc_14233464D
	mov edx, r8d
	shr r8d, 0Ah
	mov eax, 1
	shr edx, 9
	and edx, 1
	add edx, edx
	or edx, 1
	test r8b, 1
	mov r8d, 6
	cmovnz eax, r8d
	imul edx, eax
	test cl, cl
	je loc_1423345ED
	lea ecx, [rdx+r13]
	cmp ebp, 4
	jnb loc_1423345C4
	sub [rdi+rbp*2+18h], dx
loc_1423345C4:
	cmp ecx, r15d
	jl loc_142334620
	test r9b, r9b
	je loc_1423345E7
	lea eax, [r15-1]
	cmp r13d, eax
	jne loc_1423345E7
	xor edx, edx
	mov ecx, edx
	cmp ebp, 4
	jnb loc_142334620
	mov [rdi+rbp*2+18h], dx
	jmp loc_142334620
loc_1423345E7:
	lea ecx, [r15-1]
	jmp loc_142334620
loc_1423345ED:
	mov ecx, r13d
	sub ecx, edx
	cmp ebp, 4
	jnb loc_1423345FC
	add [rdi+rbp*2+18h], dx
loc_1423345FC:
	test ecx, ecx
	jns loc_142334620
	test r10b, r10b
	je loc_14233461C
	test r13d, r13d
	jne loc_14233461C
	lea ecx, [r15-1]
	cmp ebp, 4
	jnb loc_142334620
	xor edx, edx
	mov [rdi+rbp*2+18h], dx
	jmp loc_142334620
loc_14233461C:
	xor eax, eax
	mov ecx, eax
loc_142334620:
	cmp ecx, r13d
	je loc_14233464D
	mov eax, r12d
	mov r13d, ecx
	mov [rsp+80h], ecx
	not eax
	movsxd rcx, ecx
	and r12d, 0Fh
	or eax, 0FFFFFFF0h
	and [rsi+10h], eax
	mov rax, [rdi+28h]
	mov rsi, [rax+rcx*8]
	or [rsi+10h], r12d
loc_14233464D:
	test rsi, rsi
	je loc_14233470F
	mov rax, [rsi]
	mov r8b, 1
	mov rdx, r14
	mov rcx, rsi
	call qword ptr [rax+10h]
	mov r15, rax
	test rax, rax
	je loc_142334700
	cmp rax, rsi
	je loc_142334700
	mov ecx, [rsi+10h]
	mov rbx, [rax]
	and ecx, 0Fh
	or [rax+10h], ecx
	mov rdx, [rsi]
	mov rcx, rsi
	call qword ptr [rdx+38h]
	mov rcx, r15
	mov edx, eax
	call qword ptr [rbx+28h]
	movsxd rax, r13d
	xor r13d, r13d
	lea r12, [rax*8]
	mov rax, [rdi+28h]
	mov rcx, [r12+rax]
	mov [rcx+8], r13
	mov rax, [rdi+28h]
	mov rsi, [r12+rax]
	test rsi, rsi
	je loc_1423346E9
	mov rcx, rsi
	call funcCreateSyncSth
	mov r8, [rsi]
	xor edx, edx
	mov rcx, rsi
	mov rbx, rax
	call qword ptr [r8]
	mov r8, [rbx]
	mov rdx, rsi
	mov rcx, rbx
	call qword ptr [r8+58h]
	mov rax, [rdi+28h]
	mov [r12+rax], r13
loc_1423346E9:
	mov rax, [rdi+28h]
	mov rsi, r15
	mov [r12+rax], r15
	or dword ptr [r15+10h], 100h
	mov [r15+8], rdi
loc_142334700:
	mov rax, [rsi]
	mov r8b, 1
	mov rdx, r14
	mov rcx, rsi
	call qword ptr [rax+18h]
loc_14233470F:
	mov edx, 2
	jmp loc_142334766
loc_142334716:
	mov edx, 10h
	call qword ptr [rax+50h]
	mov eax, [r14+1Ch]
	shr eax, 0Ch
	test al, 1
	je shitto
	jmp continueAsNormal
shitto:
	sub rsp, 60h
	push rax
	push rbx
	push rcx
	push rdx
	push r8
	push r9
	push r10
	push r11
	mov rcx, 0Dh
	mov rax, GetAsyncKeyState
	mov rax, [rax]
	call rax
	test ax, 8001h
	jne pressedA
	pop r11
	pop r10
	pop r9
	pop r8
	pop rdx
	pop rcx
	pop rbx
	pop rax
	add rsp, 60h
	jmp loc_142334761
pressedA:
	pop r11
	pop r10
	pop r9
	pop r8
	pop rdx
	pop rcx
	pop rbx
	pop rax
	add rsp, 60h
	;je loc_142334761
continueAsNormal:
	mov rax, [rdi]
	mov edx, r12d
	mov rcx, rdi
	call qword ptr [rax+28h] ;check
	test rsi, rsi
	jne loc_142334761
	test r15d, r15d
	je loc_142334761
	mov rax, [rdi+28h]
	and r12d, 0Fh
	xor edx, edx
	mov rcx, [rax]
	mov [rsp+80h], edx
	or [rcx+10h], r12d
	cmp ebp, 4
	jnb loc_142334761
	mov [rdi+rbp*2+18h], dx
loc_142334761:
	mov edx, 20h
loc_142334766:
	mov rax, [rdi]
	mov r8, r14
	mov rcx, rdi
	call qword ptr [rax+50h]
	mov rcx, [r14+8]
	mov r15, [rsp+40h]
	mov r13, [rsp+48h]
	mov r12, [rsp+50h]
	mov rsi, [rsp+58h]
	mov rbx, [rsp+90h]
	test rcx, rcx
	je loc_1423347AA
loc_142334797:
	mov r9d, [rsp+80h]
	mov r8d, ebp
	mov rdx, rdi
	;call sub_14237CCC0
	call fAdditionalDbgFunc2
loc_1423347AA:
	inc dword ptr [r14+18h]
	add rsp, 60h
	pop r14
	pop rdi
	pop rbp
	ret
fControlDebugMenu ENDP

.data

.code

fAdditionalDbgFunc2 PROC
	mov [rsp+8], rbx
	mov [rsp+10h], rdi
	mov r11, [rcx+8]
	mov rbx, rcx
	test r11, r11
	je loc_14237CD02
	mov edi, [rcx+10h]
	mov r10d, edi
loc_14237CCE0:
	movsxd rax, r10d
	add rax, rax
	cmp [r11+rax*8], rdx
	jne loc_14237CCF7
	movsx ecx, word ptr [r11+rax*8+8]
	cmp ecx, r8d
	je loc_14237CD33
loc_14237CCF7:
	movsx r10d, word ptr [r11+rax*8+0Eh]
	cmp r10d, edi
	jne loc_14237CCE0
loc_14237CD02:
	movsxd rax, dword ptr [rbx+10h]
	add rax, rax
	movsx rcx, word ptr [r11+rax*8+0Ch]
	mov [rbx+10h], ecx
	mov rax, rcx
	add rax, rax
	mov [r11+rax*8], rdx
	mov [r11+rax*8+8], r8w
	mov [r11+rax*8+0Ah], r9w
	mov rbx, [rsp+8]
	mov rdi, [rsp+10h]
	ret
loc_14237CD33:
	test r10d, r10d
	js loc_14237CD02
	mov rdi, [rsp+10h]
	movsxd r8, r10d
	shl r8, 4
	add r8, r11
	movzx eax, word ptr [r8+0Eh]
	movsx rdx, word ptr [r8+0Ch]
	mov [r8+0Ah], r9w
	mov rcx, [rbx+8]
	add rdx, rdx
	mov [rcx+rdx*8+0Eh], ax
	mov rcx, [rbx+8]
	movsx rdx, word ptr [r8+0Eh]
	movzx eax, word ptr [r8+0Ch]
	add rdx, rdx
	mov [rcx+rdx*8+0Ch], ax
	mov rax, [rbx+8]
	movsxd rcx, dword ptr [rbx+10h]
	add rcx, rcx
	movsx rdx, word ptr [rax+rcx*8+0Ch]
	mov [r8+0Ch], dx
	movzx eax, word ptr [rbx+10h]
	mov rcx, rdx
	mov [r8+0Eh], ax
	mov rax, [rbx+8]
	add rcx, rcx
	mov [rax+rcx*8+0Eh], r10w
	movsxd rcx, dword ptr [rbx+10h]
	mov rax, [rbx+8]
	add rcx, rcx
	mov [rax+rcx*8+0Ch], r10w
	mov [rbx+10h], r10d
	mov rbx, [rsp+8]
	ret
fAdditionalDbgFunc2 ENDP

.data
	pPadMan QWORD 141D06EB0h
.code

fPassInputToDbgCtrl PROC
	push rsi
	push rdi
	xor rcx, rcx
	mov [rax+1Ch], ecx
	mov [rax+18h], ecx
	mov rcx, [pPadMan]
	mov rcx, [rcx]
	mov rcx, [rcx+10h]			;PadDevice		
	mov rdx, [rcx+8]			;...stuff
	mov rdx, [rdx+50h]
	movzx esi, byte ptr [rdx+17h]
	and esi, 1
	mov [rax+1Ch], esi
	mov rdx, [rcx+8]
	mov rdx, [rdx+50h]
	mov edx, [rdx+14h]
	shr edx, 19h
	add edx, edx
	xor edx, esi
	and edx, 2
	xor edx, esi
	mov [rax+1Ch], edx
	mov rsi, [rcx+8]
	mov rsi, [rsi+50h]
	mov esi, [rsi+14h]
	shr esi, 1Bh
	add esi, esi
	add esi, esi
	xor esi, edx
	and esi, 4
	xor esi, edx
	mov [rax+1Ch], esi
	mov rdx, [rcx+8]
	mov rdx, [rdx+50h]
	mov edx, [rdx+14h]
	shr edx, 1Ah
	add edx, edx
	add edx, edx
	add edx, edx
	xor edx, esi
	and edx, 8
	xor edx, esi
	;and edx, 8
	;xor edx, esi
	mov [rax+1Ch], edx
	mov rsi, [rcx+8]
	mov rsi, [rsi+50h]
	mov esi, [rsi+14h]
	shr esi, 1Ch
	shl esi, 4
	xor esi, edx
	and esi, 10h
	xor esi, edx
	mov [rax+1Ch], esi
	mov rdx, [rcx+8]
	mov rdx, [rdx+50h]
	mov edx, [rdx+14h]
	shr edx, 1Dh
	shl edx, 5
	xor edx, esi
	and edx, 20h
	xor edx, esi
	mov [rax+1Ch], edx
	mov rsi, [rcx+8]
	mov rsi, [rsi+50h]
	mov esi, [rsi+14h]
	shr esi, 1Fh
	shl esi, 6
	xor esi, edx
	and esi, 40h
	xor esi, edx
	mov [rax+1Ch], esi
	mov rdx, [rcx+8]
	mov rdx, [rdx+50h]
	mov edi, [rdx+14h]
	shr edi, 1Eh
	shl edi, 7
	xor edi, esi
	and edi, 80h
	xor edi, esi
	mov [rax+1Ch], edi
	mov rdx, [rcx+8]
	mov rdx, [rdx+50h]
	mov edx, [rdx+18h]
	shr edx, 4
	movzx esi, dl
	shl esi, 8
	xor esi, edi
	and esi, 100h
	xor esi, edi
	mov [rax+1Ch], esi
	mov rdx, [rcx+8]
	mov rdx, [rdx+50h]
	mov edx, [rdx+18h]
	shr edx, 0Ch
	movzx edi, dl
	shl edi, 9
	xor edi, esi
	and edi, 200h
	xor edi, esi
	mov [rax+1Ch], edi
	mov rdx, [rcx+8]
	mov rdx, [rdx+50h]
	mov edx, [edx+18h]
	shr edx, 0Ah
	movzx esi, dl
	shl esi, 0Ah
	xor esi, edi
	and esi, 400h
	xor esi, edi
	mov [rax+1Ch], esi
	test esi, 600h
	jne loc_D7F441
	xor dl, dl
	jmp loc_D7F443
loc_D7F441:
	mov dl, 1
loc_D7F443:
	movzx edx, dl
	shl edx, 0Bh
	xor edx, esi
	and edx, 800h
	xor edx, esi
	mov [rax+1Ch], edx
	mov rsi, [rcx+8]
	mov rsi, [rsi+50h]
	movzx esi, byte ptr [rsi+1Ch]
	shl esi, 0Ch
	xor esi, edx
	and esi, 1000h
	xor esi, edx
	mov [rax+1Ch], esi
	mov rdx, [rcx+8]
	mov rdx, [rdx+50h]
	mov edx, [rdx+1Ch]
	shr edx, 1
	movzx edi, dl
	shl edi, 0Dh
	xor edi, esi
	and edi, 2000h
	xor edi, esi
	mov [rax+1Ch], edi
	mov rdx, [rcx+8]
	mov rdx, [rdx+50h]
	mov edx, [rdx+18h]
	shr edx, 0Dh
	movzx esi, dl
	shl esi, 0Eh
	xor esi, edi
	and esi, 4000h
	xor esi, edi
	mov [rax+1Ch], esi
	mov rdx, [rcx+8]
	mov rdx, [rdx+50h]
	mov edx, [rdx+18h]
	shr edx, 16h
	movzx edi, dl
	shl edi, 0Fh
	xor edi, esi
	and edi, 8000h
	xor edi, esi
	mov [rax+1Ch], edi
	mov rdx, [rcx+8]
	mov rdx, [rdx+50h]
	mov esi, [rdx+18h]
	mov edx, esi
	shr edx, 0Dh
	test dl, 1
	je loc_D7F578
	mov edx, esi
	shr edx, 0Fh
	test dl, 1
	mov edx, esi
	jne loc_D7F533
	shr edx, 12h
	test dl, 1
	je loc_D7F500
	or edi, 80000h
	mov [rax+1Ch], edi
loc_D7F500:
	mov rdx, [rcx+8]
	mov rdx, [rdx+50h]
	mov edx, [rdx+18h]
	shr edx, 14h
	test dl, 1
	je loc_D7F518
	or dword ptr [rax+1Ch], 40000h
loc_D7F518:
	mov edx, [rax+1Ch]
	test edx, 80000h
	je loc_D7F578
	test edx, 40000h
	je loc_D7F578
	and edx, 0FFF3FFFFh
	jmp loc_D7F575
loc_D7F533:
	shr edx, 12h
	test dl, 1
	je loc_D7F544
	or edi, 10000h
	mov [rax+1Ch], edi
loc_D7F544:
	mov rdx, [rcx+8]
	mov rdx, [rdx+50h]
	mov edx, [rdx+18h]
	shr edx, 14h
	test dl, 1
	je loc_D7F55C
	or dword ptr [rax+1Ch], 20000h
loc_D7F55C:
	mov edx, [rax+1Ch]
	test edx, 10000h
	je loc_D7F578
	test edx, 20000h
	je loc_D7F578
	and edx, 0FFFCFFFFh
loc_D7F575:
	mov [rax+1Ch], edx
loc_D7F578:
	cmp byte ptr [rax+20h], 0
	je loc_D7F597
	mov rdx, [rcx+8]
	mov rdx, [rdx+50h]
	mov edx, [rdx+18h]
	test dl, 1
	jne loc_D7F597
	shr edx, 1
	test dl, 1
	jne loc_D7F597
	mov byte ptr [rax+20h], 0
loc_D7F597:
	cmp byte ptr [rax+21h], 0
	je loc_D7F5BE
	mov rdx, [rcx+8]
	mov rdx, [rdx+50h]
	mov esi, [rdx+18h]
	mov edx, esi
	shr edx, 2
	test dl, 1
	jne loc_D7F5BE
	mov edx, esi
	shr edx, 3
	test dl, 1
	jne loc_D7F5BE
	mov byte ptr [rax+21h], 0
loc_D7F5BE:
	cmp byte ptr [rax+20h], 0
	pop rdi
	pop rsi
	jne loc_D7F605
	cmp byte ptr [rax+21h], 0
	jne loc_D7F5FF
	mov rcx, [rcx+8]
	mov rdx, [rcx+50h]
	mov ecx, [rdx+18h]
	test cl, 1
	jne loc_D7F5FB
	mov edx, ecx
	shr edx, 1
	test dl, 1
	jne loc_D7F5FB
	mov edx, ecx
	shr edx, 2
	test dl, 1
	jne loc_D7F5F5
	shr ecx, 3
	test cl, 1
	je loc_D7F5FF
loc_D7F5F5:
	mov byte ptr [rax+21h], 1
	jmp loc_D7F5FF
loc_D7F5FB:
	mov byte ptr [rax+20h], 1
loc_D7F5FF:
	cmp byte ptr [rax+20h], 0
	je loc_D7F60C
loc_D7F605:
	and dword ptr [rax+1Ch], 0FFFFFF33h
loc_D7F60C:
	cmp byte ptr [rax+21h], 0
	je locret_D7F616
	and dword ptr [rax+1Ch], 0FFFFFFCCh
locret_D7F616:
	ret
fPassInputToDbgCtrl ENDP

.data

.code

fDbgMenuControlFocus PROC
	mov rax, [pPadMan]
	mov rax, [rax]
	mov rax, [rax+10h]
	cmp byte ptr [rax+rcx+40h], 0
	mov byte ptr [rax+rcx+38h], 1
	jne return
	mov byte ptr [rax+rcx+40h], 1
	mov rdx, rcx
	mov rcx, [rax+8]
	mov r8, 1
	mov rax, [rcx]
	jmp qword ptr [rax+70h]
return:
	ret
fDbgMenuControlFocus ENDP

.data

.code

fDbgMenuControlDefocus PROC
	mov rax, [pPadMan]
	mov rax, [rax]
	mov rax, [rax+10h]
	cmp byte ptr [rax+rdx+3Ch], 0
	mov byte ptr [rax+rdx+38h], 0
	jne loc_F75B60
	cmp byte ptr [rax+rdx+40h], 1
	jne loc_F75B7B
	mov byte ptr [rax+rdx+40h], 0
	mov rcx, [rax+8]
	mov rax, [rcx]
	jmp qword ptr [rax+78h]
loc_F75B60:
	cmp byte ptr [rax+rdx+40h], 0
	jne loc_F75B7B
	mov byte ptr [rax+rdx+40h], 1
	mov rcx, [rax+8]
	mov rax, [rcx]
	mov r8, 1
	jmp qword ptr [rax+70h]
loc_F75B7B:
	ret
fDbgMenuControlDefocus ENDP

.data
	formatString QWORD 1400C6020h
	pFileMan QWORD 141D1E4F8h
	someArray QWORD 141D1E500h
	loadingString WORD 25A0h, 4Ch, 6Fh, 61h, 64h, 69h, 6Eh, 67h, 5Bh, 25h, 64h, 3Ah, 25h, 64h, 5Dh, 0 
	floatsie DWORD 3F4CCCCDh
	floatyFloat DWORD 41E00000h
	xOffset DWORD 44800000h
	yGap QWORD 4028000000000000h
	yOffset QWORD 4050000000000000h
	uno DWORD 3F800000h
	pGameDataMan QWORD 141D278F0h
	widthOffset QWORD 4070000000000000h

.code

fDbgDispLoading PROC
	push rbp
	mov rbp, rsp
	;and rsp, -10h
	sub rsp, 0C0h
	;push rbx
	;push rsi
	;push rdi
	;push r14
	mov [rbp+10h], rbx
	mov [rbp+18h], rsi
	mov [rbp+20h], rdi
	mov [rbp+28h], r14
	mov rax, [pFileMan]
	mov rax, [rax]
	cmp byte ptr [rax+168h], 0
	jne loc_EF865B
	cmp byte ptr [rax+169h], 0
	je loc_EF8848
loc_EF865B:
	xor rdi, rdi
	;mov [rsp+50h], rdi
	mov [rsp+28h], edi
	xor r14, r14
loopstart:
	mov rcx, [someArray]
	mov rcx, [rcx+rdi*8]
	mov edx, [rcx+38h]
	mov eax, [rcx+3Ch]
	cmp edx, eax
	jg loc_EF8678
	sub eax, edx
	mov rsi, rax
	jmp loc_EF867F
loc_EF8678:
	mov rsi, [rcx+40h]
	sub rsi, rdx
	add rsi, rax
loc_EF867F:
	test rsi, rsi
	jle loc_EF883A
	call func1
	mov rbx, rax
	mov rax, [rax]
	xor r8d, r8d
	;lea rdx, [rsp+58h]
	lea rdx, [rsp+50h]
	mov rcx, rbx
	call qword ptr [rax+18h]
	mov ecx, [rax]
	shr ecx, 5
	test cl, 1
	jne success
	mov r8, heapstring
	mov edx, 3Eh
	xor ecx, ecx
	call func2
	int 3
success:
	mov [rsp+80h], r14
	mov [rsp+88h], r14
	mov [rsp+70h], rbx
	mov qword ptr [rsp+90h], 7
	;mov [rbp-15h], r14
	mov word ptr [rsp+78h], r14w
	mov byte ptr [rsp+098h], 1
	mov r9, rsi
	mov r8, rdi
	lea rdx, loadingString
	lea rcx, [rsp+70h]
	call formatString
	mov rcx, [pHgMan]
	mov rcx, [rcx]
	mov rbx, [rcx+60h]
	mov rcx, [rbx+48h]
	or edx, -1
	mov rax, 1401E3AF0h
	call rax
	mov rcx, [rbx+48h]
	cmp dword ptr [rcx+70h], 0
	je loc_EF86E5
	mov dword ptr [rcx+70h], 0
	or dword ptr [rcx+10h], 80h
loc_EF86E5:
	;mov rax, 14047CB10h
	movss xmm0, [floatsie]
	shufps xmm0, xmm0, 0
	lea rdx, [rsp+40h]
	movaps [rdx], xmm0
	mov rax, 14047CB10h
	call rax
	mov rcx, [rbx+48h]
	movss xmm0, dword ptr [rcx+78h]
	ucomiss xmm0, [floatyFloat]
	jp setThingies
	je skipSetThingies
setThingies:
	or dword ptr [rax+10h], 100h
	mov dword ptr [rax+78h], 41E00000h
skipSetThingies:
	lea r8, [rsp+78h]
	cmp qword ptr [rsp+90h], 8
	cmovnb r8, [rsp+78h]
	mov rax, [pGameDataMan]
	mov rax, [rax]
	mov rcx, [rax+68h]
	cvtsi2ss xmm0, dword ptr [rcx+0D8h]
	cvtps2pd xmm0, xmm0
	subsd xmm0, [widthOffset]
	cvtpd2ps xmm0, xmm0
	;movss xmm0, [xOffset]
	movss dword ptr [rsp+30h], xmm0
	;cvtsi2ss xmm0, dword ptr [rsp+50h]
	cvtsi2ss xmm0, dword ptr [rsp+28h]
	cvtps2pd xmm0, xmm0
	mulsd xmm0, [yGap]
	addsd xmm0, [yOffset]
	cvtpd2ps xmm0, xmm0
	movss dword ptr [rsp+34h], xmm0
	xorps xmm0, xmm0
	movss dword ptr [rsp+38h], xmm0
	movss xmm0, [uno]
	movss dword ptr [rsp+3Ch], xmm0
	;movaps xmm1, [rsp+30h]
	mov rax, 1401D6BF0h
	lea rdx, [rsp+30h]
	mov rcx, rbx
	call rax
	movss xmm0, [uno]
	shufps xmm0, xmm0, 0
	lea rdx, [rsp+40h]
	movaps [rdx], xmm0
	mov rax, 14047CB10h
	mov rcx, [rbx+48h]
	call rax
	cmp qword ptr [rsp+90h], 8
	jb loc_EF8836
	mov rcx, [rsp+70h]
	mov rax, [rcx]
	mov rdx, [rsp+78h]
	call qword ptr [rax+68h]
loc_EF8836:
	;mov rdi, [rsp+50h]
	mov edi, [rsp+28h]
loc_EF883A:
	inc edi
	cmp edi, 5
	;mov [rsp+50h], rdi
	mov [rsp+28h], edi
	jl loopstart
loc_EF8848:
	;pop r14
	;pop rdi
	;pop rsi
	;pop rbx
	mov rbx, [rbp+10h]
	mov rsi, [rbp+18h]
	mov rdi, [rbp+20h]
	mov r14, [rbp+28h]
	mov rsp, rbp
	pop rbp
	ret
fDbgDispLoading ENDP

.data

.code

fOpenLogConsole PROC
	mov [g_isOpenConsole], 1
	mov rcx, [r9+17F0h]
	jmp [bOpenLogConsole]
fOpenLogConsole ENDP

.data
	getPadDevice QWORD 1401ADBA0h
	checkButton QWORD 1401A43B0h
.code

tExitButtonComboCheck1 PROC
	call fExitButtonComboCheck
	jmp bExitButtonComboCheck1
tExitButtonComboCheck1 ENDP

tExitButtonComboCheck2 PROC
	call fExitButtonComboCheck
	jmp bExitButtonComboCheck2
tExitButtonComboCheck2 ENDP

tExitButtonComboCheck3 PROC
	call fExitButtonComboCheck
	jmp bExitButtonComboCheck3
tExitButtonComboCheck3 ENDP

fExitButtonComboCheck PROC
	push rbx
	push rcx
	push rdx
	xor ecx, ecx
	call getPadDevice
	mov rbx, rax
	mov rcx, rbx
	mov edx, 39h
	call checkButton
	test al, al
	je finish
	mov rcx, rbx
	mov edx, 3Ah
	call checkButton
finish:
	pop rdx
	pop rcx
	pop rbx
	ret
fExitButtonComboCheck ENDP

fInitRootDbgMenuLabelNode PROC
	lea rcx, [rootString]
	mov rax, 140466AA0h
	call rax
	mov rcx, [pDbgMenuMan]
	mov rcx, [rcx]
	mov [rcx+8], rax
	add rsp, 28h
	ret
fInitRootDbgMenuLabelNode ENDP

END