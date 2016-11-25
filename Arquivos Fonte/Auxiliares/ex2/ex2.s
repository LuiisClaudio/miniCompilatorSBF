/*
function
v0 = p0 + $1
ret? $0 v0
end
*/

.data
.text
.globl ex2

ex2:

push %rbp
movq %rsp, %rbp
sub $32, %rsp
movl $0, %ebx

movl %edi, %r12d
movl $1, %r13d
add %r13d, %r12d
movl %r12d, -4(%rbp)

movl $0, %ebx
movl -4(%rbp), %eax

cmpl $0, %ebx
jne FIM

movq %rbp, %rsp
pop %rbp
ret

FIM:
/*
movl $1, -4(%rbp)
movl $2, -8(%rbp)
movl $3, -12(%rbp)
movl $4, -16(%rbp)
movl $5, -20(%rbp)
*/
movl %edi, -4(%rbp)
movl %r13d, -4(%rbp)
movl %r13d, -8(%rbp)
movl %r13d, -12(%rbp)
movl %r13d, -16(%rbp)
movl %r13d, -20(%rbp)
/*
addl $1, -4(%rbp)
addl $3, -8(%rbp)
addl $4, -12(%rbp)
addl $5, -16(%rbp)
addl $6, -20(%rbp)

movl -4(%rbp), %r12d
addl %r12d, -8(%rbp)

movl -8(%rbp), %r12d
addl %r12d, -20(%rbp)
*/

movl $1, %r12d
movl $2, %r12d
movl $3, %r12d

movl -4(%rbp), %r12d
movl -8(%rbp), %r12d
movl -12(%rbp), %r12d
movl -16(%rbp), %r12d
movl -20(%rbp), %r12d


movl %edi, %r13d

movl $1, %r13d
movl $2, %r13d
movl $3, %r13d

movl -4(%rbp), %r13d
movl -8(%rbp), %r13d
movl -12(%rbp), %r13d


addl %r12d, %r13d
subl %r12d, %r13d
imull %r12d, %r13d




movl %edi, %r12d
addl $1,   %r12d
addl $4,   %r12d
movl %r12d, -4(%rbp)

movl -4(%rbp), %r12d
movl %edi, %r12d
addl -4(%rbp),   %r12d
movl %r12d, -4(%rbp)

movl $7, -8(%rbp)
movl -8(%rbp), %r12d
movl %edi, %r12d
addl -8(%rbp),   %r12d
movl %r12d, -8(%rbp)

movl %edi, %ebx

movl $394956, %ebx
movl $9493,  %ebx

movl -4(%rbp), %ebx
movl -8(%rbp), %ebx
movl -12(%rbp), %ebx
movl -16(%rbp), %ebx
movl -20(%rbp), %ebx

movl -4(%rbp), %eax
movl -8(%rbp), %eax
movl -12(%rbp), %eax
movl -16(%rbp), %eax
movl -20(%rbp), %eax

movl %edi, %eax

movl $3956, %eax
movl $9496767,  %eax

#//movl $1, %r12d
#//addl %edi, %r12d

cmpl $0, %ebx
je FIM

#FIM:
movq %rbp, %rsp
pop %rbp
ret

