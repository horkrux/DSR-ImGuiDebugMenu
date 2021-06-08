EXTERN bEzDrawAddDrawPlans1:QWORD
EXTERN bEzDrawAddDrawPlans2:QWORD
EXTERN bEzDrawAddDrawPlans3:QWORD
EXTERN bEzDrawAddDrawPlans4:QWORD
EXTERN bEzDrawAddDrawPlans5:QWORD
EXTERN bEzDrawAddDrawPlans6:QWORD

.data
	pHgMan QWORD 141C04ED8h
.code

tEzDrawAddDrawPlans1 PROC 
	call fEzDrawAddDrawPlans1
	mov r8d, esi
	mov edx, 16h
	jmp [bEzDrawAddDrawPlans1]
tEzDrawAddDrawPlans1 ENDP

tEzDrawAddDrawPlans2 PROC
	call fEzDrawAddDrawPlans1
	mov r8d, esi
	mov edx, 16h
	jmp [bEzDrawAddDrawPlans2]
tEzDrawAddDrawPlans2 ENDP

tEzDrawAddDrawPlans3 PROC
	call fEzDrawAddDrawPlans1
	mov r8d, esi
	mov edx, 16h
	jmp [bEzDrawAddDrawPlans3]
tEzDrawAddDrawPlans3 ENDP

tEzDrawAddDrawPlans4 PROC
	call fEzDrawAddDrawPlans1
	mov r8d, esi
	mov edx, 16h
	jmp [bEzDrawAddDrawPlans4]
tEzDrawAddDrawPlans4 ENDP

tEzDrawAddDrawPlans5 PROC
	call fEzDrawAddDrawPlans1
	mov r8d, esi
	mov edx, 16h
	jmp [bEzDrawAddDrawPlans5]
tEzDrawAddDrawPlans5 ENDP

tEzDrawAddDrawPlans6 PROC
	mov rax, 1404F8690h
	call rax
	mov rax, 14015CF60h
	call rax
	mov r8d, [rax+8]
	mov rcx, rsi
	mov edx, [rbp+0BCh]
	mov rax, 140163360h
	call rax
	;mov esi, [rbp+0ACh]
	;call fEzDrawAddDrawPlans1
	;pop rsi
	jmp [bEzDrawAddDrawPlans6]
tEzDrawAddDrawPlans6 ENDP

fEzDrawAddDrawPlans1 PROC
	mov rax, 14015CF60h
	call rax
	mov ebx, [rax+8]
	mov r8d, esi
	mov edx, 16h
	mov rcx, rdi
	mov rax, 1411B0240h
	call rax
	mov rcx, [rdi]
	add rcx, 3
	and rcx, -4
	lea rax, [rcx+4]
	mov [rdi], rax
	mov dword ptr [rcx], 10005h
	mov rcx, [rdi]
	add rcx, 3
	and rcx, -4
	lea rax, [rcx+4]
	mov [rdi], rax
	mov [rcx], ebx
	mov rcx, rdi
	mov rax, 1411B01E0h
	call rax
	mov r8d, esi
	mov edx, 16h
	mov rcx, rdi
	mov rax, 1411B0240h
	call rax
	mov rcx, [rdi]
	add rcx, 3
	and rcx, -4
	lea rax, [rcx+4]
	mov [rdi], rax
	mov dword ptr [rcx], 20005h
	mov rcx, rdi
	mov rax, 1411B01E0h
	call rax
	ret
fEzDrawAddDrawPlans1 ENDP

fEzDrawAddDrawPlans2 PROC
	ret
fEzDrawAddDrawPlans2 ENDP

END