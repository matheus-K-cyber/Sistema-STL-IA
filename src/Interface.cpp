#include "Interface.hpp"

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <sstream>

#include "Calculadora.hpp"

namespace {

bool converterInteiro(const std::string& texto, int& valor) {
    std::stringstream entrada(texto);
    if (!(entrada >> valor)) {
        return false;
    }
    char resto;
    return !(entrada >> resto);
}

bool converterDecimal(const std::string& texto, double& valor) {
    std::string normalizado = texto;
    std::replace(normalizado.begin(), normalizado.end(), ',', '.');
    std::stringstream entrada(normalizado);
    if (!(entrada >> valor)) {
        return false;
    }
    char resto;
    return !(entrada >> resto);
}

}

bool Interface::lerNome(std::string& nome) {
    while (true) {
        std::cout << "Nome do personagem (maximo 10 caracteres): ";
        if (!std::getline(std::cin, nome)) {
            return false;
        }
        if (nome.empty()) {
            std::cout << "O nome nao pode ficar vazio.\n";
            continue;
        }
        if (nome.size() > 10) {
            std::cout << "O nome deve ter no maximo 10 caracteres.\n";
            continue;
        }
        return true;
    }
}

bool Interface::lerPeso(const std::string& rotulo, int& peso) {
    while (true) {
        std::cout << rotulo;
        std::string linha;
        if (!std::getline(std::cin, linha)) {
            return false;
        }
        double valor;
        if (!converterDecimal(linha, valor) || !(valor >= 0.0 && valor <= 1000.0)) {
            std::cout << "Peso invalido. Use um valor entre 0.01 e 1000.00.\n";
            continue;
        }
        int centesimos = Calculadora::quilosParaCentesimos(valor);
        if (centesimos < 1 || centesimos > 100000) {
            std::cout << "Peso invalido. Use um valor entre 0.01 e 1000.00.\n";
            continue;
        }
        peso = centesimos;
        return true;
    }
}

bool Interface::lerPesoMaximo(int& pesoMaximo) {
    return lerPeso("Peso maximo em kg (0.01 a 1000.00): ", pesoMaximo);
}

bool Interface::lerInteiro(const std::string& rotulo, int minimo, int maximo, int& valor) {
    while (true) {
        std::cout << rotulo;
        std::string linha;
        if (!std::getline(std::cin, linha)) {
            return false;
        }
        int lido;
        if (!converterInteiro(linha, lido)) {
            std::cout << "Digite um numero inteiro valido.\n";
            continue;
        }
        if (lido < minimo || lido > maximo) {
            std::cout << "Valor fora do intervalo permitido (" << minimo
                      << " a " << maximo << ").\n";
            continue;
        }
        valor = lido;
        return true;
    }
}

bool Interface::lerDadosCriacao(std::string& nome, int& pesoMaximo,
                                int& capacidade, int& dinheiro) {
    std::cout << "=== Criacao do personagem ===\n";
    if (!lerNome(nome)) {
        return false;
    }
    if (!lerPesoMaximo(pesoMaximo)) {
        return false;
    }
    if (!lerInteiro("Capacidade comum (10 a 999): ", 10, 999, capacidade)) {
        return false;
    }
    if (!lerInteiro("Dinheiro inicial (0 a 9999): ", 0, 9999, dinheiro)) {
        return false;
    }
    return true;
}

bool Interface::lerNomeItem(std::string& nome) {
    while (true) {
        std::cout << "Nome do item: ";
        if (!std::getline(std::cin, nome)) {
            return false;
        }
        if (nome.empty()) {
            std::cout << "O nome nao pode ficar vazio.\n";
            continue;
        }
        return true;
    }
}

bool Interface::lerCategoria(Categoria& categoria) {
    std::cout << "Categoria:\n"
              << "1 - Minerios\n"
              << "2 - Comidas\n"
              << "3 - Pocoes\n"
              << "4 - Armas\n"
              << "5 - Unicos\n"
              << "6 - Recursos Naturais\n";
    int opcao;
    if (!lerInteiro("Categoria: ", 1, 6, opcao)) {
        return false;
    }
    categoria = static_cast<Categoria>(opcao - 1);
    return true;
}

bool Interface::lerRaridade(Raridade& raridade) {
    std::cout << "Raridade:\n"
              << "1 - Simples\n"
              << "2 - Raro\n"
              << "3 - Lendario\n";
    int opcao;
    if (!lerInteiro("Raridade: ", 1, 3, opcao)) {
        return false;
    }
    raridade = static_cast<Raridade>(opcao - 1);
    return true;
}

bool Interface::lerEfeito(Efeito& efeito) {
    std::cout << "Efeito:\n"
              << "1 - Vida\n"
              << "2 - Mana\n"
              << "3 - Vida e Mana\n";
    int opcao;
    if (!lerInteiro("Efeito: ", 1, 3, opcao)) {
        return false;
    }
    if (opcao == 1) {
        efeito = EFEITO_VIDA;
    } else if (opcao == 2) {
        efeito = EFEITO_MANA;
    } else {
        efeito = EFEITO_VIDA_E_MANA;
    }
    return true;
}

