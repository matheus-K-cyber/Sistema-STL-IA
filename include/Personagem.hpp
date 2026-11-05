#ifndef PERSONAGEM_HPP
#define PERSONAGEM_HPP

#include <map>
#include <string>

#include "ItemStack.hpp"

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

    void limpar();

    const std::string& getNome() const;
    int getPesoMaximo() const;
    int getDinheiro() const;
    int getUltimoLimiar() const;

    int ganharDinheiro(int valor);
    bool gastarDinheiro(int valor);
    AlertaPeso atualizarPeso(int pesoAtual);

    ItemStack* getEquipado(SlotEquipamento slot) const;
    void trocarEquipado(SlotEquipamento slot, ItemStack* pilha);
    ItemStack* removerEquipado(SlotEquipamento slot);
    int quantidadeEquipados() const;

private:
    std::string nome;
    int pesoMaximo;
    int dinheiro;
    int ultimoLimiar;
    std::map<SlotEquipamento, ItemStack*> equipados;
};

#endif
