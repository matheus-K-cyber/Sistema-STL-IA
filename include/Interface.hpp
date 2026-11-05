#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include <string>
#include <vector>

#include "Inventario.hpp"
#include "ItemStack.hpp"
#include "Personagem.hpp"

class Interface {
public:
    void executar();

private:
    bool lerNome(std::string& nome);
    bool lerPeso(const std::string& rotulo, int& peso);
    bool lerPesoMaximo(int& pesoMaximo);
    bool lerInteiro(const std::string& rotulo, int minimo, int maximo, int& valor);
    bool lerDadosCriacao(std::string& nome, int& pesoMaximo, int& capacidade, int& dinheiro);
    bool lerNomeItem(std::string& nome);
    bool lerCategoria(Categoria& categoria);
    bool lerRaridade(Raridade& raridade);
    bool lerEfeito(Efeito& efeito);
    bool lerSubtipo(Categoria categoria, Subtipo& subtipo);
    bool lerDadosItem(std::string& nome, int& peso, Categoria& categoria,
                      Raridade& raridade, Efeito& efeito, Subtipo& subtipo,
                      int& quantidade);
    bool pegarItem(Personagem& personagem, Inventario& inventario,
                   bool& inventarioAberto);
    bool lerItensIniciais(Inventario& inventario, Personagem& personagem);
    bool ganharDinheiro(Personagem& personagem);
    bool gastarDinheiro(Personagem& personagem);
    void mostrarAnalise(const ItemStack& pilha) const;
    void mostrarInventarioGeral(const Inventario& inventario) const;
    void mostrarAba(const Inventario& inventario, Categoria categoria) const;
    void mostrarResultadoAdicao(const ResultadoAdicao& resultado,
                                int quantidade, Categoria categoria) const;
    void alternarInventario(const Inventario& inventario,
                            bool& inventarioAberto) const;
    bool selecionarAba(const Inventario& inventario, int& abaAtual);
    bool pesquisarItem(const Inventario& inventario, int abaAtual);
    bool analisarItem(const Inventario& inventario, int abaAtual);
    bool escolherPilha(const Inventario& inventario, int abaAtual,
                       const std::string& acao,
                       const ItemStack*& escolhida);
    bool confirmar(const std::string& pergunta, bool& confirmado);
    bool consumirItem(Inventario& inventario, Personagem& personagem,
                      int abaAtual);
    bool descartarItem(Inventario& inventario, Personagem& personagem,
                       int abaAtual);
    bool equiparItem(Inventario& inventario, Personagem& personagem,
                     int abaAtual);
    bool desequiparItem(Inventario& inventario, Personagem& personagem);
    bool perguntarEquiparInicial(bool& equipar);
    void mostrarResultadosPesquisa(
        const std::vector<const ItemStack*>& resultados, int abaAtual,
        const std::string& texto) const;
    void mostrarSugestaoGeral(const Inventario& inventario, int abaAtual,
                              const std::string& texto) const;
    void mostrarStatus(const Personagem& personagem,
                       const Inventario& inventario) const;
    void mostrarAlertaPeso(const AlertaPeso& alerta) const;
    void limparDados(Personagem& personagem, Inventario& inventario) const;
    void mostrarMenu(bool inventarioAberto, int abaAtual) const;
};

#endif
