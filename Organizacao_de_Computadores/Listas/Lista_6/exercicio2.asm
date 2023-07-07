# Implemente um programa que converta a temperatura dada em Fahrenheit via teclado para Celsius. Premissas:
# ◦ Utilize a equação de conversão TC/5 = (TF – 32)/9, em que TC é a temperatura em Celsius e TF em fahreinheit;
# ◦ A equação de conversão deve ser implementada como um procedimento.
.text
main:
	li $v0, 6
	syscall
	jal FtoC
	li $v0, 2
	syscall
	j exit
FtoC:
	la $s0, ctes
	li $a0, 32
	mtc1.d $a0, $f12
	cvt.s.w $f12, $f12
	sub.s $f12, $f0, $f12
	li $a0, 9
	mtc1 $a0, $f0
	cvt.s.w $f0, $f0
	div.s $f12, $f12, $f0
	li $a0, 5
	mtc1 $a0, $f0
	cvt.s.w $f0, $f0
	mul.s  $f12, $f12, $f0
	jr $ra
exit: nop
