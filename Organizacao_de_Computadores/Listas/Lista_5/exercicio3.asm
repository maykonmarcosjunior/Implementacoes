# Escreva um programa em Assembly do MIPS que receba uma string do teclado com até 7 dígitos
# armazene esta string recebida na memória de dados. 
# Sugestão: use o comando 8 na chamada de sistema syscall.

.data
	string: .space 32
.text
	li $v0, 8
	la $a0, string
	li $a1, 8
	syscall
