#ifndef PERSONAGEM_HPP
#define PERSONAGEM_HPP

#include <string>

struct AlertaPeso {
    bool mudou;
    bool aumento;
    int limiar;
    bool cansaco;

    AlertaPeso();
};

class Personagem {
public:
    Personagem(const std::string& nomePersonagem, int pesoMaximoPersonagem,
               int dinheiroInicial);

    const std::string& getNome() const;
    int getPesoMaximo() const;
    int getDinheiro() const;
    int getUltimoLimiar() const;

    int ganharDinheiro(int valor);
    bool gastarDinheiro(int valor);
    AlertaPeso atualizarPeso(int pesoAtual);

private:
    std::string nome;
    int pesoMaximo;
    int dinheiro;
    int ultimoLimiar;
};

#endif
