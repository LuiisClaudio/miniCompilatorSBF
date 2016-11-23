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

f0:
push %rbp
movq %rsp, %rbp
sub $16, %rsp
movl $0, %ebx

#ret? p0 $1
movl $1, %eax
cmpl $0, %edi /* p0 == 0 ? */
je FIM
movl $0, %eax

#v0 = p0 + $0
movl %edi, -4(%rbp) /* v0 = p0, guarda v0 na pilha */

#v1 = v0 - $1
movl -4(%rbp), %r12d /* v1 = v0 */
subl $1, %r12d /* v1 = v0 - 1 */
movl %r12d, -8(%rbp) /* guarda v1 na pilha em cima de v0 */

#v1 = call 0 v1
movl %r12d, %edi
call f0
movl %eax, -8(%rbp) /* guarda v1 na pilha em cima de v0 */

#v0 = v0 * v1
movl -4(%rbp), %r12d
movl -8(%rbp), %r13d
imull %r13d, %r12d /* v0 = v0 * v1 */
movl %r13d, -4(%rbp)

#ret? $0 v0
movl -4(%rbp), %eax

FIM:
movq %rbp, %rsp
pop %rbp
ret
