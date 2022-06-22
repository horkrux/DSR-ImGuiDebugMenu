EXTERN bAntiTamperSkip:QWORD
EXTERN fPatchGame:QWORD

.data

.code

tPatchGame PROC
	sub rsp, 8
	call fPatchGame
	add rsp, 8
	jmp [bAntiTamperSkip]
tPatchGame ENDP

END