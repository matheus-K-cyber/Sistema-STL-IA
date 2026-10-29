#ifndef TIPOS_HPP
#define TIPOS_HPP

#include <string>

enum Categoria {
    CATEGORIA_MINERIOS,
    CATEGORIA_COMIDAS,
    CATEGORIA_POCOES,
    CATEGORIA_ARMAS,
    CATEGORIA_UNICOS,
    CATEGORIA_RECURSOS_NATURAIS
};

enum Raridade {
    RARIDADE_SIMPLES,
    RARIDADE_RARO,
    RARIDADE_LENDARIO
};

enum Efeito {
    EFEITO_NENHUM,
    EFEITO_VIDA,
    EFEITO_MANA,
    EFEITO_VIDA_E_MANA
};

enum Subtipo {
    SUBTIPO_NENHUM,
    SUBTIPO_ESPADA,
    SUBTIPO_LANCA,
    SUBTIPO_ARMA_PESADA,
    SUBTIPO_ARCO_BESTA,
    SUBTIPO_CAPACETE,
    SUBTIPO_PEITORAL,
    SUBTIPO_CALCA
};

enum SlotEquipamento {
    SLOT_ARMA,
    SLOT_CAPACETE,
    SLOT_PEITORAL,
    SLOT_CALCA
};

std::string nomeCategoria(Categoria categoria);
std::string nomeRaridade(Raridade raridade);
std::string nomeEfeito(Efeito efeito);
std::string nomeSubtipo(Subtipo subtipo);
std::string nomeSlotEquipamento(SlotEquipamento slot);

#endif
