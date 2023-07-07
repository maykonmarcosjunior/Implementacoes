# Considere que o processador MIPS está sendo utilizado para controlar um conjunto de 32
# dispositivos externos. Cada dispositivo recebe um bit indicando se ele deve ser ligado (=1) ou
# desligado (=0). Estes bits estão armazenados no endereço de dados 0x10010020. Implemente um
# programa que faça as seguintes operações:
# • O usuário deve informar pelo teclado se quer ligar ou desligar um bit. Exemplo: se digitar 1, é para
# ligar algum bit. Se digitar 0, é para desligar algum bit;
# • O usuário deve informar, na sequência, qual bit deve ser ligado/desligado. Por exemplo, ao digitar
# 2, então o bit 2 do endereço 0x10010020 deve ser ligado ou desligado (conforme instrução anterior).
# • Os estados anteriores dos outros bits devem ser preservados obrigatoriamente.
.text
main:
	li $s0, 0x10010020
input:
	li $v0, 5
	syscall
	bgt $v0, 1, exit
	move $a0, $v0
	li $v0, 5
	syscall
	li $a1, 31
	bgt $v0, $a1, exit 
	move $a1, $v0
	sllv $a0, $a0, $a1
	lw $a1, 0($s0)
	add $a0, $a1, $a0
	sw $a0 0($s0)
	j input
exit: nop
