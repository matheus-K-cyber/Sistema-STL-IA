#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>

#include "Tipos.hpp"

class Item {
public:
    Item(const std::string& nomeItem, int pesoItem, Categoria categoriaItem,
         Raridade raridadeItem, Efeito efeitoItem, Subtipo subtipoItem);

    const std::string& getNome() const;
    int getPeso() const;
    Categoria getCategoria() const;
    Raridade getRaridade() const;
    Efeito getEfeito() const;
    Subtipo getSubtipo() const;

    bool isConsumivel() const;
    bool isArma() const;
    bool isArmadura() const;
    bool isEquipavel() const;
    bool slotEquipamento(SlotEquipamento& slot) const;

    int limiteStack() const;
    bool mesmaIdentidade(const Item& outro) const;
    bool operator==(const Item& outro) const;
    bool operator<(const Item& outro) const;

private:
    std::string nome;
    int peso;
    Categoria categoria;
    Raridade raridade;
    Efeito efeito;
    Subtipo subtipo;
};

#endif
