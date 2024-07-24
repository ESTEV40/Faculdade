	.file	"main.c"
	.intel_syntax noprefix
	.text
	.globl	comp
	.type	comp, @function
comp:
.LFB11:
	.cfi_startproc
	cmp	rdi, rsi
	setl	al
	movzx	eax, al
	ret
	.cfi_endproc
.LFE11:
	.size	comp, .-comp
	.globl	function
	.type	function, @function
function:
.LFB12:
	.cfi_startproc
	mov	rax, rdi
	jmp	.L3
.L4:
	sub	rax, 1
.L3:
	test	rax, rax
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
	cmp	rdi, rsi
	jge	.L6
	mov	rax, rsi
	sub	rax, rdi
	ret
.L6:
	mov	rax, rdi
	sub	rax, rsi
	ret
	.cfi_endproc
.LFE13:
	.size	absdiff, .-absdiff
	.globl	main
	.type	main, @function
main:
.LFB14:
	.cfi_startproc
	mov	eax, 0
	ret
	.cfi_endproc
.LFE14:
	.size	main, .-main
	.ident	"GCC: (GNU) 13.2.0"
	.section	.note.GNU-stack,"",@progbits
