#include "Interface.hpp"

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <sstream>

#include "Calculadora.hpp"

namespace {

bool converterInteiro(const std::string& texto, int& valor) {
    std::stringstream entrada(texto);
    if (!(entrada >> valor)) {
        return false;
    }
    char resto;
    return !(entrada >> resto);
}

bool converterDecimal(const std::string& texto, double& valor) {
    std::string normalizado = texto;
    std::replace(normalizado.begin(), normalizado.end(), ',', '.');
    std::stringstream entrada(normalizado);
    if (!(entrada >> valor)) {
        return false;
    }
    char resto;
    return !(entrada >> resto);
}

}

bool Interface::lerNome(std::string& nome) {
    while (true) {
        std::cout << "Nome do personagem (maximo 10 caracteres): ";
        if (!std::getline(std::cin, nome)) {
            return false;
        }
        if (nome.empty()) {
            std::cout << "O nome nao pode ficar vazio.\n";
            continue;
        }
        if (nome.size() > 10) {
            std::cout << "O nome deve ter no maximo 10 caracteres.\n";
            continue;
        }
        return true;
    }
}

bool Interface::lerPesoMaximo(int& pesoMaximo) {
    while (true) {
        std::cout << "Peso maximo em kg (0.01 a 1000.00): ";
        std::string linha;
        if (!std::getline(std::cin, linha)) {
            return false;
        }
        double valor;
        if (!converterDecimal(linha, valor) || !(valor >= 0.0 && valor <= 1000.0)) {
            std::cout << "Peso invalido. Use um valor entre 0.01 e 1000.00.\n";
            continue;
        }
        int centesimos = Calculadora::quilosParaCentesimos(valor);
        if (centesimos < 1 || centesimos > 100000) {
            std::cout << "Peso invalido. Use um valor entre 0.01 e 1000.00.\n";
            continue;
        }
        pesoMaximo = centesimos;
        return true;
    }
}

bool Interface::lerInteiro(const std::string& rotulo, int minimo, int maximo, int& valor) {
    while (true) {
        std::cout << rotulo;
        std::string linha;
        if (!std::getline(std::cin, linha)) {
            return false;
        }
        int lido;
        if (!converterInteiro(linha, lido)) {
            std::cout << "Digite um numero inteiro valido.\n";
            continue;
        }
        if (lido < minimo || lido > maximo) {
            std::cout << "Valor fora do intervalo permitido (" << minimo
                      << " a " << maximo << ").\n";
            continue;
        }
        valor = lido;
        return true;
    }
}

bool Interface::lerDadosCriacao(std::string& nome, int& pesoMaximo,
                                int& capacidade, int& dinheiro) {
    std::cout << "=== Criacao do personagem ===\n";
    if (!lerNome(nome)) {
        return false;
    }
    if (!lerPesoMaximo(pesoMaximo)) {
        return false;
    }
    if (!lerInteiro("Capacidade comum (10 a 999): ", 10, 999, capacidade)) {
        return false;
    }
    if (!lerInteiro("Dinheiro inicial (0 a 9999): ", 0, 9999, dinheiro)) {
        return false;
    }
    return true;
}

void Interface::mostrarStatus(const Personagem& personagem, int capacidade) const {
    int capacidadeTotal = Calculadora::capacidadeGeral(capacidade);
    std::cout << "\n=== Status ===\n"
              << "Nome: " << personagem.getNome() << '\n'
              << "Peso maximo: " << std::fixed << std::setprecision(2)
              << Calculadora::centesimosParaQuilos(personagem.getPesoMaximo())
              << " kg\n"
              << "Capacidade: " << capacidadeTotal << " slots ("
              << capacidade << " comuns + 4 equipados)\n"
              << "Peso atual: 0.00 kg\n"
              << "Dinheiro: " << personagem.getDinheiro() << " moedas\n\n";
}

void Interface::mostrarMenu() const {
    std::cout << "=== Menu ===\n"
              << "1 - Status\n"
              << "2 - Dormir\n";
}

void Interface::executar() {
    std::string nome;
    int pesoMaximo;
    int capacidade;
    int dinheiro;

    if (!lerDadosCriacao(nome, pesoMaximo, capacidade, dinheiro)) {
        std::cout << "\nEntrada encerrada. Programa finalizado.\n";
        return;
    }

    Personagem personagem(nome, pesoMaximo, dinheiro);
    std::cout << "\nPersonagem criado com sucesso!\n";
    mostrarStatus(personagem, capacidade);

    while (true) {
        mostrarMenu();
        int opcao;
        if (!lerInteiro("Opcao: ", 1, 2, opcao)) {
            std::cout << "\nEntrada encerrada. Programa finalizado.\n";
            return;
        }

        if (opcao == 1) {
            mostrarStatus(personagem, capacidade);
        } else {
            std::cout << "\nO personagem foi dormir. Programa encerrado.\n";
            return;
        }
    }
}
