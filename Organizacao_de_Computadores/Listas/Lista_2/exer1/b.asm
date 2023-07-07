# Converta as linhas de instruções escritas em linguagem C para instruções em Assembly do MIPS.
# Considere que as variáveis indicadas A, B, C, D, E e F foram todas armazenadas previamente na
# memória de dados. Use os registradores de $s0 até $s5 para manipular os dados.
# D = (A + B - C).

.data
	A: .word 11
	B: .word 20
	C: .word 15
	D: .word 0

.text
	la $s0, A
	la $s1, B
	la $s2, C
	la $s3, D
	
	lw $t0, 0($s0)
	lw $t1, 0($s1)
	lw $t2, 0($s2)
	
	add $t0, $t0, $t1
	sub $t0, $t0, $t2
	
	sw $t0 0($s3)
