#include "Acoes.hpp"

#include <vector>

ResultadoAcao::ResultadoAcao()
    : sucesso(false), motivo(FALHA_NENHUMA), efeito(EFEITO_NENHUM),
      quantidade(0), pesoRemovido(0) {
}

ResultadoAcao Acoes::consumir(Inventario& inventario, Personagem&,
                              const ItemStack* pilha) {
    ResultadoAcao resultado;

    if (pilha == 0 || !inventario.contem(pilha)) {
        resultado.motivo = FALHA_NAO_ENCONTRADO;
        return resultado;
    }
    if (pilha->isEquipado()) {
        resultado.motivo = FALHA_EQUIPADO;
        return resultado;
    }
    if (!pilha->identidade().isConsumivel()) {
        resultado.motivo = FALHA_NAO_CONSUMIVEL;
        return resultado;
    }

    std::vector<ItemStack*> stacks =
        inventario.stacksDaIdentidade(pilha->identidade());
    ItemStack* alvo = 0;
    for (std::vector<ItemStack*>::size_type i = 0; i < stacks.size(); ++i) {
        ItemStack* atual = stacks[i];
        if (atual->isEquipado() || atual->quantidade() <= 0) {
            continue;
        }
        if (alvo == 0 || atual->quantidade() < alvo->quantidade()) {
            alvo = atual;
        }
    }

    if (alvo == 0 || alvo->quantidade() <= 0) {
        resultado.motivo = FALHA_NAO_ENCONTRADO;
        return resultado;
    }

    resultado.efeito = alvo->unidadeMaisRecente().getEfeito();
    resultado.pesoRemovido = alvo->unidadeMaisRecente().getPeso();
    if (!inventario.removerUnidade(alvo)) {
        resultado.motivo = FALHA_NAO_ENCONTRADO;
        return resultado;
    }

    resultado.sucesso = true;
    resultado.quantidade = 1;
    inventario.removerSeVazio(alvo);
    return resultado;
}

ResultadoAcao Acoes::descartar(Inventario& inventario, Personagem&,
                               const ItemStack* pilha, int quantidade) {
    ResultadoAcao resultado;

    if (pilha == 0 || !inventario.contem(pilha)) {
        resultado.motivo = FALHA_NAO_ENCONTRADO;
        return resultado;
    }
    if (pilha->isEquipado()) {
        resultado.motivo = FALHA_EQUIPADO;
        return resultado;
    }
    if (quantidade <= 0) {
        resultado.motivo = FALHA_QUANTIDADE_INSUFICIENTE;
        return resultado;
    }

    std::vector<ItemStack*> stacks =
        inventario.stacksDaIdentidade(pilha->identidade());
    int total = 0;
    for (std::vector<ItemStack*>::size_type i = 0; i < stacks.size(); ++i) {
        if (!stacks[i]->isEquipado()) {
            total += stacks[i]->quantidade();
        }
    }
    if (quantidade > total) {
        resultado.motivo = FALHA_QUANTIDADE_INSUFICIENTE;
        return resultado;
    }

    int restante = quantidade;
    for (std::vector<ItemStack*>::size_type i = 0;
         i < stacks.size() && restante > 0; ++i) {
        ItemStack* atual = stacks[i];
        if (atual->isEquipado()) {
            continue;
        }
        while (restante > 0 && atual->quantidade() > 0) {
            resultado.pesoRemovido += atual->unidadeMaisRecente().getPeso();
            inventario.removerUnidade(atual);
            ++resultado.quantidade;
            --restante;
        }
        if (atual->quantidade() == 0) {
            inventario.removerSeVazio(atual);
        }
    }

    resultado.sucesso = (restante == 0);
    if (!resultado.sucesso) {
        resultado.motivo = FALHA_QUANTIDADE_INSUFICIENTE;
    }
    return resultado;
}

ResultadoAcao Acoes::descartarTudo(Inventario& inventario,
                                   Personagem& personagem,
                                   const ItemStack* pilha) {
    ResultadoAcao resultado;

    if (pilha == 0 || !inventario.contem(pilha)) {
        resultado.motivo = FALHA_NAO_ENCONTRADO;
        return resultado;
    }
    if (pilha->isEquipado()) {
        resultado.motivo = FALHA_EQUIPADO;
        return resultado;
    }

    std::vector<ItemStack*> stacks =
        inventario.stacksDaIdentidade(pilha->identidade());
    int total = 0;
    for (std::vector<ItemStack*>::size_type i = 0; i < stacks.size(); ++i) {
        if (!stacks[i]->isEquipado()) {
            total += stacks[i]->quantidade();
        }
    }
    return descartar(inventario, personagem, pilha, total);
}
