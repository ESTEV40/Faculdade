	.file	"main.c"
	.text
	.globl	comp
	.type	comp, @function
comp:
.LFB11:
	.cfi_startproc
	cmpq	%rsi, %rdi
	setl	%al
	movzbl	%al, %eax
	ret
	.cfi_endproc
.LFE11:
	.size	comp, .-comp
	.globl	function
	.type	function, @function
function:
.LFB12:
	.cfi_startproc
	movq	%rdi, %rax
	jmp	.L3
.L4:
	subq	$1, %rax
.L3:
	testq	%rax, %rax
	jg	.L4
	ret
	.cfi_endproc
.LFE12:
	.size	function, .-function
	.globl	absdiff
	.type	absdiff, @function
absdiff:
.LFB13:
	.cfi_startproc
	cmpq	%rsi, %rdi
	jge	.L6
	movq	%rsi, %rax
	subq	%rdi, %rax
	ret
.L6:
	movq	%rdi, %rax
	subq	%rsi, %rax
	ret
	.cfi_endproc
.LFE13:
	.size	absdiff, .-absdiff
	.globl	main
	.type	main, @function
main:
.LFB14:
	.cfi_startproc
	movl	$0, %eax
	ret
	.cfi_endproc
.LFE14:
	.size	main, .-main
	.ident	"GCC: (GNU) 13.2.0"
	.section	.note.GNU-stack,"",@progbits
