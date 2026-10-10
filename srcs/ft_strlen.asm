section .text
global ft_strlen

ft_strlen:
	mov eax, 0
	call .loop

.loop:
	cmp BYTE [rdi], 0x00 ; 0x00 = \0
	je .end

	inc rax
	inc rdi
	jmp .loop

.end:
	ret

section .note.GNU-stack noalloc noexec nowrite progbits
