#include "Personagem.hpp"

#include "Calculadora.hpp"

AlertaPeso::AlertaPeso()
    : mudou(false), aumento(false), limiar(0), cansaco(false) {
}

Personagem::Personagem(const std::string& nomePersonagem,
                       int pesoMaximoPersonagem, int dinheiroInicial)
    : nome(nomePersonagem), pesoMaximo(pesoMaximoPersonagem),
      dinheiro(dinheiroInicial), ultimoLimiar(0) {
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

int Personagem::getUltimoLimiar() const {
    return ultimoLimiar;
}

int Personagem::ganharDinheiro(int valor) {
    if (valor <= 0) {
        return 0;
    }
    int dinheiroFinal = dinheiro;
    int excedente = Calculadora::somarDinheiro(dinheiro, valor, dinheiroFinal);
    dinheiro = dinheiroFinal;
    return excedente;
}

bool Personagem::gastarDinheiro(int valor) {
    if (valor <= 0) {
        return false;
    }
    int dinheiroFinal = dinheiro;
    bool sucesso = Calculadora::gastarDinheiro(dinheiro, valor, dinheiroFinal);
    dinheiro = dinheiroFinal;
    return sucesso;
}

AlertaPeso Personagem::atualizarPeso(int pesoAtual) {
    AlertaPeso alerta;
    int novoLimiar = Calculadora::limiarPeso(pesoAtual, pesoMaximo);
    alerta.limiar = novoLimiar;

    if (novoLimiar == ultimoLimiar) {
        return alerta;
    }

    alerta.mudou = true;
    alerta.aumento = novoLimiar > ultimoLimiar;
    if (alerta.aumento) {
        alerta.limiar =
            Calculadora::maiorLimiarAlcancado(ultimoLimiar, novoLimiar);
        alerta.cansaco = novoLimiar >= 100;
    } else {
        alerta.limiar =
            Calculadora::menorLimiarUltrapassado(novoLimiar, ultimoLimiar);
    }

    ultimoLimiar = novoLimiar;
    return alerta;
}
