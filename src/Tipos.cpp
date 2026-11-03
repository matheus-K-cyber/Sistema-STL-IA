#include "Tipos.hpp"

std::string normalizarTexto(const std::string& texto) {
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

std::string nomeCategoria(Categoria categoria) {
    switch (categoria) {
    case CATEGORIA_MINERIOS:
        return "Minerios";
    case CATEGORIA_COMIDAS:
        return "Comidas";
    case CATEGORIA_POCOES:
        return "Pocoes";
    case CATEGORIA_ARMAS:
        return "Armas";
    case CATEGORIA_UNICOS:
        return "Unicos";
    case CATEGORIA_RECURSOS_NATURAIS:
        return "Recursos Naturais";
    default:
        break;
    }
    return "Desconhecida";
}

std::string nomeRaridade(Raridade raridade) {
    switch (raridade) {
    case RARIDADE_SIMPLES:
        return "Simples";
    case RARIDADE_RARO:
        return "Raro";
    case RARIDADE_LENDARIO:
        return "Lendario";
    default:
        break;
    }
    return "Desconhecida";
}

std::string nomeEfeito(Efeito efeito) {
    switch (efeito) {
    case EFEITO_NENHUM:
        return "Nenhum";
    case EFEITO_VIDA:
        return "Vida";
    case EFEITO_MANA:
        return "Mana";
    case EFEITO_VIDA_E_MANA:
        return "Vida e Mana";
    default:
        break;
    }
    return "Desconhecido";
}

std::string nomeSubtipo(Subtipo subtipo) {
    switch (subtipo) {
    case SUBTIPO_NENHUM:
        return "Nenhum";
    case SUBTIPO_ESPADA:
        return "Espada";
    case SUBTIPO_LANCA:
        return "Lanca";
    case SUBTIPO_ARMA_PESADA:
        return "Arma Pesada";
    case SUBTIPO_ARCO_BESTA:
        return "Arco ou Besta";
    case SUBTIPO_CAPACETE:
        return "Capacete";
    case SUBTIPO_PEITORAL:
        return "Peitoral";
    case SUBTIPO_CALCA:
        return "Calca";
    default:
        break;
    }
    return "Desconhecido";
}

std::string nomeSlotEquipamento(SlotEquipamento slot) {
    switch (slot) {
    case SLOT_ARMA:
        return "Arma";
    case SLOT_CAPACETE:
        return "Capacete";
    case SLOT_PEITORAL:
        return "Peitoral";
    case SLOT_CALCA:
        return "Calca";
    default:
        break;
    }
    return "Desconhecido";
}
