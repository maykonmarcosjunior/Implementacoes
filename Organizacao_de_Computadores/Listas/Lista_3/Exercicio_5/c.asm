# Reproduza cada uma das expressões escritas em linguagem de alto nível a seguir para Assembly do
# MIPS. Considerações:
# – As variáveis a e b são posições de memória (segmento de dados). Os valores (inteiros positivos)
#dessas variáveis devem ser informados pelo usuário via teclado.
# – Implemente pequenos programas, um para cada expressão abaixo.
# if (a ≤ b) {a = a + 1;}
.text
main_:
	li $v0, 5
	syscall
	move $a0, $v0 # a0 = a
	li $v0, 5
	syscall
	move $a1, $v0 # a1 = b
	bgt $a0, $a1, exit
	add $a0, $a0, 1
exit:
	li $v0, 1
	syscall
