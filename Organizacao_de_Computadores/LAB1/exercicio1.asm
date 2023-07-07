####### Maykon Marcos Junior

# execrcicio 1da atividade 01
# executa a operacao a = b + 35; c = d - a + e;
# b, d, e estao armazenados na memoria de dados,
# a e c devem ser armazenados la tambem
# o resultado final deve ser armazenado em c

.data
a: .word 0
b: .word 5
c: .word 0
d: .word 10
e: .word 15

.text
main:

la $t0, a
la $t1, b
la $t2, c
la $t3, d
la $t4, e

lw $t5, 0($t1) # t5 = b
addi, $t1, $t5, 35 # t1 = b + 35
sw $t1, 0($t0) # a = b + 35 = 40

lw $t0, 0($t3) # t0 = d
lw $t3, 0($t4) # t3 = e
sub $t4, $t0, $t1 # t4 = d - a = -30
add $t5, $t4, $t3 # t5 = (d - a) + e
sw $t5, 0($t2) # c = t5 = -15