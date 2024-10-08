### 汇编阶段/优化阶段

只有在验证源代码不包含语法错误后，编译器才会进入此阶段。
在此阶段，编译器尝试将标准语言结构转换为指定的 CPU 指令集。
不同的 CPU 具有不同的功能处理，通常具有不同的指令集，寄存器和中断，
这解释了为什么不同的处理器要有不同的编译器对其支持。

gcc编译器支持一种模式：将输入文件的源代码转换成对应ASCII编码的文本文件，
其中包含了特定芯片或操作系统所对应汇编指令集的代码行。

```
$ gcc -S <input file> -o <output assembler file>.s
```

除非另有指定，否则预处理器的输出是与输入文件同名的文件，并且其文件扩展名为 `.s`。
生成的文件并不是机器码，它只是一个包含对人类可读的汇编器指令助记符的文本文件，
开发人员可以使用这些指令来更好地了解内部编译过程的工作原理。

对于x86处理器体系结构来说，编译器支持两种指令格式，汇编代码会遵循其中一种：
- AT&T格式
- Intel格式


**AT&T汇编格式示例**

当通过下面的命令将function.c文件汇编成AT&T格式时：

```
$ gcc -S -masm=att function.c -o function.s
```

生成汇编输出文件的内容如下：

```
	.file	"function.c"
	.text
	.globl	nCompletionStatus
	.bss
	.align 4
	.type	nCompletionStatus, @object
	.size	nCompletionStatus, 4
nCompletionStatus:
	.zero	4
	.text
	.globl	add
	.type	add, @function
add:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movss	%xmm0, -20(%rbp)
	movss	%xmm1, -24(%rbp)
	movss	-20(%rbp), %xmm0
	addss	-24(%rbp), %xmm0
	movss	%xmm0, -4(%rbp)
	movss	-4(%rbp), %xmm0
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	add, .-add
	.globl	add_and_multiply
	.type	add_and_multiply, @function
add_and_multiply:
.LFB1:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movss	%xmm0, -20(%rbp)
	movss	%xmm1, -24(%rbp)
	movss	-24(%rbp), %xmm0
	movl	-20(%rbp), %eax
	movaps	%xmm0, %xmm1
	movl	%eax, -28(%rbp)
	movss	-28(%rbp), %xmm0
	call	add
	movd	%xmm0, %eax
	movl	%eax, -4(%rbp)
	movss	-4(%rbp), %xmm1
	movss	.LC0(%rip), %xmm0
	mulss	%xmm1, %xmm0
	movss	%xmm0, -4(%rbp)
	movss	-4(%rbp), %xmm0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	add_and_multiply, .-add_and_multiply
	.section	.rodata
	.align 4
.LC0:
	.long	1077936128
	.ident	"GCC: (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0"
	.section	.note.GNU-stack,"",@progbits
```

**Intel汇编格式示例**

当通过下面的命令将function.c文件汇编成Intel格式时：

```
$ gcc -S -masm=intel function.c -o function.s
```

生成汇编输出文件的内容如下：

```
	.file	"function.c"
	.intel_syntax noprefix
	.text
	.globl	nCompletionStatus
	.bss
	.align 4
	.type	nCompletionStatus, @object
	.size	nCompletionStatus, 4
nCompletionStatus:
	.zero	4
	.text
	.globl	add
	.type	add, @function
add:
.LFB0:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	movss	DWORD PTR -20[rbp], xmm0
	movss	DWORD PTR -24[rbp], xmm1
	movss	xmm0, DWORD PTR -20[rbp]
	addss	xmm0, DWORD PTR -24[rbp]
	movss	DWORD PTR -4[rbp], xmm0
	movss	xmm0, DWORD PTR -4[rbp]
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	add, .-add
	.globl	add_and_multiply
	.type	add_and_multiply, @function
add_and_multiply:
.LFB1:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 32
	movss	DWORD PTR -20[rbp], xmm0
	movss	DWORD PTR -24[rbp], xmm1
	movss	xmm0, DWORD PTR -24[rbp]
	mov	eax, DWORD PTR -20[rbp]
	movaps	xmm1, xmm0
	mov	DWORD PTR -28[rbp], eax
	movss	xmm0, DWORD PTR -28[rbp]
	call	add
	movd	eax, xmm0
	mov	DWORD PTR -4[rbp], eax
	movss	xmm1, DWORD PTR -4[rbp]
	movss	xmm0, DWORD PTR .LC0[rip]
	mulss	xmm0, xmm1
	movss	DWORD PTR -4[rbp], xmm0
	movss	xmm0, DWORD PTR -4[rbp]
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	add_and_multiply, .-add_and_multiply
	.section	.rodata
	.align 4
.LC0:
	.long	1077936128
	.ident	"GCC: (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0"
	.section	.note.GNU-stack,"",@progbits
```

创建与原始源代码对应的第一个汇编器版本后，优化工作就开始了，这可以将寄存器的使用量最小化。
此外，分析能够预测出实际上不会执行的代码部分，并将其删去。


#### 参考资料:
《高级C/C++编译技术》: 2.3.3 编译的各个阶段

