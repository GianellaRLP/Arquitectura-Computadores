#include <iostream>
#include <bitset>
#include <cmath>
#include <string>

std::string decimalToBinary(double decimal) {
    std::string binaryString;
    for (int i = 0; i < 23 && decimal != 0; ++i) {
        decimal *= 2;
        int bit = static_cast<int>(decimal);
        binaryString += std::to_string(bit);
        decimal -= bit;
    }

    while (binaryString.length() < 23) {
        binaryString += '0';
    }
    return binaryString;
}

std::bitset<8> enteroToBinary(int entero){
    return std::bitset<8>(entero);
}

std::string IEET_ENTERO(int value){
    std::string binaryString = std::bitset<8>(value).to_string();

    int leadingZeros = 0;
    for (char bit : binaryString) {
        if (bit == '0') {
            leadingZeros++;
        } else {
            break;
        }
    }

    binaryString = binaryString.substr(leadingZeros);
    int exponentLength = binaryString.length();
    int exponent = exponentLength + 126; // Exponent bias

    return std::bitset<8>(exponent).to_string();
}

std::bitset<23> IEET_DECIMAL(std::bitset<8> value, std::bitset<23> BIT23)
{
    std::string binaryString = value.to_string();
    int leadingZeros = 0;
    for (char bit : binaryString) {
        if (bit == '0') {
            leadingZeros++;
        } else {
            break;
        }
    }
    
    int shift = leadingZeros;
    BIT23 >>= shift;

    return BIT23;
}

std::bitset<8> MULTI_ENTERO(std::bitset<8> num1, std::bitset<8> num2, int simbolo) {
    int sum1 = num1.to_ulong();
    int sum2 = num2.to_ulong();
    int sum = (sum1 + sum2) - 126;

    if (sum <= 255) 
    {
        return std::bitset<8>(sum);
    }
    else 
    {
        std::cout << "Overflow/Underflow in exponent\n";
        return std::bitset<8>("00000000");
    }
}

int LONGITUD_BITS23(std::bitset<23> bits) {
    std::string bitsString = bits.to_string();
    int count = 0;
    for (int i = bitsString.size() - 1; i >= 0; --i) {
        if (bitsString[i] == '1') break;
        count++;
    }
    return 23 - count;
}

int LONGITUD_BITS46(std::bitset<48> bits) {
    std::string bitsString = bits.to_string();
    int count = 0;
    for (int i = bitsString.size() - 1; i >= 0; --i) {
        if (bitsString[i] == '1') break;
        count++;
    }
    return 48 - count;
}

std::bitset<23> MULTI_DECIMAL(std::bitset<23> bits1,  std::bitset<23> bits2) {
    int Long1 = LONGITUD_BITS23(bits1);
    int Long2 = LONGITUD_BITS23(bits2);

    std::bitset<24> shifted1(bits1.to_ulong());
    std::bitset<24> shifted2(bits2.to_ulong());

    shifted1[23] = 1;
    shifted2[23] = 1;

    std::bitset<48> result = shifted1.to_ullong() * shifted2.to_ullong();

    int Long3 = LONGITUD_BITS46(result);
    int shifts = Long3 - (Long1 + Long2);

    return std::bitset<23>(result.to_string()) <<= (shifts - 1);
}

std::string multiplyDecimal(double decimal1, double decimal2) {
    double product = decimal1 * decimal2;
    return decimalToBinary(product);
}

int main() {
    double Numero1;
    double Numero2;
	
	std::cout<<"Ingrese el primer numero: ";
    std::cin  >> Numero1;
	std::cout<<"Ingrese el segundo numero: ";
    std::cin  >> Numero2;
	
    int simbolo = 0;
    bool negativo = false;
	
    if ((Numero1 < 0 && Numero2 < 0) || (Numero1 > 0 && Numero2 > 0))
        negativo = false;
    else
        negativo = true;
	
    if (Numero1 < 0) Numero1 *= -1;
    if (Numero2 < 0) Numero2 *= -1;

    if (negativo) simbolo = 1;

    int Entero1 = static_cast<int>(Numero1);
    int Entero2 = static_cast<int>(Numero2);

    double Decimal1 = Numero1 - Entero1;
    double Decimal2 = Numero2 - Entero2;

    if (Entero1 == 0 || Entero2 == 0) {
        std::cout << "Resultado: 0 00000000.00000000000000000000000\n";
    }
    else
    {
        std::bitset<8> _1bit8 = enteroToBinary(Entero1);
        std::bitset<8> NUM1bit8(IEET_ENTERO(Entero1));
        std::bitset<23> _1bits23(decimalToBinary(Decimal1));
        std::bitset<23> NUM1bits23(IEET_DECIMAL(_1bit8, _1bits23));

        std::bitset<8> _2bit8 = enteroToBinary(Entero2);
        std::bitset<8> NUM2bit8(IEET_ENTERO(Entero2));
        std::bitset<23> _2bits23(decimalToBinary(Decimal2));
        std::bitset<23> NUM2bits23(IEET_DECIMAL(_2bit8, _2bits23));

        std::bitset<8> RESULT_ENTERO_PRE = MULTI_ENTERO(NUM1bit8, NUM2bit8, simbolo);
        std::bitset<23> RESULT_DECIMAL_PRE = MULTI_DECIMAL(NUM1bits23, NUM2bits23);

        std::cout << "Resultado: " << simbolo << " " << RESULT_ENTERO_PRE << "." << RESULT_DECIMAL_PRE << std::endl;
    }

    return 0;
}

