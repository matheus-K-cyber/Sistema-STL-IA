#ifndef INVENTARIO_HPP
#define INVENTARIO_HPP

#include <list>

#include "ItemStack.hpp"

enum MotivoAdicao {
    ADICAO_SEM_FALHA,
    ADICAO_LIMITE_PESO,
    ADICAO_INVENTARIO_CHEIO,
    ADICAO_LIMITE_PESO_E_INVENTARIO
};

struct ResultadoAdicao {
    int adicionados;
    int recusados;
    int pesoAtual;
    MotivoAdicao motivo;

    ResultadoAdicao();
};

class Inventario {
public:
    explicit Inventario(int capacidadeComum);

    ResultadoAdicao adicionar(const Item& item, int quantidade, int pesoMaximo);
    int pesoTotal() const;
    int slotsComunsOcupados() const;
    int slotsExtrasOcupados() const;
    const std::list<ItemStack>& listarGeral() const;

private:
    ItemStack* encontrarAlvo(const Item& item);
    bool podeCriarNovoStack() const;
    bool temEspacoParaMais(const Item& item) const;

    int capacidadeComum;
    std::list<ItemStack> geral;
};

#endif
