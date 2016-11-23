.data
.text
.globl atr

atr:

push %rbp
movq %rsp, %rbp
sub $20, %rsp
movl $0, %ebx

movl $1, -4(%rbp)
movl $2, -8(%rbp)
movl $3, -12(%rbp)
movl $4, -16(%rbp)
movl $5, -20(%rbp)

movl %edi, -4(%rbp)
movl %edi, -8(%rbp)
movl %edi, -12(%rbp)


FIM:
movq %rbp, %rsp
pop %rbp
ret
