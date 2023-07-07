# Implemente em Assembly do MIPS o código abaixo, escrito em linguagem C. Utilize as chamadas de
# sistema (syscall) para implementar as funções printf() e scanf().
# int n1, n2;
# void leitura () {
#	printf(" \n Digite o valor do primeiro numero: ");
#	scanf("%d", &n1);
#	printf(" \n Digite o valor do segundo numero: ");
#	scanf("%d", &n2);
# }
# int soma (int n1, int n2) {
#	leitura();
#	return (n1 + n2);
# }
# int main(void) {
#	soma(n1, n2);
#	printf(" \n O resultado da soma é: %d", soma (n1, n2));
#	return 0;
# }
.data
	n1: .word 0
	n2: .word 0
	string0: .asciiz " \n Digite o valor do primeiro numero: "
	string1: .asciiz " \n Digite o valor do segundo numero: "
	string2: .asciiz " \n O resultado da soma é: "
.text
la $s0, n1
la $s1, n2
main:
	jal soma
	jal soma # na hora de imprimir chama de novo
	la $a0, string2
	li $v0, 4
	syscall
	move $a0, $v0
	li $v0, 1
	syscall
	j exit
soma:
	move $t9, $ra
	jal leitura
	lw $a0, 0($s0) # a0 = n1
	lw $a1, 0($s1) # a1 = n2
	add $v0, $a0, $a1
	move $ra, $t9
	jr $ra
leitura:
	la $a0, string0
	li $v0, 4
	syscall
	li $v0, 5
	syscall
	sw $v0, 0($s0) # n1 = input
	la $a0, string1
	li $v0, 4
	syscall
	li $v0, 5
	syscall
	sw $v0, 0($s1) # n2 = input
	jr $ra
exit: nop
