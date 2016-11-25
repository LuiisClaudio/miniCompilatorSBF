/*
 function
 ret? p0 $1
 v0 = p0 + $0
 v1 = v0 - $1
 v1 = call 0 v1
 v0 = v0 * v1
 ret? $0 v0
 end
*/

.data
.text
.globl ex3

ex3:
push %rbp
movq %rsp, %rbp
sub  $32, %rsp
movl $0, %ebx

#ret? p0 $1
movl %edi, %ebx
movl $1, %eax
cmpl $0, %ebx /* p0 == 0 ? */
jne   RET0
movq %rbp, %rsp
pop %rbp
ret
RET0:
#// removi essa linha movl $0, %eax

#v0 = p0 + $0
movl %edi, %r12d
movl $0, %r13d
add  %r13d, %r12d
movl %r12d, -4(%rbp) /* v0 = p0, guarda v0 na pilha */

#v1 = v0 - $1
movl -4(%rbp), %r12d
movl $1, %r13d
sub  %r13d, %r12d
movl %r12d, -8(%rbp)

#v1 = call 0 v1
movl -8(%rbp), %edi
call ex3
movl %eax, -8(%rbp)

#v0 = v0 * v1
movl   -4(%rbp), %r12d
movl   -8(%rbp), %r13d
imull  %r13d, %r12d
movl   %r12d, -4(%rbp)

#ret? $0 v0
movl $0, %ebx
movl -4(%rbp), %eax
cmpl $0, %ebx /* p0 == 0 ? */
jne  RET1
movq %rbp, %rsp
pop %rbp
ret
RET1:

#// Testes de possiveis chamadas
mov    -0x4(%rbp),%edi
mov    -0x8(%rbp),%edi
mov    -0xc(%rbp),%edi

mov    %edi,%edi

mov    $0x606cc,%edi
mov    $0x2515,%edi

movl %eax, -0x4(%rbp)
movl %eax, -0x8(%rbp)
movl %eax, -0xc(%rbp)


