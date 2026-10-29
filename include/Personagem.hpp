#ifndef PERSONAGEM_HPP
#define PERSONAGEM_HPP

#include <string>

class Personagem {
public:
    Personagem(const std::string& nomePersonagem, int pesoMaximoPersonagem,
               int dinheiroInicial);

    const std::string& getNome() const;
    int getPesoMaximo() const;
    int getDinheiro() const;

private:
    std::string nome;
    int pesoMaximo;
    int dinheiro;
};

#endif
