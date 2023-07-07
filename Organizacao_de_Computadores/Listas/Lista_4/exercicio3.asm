#A função abaixo, escrita em linguagem C, calcula a potência de um número (N^M).
# Implemente um programa em Assembly para o MIPS que:
# – Receba os valores de Base e Expoente via teclado;
# – Chame a função pow() para calcular a potência do número;
# – Mostre o resultado na tela do computador.
# int pow (int base, int expoente) {
#	int result = 1;
# 	for (int i = 0; i < expoente; i++) {
#	    result *= base;
#	}
#	return result;
# }
.text
main:
	li $v0, 5
	syscall
	move $a0, $v0 # a0 = base
	li $v0, 5
	syscall
	move $a1, $v0 # a1 = expoente
	li $a2, 1 # a2 = result
	jal pow
	move $a0, $v0
	li $v0, 1
	syscall
	j exit
pow:
	mult $a2, $a0 # mult = result*base
	mflo $a2 # result = mult
	subi $a1, $a1, 1
	bne $a1, $0, pow
	move $v0, $a2
	jr $ra
exit: nop
