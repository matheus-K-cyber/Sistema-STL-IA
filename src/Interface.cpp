#include "Interface.hpp"

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <sstream>

#include "Acoes.hpp"
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

std::string nomeAbaAtual(int abaAtual) {
    if (abaAtual == 0) {
        return "Geral";
    }
    return nomeCategoria(static_cast<Categoria>(abaAtual - 1));
}

std::string descricaoLimiar(int limiar) {
    if (limiar <= 0) {
        return "abaixo de 25%";
    }
    std::stringstream texto;
    texto << limiar << "% ou mais";
    return texto.str();
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

bool Interface::lerDadosItem(std::string& nome, int& peso,
                             Categoria& categoria, Raridade& raridade,
                             Efeito& efeito, Subtipo& subtipo,
                             int& quantidade) {
    efeito = EFEITO_NENHUM;
    subtipo = SUBTIPO_NENHUM;

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
    if (!lerInteiro("Quantidade (maior que zero): ", 1, 1000000, quantidade)) {
        return false;
    }
    return true;
}

bool Interface::pegarItem(Personagem& personagem, Inventario& inventario,
                          bool& inventarioAberto) {
    if (Calculadora::limiarPeso(inventario.pesoTotal(),
                                personagem.getPesoMaximo()) >= 100) {
        std::cout << "\nCarga em 100%: o personagem esta cansado e nao pode"
                  << " atacar, correr nem pegar itens.\n\n";
        return true;
    }

    std::string nome;
    int peso;
    Categoria categoria;
    Raridade raridade;
    Efeito efeito;
    Subtipo subtipo;
    int quantidade;

    if (!lerDadosItem(nome, peso, categoria, raridade, efeito, subtipo,
                      quantidade)) {
        return false;
    }

    Item item(nome, peso, categoria, raridade, efeito, subtipo);
    ResultadoAdicao resultado =
        inventario.adicionar(item, quantidade, personagem.getPesoMaximo());

    mostrarResultadoAdicao(resultado, quantidade, categoria);
    mostrarAlertaPeso(personagem.atualizarPeso(inventario.pesoTotal()));
    if (!inventarioAberto) {
        inventarioAberto = true;
        std::cout << "O inventario foi aberto automaticamente.\n";
    }
    mostrarInventarioGeral(inventario);
    return true;
}

bool Interface::lerItensIniciais(Inventario& inventario,
                                 Personagem& personagem) {
    int total;
    if (!lerInteiro("Quantidade de itens iniciais (0 para nenhum): ", 0, 1000,
                    total)) {
        return false;
    }

    for (int i = 0; i < total; ++i) {
        std::string nome;
        int peso;
        Categoria categoria;
        Raridade raridade;
        Efeito efeito;
        Subtipo subtipo;
        int quantidade;

        std::cout << "\n--- Item inicial " << (i + 1) << " ---\n";
        if (!lerDadosItem(nome, peso, categoria, raridade, efeito, subtipo,
                          quantidade)) {
            return false;
        }

        Item item(nome, peso, categoria, raridade, efeito, subtipo);
        ResultadoAdicao resultado =
            inventario.adicionar(item, quantidade, personagem.getPesoMaximo());
        mostrarResultadoAdicao(resultado, quantidade, categoria);
        mostrarAlertaPeso(personagem.atualizarPeso(inventario.pesoTotal()));

        if (item.isEquipavel() && resultado.adicionados > 0) {
            bool equipar = false;
            if (!perguntarEquiparInicial(equipar)) {
                return false;
            }
            if (equipar) {
                std::vector<ItemStack*> pilhas =
                    inventario.stacksDaIdentidade(item);
                ItemStack* alvo = 0;
                for (std::vector<ItemStack*>::size_type j = 0;
                     j < pilhas.size(); ++j) {
                    if (!pilhas[j]->isEquipado()
                        && pilhas[j]->quantidade() == 1) {
                        alvo = pilhas[j];
                        break;
                    }
                }
                if (alvo != 0) {
                    ResultadoAcao acao =
                        Acoes::equipar(inventario, personagem, alvo);
                    std::cout << '\n';
                    if (acao.sucesso) {
                        SlotEquipamento slot;
                        alvo->identidade().slotEquipamento(slot);
                        std::cout << "Item inicial equipado no slot "
                                  << nomeSlotEquipamento(slot) << ".\n\n";
                    } else {
                        std::cout << "Nao foi possivel equipar o item inicial.\n\n";
                    }
                }
            }
        }
    }
    return true;
}

bool Interface::ganharDinheiro(Personagem& personagem) {
    int valor;
    if (!lerInteiro("Moedas ganhas (maior que zero): ", 1, 1000000, valor)) {
        return false;
    }

    int excedente = personagem.ganharDinheiro(valor);
    std::cout << "\nO personagem ganhou " << valor << " moedas! Agora possui "
              << personagem.getDinheiro() << " moedas.\n";
    if (excedente > 0) {
        std::cout << excedente
                  << " moedas foram descartadas por exceder o limite de 9999.\n";
    }
    std::cout << '\n';
    return true;
}

bool Interface::gastarDinheiro(Personagem& personagem) {
    int valor;
    if (!lerInteiro("Moedas gastas ou perdidas (maior que zero): ", 1,
                    1000000, valor)) {
        return false;
    }

    bool sucesso = personagem.gastarDinheiro(valor);
    std::cout << '\n';
    if (!sucesso) {
        std::cout << "Saldo insuficiente: o personagem possui "
                  << personagem.getDinheiro() << " moedas e tentou gastar "
                  << valor << ". A acao foi bloqueada.\n\n";
        return true;
    }

    std::cout << "O personagem gastou " << valor << " moedas. Agora possui "
              << personagem.getDinheiro() << " moedas.\n";
    if (personagem.getDinheiro() == 0) {
        std::cout << "Aviso: o saldo do personagem zerou.\n";
    }
    std::cout << '\n';
    return true;
}

void Interface::mostrarAnalise(const ItemStack& pilha) const {
    const Item& item = pilha.unidadeMaisRecente();
    std::cout << "\n=== Analise do item ===\n"
              << "Nome: " << item.getNome() << '\n'
              << "Categoria: " << nomeCategoria(item.getCategoria()) << '\n'
              << "Raridade: " << nomeRaridade(item.getRaridade()) << '\n'
              << "Consumivel: " << (item.isConsumivel() ? "Sim" : "Nao") << '\n';
    if (item.getEfeito() != EFEITO_NENHUM) {
        std::cout << "Efeito: " << nomeEfeito(item.getEfeito()) << '\n';
    }
    std::cout << "Stacka: " << (pilha.limite() > 1 ? "Sim" : "Nao") << '\n'
              << "Limite de stack: " << pilha.limite() << '\n'
              << "Peso unitario: " << std::fixed << std::setprecision(2)
              << Calculadora::centesimosParaQuilos(item.getPeso()) << " kg\n";
    if (item.isEquipavel()) {
        std::cout << "Subtipo: " << nomeSubtipo(item.getSubtipo()) << '\n';
    }
    std::cout << "Peso total do stack: " << std::fixed << std::setprecision(2)
              << Calculadora::centesimosParaQuilos(pilha.pesoTotal()) << " kg\n\n";
}

void Interface::mostrarInventarioGeral(const Inventario& inventario) const {
    const std::list<ItemStack>& geral = inventario.listarGeral();
    std::cout << "\n=== Inventario geral (mais recente primeiro) ===\n"
              << "Slots comuns: " << inventario.slotsComunsOcupados() << "/"
              << inventario.getCapacidadeComum()
              << " | Sobressalentes: " << inventario.getSobressalentes()
              << '\n';
    if (geral.empty()) {
        std::cout << "Inventario vazio.\n\n";
        return;
    }

    int posicao = 1;
    for (std::list<ItemStack>::const_iterator it = geral.begin();
         it != geral.end(); ++it) {
        std::cout << posicao << " - " << it->identidade().getNome()
                  << " | " << it->quantidade()
                  << (it->quantidade() == 1 ? " unidade" : " unidades")
                  << " | Peso: " << std::fixed << std::setprecision(2)
                  << Calculadora::centesimosParaQuilos(it->pesoTotal())
                  << " kg\n";
        ++posicao;
    }
    std::cout << "Peso total: " << std::fixed << std::setprecision(2)
              << Calculadora::centesimosParaQuilos(inventario.pesoTotal())
              << " kg\n\n";
}

void Interface::mostrarAba(const Inventario& inventario,
                           Categoria categoria) const {
    const std::vector<ItemStack*>& aba = inventario.listarAba(categoria);
    std::cout << "\n=== Aba " << nomeCategoria(categoria) << " ("
              << aba.size() << "/" << inventario.getCapacidadeAba(categoria)
              << " slots) ===\n";
    if (aba.empty()) {
        std::cout << "Aba vazia.\n\n";
        return;
    }

    int pesoAba = 0;
    for (std::vector<ItemStack*>::size_type i = 0; i < aba.size(); ++i) {
        const ItemStack& pilha = *aba[i];
        pesoAba += pilha.pesoTotal();
        std::cout << (i + 1) << " - " << pilha.identidade().getNome()
                  << " | " << pilha.quantidade()
                  << (pilha.quantidade() == 1 ? " unidade" : " unidades")
                  << " | Peso: " << std::fixed << std::setprecision(2)
                  << Calculadora::centesimosParaQuilos(pilha.pesoTotal())
                  << " kg\n";
    }
    std::cout << "Peso da aba: " << std::fixed << std::setprecision(2)
              << Calculadora::centesimosParaQuilos(pesoAba) << " kg\n\n";
}

void Interface::mostrarResultadoAdicao(const ResultadoAdicao& resultado,
                                       int quantidade,
                                       Categoria categoria) const {
    std::cout << "\n=== Resultado da adicao ===\n"
              << "Quantidade pedida: " << quantidade << '\n';
    if (resultado.adicionados == 0) {
        std::cout << "Nenhuma unidade foi adicionada.\n";
    } else if (resultado.recusados > 0) {
        std::cout << "Unidades adicionadas: " << resultado.adicionados << '\n'
                  << "Unidades que ficaram de fora: " << resultado.recusados
                  << '\n';
    } else {
        std::cout << "Todas as unidades foram adicionadas.\n";
    }
    if (resultado.motivo == ADICAO_LIMITE_PESO) {
        std::cout << "Motivo: o peso maximo do personagem seria ultrapassado.\n";
    } else if (resultado.motivo == ADICAO_INVENTARIO_CHEIO) {
        std::cout << "Motivo: o inventario esta cheio (sem slot livre para este item).\n"
                  << "Os 4 slots extras sao exclusivos para itens equipados.\n";
    } else if (resultado.motivo == ADICAO_LIMITE_ABA) {
        std::cout << "Motivo: a aba de " << nomeCategoria(categoria)
                  << " esta cheia e nao ha slots sobressalentes.\n";
    } else if (resultado.motivo == ADICAO_LIMITE_PESO_E_INVENTARIO) {
        std::cout << "Motivo: o peso maximo seria ultrapassado e o inventario"
                  << " esta cheio.\n";
    } else if (resultado.motivo == ADICAO_LIMITE_PESO_E_ABA) {
        std::cout << "Motivo: o peso maximo seria ultrapassado e a aba de "
                  << nomeCategoria(categoria)
                  << " esta cheia sem slots sobressalentes.\n";
    }
    std::cout << "Peso atual: " << std::fixed << std::setprecision(2)
              << Calculadora::centesimosParaQuilos(resultado.pesoAtual)
              << " kg\n";
}

void Interface::alternarInventario(const Inventario& inventario,
                                   bool& inventarioAberto) const {
    if (inventarioAberto) {
        inventarioAberto = false;
        std::cout << "\nInventario fechado.\n\n";
        return;
    }
    inventarioAberto = true;
    std::cout << "\nInventario aberto.\n";
    mostrarInventarioGeral(inventario);
}

void Interface::mostrarSugestaoGeral(const Inventario& inventario, int abaAtual,
                                     const std::string& texto) const {
    if (abaAtual == 0) {
        return;
    }
    Categoria categoria = static_cast<Categoria>(abaAtual - 1);
    std::vector<const ItemStack*> naGeral =
        inventario.pesquisar(texto, categoria, true);
    if (naGeral.empty()) {
        std::cout << "Nenhum item com esse prefixo no inventario.\n";
    } else {
        std::cout << "Existe(m) item(ns) com esse prefixo na aba Geral. "
                  << "Selecione a aba Geral para pesquisar la.\n";
    }
}

void Interface::mostrarResultadosPesquisa(
    const std::vector<const ItemStack*>& resultados, int abaAtual,
    const std::string& texto) const {
    struct GrupoPesquisa {
        const ItemStack* representante;
        int quantidadeTotal;
    };

    std::vector<GrupoPesquisa> grupos;
    for (std::vector<const ItemStack*>::size_type i = 0; i < resultados.size();
         ++i) {
        const ItemStack* pilha = resultados[i];
        bool encontrado = false;
        for (std::vector<GrupoPesquisa>::size_type j = 0; j < grupos.size();
             ++j) {
            if (grupos[j].representante->identidade().mesmaIdentidade(
                    pilha->identidade())) {
                grupos[j].quantidadeTotal += pilha->quantidade();
                encontrado = true;
                break;
            }
        }
        if (!encontrado) {
            GrupoPesquisa grupo;
            grupo.representante = pilha;
            grupo.quantidadeTotal = pilha->quantidade();
            grupos.push_back(grupo);
        }
    }

    std::cout << "\n=== Pesquisa na aba " << nomeAbaAtual(abaAtual) << " ===\n"
              << "Texto pesquisado: \"" << texto << "\"\n";
    for (std::vector<GrupoPesquisa>::size_type i = 0; i < grupos.size(); ++i) {
        const Item& item = grupos[i].representante->identidade();
        std::cout << (i + 1) << " - " << item.getNome()
                  << " | " << nomeCategoria(item.getCategoria())
                  << " | " << nomeRaridade(item.getRaridade());
        if (item.isConsumivel() && item.getEfeito() != EFEITO_NENHUM) {
            std::cout << " | Efeito: " << nomeEfeito(item.getEfeito());
        }
        if (item.isEquipavel()) {
            std::cout << " | Subtipo: " << nomeSubtipo(item.getSubtipo());
        }
        std::cout << " | Total: " << grupos[i].quantidadeTotal
                  << (grupos[i].quantidadeTotal == 1 ? " unidade" : " unidades")
                  << '\n';
    }

    std::string textoNormalizado = normalizarTexto(texto);
    bool mostrouCabecalho = false;
    for (std::vector<GrupoPesquisa>::size_type i = 0; i < grupos.size(); ++i) {
        const Item& item = grupos[i].representante->identidade();
        if (normalizarTexto(item.getNome()) != textoNormalizado) {
            continue;
        }
        if (!mostrouCabecalho) {
            std::cout << "\nStacks do nome exato:\n";
            mostrouCabecalho = true;
        }
        std::cout << "  " << item.getNome() << " ("
                  << nomeRaridade(item.getRaridade());
        if (item.isConsumivel() && item.getEfeito() != EFEITO_NENHUM) {
            std::cout << ", Efeito: " << nomeEfeito(item.getEfeito());
        }
        if (item.isEquipavel()) {
            std::cout << ", Subtipo: " << nomeSubtipo(item.getSubtipo());
        }
        std::cout << "):\n";

        int numero = 1;
        for (std::vector<const ItemStack*>::size_type j = 0;
             j < resultados.size(); ++j) {
            if (!resultados[j]->identidade().mesmaIdentidade(item)) {
                continue;
            }
            std::cout << "    Stack " << numero << ": "
                      << resultados[j]->quantidade()
                      << (resultados[j]->quantidade() == 1 ? " unidade"
                                                           : " unidades");
            if (resultados[j]->isEquipado()) {
                std::cout << " [equipado]";
            }
            std::cout << '\n';
            ++numero;
        }
    }
    std::cout << '\n';
}

bool Interface::pesquisarItem(const Inventario& inventario, int abaAtual) {
    std::string texto;
    std::cout << "Texto da pesquisa: ";
    if (!std::getline(std::cin, texto)) {
        return false;
    }
    if (texto.empty()) {
        std::cout << "Digite um nome para pesquisar.\n";
        return true;
    }

    bool naGeral = (abaAtual == 0);
    Categoria categoria = naGeral ? CATEGORIA_MINERIOS
                                  : static_cast<Categoria>(abaAtual - 1);
    std::vector<const ItemStack*> resultados =
        inventario.pesquisar(texto, categoria, naGeral);
    if (resultados.empty()) {
        std::cout << "\n=== Pesquisa na aba " << nomeAbaAtual(abaAtual)
                  << " ===\n"
                  << "Nenhum item encontrado com o prefixo \"" << texto
                  << "\".\n";
        mostrarSugestaoGeral(inventario, abaAtual, texto);
        std::cout << '\n';
        return true;
    }

    mostrarResultadosPesquisa(resultados, abaAtual, texto);
    return true;
}

bool Interface::analisarItem(const Inventario& inventario, int abaAtual) {
    std::string texto;
    std::cout << "Nome do item para analisar: ";
    if (!std::getline(std::cin, texto)) {
        return false;
    }
    if (texto.empty()) {
        std::cout << "Digite um nome para analisar.\n";
        return true;
    }

    bool naGeral = (abaAtual == 0);
    Categoria categoria = naGeral ? CATEGORIA_MINERIOS
                                  : static_cast<Categoria>(abaAtual - 1);
    std::vector<const ItemStack*> resultados =
        inventario.pesquisar(texto, categoria, naGeral);
    if (resultados.empty()) {
        std::cout << "\n=== Analise na aba " << nomeAbaAtual(abaAtual)
                  << " ===\n"
                  << "Nenhum item encontrado com o prefixo \"" << texto
                  << "\".\n";
        mostrarSugestaoGeral(inventario, abaAtual, texto);
        std::cout << '\n';
        return true;
    }

    const ItemStack* escolhida = 0;
    if (resultados.size() == 1) {
        escolhida = resultados[0];
    } else {
        std::cout << "\nItens encontrados na aba " << nomeAbaAtual(abaAtual)
                  << ":\n";
        for (std::vector<const ItemStack*>::size_type i = 0;
             i < resultados.size(); ++i) {
            std::cout << (i + 1) << " - "
                      << resultados[i]->identidade().getNome()
                      << " | " << resultados[i]->quantidade()
                      << (resultados[i]->quantidade() == 1 ? " unidade"
                                                          : " unidades");
            if (resultados[i]->isEquipado()) {
                std::cout << " [equipado]";
            }
            std::cout << '\n';
        }
        int escolha;
        if (!lerInteiro("Item para analisar: ", 1,
                        static_cast<int>(resultados.size()), escolha)) {
            return false;
        }
        escolhida = resultados[escolha - 1];
    }

    if (escolhida->isEquipado()) {
        std::cout << "\nNao e possivel analisar um item equipado. "
                  << "Desequipe-o primeiro.\n\n";
        return true;
    }

    mostrarAnalise(*escolhida);
    return true;
}

bool Interface::escolherPilha(const Inventario& inventario, int abaAtual,
                              const std::string& acao,
                              const ItemStack*& escolhida) {
    escolhida = 0;

    std::string texto;
    std::cout << "Nome do item para " << acao << ": ";
    if (!std::getline(std::cin, texto)) {
        return false;
    }
    if (texto.empty()) {
        std::cout << "Digite um nome.\n";
        return true;
    }

    bool naGeral = (abaAtual == 0);
    Categoria categoria = naGeral ? CATEGORIA_MINERIOS
                                  : static_cast<Categoria>(abaAtual - 1);
    std::vector<const ItemStack*> resultados =
        inventario.pesquisar(texto, categoria, naGeral);
    if (resultados.empty()) {
        std::cout << "\n=== " << acao << " na aba "
                  << nomeAbaAtual(abaAtual) << " ===\n"
                  << "Nenhum item encontrado com o prefixo \"" << texto
                  << "\".\n";
        mostrarSugestaoGeral(inventario, abaAtual, texto);
        std::cout << '\n';
        return true;
    }

    if (resultados.size() == 1) {
        escolhida = resultados[0];
        return true;
    }

    std::cout << "\nItens encontrados na aba " << nomeAbaAtual(abaAtual)
              << ":\n";
    for (std::vector<const ItemStack*>::size_type i = 0;
         i < resultados.size(); ++i) {
        std::cout << (i + 1) << " - "
                  << resultados[i]->identidade().getNome()
                  << " | " << resultados[i]->quantidade()
                  << (resultados[i]->quantidade() == 1 ? " unidade"
                                                      : " unidades");
        if (resultados[i]->isEquipado()) {
            std::cout << " [equipado]";
        }
        std::cout << '\n';
    }

    int escolha;
    if (!lerInteiro("Item para " + acao + ": ", 1,
                    static_cast<int>(resultados.size()), escolha)) {
        return false;
    }
    escolhida = resultados[escolha - 1];
    return true;
}

bool Interface::confirmar(const std::string& pergunta, bool& confirmado) {
    std::cout << '\n' << pergunta << '\n'
              << "1 - Sim\n"
              << "2 - Nao\n";
    int opcao;
    if (!lerInteiro("Confirmacao: ", 1, 2, opcao)) {
        return false;
    }
    confirmado = (opcao == 1);
    return true;
}

bool Interface::perguntarEquiparInicial(bool& equipar) {
    int opcao;
    if (!lerInteiro("Equipar este item agora? (1 - Sim, 2 - Nao): ", 1, 2,
                    opcao)) {
        return false;
    }
    equipar = (opcao == 1);
    return true;
}

bool Interface::consumirItem(Inventario& inventario, Personagem& personagem,
                             int abaAtual) {
    const ItemStack* pilha = 0;
    if (!escolherPilha(inventario, abaAtual, "consumir", pilha)) {
        return false;
    }
    if (pilha == 0) {
        return true;
    }

    std::string nome = pilha->identidade().getNome();
    ResultadoAcao resultado = Acoes::consumir(inventario, personagem, pilha);

    std::cout << '\n';
    if (!resultado.sucesso) {
        if (resultado.motivo == FALHA_NAO_ENCONTRADO) {
            std::cout << "O item nao esta mais no inventario.\n\n";
        } else if (resultado.motivo == FALHA_EQUIPADO) {
            std::cout << "Nao e possivel consumir um item equipado. "
                      << "Desequipe-o primeiro.\n\n";
        } else if (resultado.motivo == FALHA_NAO_CONSUMIVEL) {
            std::cout << "Este item nao e consumivel. Somente Comidas e "
                      << "Pocoes podem ser consumidas.\n\n";
        } else {
            std::cout << "Nao foi possivel consumir o item.\n\n";
        }
        return true;
    }

    std::cout << "Voce consumiu 1 unidade de " << nome << ".\n";
    if (resultado.efeito == EFEITO_VIDA) {
        std::cout << "Aviso: 20% da vida foi restaurada.\n";
    } else if (resultado.efeito == EFEITO_MANA) {
        std::cout << "Aviso: 20% da mana foi restaurada.\n";
    } else if (resultado.efeito == EFEITO_VIDA_E_MANA) {
        std::cout << "Aviso: 20% da vida e 20% da mana foram restaurados.\n";
    }
    std::cout << "Peso removido: " << std::fixed << std::setprecision(2)
              << Calculadora::centesimosParaQuilos(resultado.pesoRemovido)
              << " kg.\n\n";

    mostrarAlertaPeso(personagem.atualizarPeso(inventario.pesoTotal()));
    return true;
}

bool Interface::descartarItem(Inventario& inventario, Personagem& personagem,
                              int abaAtual) {
    const ItemStack* pilha = 0;
    if (!escolherPilha(inventario, abaAtual, "descartar", pilha)) {
        return false;
    }
    if (pilha == 0) {
        return true;
    }

    std::cout << "\nTipo de descarte:\n"
              << "1 - Uma unidade\n"
              << "2 - Todos\n"
              << "3 - Quantidade escolhida\n";
    int modo;
    if (!lerInteiro("Opcao de descarte: ", 1, 3, modo)) {
        return false;
    }

    int quantidade = 1;
    if (modo == 3) {
        if (!lerInteiro("Quantidade a descartar (maior que zero): ", 1,
                        1000000, quantidade)) {
            return false;
        }
    }

    bool confirmado = false;
    if (!confirmar("Confirma o descarte?", confirmado)) {
        return false;
    }
    if (!confirmado) {
        std::cout << "\nDescarte cancelado.\n\n";
        return true;
    }

    std::string nome = pilha->identidade().getNome();
    ResultadoAcao resultado;
    if (modo == 2) {
        resultado = Acoes::descartarTudo(inventario, personagem, pilha);
    } else {
        resultado = Acoes::descartar(inventario, personagem, pilha, quantidade);
    }

    std::cout << '\n';
    if (!resultado.sucesso) {
        if (resultado.motivo == FALHA_NAO_ENCONTRADO) {
            std::cout << "O item nao esta mais no inventario.\n\n";
        } else if (resultado.motivo == FALHA_EQUIPADO) {
            std::cout << "Nao e possivel descartar um item equipado. "
                      << "Desequipe-o primeiro.\n\n";
        } else if (resultado.motivo == FALHA_QUANTIDADE_INSUFICIENTE) {
            std::cout << "A quantidade informada nao existe no inventario. "
                      << "O descarte foi bloqueado.\n\n";
        } else {
            std::cout << "Nao foi possivel descartar o item.\n\n";
        }
        return true;
    }

    std::cout << "Descartadas " << resultado.quantidade
              << (resultado.quantidade == 1 ? " unidade de "
                                            : " unidades de ")
              << nome << " (a unidade mais recente de cada stack).\n"
              << "Peso removido: " << std::fixed << std::setprecision(2)
              << Calculadora::centesimosParaQuilos(resultado.pesoRemovido)
              << " kg.\n\n";

    mostrarAlertaPeso(personagem.atualizarPeso(inventario.pesoTotal()));
    return true;
}

bool Interface::equiparItem(Inventario& inventario, Personagem& personagem,
                            int abaAtual) {
    const ItemStack* pilha = 0;
    if (!escolherPilha(inventario, abaAtual, "equipar", pilha)) {
        return false;
    }
    if (pilha == 0) {
        return true;
    }

    SlotEquipamento slot = SLOT_ARMA;
    bool equipavel = pilha->identidade().slotEquipamento(slot);
    const ItemStack* antigo = equipavel ? personagem.getEquipado(slot) : 0;
    std::string nomeAntigo =
        antigo != 0 ? antigo->identidade().getNome() : "";
    std::string nome = pilha->identidade().getNome();
    ResultadoAcao resultado = Acoes::equipar(inventario, personagem, pilha);

    std::cout << '\n';
    if (!resultado.sucesso) {
        if (resultado.motivo == FALHA_NAO_ENCONTRADO) {
            std::cout << "O item nao esta mais no inventario.\n\n";
        } else if (resultado.motivo == FALHA_EQUIPADO) {
            std::cout << "Nao e possivel equipar um item que ja esta equipado. "
                      << "Desequipe-o primeiro.\n\n";
        } else if (resultado.motivo == FALHA_NAO_EQUIPAVEL) {
            std::cout << "Somente armas e pecas de armadura podem ser "
                      << "equipadas.\n\n";
        } else if (resultado.motivo == FALHA_QUANTIDADE_INSUFICIENTE) {
            std::cout << "O item precisa ter uma unidade para ser equipado.\n\n";
        } else {
            std::cout << "Nao foi possivel equipar o item.\n\n";
        }
        return true;
    }

    std::cout << "O item " << nome << " foi equipado no slot "
              << nomeSlotEquipamento(slot) << ".\n";
    if (antigo != 0) {
        std::cout << "O item " << nomeAntigo << " voltou para a aba "
                  << nomeCategoria(antigo->identidade().getCategoria())
                  << " e ocupou o lugar que o novo deixou.\n"
                  << "Os dois continuam na aba geral, na mesma ordem.\n\n";
    } else {
        std::cout << "O item saiu da aba categorizada e continua na aba "
                  << "geral, na mesma ordem.\n\n";
    }
    return true;
}

bool Interface::desequiparItem(Inventario& inventario,
                               Personagem& personagem) {
    if (personagem.quantidadeEquipados() == 0) {
        std::cout << "\nNao ha itens equipados para desequipar.\n\n";
        return true;
    }

    std::vector<SlotEquipamento> ocupados;
    std::cout << "\nItens equipados:\n";
    for (int i = 0; i < 4; ++i) {
        SlotEquipamento slot = static_cast<SlotEquipamento>(i);
        const ItemStack* pilha = personagem.getEquipado(slot);
        if (pilha == 0) {
            continue;
        }
        ocupados.push_back(slot);
        std::cout << ocupados.size() << " - " << nomeSlotEquipamento(slot)
                  << ": " << pilha->identidade().getNome() << '\n';
    }

    int escolha;
    if (!lerInteiro("Slot para desequipar: ", 1,
                    static_cast<int>(ocupados.size()), escolha)) {
        return false;
    }
    SlotEquipamento slot = ocupados[escolha - 1];
    ItemStack* pilha = personagem.getEquipado(slot);
    std::string nome = pilha->identidade().getNome();
    Categoria categoria = pilha->identidade().getCategoria();
    ResultadoAcao resultado = Acoes::desequipar(inventario, personagem, slot);

    std::cout << '\n';
    if (!resultado.sucesso) {
        if (resultado.motivo == FALHA_NAO_ENCONTRADO) {
            std::cout << "Nao ha item equipado nesse slot.\n\n";
        } else if (resultado.motivo == FALHA_SEM_ESPACO_GERAL) {
            std::cout << "Nao ha vaga na aba geral comum. O desequipamento "
                      << "foi bloqueado.\n\n";
        } else if (resultado.motivo == FALHA_SEM_ESPACO_ABA) {
            std::cout << "Nao ha vaga na aba de " << nomeCategoria(categoria)
                      << " nem slot sobressalente. O desequipamento foi "
                      << "bloqueado.\n\n";
        } else {
            std::cout << "Nao foi possivel desequipar o item.\n\n";
        }
        return true;
    }

    std::cout << "O item " << nome << " foi desequipado do slot "
              << nomeSlotEquipamento(slot) << " e voltou para a aba "
              << nomeCategoria(categoria) << ".\n\n";
    return true;
}

bool Interface::selecionarAba(const Inventario& inventario, int& abaAtual) {
    std::cout << "Abas:\n"
              << "1 - Geral\n"
              << "2 - Minerios\n"
              << "3 - Comidas\n"
              << "4 - Pocoes\n"
              << "5 - Armas\n"
              << "6 - Unicos\n"
              << "7 - Recursos Naturais\n";
    int opcao;
    if (!lerInteiro("Aba: ", 1, 7, opcao)) {
        return false;
    }

    if (opcao == 1) {
        abaAtual = 0;
        mostrarInventarioGeral(inventario);
    } else {
        abaAtual = opcao - 1;
        mostrarAba(inventario, static_cast<Categoria>(abaAtual - 1));
    }
    std::cout << "Aba atual: " << nomeAbaAtual(abaAtual) << "\n\n";
    return true;
}

void Interface::mostrarStatus(const Personagem& personagem,
                              const Inventario& inventario) const {
    int capacidadeTotal =
        Calculadora::capacidadeGeral(inventario.getCapacidadeComum());
    int limiar = personagem.getUltimoLimiar();

    std::cout << "\n=== Status ===\n"
              << "Nome: " << personagem.getNome() << '\n'
              << "Peso maximo: " << std::fixed << std::setprecision(2)
              << Calculadora::centesimosParaQuilos(personagem.getPesoMaximo())
              << " kg\n"
              << "Capacidade: " << capacidadeTotal << " slots ("
              << inventario.getCapacidadeComum() << " comuns + 4 equipados)\n"
              << "Slots comuns: " << inventario.slotsComunsOcupados() << "/"
              << inventario.getCapacidadeComum() << '\n'
              << "Slots equipados: " << inventario.slotsEquipadosOcupados()
              << "/4\n"
              << "Peso total: " << std::fixed << std::setprecision(2)
              << Calculadora::centesimosParaQuilos(inventario.pesoTotal())
              << " kg\n"
              << "Dinheiro: " << personagem.getDinheiro() << " moedas\n"
              << "Limiar atual: " << descricaoLimiar(limiar) << '\n';
    if (limiar >= 100) {
        std::cout << "Cansaco: nao pode atacar, correr nem pegar itens.\n";
    }
    std::cout << '\n';
}

void Interface::mostrarAlertaPeso(const AlertaPeso& alerta) const {
    if (!alerta.mudou) {
        return;
    }

    if (alerta.aumento) {
        if (alerta.cansaco) {
            std::cout << "\nAviso de peso: o personagem atingiu 100% da carga"
                      << " maxima e ficou mais lento.\n"
                      << "Cansaco: nao pode atacar, correr nem pegar itens.\n";
        } else {
            std::cout << "\nAviso de peso: o personagem esta carregando "
                      << alerta.limiar
                      << "% ou mais do peso maximo e ficou mais lento.\n";
        }
    } else {
        std::cout << "\nAviso de peso: o peso reduziu para menos de "
                  << alerta.limiar << "% do peso maximo. "
                  << "O personagem ficou mais rapido.\n";
    }
}

void Interface::limparDados(Personagem& personagem,
                            Inventario& inventario) const {
    personagem.limpar();
    inventario.limpar();
}

void Interface::mostrarMenu(bool inventarioAberto, int abaAtual) const {
    std::cout << "=== Menu ===\n"
              << "1 - Status\n"
              << "2 - Dormir\n"
              << "3 - Pegar item\n"
              << "4 - "
              << (inventarioAberto ? "Fechar inventario" : "Abrir inventario")
              << '\n'
              << "5 - Selecionar aba\n"
              << "6 - Pesquisar\n"
              << "7 - Analisar\n"
              << "8 - Ganhar dinheiro\n"
              << "9 - Gastar ou perder dinheiro\n"
              << "10 - Consumir\n"
              << "11 - Descartar\n"
              << "12 - Equipar\n"
              << "13 - Desequipar\n"
              << "14 - Morrer\n";
    if (inventarioAberto) {
        std::cout << "Aba atual: " << nomeAbaAtual(abaAtual) << '\n';
    }
}

void Interface::executar() {
    bool criarOutro = true;
    while (criarOutro) {
        criarOutro = false;

        std::string nome;
        int pesoMaximo;
        int capacidade;
        int dinheiro;

        if (!lerDadosCriacao(nome, pesoMaximo, capacidade, dinheiro)) {
            std::cout << "\nEntrada encerrada. Programa finalizado.\n";
            return;
        }

        Personagem personagem(nome, pesoMaximo, dinheiro);
        Inventario inventario(capacidade);
        bool inventarioAberto = false;
        int abaAtual = 0;

        std::cout << "\nPersonagem criado com sucesso!\n";
        if (!lerItensIniciais(inventario, personagem)) {
            std::cout << "\nEntrada encerrada. Programa finalizado.\n";
            return;
        }
        mostrarStatus(personagem, inventario);

        while (true) {
            mostrarMenu(inventarioAberto, abaAtual);
            int opcao;
            if (!lerInteiro("Opcao: ", 1, 14, opcao)) {
                std::cout << "\nEntrada encerrada. Programa finalizado.\n";
                return;
            }

            if (opcao == 1) {
                mostrarStatus(personagem, inventario);
            } else if (opcao == 2) {
                limparDados(personagem, inventario);
                std::cout << "\nO personagem foi dormir. Programa encerrado.\n";
                return;
            } else if (opcao == 3) {
                if (!pegarItem(personagem, inventario, inventarioAberto)) {
                    std::cout << "\nEntrada encerrada. Programa finalizado.\n";
                    return;
                }
            } else if (opcao == 4) {
                alternarInventario(inventario, inventarioAberto);
            } else if (opcao == 5) {
                if (!inventarioAberto) {
                    std::cout << "\nAbra o inventario primeiro.\n";
                } else if (!selecionarAba(inventario, abaAtual)) {
                    std::cout << "\nEntrada encerrada. Programa finalizado.\n";
                    return;
                }
            } else if (opcao == 6) {
                if (!inventarioAberto) {
                    std::cout << "\nAbra o inventario primeiro.\n";
                } else if (!pesquisarItem(inventario, abaAtual)) {
                    std::cout << "\nEntrada encerrada. Programa finalizado.\n";
                    return;
                }
            } else if (opcao == 7) {
                if (!inventarioAberto) {
                    std::cout << "\nAbra o inventario primeiro.\n";
                } else if (!analisarItem(inventario, abaAtual)) {
                    std::cout << "\nEntrada encerrada. Programa finalizado.\n";
                    return;
                }
            } else if (opcao == 8) {
                if (!ganharDinheiro(personagem)) {
                    std::cout << "\nEntrada encerrada. Programa finalizado.\n";
                    return;
                }
            } else if (opcao == 9) {
                if (!gastarDinheiro(personagem)) {
                    std::cout << "\nEntrada encerrada. Programa finalizado.\n";
                    return;
                }
            } else if (opcao == 10) {
                if (!inventarioAberto) {
                    std::cout << "\nAbra o inventario primeiro.\n";
                } else if (!consumirItem(inventario, personagem, abaAtual)) {
                    std::cout << "\nEntrada encerrada. Programa finalizado.\n";
                    return;
                }
            } else if (opcao == 11) {
                if (!inventarioAberto) {
                    std::cout << "\nAbra o inventario primeiro.\n";
                } else if (!descartarItem(inventario, personagem, abaAtual)) {
                    std::cout << "\nEntrada encerrada. Programa finalizado.\n";
                    return;
                }
            } else if (opcao == 12) {
                if (!inventarioAberto) {
                    std::cout << "\nAbra o inventario primeiro.\n";
                } else if (!equiparItem(inventario, personagem, abaAtual)) {
                    std::cout << "\nEntrada encerrada. Programa finalizado.\n";
                    return;
                }
            } else if (opcao == 13) {
                if (!inventarioAberto) {
                    std::cout << "\nAbra o inventario primeiro.\n";
                } else if (!desequiparItem(inventario, personagem)) {
                    std::cout << "\nEntrada encerrada. Programa finalizado.\n";
                    return;
                }
            } else {
                std::cout << "\nPersonagem teve sua vida zerada, agora ele esta"
                          << " morto e seus dados serao descartados e o"
                          << " inventario esvaziado...\n";
                limparDados(personagem, inventario);
                std::cout << "\nDados do personagem apagados.\n"
                          << "Deseja criar outro personagem ou encerrar?\n"
                          << "1 - Criar outro personagem\n"
                          << "2 - Encerrar\n";
                int escolha;
                if (!lerInteiro("Opcao: ", 1, 2, escolha)) {
                    std::cout << "\nEntrada encerrada. Programa finalizado.\n";
                    return;
                }
                if (escolha == 1) {
                    criarOutro = true;
                    break;
                }
                std::cout << "\nEncerrando o gerenciamento da mochila."
                          << " Programa finalizado.\n";
                return;
            }
        }
    }
}
