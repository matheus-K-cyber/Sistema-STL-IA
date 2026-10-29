#include "Tipos.hpp"

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
    }
    return "Desconhecido";
}
