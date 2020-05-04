section .text
global _main
_main:
    jmp message
go_back:
    mov rax, 0x2000004
    mov rdi, 1
    pop rsi
    mov rdx, 12
    syscall
    nop
    nop
    jmp address
message:
    call go_back
    db "Hello World",0xa
address:
    mov rax, 0x00000001000011E8
    jmp rax
