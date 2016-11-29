.data 
.text

.globl function

function:
push %rbp
movq %rsp, %rbp
subq $20, %rsp
movl $0, %ebx

movl $0, %ebx
movl $1, %eax

cmpl $0, %ebx
jne FIM

movq %rbp, %rsp
pop %rbp
ret

FIM:
movq %rbp, %rsp
pop %rbp
ret
