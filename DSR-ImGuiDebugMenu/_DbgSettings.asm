EXTERN bApplySettingsDamageMan:QWORD
EXTERN bApplySettingsWorldChrManDbg:QWORD
EXTERN bLoadDbgMenuTextHighlightColor:QWORD
EXTERN pSettingsDamageMan:QWORD
EXTERN pSettingsWorldChrManDbg:QWORD
EXTERN textHighlightColorRStr:QWORD
EXTERN textHighlightColorGStr:QWORD
EXTERN textHighlightColorBStr:QWORD
EXTERN textHighlightColorAStr:QWORD
EXTERN textHighlightColor:DWORD
EXTERN fConvertColor:QWORD
EXTERN damageManDebugBallDisplayStr:QWORD
EXTERN damageManDebugInfoDisplayStr:QWORD
EXTERN damageManDamageWpnPolyStr:QWORD
EXTERN damageManDamageAtkParamRefStr:QWORD

.data
	pMainMem QWORD 141C04F20h
	pDamageMan QWORD 141D173C0h
.code

fApplySettingsDamageMan PROC
	mov rcx, [pSettingsDamageMan]
	mov eax, [rcx]
	mov rcx, [pDamageMan]
	mov rcx, [rcx]
	mov [rcx+30h], eax
	mov rcx, [pMainMem]
	mov rcx, [rcx]
	jmp [bApplySettingsDamageMan]
fApplySettingsDamageMan ENDP

tApplySettingsDamageMan PROC
	lea rcx, [damageManDebugBallDisplayStr]
	mov edx, 26
	mov r8d, 0
	call fGetBoolValue
	mov [rsi+30h], al
	lea rcx, [damageManDebugInfoDisplayStr]
	mov edx, 26
	mov r8d, 0
	call fGetBoolValue
	mov [rsi+31h], al
	lea rcx, [damageManDamageWpnPolyStr]
	mov edx, 23
	mov r8d, 1
	call fGetBoolValue
	mov [rsi+32h], al
	lea rcx, [damageManDamageAtkParamRefStr]
	mov edx, 27
	mov r8d, 1
	call fGetBoolValue
	mov [rsi+33h], al
	mov rax, [rsi+20h]
	lea r8, [rsi+30h]
	mov r9b, 1
	jmp [bApplySettingsDamageMan]
tApplySettingsDamageMan ENDP

.data
	pWorldChrManDbg QWORD 141D151F8h
.code

fApplySettingsWorldChrManDbg PROC
	mov rax, [pWorldChrManDbg]
	mov rax, [rax]
	mov rcx, [pSettingsWorldChrManDbg]
	mov r8b, [rcx]
	mov [rax+39h], r8b
	mov r8b, [rcx+1]
	mov [rax+3Ah], r8b
	mov rax, 1402C9880h
	call rax
	jmp [bApplySettingsWorldChrManDbg]
fApplySettingsWorldChrManDbg ENDP

.data
	
.code

tLoadDbgMenuTextHighlightColor PROC
	lea rcx, [rsp+30h]
	call fLoadDbgMenuTextHighlightColor
	mov rcx, rax
	call fConvertColor
	mov [textHighlightColor], eax
	lea rcx, [rsp+30h]
	jmp [bLoadDbgMenuTextHighlightColor]
tLoadDbgMenuTextHighlightColor ENDP

.data

	heapoAllocato QWORD 141D95FF0h
	textHighlightColorDefault DWORD 0.5, 1.0, 0.75, 1.0
	_theGameProperties QWORD 141D06858h
.code

fLoadDbgMenuTextHighlightColor PROC
	mov rax, rsp
	push rbp
	lea rbp, [rax-5Fh]
	sub rsp, 0B0h
	mov qword ptr [rbp-31h], -2
	mov [rax+8], rbx
	mov [rax+10h], rdi
	movaps xmmword ptr [rax-18h], xmm6
	movaps xmmword ptr [rax-28h], xmm7
	movaps xmmword ptr [rax-38h], xmm8
	movaps xmmword ptr [rax-48h], xmm9
	mov rbx, rcx
	mov rcx, heapoAllocato
	mov rcx, [rcx]
	test rcx, rcx
	jne loc_14018E02D
	mov rax, 140D7FDD0h
	call rax
	mov rcx, rax
	mov rax, 141D95FF0h
	mov [rax], rcx
