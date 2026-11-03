#ifndef ACOES_HPP
#define ACOES_HPP

#include "Inventario.hpp"
#include "Personagem.hpp"

enum MotivoFalha {
    FALHA_NENHUMA,
    FALHA_NAO_ENCONTRADO,
    FALHA_NAO_CONSUMIVEL,
    FALHA_EQUIPADO,
    FALHA_QUANTIDADE_INSUFICIENTE
};

struct ResultadoAcao {
    bool sucesso;
    MotivoFalha motivo;
    Efeito efeito;
    int quantidade;
    int pesoRemovido;

    ResultadoAcao();
};

class Acoes {
public:
    static ResultadoAcao consumir(Inventario& inventario,
                                  Personagem& personagem,
                                  const ItemStack* pilha);
    static ResultadoAcao descartar(Inventario& inventario,
                                   Personagem& personagem,
                                   const ItemStack* pilha,
                                   int quantidade);
    static ResultadoAcao descartarTudo(Inventario& inventario,
                                       Personagem& personagem,
                                       const ItemStack* pilha);

private:
    Acoes();
};

#endif
