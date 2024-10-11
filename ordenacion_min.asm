#	Cuando se hallan números repetidos y estos son los mayores en el array, 
#   solo tomará al primero que encuentre en el array y considerará su posición. 
#   Fuera el caso de que se hallen números repetidos y no sea los mayores entonces los ignorará


.data
array:        .word 23, 5, 4, 6, 9, 9, 74, 12, 1  
tamano:       .word 9                            # Tamaño del array
v_max:        .word 0                            # Valor máximo
i_max:        .word 0                            # Índice del valor máximo
mensaje_intro: .asciiz "Buscando el valor máximo en el array:\n"
mensaje_array: .asciiz "\nContenido del array: "
mensaje1:     .asciiz "\nValor máximo: "
mensaje2:     .asciiz "\nPosición: "
comma_space:  .asciiz ", "                       # Coma y espacio para separar los números

.text 
main:
    
    li $v0, 4                              
    la $a0, mensaje_intro                  
    syscall                                 

    # Imprimir mensaje array
    li $v0, 4                              
    la $a0, mensaje_array                  
    syscall                                 

    la $t0, array                          
    lw $t1, tamano                         

    # Imprimir el array
    li $t2, 0 
                                  
print_array:
    bge $t2, $t1, find_max                 
    lw $a0, 0($t0)                          
    li $v0, 1                               
    syscall                                 

    # Imprimir coma y espacio después de cada número 
    addi $t2, $t2, 1                        # Incrementar el índice
    bge $t2, $t1, skip_comma                # Si es el último elemento, saltar
    li $v0, 4                               
    la $a0, comma_space                     # Cargar dirección de coma y espacio
    syscall                                  

skip_comma:
    addi $t0, $t0, 4                        # Avanzar al siguiente elemento del array
    j print_array                           

find_max:
    la $a0, array                          
    lw $a1, tamano                         
    jal max                                 

    sw $v0, v_max                          
    sw $v1, i_max                           

    # Imprimir el valor y posición
    li $v0, 4                              
    la $a0, mensaje1                       
    syscall                                  

    li $v0, 1                               
    lw $a0, v_max                           
    syscall                                  

    li $v0, 4                               
    la $a0, mensaje2                        
    syscall                                 

    li $v0, 1                               
    lw $a0, i_max                           
    syscall                                  

    li $v0, 10                              # Finalizar programa               
    syscall


max:
    lw $t0, 0($a0)                          # Cargar el primer elemento
    li $t1, 0                               # Inicializar índice del máximo
    li $t2, 0                               # Contador para iterar

loop:
    bge $t2, $a1, done                     # Si se ha procesado todo el array, salir
    lw $t3, 0($a0)                          # Cargar el elemento actual
    bgt $t3, $t0, actualizar                # Si el elemento actual es mayor, actualizar

    addi $a0, $a0, 4                        # Avanzar al siguiente elemento
    addi $t2, $t2, 1                        # Incrementar el contador
    j loop                                   # Volver al inicio del bucle

actualizar:
    move $t0, $t3                           # Actualizar el valor máximo
    move $t1, $t2                           # Actualizar el índice del máximo
    addi $a0, $a0, 4                        # Avanzar al siguiente elemento
    addi $t2, $t2, 1                        # Incrementar el contador
    j loop                                   # Volver al inicio del bucle

done:
    move $v0, $t0                           # Mover el valor máximo a $v0
    move $v1, $t1                           # Mover el índice del máximo a $v1
    jr $ra                                   # Retornar al llamador
