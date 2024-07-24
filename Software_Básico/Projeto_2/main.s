	.file	"main.c"
	.text
	.globl	multiply
	.type	multiply, @function
multiply:
.LFB11:
	.cfi_startproc
	movl	$1, %ecx
	jmp	.L2
.L3:
	imull	%edi, %edi
	movl	%esi, %eax
	shrl	$31, %eax
	addl	%eax, %esi
	sarl	%esi
.L2:
	testl	%esi, %esi
	jle	.L5
	movl	%esi, %edx
	shrl	$31, %edx
	leal	(%rsi,%rdx), %eax
	andl	$1, %eax
	subl	%edx, %eax
	cmpl	$1, %eax
	jne	.L3
	imull	%edi, %ecx
	jmp	.L3
.L5:
	movl	%ecx, %eax
	ret
	.cfi_endproc
.LFE11:
	.size	multiply, .-multiply
	.globl	potencia
	.type	potencia, @function
potencia:
.LFB12:
	.cfi_startproc
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	movq	%rdx, %rbx
	testl	%esi, %esi
	jne	.L7
	movl	$1, (%rdx)
.L6:
	popq	%rbx
	.cfi_remember_state
	.cfi_def_cfa_offset 8
	ret
.L7:
	.cfi_restore_state
	call	multiply
	movl	%eax, (%rbx)
	jmp	.L6
	.cfi_endproc
.LFE12:
	.size	potencia, .-potencia
	.globl	main
	.type	main, @function
main:
.LFB13:
	.cfi_startproc
	movl	$0, %eax
	ret
	.cfi_endproc
.LFE13:
	.size	main, .-main
	.ident	"GCC: (GNU) 13.2.0"
	.section	.note.GNU-stack,"",@progbits
