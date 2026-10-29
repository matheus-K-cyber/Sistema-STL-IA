#ifndef ITEMSTACK_HPP
#define ITEMSTACK_HPP

#include <vector>

#include "Item.hpp"

class ItemStack {
public:
    ItemStack();

    int quantidade() const;
    int pesoTotal() const;
    const Item& identidade() const;
    const Item& unidadeMaisRecente() const;
    int limite() const;

    bool aceita(const Item& item) const;
    bool adicionar(const Item& item);
    bool removerUltima();

    bool isEquipado() const;
    void setEquipado(bool valor);

    bool operator<(const ItemStack& outro) const;

private:
    std::vector<Item> unidades;
    bool equipado;
};

#endif
