#ifndef INVENTARIO_HPP
#define INVENTARIO_HPP

#include <list>
#include <map>
#include <string>
#include <vector>

#include "ItemStack.hpp"

enum MotivoAdicao {
    ADICAO_SEM_FALHA,
    ADICAO_LIMITE_PESO,
    ADICAO_INVENTARIO_CHEIO,
    ADICAO_LIMITE_ABA,
    ADICAO_LIMITE_PESO_E_INVENTARIO,
    ADICAO_LIMITE_PESO_E_ABA
};

struct ResultadoAdicao {
    int adicionados;
    int recusados;
    int pesoAtual;
    MotivoAdicao motivo;

    ResultadoAdicao();
};

class Inventario {
public:
    explicit Inventario(int capacidadeComum);

    void configurar(int capacidadeComum);

    ResultadoAdicao adicionar(const Item& item, int quantidade, int pesoMaximo);
    int pesoTotal() const;
    int getCapacidadeComum() const;
    int getSobressalentes() const;
    int getCapacidadeAba(Categoria categoria) const;
    int slotsComunsOcupados() const;
    int slotsEquipadosOcupados() const;
    bool temEspacoComum() const;
    bool temEspacoAba(Categoria categoria) const;
    const std::list<ItemStack>& listarGeral() const;
    const std::vector<ItemStack*>& listarAba(Categoria categoria) const;
    void ordenarAba(Categoria categoria);
    bool removerDaAba(ItemStack* pilha);
    bool adicionarNaAba(ItemStack* pilha);
    std::vector<const ItemStack*> pesquisar(const std::string& prefixo,
                                            Categoria categoria,
                                            bool naGeral) const;
    std::vector<ItemStack*> stacksDaIdentidade(const Item& item);
    bool contem(const ItemStack* pilha) const;
    bool removerUnidade(ItemStack* pilha);
    bool removerSeVazio(ItemStack* pilha);

private:
    ItemStack* encontrarAlvo(const Item& item);
    bool reservarSlotAba(Categoria categoria);
    bool temEspacoParaMais(const Item& item) const;

    int capacidadeComum;
    int sobressalentes;
    std::map<Categoria, std::vector<ItemStack*> > abas;
    std::map<Categoria, int> capacidadeAba;
    std::list<ItemStack> geral;
};

#endif
