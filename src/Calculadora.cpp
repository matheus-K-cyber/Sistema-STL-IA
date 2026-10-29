#include "Calculadora.hpp"

#include <cmath>

int Calculadora::quilosParaCentesimos(double quilos) {
    return static_cast<int>(std::round(quilos * 100.0));
}

double Calculadora::centesimosParaQuilos(int centesimos) {
    return static_cast<double>(centesimos) / 100.0;
}

int Calculadora::capacidadeGeral(int slotsComuns) {
    return slotsComuns + 4;
}

bool Calculadora::ultrapassaPesoMaximo(int pesoAtual, int pesoNovo, int pesoMaximo) {
    return pesoAtual + pesoNovo > pesoMaximo;
}

int Calculadora::limiarPeso(int pesoAtual, int pesoMaximo) {
    if (pesoMaximo <= 0 || pesoAtual <= 0) {
        return 0;
    }
    if (pesoAtual >= pesoMaximo) {
        return 100;
    }
    if (pesoAtual * 100 >= pesoMaximo * 75) {
        return 75;
    }
    if (pesoAtual * 100 >= pesoMaximo * 50) {
        return 50;
    }
    if (pesoAtual * 100 >= pesoMaximo * 25) {
        return 25;
    }
    return 0;
}

int Calculadora::somarDinheiro(int dinheiroAtual, int valorRecebido, int& dinheiroFinal) {
    const int limite = 9999;
    if (dinheiroAtual >= limite) {
        dinheiroFinal = limite;
        return valorRecebido;
    }
    int disponivel = limite - dinheiroAtual;
    if (valorRecebido > disponivel) {
        dinheiroFinal = limite;
        return valorRecebido - disponivel;
    }
    dinheiroFinal = dinheiroAtual + valorRecebido;
    return 0;
}

int Calculadora::contarCaracteresSemEspaco(const std::string& texto) {
    int total = 0;
    for (std::string::size_type i = 0; i < texto.size(); ++i) {
        if (texto[i] != ' ') {
            ++total;
        }
    }
    return total;
}
