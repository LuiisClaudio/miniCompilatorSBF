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
mov  %rsp, %rbp
sub  $32, %rsp
mov  $0, %ebx

#ret? p0 $1
mov  %edi, %ebx
mov  $1, %eax
cmpl $0, %ebx /* p0 == 0 ? */
je   FIM
mov  $0, %eax

#v0 = p0 + $0
mov  %edi, %r12d
mov  $0, %r13d
add  %r12d, %r13d
movl %r13d, -4(%rbp) /* v0 = p0, guarda v0 na pilha */

#v1 = v0 - $1
mov  -4(%rbp), %r12d
mov  $1, %r13d
sub  %r12d, %r13d
mov  %r13d, -8(%rbp)

#v1 = call 0 v1
mov  -8(%rbp), %edi
call ex3
mov  %eax, -8(%rbp)

#v0 = v0 * v1
mov   -4(%rbp), %r12d
mov   -8(%rbp), %r13d
imul  %r12d, %r13d
mov   %r13d, -4(%rbp)

movl -4(%rbp), %r12d
movl %eax, %r13d
imull %r13d, %r12d /* v0 = v0 * v1 */

#ret? $0 v0
mov  $0, %ebx
mov  -4(%rbp), %eax
cmpl $0, %ebx /* p0 == 0 ? */
je   FIM
mov  $0, %eax

FIM:
movq %rbp, %rsp
pop %rbp
ret
