# Converta as linhas de instruções escritas em linguagem C para instruções em Assembly do MIPS.
# Considere que as variáveis indicadas A, B, C, D, E e F foram todas armazenadas previamente na
# memória de dados. Use os registradores de $s0 até $s5 para manipular os dados.
# A[45] = B – C + D[67];
.data
	A: .space 184
	B: .word 100
	C: .word 99
	D: .space 272

.text
main:
	la $s0, A
	la $s1, B
	la $s2, C
	la $s3, D

	lw $t0, 0($s1)
	lw $t1, 0($s2)
	lw $t2, 268($s3)
	
	sub $t0, $t0, $t1
	add $t0, $t0, $t2
	
	sw $t0, 180($s0)
