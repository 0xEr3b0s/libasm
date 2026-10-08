extern __errno_location

section .text
global ft_read

ft_read:
	xor eax, eax ; set all bit to 0 to syscall read ( opcode = 0 )
	syscall

	cmp rax, 0 ; si
	jb .error

	ret

.error:
	neg rax ; absolute value
	mov rdi, rax
	call __errno_location
	mov [rax], edi
	mov rax, -1
	ret

