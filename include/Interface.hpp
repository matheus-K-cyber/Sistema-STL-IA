#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include <string>

#include "Personagem.hpp"

class Interface {
public:
    void executar();

private:
    bool lerNome(std::string& nome);
    bool lerPesoMaximo(int& pesoMaximo);
    bool lerInteiro(const std::string& rotulo, int minimo, int maximo, int& valor);
    bool lerDadosCriacao(std::string& nome, int& pesoMaximo, int& capacidade, int& dinheiro);
    void mostrarStatus(const Personagem& personagem, int capacidade) const;
    void mostrarMenu() const;
};

#endif
