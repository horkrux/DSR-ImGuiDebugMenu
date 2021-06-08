EXTERN bApplySettingsDamageMan:QWORD
EXTERN bApplySettingsWorldChrManDbg:QWORD
EXTERN pSettingsDamageMan:QWORD
EXTERN pSettingsWorldChrManDbg:QWORD

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

END