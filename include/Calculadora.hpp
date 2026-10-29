#ifndef CALCULADORA_HPP
#define CALCULADORA_HPP

#include <string>

#include "Tipos.hpp"

class Calculadora {
public:
    static int quilosParaCentesimos(double quilos);
    static double centesimosParaQuilos(int centesimos);
    static int capacidadeGeral(int slotsComuns);
    static int limiteStack(Raridade raridade, bool equipavel);

    static bool ultrapassaPesoMaximo(int pesoAtual, int pesoNovo, int pesoMaximo);
    static int limiarPeso(int pesoAtual, int pesoMaximo);
    static int somarDinheiro(int dinheiroAtual, int valorRecebido, int& dinheiroFinal);
    static int contarCaracteresSemEspaco(const std::string& texto);

private:
    Calculadora();
};

#endif
