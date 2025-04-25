.data
t0: .asciiz "false"
t1: .asciiz "red"
.text
.globl main
main:
	li $v0, 4
	la $a0, t0
	syscall
	li $v0, 11
	li $a0, 10
	syscall

	li $v0, 4
	la $a0, t1
	syscall
	li $v0, 11
	li $a0, 10
	syscall

	li $v0, 10
	syscall
