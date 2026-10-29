#include "Personagem.hpp"

Personagem::Personagem(const std::string& nomePersonagem,
                       int pesoMaximoPersonagem, int dinheiroInicial)
    : nome(nomePersonagem), pesoMaximo(pesoMaximoPersonagem),
      dinheiro(dinheiroInicial) {
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
