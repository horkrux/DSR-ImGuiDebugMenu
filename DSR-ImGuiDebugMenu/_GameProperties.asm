EXTERN bLoadGamePropertiesOrSth:QWORD
EXTERN gamePropertiesPathString:QWORD

.data
	heapoAllocato QWORD 141D95FF0h
	initDLFileInputStream QWORD 140CEF970h
	deleteDLFileInputStream QWORD 140CEF9E0h
	thingy BYTE 0
	_theGameProperties QWORD 141D06858h
.code

tLoadGamePropertiesOrSth PROC
	lea rdx, [gamePropertiesPathString]
	mov rcx, [_theGameProperties]
	mov rcx, [rcx]
	call fLoadGamePropertiesOrSth
	lea rcx, [rsi+140h]
	jmp [bLoadGamePropertiesOrSth]
tLoadGamePropertiesOrSth ENDP

fLoadGamePropertiesOrSth PROC
	mov rax, rsp
	push rdi
	sub rsp, 70h
	mov qword ptr [rax-48h], -2
	mov [rax+8], rbx
	mov [rax+10h], rsi
	mov rsi, rdx
	mov rdi, rcx
	xor bl, bl
	test rdx, rdx
	je epi
	mov rax, heapoAllocato
	mov rax, [rax]
	test rax, rax
	jne heapSet
	mov rax, 140D7FDD0h
	call rax
	mov rdx, heapoAllocato
	mov rdx, [rdx]
	mov [rdx], rax
heapSet:
	mov byte ptr [rsp+28h], 0
	mov byte ptr [rsp+20h], 0
	mov r9, rax
	xor r8d, r8d
	mov rdx, rsi
	lea rcx, [rsp+50h]
	mov rax, 140CEE4C0h
	call rax
	nop
	xor r8d, r8d
	lea rdx, [rsp+50h]
	lea rcx, [rsp+38h]
	call initDLFileInputStream
	nop
	mov rax, 141B14575h
	movzx eax, byte ptr [rax]
	mov byte ptr [thingy], al
	xor r9d, r9d
	lea r8, [thingy]
	lea rdx, [rsp+38h]
	mov rcx, rdi
	mov rax, 140D9D8F0h
	call rax
	mov bl, al
	lea rcx, [rsp+50h]
	mov rax, 140CEED00h
	call rax
	lea rcx, [rsp+38h]
	call deleteDLFileInputStream
	nop
	lea rcx, [rsp+50h]
	mov rax, 140CEE500h
	call rax
epi:
	movzx eax, bl
	lea r11, [rsp+70h]
	mov rbx, [r11+10h]
	mov rsi, [r11+18h]
	mov rsp, r11
	pop rdi
	ret
fLoadGamePropertiesOrSth ENDP

END