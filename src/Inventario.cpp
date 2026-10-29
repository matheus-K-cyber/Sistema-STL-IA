#include "Inventario.hpp"

#include "Calculadora.hpp"

ResultadoAdicao::ResultadoAdicao()
    : adicionados(0), recusados(0), pesoAtual(0), motivo(ADICAO_SEM_FALHA) {
}

ResultadoAdicao Inventario::adicionar(const Item& item, int quantidade,
                                      int pesoMaximo) {
    ResultadoAdicao resultado;
    resultado.pesoAtual = pesoTotal();

    if (quantidade <= 0) {
        return resultado;
    }

    int restante = quantidade;
    while (restante > 0) {
        if (Calculadora::ultrapassaPesoMaximo(resultado.pesoAtual,
                                              item.getPeso(), pesoMaximo)) {
            resultado.motivo = ADICAO_LIMITE_PESO;
            break;
        }

        ItemStack* alvo = 0;
        int menorQuantidade = 0;
        for (std::list<ItemStack>::iterator it = geral.begin();
             it != geral.end(); ++it) {
            if (!it->aceita(item)) {
                continue;
            }
            if (alvo == 0 || it->quantidade() < menorQuantidade) {
                alvo = &(*it);
                menorQuantidade = it->quantidade();
            }
        }

        if (alvo == 0) {
            geral.push_front(ItemStack());
            alvo = &geral.front();
        }

        int antes = resultado.adicionados;
        while (restante > 0 && alvo->aceita(item)
               && !Calculadora::ultrapassaPesoMaximo(
                      resultado.pesoAtual, item.getPeso(), pesoMaximo)) {
            alvo->adicionar(item);
            ++resultado.adicionados;
            resultado.pesoAtual += item.getPeso();
            --restante;
        }

        if (resultado.adicionados == antes) {
            resultado.motivo = ADICAO_LIMITE_PESO;
            break;
        }
    }

    resultado.recusados = restante;
    if (resultado.recusados == 0) {
        resultado.motivo = ADICAO_SEM_FALHA;
    }
    return resultado;
}

int Inventario::pesoTotal() const {
    int total = 0;
    for (std::list<ItemStack>::const_iterator it = geral.begin();
         it != geral.end(); ++it) {
        total += it->pesoTotal();
    }
    return total;
}

const std::list<ItemStack>& Inventario::listarGeral() const {
    return geral;
}