loc_14018E02D:
	mov [rbp-29h], rcx
	mov rax, [rcx]
	xor r8d, r8d
	lea rdx, [rbp-39h]
	call qword ptr [rax+18h]
	mov ecx, [rax]
	shr ecx, 5
	test cl, 1
	jne loc_14018E05C
	mov r8, 1414A1BC8h
	mov edx, 43h
	xor ecx, ecx
	mov rax, 140D4FD10h
	call rax
	int 3
loc_14018E05C:
	mov qword ptr [rbp-9], 7
	xor edi, edi
	mov [rbp-11h], rdi
	mov word ptr [rbp-21h], di
	lea r8d, [rdi+20h]
	lea rdx, [textHighlightColorRStr]
	lea rcx, [rbp-29h]
	mov rax, 140094F70h
	call rax
	mov byte ptr [rbp-1], 1
loc_14018E086:
	movss xmm2, dword ptr [textHighlightColorDefault]
	lea rdx, [rbp-29h]
	mov rcx, [_theGameProperties]
	mov rcx, [rcx]
	mov rax, 140D9EEF0h
	call rax
	movaps xmm9, xmm0
loc_14018E0A2:
	cmp qword ptr [rbp-9], 8
	jb loc_14018E0B8
	mov rcx, [rbp-29h]
	mov rax, [rcx]
	mov rdx, [rbp-21h]
	call qword ptr [rax+68h]
	nop
loc_14018E0B8:
	mov rcx, heapoAllocato
	mov rcx, [rcx]
	test rcx, rcx
	jne loc_14018E0D3
	mov rax, 140D7FDD0h
	call rax
	mov rcx, rax
	mov rax, 141D95FF0h
	mov [rax], rcx
loc_14018E0D3:
	mov [rbp-29h], rcx
	mov rax, [rcx]
	xor r8d, r8d
	lea rdx, [rbp-39h]
	call qword ptr [rax+18h]
	mov ecx, [rax]
	shr ecx, 5
	test cl, 1
	jne loc_14018E102
	mov r8, 1414A1BC8h
	mov edx, 43h
	xor ecx, ecx
	mov rax, 140D4FD10h
	call rax
	int 3 
loc_14018E102:
	mov qword ptr [rbp-9], 7
	mov [rbp-11h], rdi
	mov word ptr [rbp-21h], di
	mov r8d, 20h
	lea rdx, [textHighlightColorGStr]
	lea rcx, [rbp-29h]
	mov rax, 140094F70h
	mov byte ptr [rbp-1], 1
loc_14018E12C:
	movss xmm2, dword ptr [textHighlightColorDefault+4]
	lea rdx, [rbp-29h]
	mov rcx, [_theGameProperties]
	mov rcx, [rcx]
	mov rax, 140D9EEF0h
	call rax
	movaps xmm8, xmm0
loc_14018E148:
	cmp qword ptr [rbp-9], 8
	jb loc_14018E15E
	mov rcx, [rbp-29h]
	mov rax, [rcx]
	mov rdx, [rbp-21h]
	call qword ptr [rax+68h]
	nop
loc_14018E15E:
	mov rcx, heapoAllocato
	mov rcx, [rcx]
	test rcx, rcx
	jne loc_14018E179
	mov rax, 140D7FDD0h
	call rax
	mov rcx, rax
	mov rax, 141D95FF0h
	mov [rax], rcx
loc_14018E179:
	mov [rbp-29h], rcx
	mov rax, [rcx]
	xor r8d, r8d
	lea rdx, [rbp-39h]
	call qword ptr [rax+18h]
	mov ecx, [rax]
	shr ecx, 5
	test cl, 1
	jne loc_14018E1A8
	mov r8, 1414A1BC8h
	mov edx, 43h
	xor ecx, ecx
	mov rax, 140D4FD10h
	call rax
	int 3 
loc_14018E1A8:
	mov qword ptr [rbp-9], 7
	mov [rbp-11h], rdi
	mov word ptr [rbp-21h], di
	mov r8d, 20h
	lea rdx, [textHighlightColorBStr]
	lea rcx, [rbp-29h]
	mov rax, 140094F70h
	call rax
	mov byte ptr [rbp-1], 1
loc_14018E1D2:
	movss xmm2, dword ptr [textHighlightColorDefault+8]
	lea rdx, [rbp-29h]
	mov rcx, [_theGameProperties]
	mov rcx, [rcx]
	mov rax, 140D9EEF0h
	call rax
	movaps xmm7, xmm0
loc_14018E1ED:
	cmp qword ptr [rbp-9], 8
	jb loc_14018E203
	mov rcx, [rbp-29h]
	mov rax, [rcx]
	mov rdx, [rbp-21h]
	call qword ptr [rax+68h]
	nop
