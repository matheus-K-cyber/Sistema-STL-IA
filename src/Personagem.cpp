#include "Personagem.hpp"

Personagem::Personagem(const std::string& nome, int pesoMaximo, int dinheiro)
    : nome(nome), pesoMaximo(pesoMaximo), dinheiro(dinheiro) {
}

const std::string& Personagem::getNome() const {
    return nome;
}

int Personagem::getPesoMaximo() const {
    return pesoMaximo;
}

int Personagem::getDinheiro() const {
    return dinheiro;
}
