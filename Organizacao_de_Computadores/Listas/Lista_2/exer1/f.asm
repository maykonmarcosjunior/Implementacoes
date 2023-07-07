# Converta as linhas de instruções escritas em linguagem C para instruções em Assembly do MIPS.
# Considere que as variáveis indicadas A, B, C, D, E e F foram todas armazenadas previamente na
# memória de dados. Use os registradores de $s0 até $s5 para manipular os dados.
# F = E – (A – b) * (B – C).
.data
	A: .word 10
	B: .word 20
	C: .word 30
	b: .word -10
	E: .word -20
	F: .word 0

.text
main:
	la $s0, A
	la $s1, B
	la $s2, C
	la $s3, b
	la $s4, E
	la $s5, F
	
	lw $t0, 0($s0)
	lw $t1, 0($s1)
	lw $t2, 0($s2)
	lw $t3, 0($s3)
	lw $t4, 0($s4)
	
	sub $t0, $t0, $t3
	sub $t1, $t1, $t2
	
	mult $t0, $t1
	mflo $t0
	
	sub $t0, $t4, $t0
	
	sw $t0, 0($s5)
