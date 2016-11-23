.data 
.text

.globl function

function:
push %rbp
movq %rsp, %rbp
subq $20, %rsp
movl $0, %ebx 

movl $1, %eax

cmpl $0, %ebx
je FIM


FIM:
movq %rbp, %rsp
pop %rbp
ret 

