
#include <iostream>
#include <bitset>

// Función que actualiza los bits de A, C, y D según el corrimiento aritmético
template<size_t n>
void actualizarBits(std::bitset<n>& A, std::bitset<n>& C, std::bitset<1>& D) {
    D[0] = C[0];  // D toma el valor de C[0]
    C >>= 1;      // C se desplaza a la derecha
    C[n - 1] = A[0];  // El bit más significativo de C toma el valor de A[0]
    A >>= 1;      // A se desplaza a la derecha
    A[n - 1] = A[n - 2];  // Mantiene el signo de A (bit de signo)
}

// Suma binaria de dos números de n bits
template<size_t n>
std::bitset<n> add_binary_numbers(std::bitset<n> num1, std::bitset<n> num2) {
    std::bitset<n> result;
    int carry = 0;

    for (int i = 0; i < n; i++) {
        int sum = num1[i] + num2[i] + carry;  // Suma los bits más el acarreo
        result[i] = sum % 2;  // Almacena el bit resultante
        carry = sum / 2;      // Calcula el acarreo
    }

    return result;
}

// Calcula el complemento a 2 de un número binario de n bits
template<size_t n>
std::bitset<n> complementA2(std::bitset<n> binary) {
    return std::bitset<n>(~binary.to_ulong() + 1);  // Complemento a 2
}

// Convierte un número decimal a su representación binaria de n bits
template<size_t n>
std::bitset<n> decimalToBinary(int decimal) {
    return std::bitset<n>(decimal);
}

// Implementación del algoritmo de Booth
template<size_t n>
std::bitset<n * 2> boothMultiplicacion(int multiplicando, int multiplicador) {
    std::bitset<n> A(0);  // Inicializa A en 0
    std::bitset<n> M = decimalToBinary<n>(multiplicando);  // Multiplicando en binario
    std::bitset<n> C = decimalToBinary<n>(multiplicador);  // Multiplicador en binario
    std::bitset<1> D(0);  // Inicializa el bit Q-1 en 0

    // Calcula el complemento a 2 de M
    std::bitset<n> M_complemento = complementA2(M);

    // Ejecuta el algoritmo n veces
    for (int i = 0; i < n; i++) {
        // Si C[0] == 1 y D[0] == 0, A = A - M
        if (C[0] == 1 && D[0] == 0) {
            A = add_binary_numbers(A, M_complemento);
        }
        // Si C[0] == 0 y D[0] == 1, A = A + M
        else if (C[0] == 0 && D[0] == 1) {
            A = add_binary_numbers(A, M);
        }
        // Realiza el corrimiento aritmético
        actualizarBits(A, C, D);
    }

    // Combinamos A y C para formar un número de 2n bits como resultado
    std::bitset<n * 2> resultado;
    for (int i = 0; i < n; i++) {
        resultado[i] = C[i];         // Parte baja del resultado es C
        resultado[i + n] = A[i];     // Parte alta del resultado es A
    }

    return resultado;
}

int main() {
    int multiplicando, multiplicador;

    // Pide al usuario ingresar el multiplicando y el multiplicador
    std::cout << "Ingrese el multiplicando: ";
    std::cin >> multiplicando;
    std::cout << "Ingrese el multiplicador: ";
    std::cin >> multiplicador;

    // Definimos el número de bits para la operación (8 en este caso, se puede cambiar a otro tamaño)
    const size_t n = 8;

    // Calculamos el resultado con el algoritmo de Booth
    std::bitset<n * 2> resultado = boothMultiplicacion<n>(multiplicando, multiplicador);

    // Imprime el resultado en binario y en decimal
    std::cout << "Resultado (binario): " << resultado << std::endl;
    std::cout << "Resultado (decimal): " << static_cast<int>(resultado.to_ulong()) << std::endl;

    return 0;
}


