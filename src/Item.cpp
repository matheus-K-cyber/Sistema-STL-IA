#include "Item.hpp"

#include <string>

#include "Calculadora.hpp"

namespace {

std::string normalizarNome(const std::string& texto) {
    std::string resultado;
    resultado.reserve(texto.size());
    std::string::size_type i = 0;
    while (i < texto.size()) {
        unsigned char atual = static_cast<unsigned char>(texto[i]);
        if (atual < 0x80) {
            if (atual >= 'A' && atual <= 'Z') {
                resultado += static_cast<char>(atual - 'A' + 'a');
            } else {
                resultado += static_cast<char>(atual);
            }
            ++i;
            continue;
        }
        if (atual == 0xC3 && i + 1 < texto.size()) {
            unsigned char proximo = static_cast<unsigned char>(texto[i + 1]);
            char base = 0;
            switch (proximo) {
            case 0xA1:
            case 0xA0:
            case 0xA2:
            case 0xA3:
            case 0x81:
            case 0x80:
            case 0x82:
            case 0x83:
                base = 'a';
                break;
            case 0xA9:
            case 0xAA:
            case 0x89:
            case 0x8A:
                base = 'e';
                break;
            case 0xAD:
            case 0x8D:
                base = 'i';
                break;
            case 0xB3:
            case 0xB4:
            case 0xB5:
            case 0x93:
            case 0x94:
            case 0x95:
                base = 'o';
                break;
            case 0xBA:
            case 0x9A:
                base = 'u';
                break;
            case 0xA7:
            case 0x87:
                base = 'c';
                break;
            default:
                break;
            }
            if (base != 0) {
                resultado += base;
                i += 2;
                continue;
            }
        }
        resultado += static_cast<char>(atual);
        ++i;
    }
    return resultado;
}

}

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
    std::string nomeNormalizado = normalizarNome(nome);
    std::string outroNomeNormalizado = normalizarNome(outro.nome);
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
