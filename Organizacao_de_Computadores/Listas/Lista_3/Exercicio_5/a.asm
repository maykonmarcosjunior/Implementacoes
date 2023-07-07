# Reproduza cada uma das expressões escritas em linguagem de alto nível a seguir para Assembly do
# MIPS. Considerações:
# – As variáveis a e b são posições de memória (segmento de dados). Os valores (inteiros positivos)
#dessas variáveis devem ser informados pelo usuário via teclado.
# – Implemente pequenos programas, um para cada expressão abaixo.
# if (a > b) { a = a + 1;}
.text
main_:
	li $v0, 5
	syscall
	move $s0, $v0 # s0 = a
	li $v0, 5
	syscall
	move $s1, $v0 # s1 = b
	blt $s1, $s0, incrementaA
	j exit
incrementaA:
	addi $s0, $s0, 1
	move $a0, $s0
	li $v0, 1
	syscall
exit: nop	
