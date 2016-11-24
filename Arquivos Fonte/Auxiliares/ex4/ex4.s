.data
.text
.globl f0, f1

//Calcula o quadrado de n
f0:
/*
 function
 v0 = p0 * p0
 ret? $0 p0
 end
*/
push %rbp
movq %rsp, %rbp
sub  $32, %rsp
movl $0, %ebx

#v0 = p0 * p0
movl   %edi, %r12d
movl   %edi, %r13d
imull  %r13d, %r12d
movl   %r12d, -4(%rbp)

#ret? $0 v0
movl $0, %ebx
movl -4(%rbp), %eax
cmpl $0, %ebx /* p0 == 0 ? */
je   FIM0
movl $0, %eax

FIM0:
movq %rbp, %rsp
pop %rbp
ret

//Calcula a soma dos quadrados dos n primeiros naturais
f1:
/*
 function
 ret? p0 $0
 v0 = p0 - $1
 v1 = call 0 p0
 v0 = call 1 v0
 v0 = v0 + v1
 ret? $0 v0
 end
*/
push %rbp
movq %rsp, %rbp
sub  $32, %rsp
movl $0, %ebx

#ret? p0  $0
movl %edi, %ebx
movl $0, %eax
cmpl $0, %ebx /* p0 == 0 ? */
je   FIM1
movl $0, %eax

#v0 = p0 - $1
movl   %edi, %r12d
movl   $1, %r13d
sub    %r13d, %r12d
movl   %r12d, -4(%rbp)

#v1 = call 0 p0
movl %edi, %edi
call f0
movl %eax, -8(%rbp)

#v0 = call 1 v0
movl -4(%rbp), %edi
call f1
movl %eax, -4(%rbp)

#v0 = v0 + v1
movl   -4(%rbp), %r12d
movl   -8(%rbp), %r13d
add    %r13d, %r12d
movl   %r12d, -4(%rbp)

#ret? $0 v0
movl $0, %ebx
movl -4(%rbp), %eax
cmpl $0, %ebx /* p0 == 0 ? */
je   FIM1
movl $0, %eax

FIM1:
movq %rbp, %rsp
pop %rbp
ret
