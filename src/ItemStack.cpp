#include "ItemStack.hpp"

ItemStack::ItemStack() : unidades(), equipado(false) {
}

int ItemStack::quantidade() const {
    return static_cast<int>(unidades.size());
}

int ItemStack::pesoTotal() const {
    int total = 0;
    for (std::vector<Item>::size_type i = 0; i < unidades.size(); ++i) {
        total += unidades[i].getPeso();
    }
    return total;
}

const Item& ItemStack::identidade() const {
    return unidades.front();
}

const Item& ItemStack::unidadeMaisRecente() const {
    return unidades.back();
}

int ItemStack::limite() const {
    if (unidades.empty()) {
        return 0;
    }
    return identidade().limiteStack();
}

bool ItemStack::aceita(const Item& item) const {
    if (equipado) {
        return false;
    }
    if (unidades.empty()) {
        return true;
    }
    return identidade().mesmaIdentidade(item) && quantidade() < limite();
}

bool ItemStack::adicionar(const Item& item) {
    if (!aceita(item)) {
        return false;
    }
    unidades.push_back(item);
    return true;
}

bool ItemStack::removerUltima() {
    if (unidades.empty()) {
        return false;
    }
    unidades.pop_back();
    return true;
}

bool ItemStack::isEquipado() const {
    return equipado;
}

void ItemStack::setEquipado(bool valor) {
    equipado = valor;
}

bool ItemStack::operator<(const ItemStack& outro) const {
    if (unidades.empty() && outro.unidades.empty()) {
        return false;
    }
    if (unidades.empty()) {
        return true;
    }
    if (outro.unidades.empty()) {
        return false;
    }
    return identidade() < outro.identidade();
}