bool Interface::lerSubtipo(Categoria categoria, Subtipo& subtipo) {
    if (categoria == CATEGORIA_ARMAS) {
        std::cout << "Subtipo da arma:\n"
                  << "1 - Espada\n"
                  << "2 - Lanca\n"
                  << "3 - Arma Pesada\n"
                  << "4 - Arco ou Besta\n";
        int opcao;
        if (!lerInteiro("Subtipo: ", 1, 4, opcao)) {
            return false;
        }
        if (opcao == 1) {
            subtipo = SUBTIPO_ESPADA;
        } else if (opcao == 2) {
            subtipo = SUBTIPO_LANCA;
        } else if (opcao == 3) {
            subtipo = SUBTIPO_ARMA_PESADA;
        } else {
            subtipo = SUBTIPO_ARCO_BESTA;
        }
        return true;
    }
    if (categoria == CATEGORIA_UNICOS) {
        std::cout << "Tipo do item unico:\n"
                  << "1 - Nenhum (item unico)\n"
                  << "2 - Capacete\n"
                  << "3 - Peitoral\n"
                  << "4 - Calca\n";
        int opcao;
        if (!lerInteiro("Tipo: ", 1, 4, opcao)) {
            return false;
        }
        if (opcao == 1) {
            subtipo = SUBTIPO_NENHUM;
        } else if (opcao == 2) {
            subtipo = SUBTIPO_CAPACETE;
        } else if (opcao == 3) {
            subtipo = SUBTIPO_PEITORAL;
        } else {
            subtipo = SUBTIPO_CALCA;
        }
        return true;
    }
    subtipo = SUBTIPO_NENHUM;
    return true;
}

bool Interface::criarItemTeste() {
    std::string nome;
    int peso;
    Categoria categoria;
    Raridade raridade;
    Efeito efeito = EFEITO_NENHUM;
    Subtipo subtipo = SUBTIPO_NENHUM;

    if (!lerNomeItem(nome)) {
        return false;
    }
    if (!lerPeso("Peso do item em kg (0.01 a 1000.00): ", peso)) {
        return false;
    }
    if (!lerCategoria(categoria)) {
        return false;
    }
    if (!lerRaridade(raridade)) {
        return false;
    }
    if (categoria == CATEGORIA_COMIDAS || categoria == CATEGORIA_POCOES) {
        if (!lerEfeito(efeito)) {
            return false;
        }
    }
    if (!lerSubtipo(categoria, subtipo)) {
        return false;
    }

    Item item(nome, peso, categoria, raridade, efeito, subtipo);
    ItemStack pilha;
    pilha.adicionar(item);
    mostrarAnalise(pilha);
    return true;
}

void Interface::mostrarAnalise(const ItemStack& pilha) const {
    const Item& item = pilha.unidadeMaisRecente();
    std::cout << "\n=== Analise do item ===\n"
              << "Nome: " << item.getNome() << '\n'
              << "Categoria: " << nomeCategoria(item.getCategoria()) << '\n'
              << "Raridade: " << nomeRaridade(item.getRaridade()) << '\n'
              << "Consumivel: " << (item.isConsumivel() ? "Sim" : "Nao") << '\n'
              << "Efeito: " << nomeEfeito(item.getEfeito()) << '\n'
              << "Subtipo: " << nomeSubtipo(item.getSubtipo()) << '\n'
              << "Stacka: " << (pilha.limite() > 1 ? "Sim" : "Nao") << '\n'
              << "Limite de stack: " << pilha.limite() << '\n'
              << "Peso unitario: " << std::fixed << std::setprecision(2)
              << Calculadora::centesimosParaQuilos(item.getPeso()) << " kg\n"
              << "Peso total do stack: " << std::fixed << std::setprecision(2)
              << Calculadora::centesimosParaQuilos(pilha.pesoTotal()) << " kg\n\n";
}

void Interface::mostrarStatus(const Personagem& personagem, int capacidade) const {
    int capacidadeTotal = Calculadora::capacidadeGeral(capacidade);
    std::cout << "\n=== Status ===\n"
              << "Nome: " << personagem.getNome() << '\n'
              << "Peso maximo: " << std::fixed << std::setprecision(2)
              << Calculadora::centesimosParaQuilos(personagem.getPesoMaximo())
              << " kg\n"
              << "Capacidade: " << capacidadeTotal << " slots ("
              << capacidade << " comuns + 4 equipados)\n"
              << "Peso atual: 0.00 kg\n"
              << "Dinheiro: " << personagem.getDinheiro() << " moedas\n\n";
}

void Interface::mostrarMenu() const {
    std::cout << "=== Menu ===\n"
              << "1 - Status\n"
              << "2 - Dormir\n"
              << "3 - Criar item de teste\n";
}

void Interface::executar() {
    std::string nome;
    int pesoMaximo;
    int capacidade;
    int dinheiro;

    if (!lerDadosCriacao(nome, pesoMaximo, capacidade, dinheiro)) {
        std::cout << "\nEntrada encerrada. Programa finalizado.\n";
        return;
    }

    Personagem personagem(nome, pesoMaximo, dinheiro);
    std::cout << "\nPersonagem criado com sucesso!\n";
    mostrarStatus(personagem, capacidade);

    while (true) {
        mostrarMenu();
        int opcao;
        if (!lerInteiro("Opcao: ", 1, 3, opcao)) {
            std::cout << "\nEntrada encerrada. Programa finalizado.\n";
            return;
        }

        if (opcao == 1) {
            mostrarStatus(personagem, capacidade);
        } else if (opcao == 2) {
            std::cout << "\nO personagem foi dormir. Programa encerrado.\n";
            return;
        } else {
            if (!criarItemTeste()) {
                std::cout << "\nEntrada encerrada. Programa finalizado.\n";
                return;
            }
        }
    }
}
