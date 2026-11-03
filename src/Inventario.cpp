#include "Inventario.hpp"

#include "Calculadora.hpp"

ResultadoAdicao::ResultadoAdicao()
    : adicionados(0), recusados(0), pesoAtual(0), motivo(ADICAO_SEM_FALHA) {
}

Inventario::Inventario(int capacidadeComum)
    : capacidadeComum(capacidadeComum), geral() {
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
        ItemStack* alvo = encontrarAlvo(item);

        if (alvo == 0) {
            if (!podeCriarNovoStack()) {
                break;
            }
            if (Calculadora::ultrapassaPesoMaximo(resultado.pesoAtual,
                                                  item.getPeso(), pesoMaximo)) {
                break;
            }

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
            break;
        }
    }

    resultado.recusados = restante;
    if (resultado.recusados == 0) {
        resultado.motivo = ADICAO_SEM_FALHA;
    } else {
        bool limitePeso = Calculadora::ultrapassaPesoMaximo(
            resultado.pesoAtual, item.getPeso(), pesoMaximo);
        bool inventarioCheio = !temEspacoParaMais(item);

        if (limitePeso && inventarioCheio) {
            resultado.motivo = ADICAO_LIMITE_PESO_E_INVENTARIO;
        } else if (inventarioCheio) {
            resultado.motivo = ADICAO_INVENTARIO_CHEIO;
        } else {
            resultado.motivo = ADICAO_LIMITE_PESO;
        }
    }
    return resultado;
}

ItemStack* Inventario::encontrarAlvo(const Item& item) {
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
    return alvo;
}

bool Inventario::podeCriarNovoStack() const {
    return slotsComunsOcupados() < capacidadeComum;
}

bool Inventario::temEspacoParaMais(const Item& item) const {
    for (std::list<ItemStack>::const_iterator it = geral.begin();
         it != geral.end(); ++it) {
        if (it->aceita(item)) {
            return true;
        }
    }
    return podeCriarNovoStack();
}

int Inventario::pesoTotal() const {
    int total = 0;
    for (std::list<ItemStack>::const_iterator it = geral.begin();
         it != geral.end(); ++it) {
        total += it->pesoTotal();
    }
    return total;
}

int Inventario::slotsComunsOcupados() const {
    int total = 0;
    for (std::list<ItemStack>::const_iterator it = geral.begin();
         it != geral.end(); ++it) {
        if (!it->isEquipado()) {
            ++total;
        }
    }
    return total;
}

int Inventario::slotsExtrasOcupados() const {
    int total = 0;
    for (std::list<ItemStack>::const_iterator it = geral.begin();
         it != geral.end(); ++it) {
        if (it->isEquipado()) {
            ++total;
        }
    }
    return total;
}

const std::list<ItemStack>& Inventario::listarGeral() const {
    return geral;
}
