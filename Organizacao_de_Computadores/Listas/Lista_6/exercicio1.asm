# Considere que o valor de π (pi) seja 3.141592653589793.
# Crie um programa que calcule a área de um círculo.
# O usuário deverá informar o raio do círculo via teclado.
.data
	pi: .double 3.141592653589793
.text
main:
	la $s0, pi
	l.d $f12, 0($s0)
	li $v0, 7
	syscall
	mul.d $f0, $f0, $f0
	mul.d $f12, $f0, $f12
	li $v0, 3
	syscall
