EXTERN fPrintDbgLog:QWORD

.data
argMem QWORD 0,0,0,0,0,0,0,0,0
getEzStateActionEventArg QWORD 140391750h
argBuf QWORD 32 dup(0)
stringFunc QWORD 140E57090h
formatString QWORD 0
bEsdActionEventEnd QWORD 14039152Fh

.code

tEsdDbgLogOutput PROC
	mov r12, rax
	cmp rax, 2
	jb endlbl
	mov rcx, [r13+8]
	test rcx, rcx
	je endlbl
	cmp byte ptr [rcx+550h], 0
	je endlbl
	mov rbx, 0
	mov rcx, 32
	push rdi
	lea rdi, argBuf
zeroout:
	mov [rdi], rbx
	add rdi, 8
	dec rcx
	jne zeroout
	pop rdi
	
	mov r9, 2
	lea rdx, argMem
	lea r10, argBuf
	mov r8d, 1
	mov rcx, rdi
	call getEzStateActionEventArg
	mov ebx, [rax+8]
	cmp ebx, 3
	jne endlbl
	mov rcx, [rax]
	call stringFunc
	lea rdx, [rax+8]
	cmp qword ptr [rdx+18h], 8
	jb shortfirststring
	mov rdx, [rdx]
shortfirststring:
	mov [formatString], rdx
	cmp r12, 2
	je printlbl
getarg:
	mov r8d, r9d
	lea rdx, argMem
	mov rcx, rdi
	call getEzStateActionEventArg
	mov ebx, [rax+8]
	cmp ebx, 2
	jne cmpstring
	mov r11d, [rax]
	mov [r10], r11d
	add r10, 8
	jmp iter
cmpstring:
	cmp ebx, 3
	jne iter
	mov rcx, [rax]
	call stringFunc
	lea rdx, [rax+8]
	cmp qword ptr [rdx+18h], 8
	jb shortstring
	mov rdx, [rdx]
shortstring:
	mov [r10], rdx
	add r10, 8
iter:
	inc r9
	cmp r9, r12
	jnz getarg
printlbl:
	mov rcx, [formatString]
	lea rdx, argBuf
	mov r8, r14
	call fPrintDbgLog
endlbl:
	jmp [bEsdActionEventEnd]

tEsdDbgLogOutput ENDP

END