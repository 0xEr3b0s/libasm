section .text
global ft_read
extern __errno_location

ft_read:
	xor eax, eax
	syscall

	cmp rax, 0
	js .error
	ret

.error:
	neg rax
	mov rdi, rax
	call __errno_location wrt ..plt
	mov [rax], edi
	mov rax, -1
	ret

section .note.GNU-stack noalloc noexec nowrite progbits
