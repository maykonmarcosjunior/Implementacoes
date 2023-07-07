# A função abaixo, escrita em linguagem C, calcula o fatorial de um número. Implemente um
# programa em Assembly para o MIPS que:
# – Receba via teclado o valor do número a ser calculado o fatorial;
# – Chame a função fatorial( ) para calcular o fatorial do número;
# – Mostre o resultado na tela do computador
# int fatorial (int n) {
#	if (n<1) return 1;
#	else
# return (n * fatorial(n - 1));
# }
.text
main:
	li $v0, 5
	syscall
	move $a0, $v0 # a0 = n
	jal fatorial
	move $a0, $v0
	li $v0, 1
	syscall
	j exit

fatorial:
	subi $sp, $sp, 8
	sw $ra, 4($sp)
	sw $a0, 0($sp)
	bge $a0, 1, recursao
	li $v0, 1
	addi $sp, $sp, 8
	jr $ra
recursao:
	subi $a0, $a0, 1
	jal fatorial
	lw $a0, 0($sp)
	lw $ra, 4($sp)
	addi $sp, $sp, 8
	mul $v0, $a0, $v0
	jr $ra

exit:	nop
