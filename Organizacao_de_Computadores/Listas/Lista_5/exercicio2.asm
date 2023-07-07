# Implemente o código abaixo e verifique o resultado final nos registradores $t0 e $t1:

.data
	ENTRADA: .byte 1 2 -2 -3 -4
.text
main:
	la $s2, ENTRADA
	lb $t0, 2($s2)
	lbu $t1, 3($s2)
loop:
	j loop
