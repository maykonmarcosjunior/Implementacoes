# Converta as linhas de instruções escritas em linguagem C para instruções em Assembly do MIPS.
# Considere que as variáveis indicadas A, B, C, D, E e F foram todas armazenadas previamente na
# memória de dados. Use os registradores de $s0 até $s5 para manipular os dados.
# A = B[15] – C;  
.data
	A: .word 1
	B: .word 0 0 0 0 0 0 0 0 0 0 0 0 0 0 20
	C: .word -100
	
.text
main:
	la $s0, A
	la $s1, B
	la $s2, C
	
	lw $t0, 56($s1)
	lw $t1, 0($s2)
	
	sub $t0, $t0, $t1
	
	sw $t0, 0($s0)
