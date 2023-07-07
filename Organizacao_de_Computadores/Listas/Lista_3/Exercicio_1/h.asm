# Converta as linhas de instruções escritas em linguagem C para instruções em Assembly do MIPS.
# Considere que:
# – As variáveis indicadas A = 10, B = 15, C = 20, D = 25, E = 30 e F = 35 foram todas armazenadas
# previamente na memória de dados. Use os registradores de $s0 até $s5 para manipular os dados.
# – Os vetores G e H possuem quatro posições cada e inicializam com zeros em suas posições
# (words). Use os registradores $s6 e $s7 para manipular estas posições.
# – Implemente as linhas de instruções abaixo como sendo linhas de um mesmo programa.
# H[3] = B – G[0] + D;
.data
	A: .word 10
	B: .word 15
	C: .word 20
	D: .word 25
	E: .word 30
	F: .word 35
	G: .word 10 5 -15 -5
	H: .word -5 30 -10 0 # --> -5 30 -10 30
.text
main_:
	la $s1, B
	la $s3, D
	la $s6, G
	la $s7, H
	
	lw $t1, 0($s1)
	lw $t3, 0($s3)
	lw $t6, 0($s6)
	
	sub $t1, $t1, $t6
	add $t1, $t1, $t3
	
	sw $t1, 12($s7)

