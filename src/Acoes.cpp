#include "Acoes.hpp"

#include <vector>

namespace {

ItemStack* localizarPilha(Inventario& inventario, const ItemStack* alvo) {
    std::vector<ItemStack*> pilhas =
        inventario.stacksDaIdentidade(alvo->identidade());
    for (std::vector<ItemStack*>::size_type i = 0; i < pilhas.size(); ++i) {
        if (pilhas[i] == alvo) {
            return pilhas[i];
        }
    }
    return 0;
}

}

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

ResultadoAcao Acoes::equipar(Inventario& inventario, Personagem& personagem,
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
    if (pilha->quantidade() != 1) {
        resultado.motivo = FALHA_QUANTIDADE_INSUFICIENTE;
        return resultado;
    }

    SlotEquipamento slot;
    if (!pilha->identidade().slotEquipamento(slot)) {
        resultado.motivo = FALHA_NAO_EQUIPAVEL;
        return resultado;
    }

    ItemStack* novo = localizarPilha(inventario, pilha);
    if (novo == 0) {
        resultado.motivo = FALHA_NAO_ENCONTRADO;
        return resultado;
    }

    ItemStack* antigo = personagem.getEquipado(slot);
    if (!inventario.removerDaAba(novo)) {
        resultado.motivo = FALHA_NAO_ENCONTRADO;
        return resultado;
    }

    novo->setEquipado(true);
    personagem.trocarEquipado(slot, novo);

    if (antigo != 0) {
        antigo->setEquipado(false);
        if (!inventario.adicionarNaAba(antigo)) {
            personagem.trocarEquipado(slot, antigo);
            antigo->setEquipado(true);
            novo->setEquipado(false);
            inventario.adicionarNaAba(novo);
            resultado.motivo = FALHA_SEM_ESPACO_ABA;
            return resultado;
        }
    }

    resultado.sucesso = true;
    resultado.quantidade = 1;
    return resultado;
}

ResultadoAcao Acoes::desequipar(Inventario& inventario,
                                Personagem& personagem,
                                SlotEquipamento slot) {
    ResultadoAcao resultado;

    ItemStack* pilha = personagem.getEquipado(slot);
    if (pilha == 0 || !inventario.contem(pilha)) {
        resultado.motivo = FALHA_NAO_ENCONTRADO;
        return resultado;
    }

    Categoria categoria = pilha->identidade().getCategoria();
    if (!inventario.temEspacoComum()) {
        resultado.motivo = FALHA_SEM_ESPACO_GERAL;
        return resultado;
    }
    if (!inventario.temEspacoAba(categoria)) {
        resultado.motivo = FALHA_SEM_ESPACO_ABA;
        return resultado;
    }
    if (!inventario.adicionarNaAba(pilha)) {
        resultado.motivo = FALHA_SEM_ESPACO_ABA;
        return resultado;
    }

    pilha->setEquipado(false);
    personagem.removerEquipado(slot);
    resultado.sucesso = true;
    resultado.quantidade = 1;
    return resultado;
}
