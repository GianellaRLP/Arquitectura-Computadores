// Algoritmo de multiplicación de enteros con signo

//A es una palabra binaria auxiliar de n bits
//M es el multiplicando (palabra binaria de n bits)
//Q es el multiplicador (palabra binaria de n bits) en este caso C es el multiplicador
//Q−1 es el bit a la derecha auxiliar LSB de Q) en este caso usé la D
//n es la cantidad de bits de los factores a multiplicar

#include <iostream>
#include <bitset>

template<size_t n>
void actualizarBits(std::bitset<n>& A, std::bitset<n>& C, std::bitset<1>& D) {
    D[0] = C[0];  
    C >>= 1;      
    C[n - 1] = A[0];  // El bit más significativo de C toma el valor de A[0]
    A >>= 1;      
    A[n - 1] = A[n - 2];  
}

// suma binaria de dos números de n bits
template<size_t n>
std::bitset<n> add_binary_numbers(std::bitset<n> num1, std::bitset<n> num2) {
    std::bitset<n> result;
    int carry = 0;

    for (int i = 0; i < n; i++) {
        int sum = num1[i] + num2[i] + carry;  // suma los bits más el acarreo
        result[i] = sum % 2;  
        carry = sum / 2;      
    }

    return result;
}

// calcula el complemento a 2 de un número binario de n bits
template<size_t n>
std::bitset<n> complementA2(std::bitset<n> binary) {
    return std::bitset<n>(~binary.to_ulong() + 1);  // Complemento a 2
}

// número decimal a binario 
template<size_t n>
std::bitset<n> decimalToBinary(int decimal) {
    return std::bitset<n>(decimal);
}

template<size_t n>
std::bitset<n * 2> boothMultiplicacion(int multiplicando, int multiplicador) {
    std::bitset<n> A(0);  // Inicializa A en 0
    std::bitset<n> M = decimalToBinary<n>(multiplicando);  // Multiplicando en binario
    std::bitset<n> C = decimalToBinary<n>(multiplicador);  // Multiplicador en binario
    std::bitset<1> D(0);  // Inicializa el bit Q-1 en 0

    std::bitset<n> M_complemento = complementA2(M);
    
    for (int i = 0; i < n; i++) {
        if (C[0] == 1 && D[0] == 0) {
            A = add_binary_numbers(A, M_complemento);
        }
        else if (C[0] == 0 && D[0] == 1) {
            A = add_binary_numbers(A, M);
        }
        actualizarBits(A, C, D);
    }

    std::bitset<n * 2> resultado;
    for (int i = 0; i < n; i++) {
        resultado[i] = C[i];        
        resultado[i + n] = A[i];  
    }
    return resultado;
}

// convertir un bitset de 2n bits a entero con signo
template<size_t n>
int bitsetToSignedDecimal(std::bitset<n * 2> resultado) {
    if (resultado[n * 2 - 1] == 1) {     //si el bit más significativo es 1 (número negativo)
        return -((~resultado.to_ulong() + 1) & ((1 << (n * 2)) - 1)); // obtenemos el complemento a 2 para obtener el valor en negativo
    } else {
        return static_cast<int>(resultado.to_ulong()); // pero si es positivo solo se convierte a decimal
    }
}

int main() {
    int multiplicando, multiplicador;

    std::cout << "Ingrese el multiplicando: ";
    std::cin >> multiplicando;
    std::cout << "Ingrese el multiplicador: ";
    std::cin >> multiplicador;

    // definimos el número de bits
    const size_t n = 8;
    
    std::bitset<n * 2> resultado = boothMultiplicacion<n>(multiplicando, multiplicador);

    std::cout << "Resultado (binario): " << resultado << std::endl;
    int resultadoDecimal = bitsetToSignedDecimal<n>(resultado);
    std::cout << "Resultado (decimal): " << resultadoDecimal << std::endl;

    return 0;
}



