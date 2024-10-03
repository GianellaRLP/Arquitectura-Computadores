.text
.globl __start
__start:
    la $a0, prm1
    li $v0, 4
    syscall

    la $a0, orig
    li $v0, 4
    syscall

    la $s0, orig          # Cargar dirección de la cadena original
    li $t0, 0             # contador

    li $t2, 1             # leí un espacio
    li $t3, 0             # indicador de rango minúsculas
    li $t4, 0
    li $t6, 0x20          # ASCII space
    li $t7, 0x61          # ASCII 'a'
    li $t8, 0x7a          # ASCII 'z'

loop:                     # bucle barrer cadena y alterar
    lb $t1, 0($s0)        # cargar byte actual de la cadena
    beq $t1, $zero, endLoop  # si es null, fin del bucle

    slt $t3, $t1, $t7      # t3 = 1 si t1 < 0x61 (fuera de minúsculas)
    slt $t4, $t8, $t1      # t4 = 1 si t1 > 0x7a
    or $t3, $t3, $t4       # 1 -> fuera de rango minúsculas

    beq $t2, $zero, nospace  # si no se leyó espacio antes
    bne $t3, $zero, nospace  # si no es minúscula, saltar

    addi $t1, $t1, -32     # convertir a mayúscula
    sb $t1, 0($s0)         # guardar byte cambiado

nospace:
    bne $t1, $t6, nospacenow  # si no es espacio, saltar
    li $t2, 1                # espacio leído
    j endspace
 
nospacenow:
    li $t2, 0                # no se leyó espacio

endspace:
    addi $s0, $s0, 1         # siguiente carácter
    j loop

endLoop:
    la $a0, prm2            # imprimir etiqueta 'Upcased'
    li $v0, 4
    syscall

    la $a0, orig            # imprimir cadena modificada
    li $v0, 4
    syscall

    li $v0, 10              # finaliza
    syscall

.data
orig: .asciiz "La cadena original con letras todas minusculas"
prm1: .asciiz "Original: "
prm2: .asciiz "\nUpcased: "
