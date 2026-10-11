section .text
global ft_strcmp

ft_strcmp:

.loop:
    mov cl, byte [rdi]
    mov dl, byte [rsi]

    cmp cl, dl
    jne .end

    test cl, cl
    je .equal

    inc rdi
    inc rsi
    jmp .loop

.end:
    movzx eax, cl
    movzx edx, dl
    sub eax, edx
    ret

.equal:
    xor eax, eax
    ret

section .note.GNU-stack noalloc noexec nowrite progbits
