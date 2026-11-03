#include "Item.hpp"

#include <string>

#include "Calculadora.hpp"

Item::Item(const std::string& nomeItem, int pesoItem, Categoria categoriaItem,
           Raridade raridadeItem, Efeito efeitoItem, Subtipo subtipoItem)
    : nome(nomeItem), peso(pesoItem), categoria(categoriaItem),
      raridade(raridadeItem), efeito(efeitoItem), subtipo(subtipoItem) {
}

const std::string& Item::getNome() const {
    return nome;
}

int Item::getPeso() const {
    return peso;
}

Categoria Item::getCategoria() const {
    return categoria;
}

Raridade Item::getRaridade() const {
    return raridade;
}

Efeito Item::getEfeito() const {
    return efeito;
}

Subtipo Item::getSubtipo() const {
    return subtipo;
}

bool Item::isConsumivel() const {
    return categoria == CATEGORIA_COMIDAS || categoria == CATEGORIA_POCOES;
}

bool Item::isArma() const {
    return categoria == CATEGORIA_ARMAS;
}

bool Item::isArmadura() const {
    return subtipo == SUBTIPO_CAPACETE || subtipo == SUBTIPO_PEITORAL
        || subtipo == SUBTIPO_CALCA;
}

bool Item::isEquipavel() const {
    return isArma() || isArmadura();
}

bool Item::slotEquipamento(SlotEquipamento& slot) const {
    if (isArma()) {
        slot = SLOT_ARMA;
        return true;
    }
    if (subtipo == SUBTIPO_CAPACETE) {
        slot = SLOT_CAPACETE;
        return true;
    }
    if (subtipo == SUBTIPO_PEITORAL) {
        slot = SLOT_PEITORAL;
        return true;
    }
    if (subtipo == SUBTIPO_CALCA) {
        slot = SLOT_CALCA;
        return true;
    }
    return false;
}

int Item::limiteStack() const {
    return Calculadora::limiteStack(raridade, isEquipavel());
}

bool Item::mesmaIdentidade(const Item& outro) const {
    if (nome != outro.nome) {
        return false;
    }
    if (categoria != outro.categoria) {
        return false;
    }
    if (raridade != outro.raridade) {
        return false;
    }
    if (isConsumivel() && efeito != outro.efeito) {
        return false;
    }
    if (isEquipavel() && subtipo != outro.subtipo) {
        return false;
    }
    return true;
}

bool Item::operator==(const Item& outro) const {
    return mesmaIdentidade(outro);
}

bool Item::operator<(const Item& outro) const {
    std::string nomeNormalizado = normalizarTexto(nome);
    std::string outroNomeNormalizado = normalizarTexto(outro.nome);
    if (nomeNormalizado != outroNomeNormalizado) {
        return nomeNormalizado < outroNomeNormalizado;
    }
    if (categoria != outro.categoria) {
        return static_cast<int>(categoria) < static_cast<int>(outro.categoria);
    }
    if (raridade != outro.raridade) {
        return static_cast<int>(raridade) < static_cast<int>(outro.raridade);
    }
    if (efeito != outro.efeito) {
        return static_cast<int>(efeito) < static_cast<int>(outro.efeito);
    }
    return static_cast<int>(subtipo) < static_cast<int>(outro.subtipo);
}
