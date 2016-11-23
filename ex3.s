/*function
ret? p0 $1
v0 = p0 + $0
v1 = v0 - $1
v1 = call 0 v1
v0 = v0 * v1
ret? $0 v0
end*/

.data
.text
.globl ex3

ex3:

push %rbp
movq %rsp, %rbp
sub $20, %rsp
movl $0, %ebx

#ret? p0 $1
movl $0, %ebx
movl $1, %eax

cmpl $0, %ebx
je FIM
movl $0, %eax

#v0 = p0 + $0
movl %edi, %r12d
movl $1, %r13d
add %r12d, %r13d
movl %r13d, -4(%rbp)

#v1 = call 0 v1
movl -4(%rbp), %r12d
movl $1, %r13d
subl %r13d, %r12d 

#v1 = call 0 v1



FIM:
movq %rbp, %rsp
pop %rbp
ret
