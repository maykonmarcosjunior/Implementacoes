.data
	ARRAY: .word 1 2 3 4 5 6 7
	STRING: .asciiz "               "
	fout: .asciiz "array.txt"
	
.text
	# ===============================================================================================
	# In�cio do Programa principal - main.
	# ===============================================================================================	
main:
	#
	# ----- O c�digo abaixo abre um arquivo para ser escrito. -----
	#
	li	$v0, 13			# Comando para abrir novo arquivo.
	la	$a0, fout		# Carrega o nome do arquivo a ser aberto.
	li	$a1, 1			# Aberto para escrita (0: l�r; 1: escrever).
	li	$a2, 0			# Modo ignorado (neste caso).
	syscall				# Chamada de sistema. Descritor do arquivo � colocado em $v0.
	move	$s6, $v0		# Salva descritor do arquivo para uso no fechamento posterior.
	
	# 
	# ----- Aqui o programa principal chama o procedimento de convers�o de dados escritos no buffer ARRAY 
	# para o buffer STRING em ASCII. -----
	# 	
	jal	transfer		# Chama procedimento para manipula��o dos arrrays. 

	# 
	# ----- Ap�s o retorno do procedimento, salva o buffer STRING no arquivo que foi aberto anteriormente. -----
	# 		
	li	$v0, 15			# Comando para escrever no arquivo.
	move	$a0, $s6		# Passa o descritor do arquivo previamente salvo.
	la	$a1, STRING		# Passa endere�o base do buffer a ser salvo.
	li	$a2, 44			# Delimita tamanho do buffer a ser escrito.
	syscall				# Chamada de sistema. Escreve buffer no arquivo.
	
	# 
	# ----- Ap�s transferir o buffer para o arquvio, o c�digo abaixo fecha o arquivo com uma chamada no SO. -----
	# 	
	li	$v0, 16			# Comando para fechamento do arquivo.
	move	$a0, $s6		# Passa o descritor do arquivo que ser� fechado.
	syscall				# Arquivo � fechado pelo Sistema Operacional.
	
end:
	j	fim			# Loop eterno. Programa fica neste ponto indefinidamente.
	# ===============================================================================================
	# Fim do programa principal. 
	# ===============================================================================================
		

	# ===============================================================================================
	# In�cio do Procedimento para transfer�ncia de dados entre ARRAY e STRING. 
	# ===============================================================================================
transfer:
	addi	$sp, $sp, -12		# Prepara PUSH para salvar dados de a0 e a1 (usados na rotina principal!)
	sw	$ra, 8($sp)		# Salva retorno - Stack Pointer.
	sw	$a0, 4($sp)		# Salva $a0.
	sw	$a1, 0($sp)		# Salva $a1.

	la	$a0, ARRAY		# Atualiza os endere�os de ARRAY e STRING em $a0 e $a1.
	la	$a1, STRING		#
		
	li	$s2, 7			# Limite de itera��es a serem feitas para transferir os dados
	li	$s7, 0   		# Ser� usado para contar la�o de loop.
	li	$s4, 0  		# �ndice do ARRAY come�ando em i = 0
	li	$s5, 0   		# �ndice da STRING come�ando em j = 0
loop:	
	#
	# ----- Nesta sequ�ncia vamos tirar um dado de ARRAY[i] -----
	#
	move	$s3, $s4		# Pega �ndice de ARRAY.
	add	$t1, $s3, $s3		# Aponta para o pr�ximo �ndice (2*i).
	add	$t1, $t1, $t1		# (4*i), sendo que i est� armazenado em $s3.
	add	$t1, $t1, $a0		# Endere�o Base + 4*i --> agora, apontando para o elemento do array.
	
	lw	$t0, 0($t1)		# $t0 <-- ARRAY[i].
	addi	$t0, $t0, 48		# Incrementa de 48 para transformar em caractere ASCII.
	addi	$s4, $s4, 1		# Incrementa �ndice i para a pr�xima itera��o.
	
	#
	# ----- Nesta sequ�ncia vamos colocar o dado retirado de ARRAY[i] em STRING[j] -----
	#
	move	$s3, $s5		# Pega �ndice da STRING de destino.
	add	$t1, $s3, $s3		# Aponta para o pr�ximo �ndice (2*j)
	add	$t1, $t1, $t1		# (4*j), sendo que j est� armazenado em $s3
	add	$t1, $t1, $a1		# Endere�o Base + 4*i --> agora, apontando para o elemento do array.
	
	sw	$t0, 0($t1)		# Armazena conte�do retirado de ARRAY[i] em STRING[j].
	li	$t0, 32			# Coloca caracter de "espaco em branco" (ASCII) em $t0.
	sw	$t0, 4($t1)		# Armazena espe�o em branco em STRING[j+1].
	addi	$s5, $s5, 1		# Incrementa �ndice j para a pr�xima itera��o.
	addi	$s7, $s7, 1		# Incrementa la�o do loop.
	bne	$s2, $s7, loop
	
	lw	$a1, 0($sp)		# Restaura $a1.
	lw	$a0, 4($sp)		# Restaura $a0.
	lw	$ra, 8($sp)		# Restaura $ra.
	addi	$sp, $sp, 12		# Atualiza $SP (POP de tr�s instru��es).
	jr	$ra			# Retorna do procedimento para o programa principal.
	# ===============================================================================================
	# Fim do Procedimento. 
	# ===============================================================================================
fim: nop