loc_14018E203:
	mov rcx, heapoAllocato
	mov rcx, [rcx]
	test rcx, rcx
	jne loc_14018E21E
	mov rax, 140D7FDD0h
	call rax
	mov rcx, rax
	mov rax, 141D95FF0h
	mov [rax], rcx
loc_14018E21E:
	mov [rbp-29h], rcx
	mov rax, [rcx]
	xor r8d, r8d
	lea rdx, [rbp-39h]
	call qword ptr [rax+18h]
	mov ecx, [rax]
	shr ecx, 5
	test cl, 1
	jne loc_14018E24D
	mov r8, 1414A1BC8h
	mov edx, 43h
	xor ecx, ecx
	mov rax, 140D4FD10h
	call rax
	int 3 
loc_14018E24D:
	mov qword ptr [rbp-9], 7
	mov [rbp-11h], rdi
	mov word ptr [rbp-21h], di
	mov r8d, 20h
	lea rdx, [textHighlightColorAStr]
	lea rcx, [rbp-29h]
	mov rax, 140094F70h
	call rax
	mov byte ptr [rbp-1], 1
loc_14018E277:
	movss xmm2, dword ptr [textHighlightColorDefault+0Ch]
	lea rdx, [rbp-29h]
	mov rcx, [_theGameProperties]
	mov rcx, [rcx]
	mov rax, 140D9EEF0h
	call rax
	movaps xmm6, xmm0
loc_14018E292:
	cmp qword ptr [rbp-9], 8
	jb loc_14018E2A8
	mov rcx, [rbp-29h]
	mov rax, [rcx]
	mov rdx, [rbp-21h]
	call qword ptr [rax+68h]
	nop
loc_14018E2A8:
	movaps xmm2, xmm8
	movaps xmm3, xmm9
	unpcklps xmm3, xmm7
	unpcklps xmm2, xmm6
	unpcklps xmm3, xmm2
	movaps xmmword ptr [rbx], xmm3
	mov rax, rbx
	lea r11, [rsp+0B0h]
	mov rbx, [r11+10h]
	mov rdi, [r11+18h]
	movaps xmm6, xmmword ptr [r11-10h]
	movaps xmm7, xmmword ptr [r11-20h]
	movaps xmm8, xmmword ptr [r11-30h]
	movaps xmm9, xmmword ptr [r11-40h]
	mov rsp, r11
	pop rbp
	ret
fLoadDbgMenuTextHighlightColor ENDP

.data

.code

tGetDamageManSettings PROC
	
tGetDamageManSettings ENDP

.data

.code

fGetBoolValue PROC
	push rbx
	sub rsp, 70h
	mov qword ptr [rsp+28h], -2
	mov rbx, rcx
	mov dword ptr [rsp+60h], edx
	mov dword ptr [rsp+64h], r8d
	mov rcx, heapoAllocato
	mov rcx, [rcx]
	test rcx, rcx
	jne loc_14018C6E9
	mov rax, 140D7FDD0h
	call rax
	mov rcx, rax
	mov rax, 141D95FF0h
	mov [rax], rcx
loc_14018C6E9:
	mov [rsp+30h], rcx
	mov rax, [rcx]
	xor r8d, r8d
	lea rdx, [rsp+20h]
	call qword ptr [rax+18h]
	mov ecx, [rax]
	shr ecx, 5
	test cl, 1
	jne loc_14018C71A
	mov r8, 1414A1BC8h
	mov edx, 43h
	xor ecx, ecx
	mov rax, 140D4FD10h
	call rax
	int 3 
loc_14018C71A:
	mov qword ptr [rsp+50h], 7
	xor eax, eax
	mov [rsp+48h], rax
	mov word ptr [rsp+38h], ax
	mov r8d, dword ptr [rsp+60h]
	mov rdx, rbx
	lea rcx, [rsp+30h]
	mov rax, 140094F70h
	call rax
	mov qword ptr [rsp+58h], 1
loc_14018C749:
	mov r8d, [rsp+64h]
	lea rdx, [rsp+30h]
	mov rcx, [_theGameProperties]
	mov rcx, [rcx]
	mov rax, 140D9EB10h
	call rax
	movzx ebx, al
loc_14018C760:
	cmp qword ptr [rsp+50h], 8
	jb loc_14018C77A
	mov rcx, [rsp+30h]
	mov r8, [rcx]
	mov rdx, [rsp+38h]
	call qword ptr [r8+68h]
	nop
loc_14018C77A:
	movzx eax, bl
	add rsp, 70h
	pop rbx
	ret
fGetBoolValue ENDP

END