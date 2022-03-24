	.file	"activity.c"
	.text
	.section	.rodata
.LC0:
	.string	"Enter arrow base height:"
.LC1:
	.string	"%d"
.LC2:
	.string	"Enter arrow base width:"
.LC3:
	.string	"Enter arrow head width:"
.LC4:
	.string	"**"
.LC5:
	.string	"****"
.LC6:
	.string	"***"
.LC7:
	.string	"*"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	$.LC0, %edi
	call	puts
	leaq	-4(%rbp), %rax
	movq	%rax, %rsi
	movl	$.LC1, %edi
	movl	$0, %eax
	call	__isoc99_scanf
	movl	$.LC2, %edi
	call	puts
	leaq	-8(%rbp), %rax
	movq	%rax, %rsi
	movl	$.LC1, %edi
	movl	$0, %eax
	call	__isoc99_scanf
	movl	$.LC3, %edi
	call	puts
	leaq	-12(%rbp), %rax
	movq	%rax, %rsi
	movl	$.LC1, %edi
	movl	$0, %eax
	call	__isoc99_scanf
	movl	$10, %edi
	call	putchar
	movl	$.LC4, %edi
	call	puts
	movl	$.LC4, %edi
	call	puts
	movl	$.LC4, %edi
	call	puts
	movl	$.LC5, %edi
	call	puts
	movl	$.LC6, %edi
	call	puts
	movl	$.LC4, %edi
	call	puts
	movl	$.LC7, %edi
	call	puts
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (GNU) 8.4.1 20200928 (Red Hat 8.4.1-1)"
	.section	.note.GNU-stack,"",@progbits
