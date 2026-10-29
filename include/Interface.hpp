#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include <string>

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
    bool criarItemTeste();
    void mostrarAnalise(const ItemStack& pilha) const;
    void mostrarStatus(const Personagem& personagem, int capacidade) const;
    void mostrarMenu() const;
};

#endif
