.data
	array:		.word 4, -10, 11, 2, 12
	out:		.asciiz "Max value in array is "
	newLine:	.asciiz "\n"
.text
	j	 main
findMax:
# array pointer - t0
# array size 	- t1
# for loop i	- t2
# max		- t3
# array [ i ]	- t4

	move 	$t0, $a0
	move	$t1, $a1
	lw 	$t3, 0($t0)

# set iterator
move	$t2, $zero

start_for:
# bge - check break condition
	bge 	$t2, $t1, end_loop
# body of loop
	# first read array[i] into t4
	lw	$t4, 0($t0)
	
	# if statement
	ble	$t4, $t3, if_false
	# true
	move	$t3, $t4
if_false:
	# false
	# increment iterator
	addi 	$t2, 1
	addi 	$t0, 4
	# j start_for - jump to condition check
	b	start_for	

end_loop:
	move 	$v0, $t3
	jr	$ra
# rest of code

main: 
	# Stack
	# return of findMax(4 bytes)
	# padded to 8 bytes = 8 bytes
	
	addi	$sp, $sp, -8
	
	# size 	- t0
	# array {4, -10, 11, 2, 12}
	
	li 	$t0, 5
	la 	$a0, array
	move	$a1, $t0
	jal	findMax
	
	# max is currently in v0
	sw	$v0, 0($sp)
	
	# print
	li	$v0, 4
	la	$a0, out
	syscall
	
	# print max value
	lw	$a0, 0($sp)
	li	$v0, 1
	syscall
	
	# print newLine
	li	$v0, 4
	la	$a0, newLine
	syscall
	
	addi	$sp, $sp, 8