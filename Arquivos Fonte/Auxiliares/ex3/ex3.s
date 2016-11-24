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
sub $32, %rsp
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
//movl %r12d, -8(%rbp) /* guarda v1 na pilha em cima de v0 */

#v1 = call 0 v1
movl %r12d, %edi
call ex3

#v0 = v0 * v1
movl -4(%rbp), %r12d
movl %eax, %r13d
imull %r13d, %r12d /* v0 = v0 * v1 */

#ret? $0 v0
movl %r12d, %eax

FIM:
movq %rbp, %rsp
pop %rbp
ret
