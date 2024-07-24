.section .text
.globl parity

parity:
    movl %edi, %eax    # Mover o primeiro argumento (número) para eax
    xorl %eax, %eax    # Limpar o registrador eax
    testl %edi, %edi   # Testar o número
    setpo %al          # Definir o byte baixo de eax se a parity for ímpar
    ret                # Retornar