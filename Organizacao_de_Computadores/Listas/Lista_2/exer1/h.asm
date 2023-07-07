# Converta as linhas de instruções escritas em linguagem C para instruções em Assembly do MIPS.
# Considere que as variáveis indicadas A, B, C, D, E e F foram todas armazenadas previamente na
# memória de dados. Use os registradores de $s0 até $s5 para manipular os dados.
# B = A[5] + C[3]; 
.data
	A: .word 0 0 0 0 10
	B: .word 0
	C: .word 0 0 35

.text
main:
	la $s0, A
	la $s1, B
	la $s2, C
	
	lw $t0, 16($s0)
	lw $t1, 8($s2)
	
	add $t0, $t1, $t0
	
	sw $t0, 0($s1)
