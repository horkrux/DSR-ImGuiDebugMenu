EXTERN bCheckDebugDash:QWORD

.data
pDashSpeedFactor QWORD 1412D9D3Ch
pWorldChrDbgMan QWORD 141D151F8h
pDivide QWORD 1412C8BD0h
getPadDevice QWORD 1401ADBA0h
dbgMapWalkPadMem QWORD 0, 0, 0
pDbgMapWalkPad QWORD 1412DA5B8h
pDebugDashSwitch QWORD 141D151DAh
checkButton QWORD 1401A43B0h
getPosition QWORD 14031F920h
setPosition QWORD 14031FB90h
pFloaties1 QWORD 141331BC0h
pFloaties2 QWORD 141B2A410h

.code

tCheckDebugDash PROC
	movaps xmm7, xmm6
	mov rax, [pDashSpeedFactor]
	movss xmm8, dword ptr [rax]
	mov rcx, [pWorldChrDbgMan]
	mov rcx, [rcx]
	mov rax, [rcx+0F0h]
	test rax, rax
	jne cmpChrWithThis
	mov rax, [r14+68h]
cmpChrWithThis:
	cmp rdi, rax
	jne transfer
	mov r8, rdi
	movaps xmm1, xmm7
	call fCheckDebugDash
	test al, al
	je transfer
	movaps xmm6, xmm7
	mulss xmm6, xmm8
transfer:
	movss dword ptr [rbx+8], xmm6
	jmp [bCheckDebugDash]
tCheckDebugDash ENDP

.data

.code

fCheckDebugDash PROC
	push rbx
	push rsi
	sub rsp, 78h
	movaps [rsp+50h], xmm7
	mov [rsp+70h], rdi
	mov rsi, r8
	movaps xmm7, xmm1
	mov rbx, rcx
	mov rcx, [pDivide]
	divss xmm7, dword ptr [rcx]
	xor ecx, ecx
	call getPadDevice
	lea rdi, [dbgMapWalkPadMem]
	mov r8, [pDbgMapWalkPad]
	lea r8, [r8]
	mov [rdi], r8
	mov [rdi+8], rax
	mov [rdi+10h], rcx
	mov rcx, [pDebugDashSwitch]
	cmp byte ptr [rcx], 0
	je debugDashSwitchOff
	mov rcx, [rdi+8]
	;mov edx, 46h
	;call checkButton
	call DashActivateCheck1
	test al, al
	jne activateDash
	mov rcx, [rdi+8]
	call DashActivateCheck2
	test al, al
	je debugDashTest
activateDash:
	cmp byte ptr [rbx+34h], 0
	lea rdx, [rsp+20h]
	mov rcx, rsi
	sete al
	mov [rbx+34h], al
	call getPosition
	mov rcx, rsi
	mov rdx, rax
	call setPosition
	jmp debugDashTest
debugDashSwitchOff:
	mov byte ptr [rbx+34h], 0
debugDashTest:
	cmp byte ptr [rbx+34h], 0
	je debugDashDisabled
	or byte ptr [rsi+2A5h], 40h
	movaps [rsp+60h], xmm6
	mov rcx, [pFloaties1]
	movaps xmm6, [rcx]
	movss xmm0, xmm7
	mov rcx, [pFloaties2]
	shufps xmm0, xmm0, 0
	mulps xmm6, [rcx]
	mulps xmm6, xmm0
	mov rcx, [rdi+8]
	mov edx, 44h
	call checkButton
	test al, al
	je L2NotPressed
	lea rdx, [rsp+30h]
	mov rcx, rsi
	call getPosition
	lea rdx, [rsp+20h]
	mov rcx, rsi
	movaps xmm0, [rax]
	addps xmm0, xmm6
	movaps [rsp+20h], xmm0
	call setPosition
L2NotPressed:
	mov rcx, [rdi+8]
	mov edx, 43h
	call checkButton
	test al, al
	je L1NotPressed
	lea rdx, [rsp+30h]
	mov rcx, rsi
	call getPosition
	lea rdx, [rsp+20h]
	mov rcx, rsi
	movaps xmm0, [rax]
	subps xmm0, xmm6
	movaps [rsp+20h], xmm0
	call setPosition
L1NotPressed:
	mov rcx, [rdi+8]
	mov edx, 42h
	call checkButton
	mov rcx, [rsi+68h]
	test al, al
	je R2NotPressed
	or word ptr [rcx+104h], 8
	jmp setReturnValue
R2NotPressed:
	mov word ptr [rcx+104h], 0
setReturnValue:
	mov al, 1
	jmp epilogue
debugDashDisabled:
	mov rcx, [rsi+68h]
	;mov word ptr [rcx+104h], 0
	and byte ptr [rsi+2A5h], 0BFh
	xor al, al
epilogue:
	mov rdi, [rsp+70h]
	movaps xmm7, [rsp+50h]
	add rsp, 78h
	pop rsi
	pop rbx
	ret
fCheckDebugDash ENDP

.data

.code

DashActivateCheck1 PROC
	sub rsp, 20h
	mov edx, 46h
	call checkButton
	test al, al
	je ending
	mov rcx, [rdi+8]
	mov edx, 64h
	call checkButton
	test al, al
	je success
	xor al, al
	jmp ending
success:
	mov al, 1
ending:
	add rsp, 20h
	ret
DashActivateCheck1 ENDP

DashActivateCheck2 PROC
	sub rsp, 20h
	mov edx, 35h
	call checkButton
	test al, al
	je ending
	mov rcx, [rdi+8]
	mov edx, 2Fh
	call checkButton
	test al, al
	je ending
	mov rcx, [rdi+8]
	mov edx, 30h
	call checkButton
	test al, al
	je success
	xor al, al
	jmp ending
success:
	mov al, 1
ending:
	add rsp, 20h
	ret
DashActivateCheck2 ENDP
END