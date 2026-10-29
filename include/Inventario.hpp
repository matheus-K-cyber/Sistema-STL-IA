#ifndef INVENTARIO_HPP
#define INVENTARIO_HPP

#include <list>

#include "ItemStack.hpp"

enum MotivoAdicao {
    ADICAO_SEM_FALHA,
    ADICAO_LIMITE_PESO
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
    ResultadoAdicao adicionar(const Item& item, int quantidade, int pesoMaximo);
    int pesoTotal() const;
    const std::list<ItemStack>& listarGeral() const;

private:
    std::list<ItemStack> geral;
};

#endif
