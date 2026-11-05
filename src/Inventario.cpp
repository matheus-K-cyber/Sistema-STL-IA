#include "Inventario.hpp"

#include <algorithm>

#include "Calculadora.hpp"

namespace {

bool compararPilhas(const ItemStack* a, const ItemStack* b) {
    return *a < *b;
}

}

ResultadoAdicao::ResultadoAdicao()
    : adicionados(0), recusados(0), pesoAtual(0), motivo(ADICAO_SEM_FALHA) {
}

Inventario::Inventario(int capacidadeComum)
    : capacidadeComum(0), sobressalentes(0), abas(), capacidadeAba(), geral() {
    configurar(capacidadeComum);
}

void Inventario::configurar(int capacidadeComum) {
    this->capacidadeComum = capacidadeComum;
    sobressalentes = capacidadeComum % 6;

    abas.clear();
    capacidadeAba.clear();

    int slotsPorAba = capacidadeComum / 6;
    for (int i = 0; i < 6; ++i) {
        Categoria categoria = static_cast<Categoria>(i);
        abas[categoria] = std::vector<ItemStack*>();
        capacidadeAba[categoria] = slotsPorAba;
    }
}

void Inventario::limpar() {
    abas.clear();
    capacidadeAba.clear();
    geral.clear();
    capacidadeComum = 0;
    sobressalentes = 0;
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
        Categoria categoria = item.getCategoria();
        bool criouStack = false;

        if (alvo == 0) {
            if (Calculadora::ultrapassaPesoMaximo(resultado.pesoAtual,
                                                  item.getPeso(), pesoMaximo)) {
                break;
            }
            if (!temEspacoComum()) {
                break;
            }
            if (!reservarSlotAba(categoria)) {
                break;
            }

            geral.push_front(ItemStack());
            alvo = &geral.front();
            abas[categoria].push_back(alvo);
            criouStack = true;
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

        if (criouStack) {
            ordenarAba(categoria);
        }
        if (resultado.adicionados == antes) {
            break;
        }
    }

    resultado.recusados = restante;
    if (resultado.recusados == 0) {
        resultado.motivo = ADICAO_SEM_FALHA;
        return resultado;
    }

    bool limitePeso = Calculadora::ultrapassaPesoMaximo(
        resultado.pesoAtual, item.getPeso(), pesoMaximo);
    bool semEspaco = !temEspacoParaMais(item);

    if (!semEspaco) {
        resultado.motivo = ADICAO_LIMITE_PESO;
    } else if (!temEspacoComum()) {
        resultado.motivo = limitePeso ? ADICAO_LIMITE_PESO_E_INVENTARIO
                                      : ADICAO_INVENTARIO_CHEIO;
    } else {
        resultado.motivo = limitePeso ? ADICAO_LIMITE_PESO_E_ABA
                                      : ADICAO_LIMITE_ABA;
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

bool Inventario::reservarSlotAba(Categoria categoria) {
    std::map<Categoria, std::vector<ItemStack*> >::iterator aba =
        abas.find(categoria);
    std::map<Categoria, int>::iterator capacidade =
        capacidadeAba.find(categoria);

    if (aba == abas.end() || capacidade == capacidadeAba.end()) {
        return false;
    }
    if (static_cast<int>(aba->second.size()) < capacidade->second) {
        return true;
    }
    if (sobressalentes <= 0) {
        return false;
    }

    ++capacidade->second;
    --sobressalentes;
    return true;
}

bool Inventario::temEspacoParaMais(const Item& item) const {
    for (std::list<ItemStack>::const_iterator it = geral.begin();
         it != geral.end(); ++it) {
        if (it->aceita(item)) {
            return true;
        }
    }
    return temEspacoComum() && temEspacoAba(item.getCategoria());
}

int Inventario::pesoTotal() const {
    int total = 0;
    for (std::list<ItemStack>::const_iterator it = geral.begin();
         it != geral.end(); ++it) {
        total += it->pesoTotal();
    }
    return total;
}

int Inventario::getCapacidadeComum() const {
    return capacidadeComum;
}

int Inventario::getSobressalentes() const {
    return sobressalentes;
}

int Inventario::getCapacidadeAba(Categoria categoria) const {
    std::map<Categoria, int>::const_iterator it = capacidadeAba.find(categoria);
    if (it == capacidadeAba.end()) {
        return 0;
    }
    return it->second;
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

int Inventario::slotsEquipadosOcupados() const {
    int total = 0;
    for (std::list<ItemStack>::const_iterator it = geral.begin();
         it != geral.end(); ++it) {
        if (it->isEquipado()) {
            ++total;
        }
    }
    return total;
}

bool Inventario::temEspacoComum() const {
    return slotsComunsOcupados() < capacidadeComum;
}

bool Inventario::temEspacoAba(Categoria categoria) const {
    std::map<Categoria, std::vector<ItemStack*> >::const_iterator aba =
        abas.find(categoria);
    std::map<Categoria, int>::const_iterator capacidade =
        capacidadeAba.find(categoria);

    if (aba == abas.end() || capacidade == capacidadeAba.end()) {
        return false;
    }
    if (static_cast<int>(aba->second.size()) < capacidade->second) {
        return true;
    }
    return sobressalentes > 0;
}

const std::list<ItemStack>& Inventario::listarGeral() const {
    return geral;
}

const std::vector<ItemStack*>& Inventario::listarAba(
    Categoria categoria) const {
    static const std::vector<ItemStack*> abaVazia;

    std::map<Categoria, std::vector<ItemStack*> >::const_iterator it =
        abas.find(categoria);
    if (it == abas.end()) {
        return abaVazia;
    }
    return it->second;
}

void Inventario::ordenarAba(Categoria categoria) {
    std::map<Categoria, std::vector<ItemStack*> >::iterator it =
        abas.find(categoria);
    if (it != abas.end()) {
        std::sort(it->second.begin(), it->second.end(), compararPilhas);
    }
}

bool Inventario::removerDaAba(ItemStack* pilha) {
    if (pilha == 0) {
        return false;
    }

    Categoria categoria = pilha->identidade().getCategoria();
    std::map<Categoria, std::vector<ItemStack*> >::iterator aba =
        abas.find(categoria);
    if (aba == abas.end()) {
        return false;
    }

    std::vector<ItemStack*>::iterator posicao =
        std::find(aba->second.begin(), aba->second.end(), pilha);
    if (posicao == aba->second.end()) {
        return false;
    }
    aba->second.erase(posicao);
    return true;
}

bool Inventario::adicionarNaAba(ItemStack* pilha) {
    if (pilha == 0 || pilha->quantidade() <= 0) {
        return false;
    }

    Categoria categoria = pilha->identidade().getCategoria();
    std::map<Categoria, std::vector<ItemStack*> >::iterator aba =
        abas.find(categoria);
    if (aba == abas.end()) {
        return false;
    }
    if (std::find(aba->second.begin(), aba->second.end(), pilha)
        != aba->second.end()) {
        return false;
    }
    if (!reservarSlotAba(categoria)) {
        return false;
    }

    aba->second.push_back(pilha);
    ordenarAba(categoria);
    return true;
}

std::vector<const ItemStack*> Inventario::pesquisar(
    const std::string& prefixo, Categoria categoria, bool naGeral) const {
    std::vector<const ItemStack*> encontrados;
    std::string textoNormalizado = normalizarTexto(prefixo);
    if (textoNormalizado.empty()) {
        return encontrados;
    }

    if (naGeral) {
        for (std::list<ItemStack>::const_iterator it = geral.begin();
             it != geral.end(); ++it) {
            if (it->quantidade() == 0) {
                continue;
            }
            std::string nomeNormalizado =
                normalizarTexto(it->identidade().getNome());
            if (nomeNormalizado.compare(0, textoNormalizado.size(),
                                        textoNormalizado) == 0) {
                encontrados.push_back(&(*it));
            }
        }
        return encontrados;
    }

    std::map<Categoria, std::vector<ItemStack*> >::const_iterator aba =
        abas.find(categoria);
    if (aba == abas.end()) {
        return encontrados;
    }

    for (std::vector<ItemStack*>::const_iterator it = aba->second.begin();
         it != aba->second.end(); ++it) {
        const ItemStack* pilha = *it;
        if (pilha == 0 || pilha->quantidade() == 0 || pilha->isEquipado()) {
            continue;
        }
        std::string nomeNormalizado =
            normalizarTexto(pilha->identidade().getNome());
        if (nomeNormalizado.compare(0, textoNormalizado.size(),
                                    textoNormalizado) == 0) {
            encontrados.push_back(pilha);
        }
    }
    return encontrados;
}

std::vector<ItemStack*> Inventario::stacksDaIdentidade(const Item& item) {
    std::vector<ItemStack*> encontrados;
    for (std::list<ItemStack>::iterator it = geral.begin();
         it != geral.end(); ++it) {
        if (it->quantidade() > 0
            && it->identidade().mesmaIdentidade(item)) {
            encontrados.push_back(&(*it));
        }
    }
    return encontrados;
}

bool Inventario::contem(const ItemStack* pilha) const {
    if (pilha == 0) {
        return false;
    }
    for (std::list<ItemStack>::const_iterator it = geral.begin();
         it != geral.end(); ++it) {
        if (&(*it) == pilha) {
            return true;
        }
    }
    return false;
}

bool Inventario::removerUnidade(ItemStack* pilha) {
    if (!contem(pilha)) {
        return false;
    }
    return pilha->removerUltima();
}

bool Inventario::removerSeVazio(ItemStack* pilha) {
    if (pilha == 0 || pilha->quantidade() > 0) {
        return false;
    }

    for (std::map<Categoria, std::vector<ItemStack*> >::iterator aba =
             abas.begin();
         aba != abas.end(); ++aba) {
        std::vector<ItemStack*>::iterator posicao =
            std::find(aba->second.begin(), aba->second.end(), pilha);
        if (posicao != aba->second.end()) {
            aba->second.erase(posicao);
            break;
        }
    }

    for (std::list<ItemStack>::iterator it = geral.begin();
         it != geral.end(); ++it) {
        if (&(*it) == pilha) {
            geral.erase(it);
            return true;
        }
    }
    return false;
}
