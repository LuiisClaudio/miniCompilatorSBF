
ex3.o:     file format elf64-x86-64


Disassembly of section .text:

0000000000000000 <ex3>:
   0:	55                   	push   %rbp
   1:	48 89 e5             	mov    %rsp,%rbp
   4:	48 83 ec 20          	sub    $0x20,%rsp
   8:	bb 00 00 00 00       	mov    $0x0,%ebx

   d:	89 fb                	mov    %edi,%ebx
   f:	b8 01 00 00 00       	mov    $0x1,%eax
  14:	83 fb 00             	cmp    $0x0,%ebx
  17:	75 05                	jne    1e <RET0>
  19:	48 89 ec             	mov    %rbp,%rsp
  1c:	5d                   	pop    %rbp
  1d:	c3                   	retq   

000000000000001e <RET0>:
  1e:	41 89 fc             	mov    %edi,%r12d
  21:	41 bd 00 00 00 00    	mov    $0x0,%r13d
  27:	45 01 ec             	add    %r13d,%r12d
  2a:	44 89 65 fc          	mov    %r12d,-0x4(%rbp)

  2e:	44 8b 65 fc          	mov    -0x4(%rbp),%r12d
  32:	41 bd 01 00 00 00    	mov    $0x1,%r13d
  38:	45 29 ec             	sub    %r13d,%r12d
  3b:	44 89 65 f8          	mov    %r12d,-0x8(%rbp)

  3f:	8b 7d f8             	mov    -0x8(%rbp),%edi
  42:	e8 00 00 00 00       	callq  47 <RET0+0x29>
  47:	89 45 f8             	mov    %eax,-0x8(%rbp)

  4a:	44 8b 65 fc          	mov    -0x4(%rbp),%r12d
  4e:	44 8b 6d f8          	mov    -0x8(%rbp),%r13d
  52:	45 0f af e5          	imul   %r13d,%r12d
  56:	44 89 65 fc          	mov    %r12d,-0x4(%rbp)

  5a:	bb 00 00 00 00       	mov    $0x0,%ebx
  5f:	8b 45 fc             	mov    -0x4(%rbp),%eax
  62:	83 fb 00             	cmp    $0x0,%ebx
  65:	75 05                	jne    6c <RET1>
  67:	48 89 ec             	mov    %rbp,%rsp
  6a:	5d                   	pop    %rbp
  6b:	c3                   	retq   

000000000000006c <RET1>:
  6c:	8b 7d fc             	mov    -0x4(%rbp),%edi
  6f:	8b 7d f8             	mov    -0x8(%rbp),%edi
  72:	8b 7d f4             	mov    -0xc(%rbp),%edi

  75:	89 ff                	mov    %edi,%edi

  77:	bf cc 06 06 00       	mov    $0x606cc,%edi
  7c:	bf 15 25 00 00       	mov    $0x2515,%edi

  81:	89 45 fc             	mov    %eax,-0x4(%rbp)
  84:	89 45 f8             	mov    %eax,-0x8(%rbp)
  87:	89 45 f4             	mov    %eax,-0xc(%rbp)


