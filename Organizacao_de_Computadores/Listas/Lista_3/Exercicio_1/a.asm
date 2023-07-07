# Converta as linhas de instruções escritas em linguagem C para instruções em Assembly do MIPS.
# Considere que:
# – As variáveis indicadas A = 10, B = 15, C = 20, D = 25, E = 30 e F = 35 foram todas armazenadas
# previamente na memória de dados. Use os registradores de $s0 até $s5 para manipular os dados.
# – Os vetores G e H possuem quatro posições cada e inicializam com zeros em suas posições
# (words). Use os registradores $s6 e $s7 para manipular estas posições.
# – Implemente as linhas de instruções abaixo como sendo linhas de um mesmo programa.
# G[0] = (A – (B + C) + F);
.data
	A: .word 10
	B: .word 15
	C: .word 20
	D: .word 25
	E: .word 30
	F: .word 35
	G: .word 1 0 0 0
	H: .word 0 0 0 0
.text
main:
	la $s0, A
	la $s1, B
	la $s2, C
	la $s5, F
	la $s6, G
	
	lw $t0, 0($s0)
	lw $t1, 0($s1)
	lw $t2, 0($s2)
	lw $t5, 0($s5)
	
	add $t1, $t1, $t2
	sub $t0, $t0, $t1
	add, $t0, $t0, $t5
	
	sw $t0, 0($s6)
