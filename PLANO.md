# Plano de implementação

Sistema de inventário de RPG descrito em `DESCRICAO.md`. Este arquivo é só o
plano: ainda não há código. Cada etapa termina com o projeto compilando pelo
comando do `README.md` e com um arquivo em `exemplos/` para testar.

## Decisões gerais

- C++11 e somente a biblioteca padrão.
- Nenhuma classe do sistema usa `cin`/`cout`; só a `Interface`.
- Sem `new`, `delete`, lambda ou `unordered_map`.
- O peso é guardado internamente em centésimos de kg (`int`), porque o limite
  é duas casas. Exemplo: `1,25 kg` vira `125`. A interface lê `double`,
  arredonda com `std::round(valor * 100)` e converte. Assim somas e comparações
  de peso não têm erro de ponto flutuante.
- A aba geral guarda **todos** os stacks em uma única `std::list`, inclusive
  os equipados. Cada stack tem um `bool equipado`. As abas por categoria
  guardam ponteiros apenas para os stacks não equipados. Isso mantém a ordem
  da geral quando equipamos/desequipamos e evita duplicar itens.
- O `Personagem` guarda ponteiros não proprietários para os stacks equipados;
  o dono é o `Inventario`. Como `std::list` não muda os nós ao inserir ou
  remover outros, os ponteiros continuam válidos. Nada de `new`/`delete`.
- Dois itens são iguais para stack quando têm o mesmo nome exato, categoria,
  raridade, efeito (se consumível) e subtipo; o peso não entra. Para busca e
  ordenação, o nome é normalizado (minúsculas e acentos comuns do português).
- A classe de dados gerais que você imaginou fica dividida em `Personagem`
  (dinheiro, peso máximo, último limiar de peso, equipados) e `Calculadora`
  (contas). O peso atual não é guardado duas vezes: ele é sempre recalculado
  a partir do inventário e passado para `Personagem::atualizarPeso`.
- Ações como consumir, descartar e equipar recebem o item escolhido pela
  interface e conferem se ele está mesmo no inventário. Se houver mais de um
  item com o mesmo nome, a interface mostra uma lista numerada para escolher.

## Classes e responsabilidades

### `Item` (`include/Item.hpp`, `src/Item.cpp`)

Guarda **uma unidade** de item:

- nome, peso em centésimos, categoria, raridade, efeito e subtipo;
- consumível calculado pela categoria: só Comidas e Poções são consumíveis.

Métodos principais:

- getters e conversões: `isArma`, `isArmadura`, `isEquipavel`,
  `slotEquipamento`;
- `limiteStack`: 30 para Simples, 20 para Raro, 1 para Lendário; arma ou
  armadura sempre 1;
- `mesmaIdentidade` e `operator==` para saber se dois itens entram no mesmo
  stack;
- `operator<` para ordenar pelo nome normalizado; empate por categoria,
  raridade, efeito e subtipo. Esse é o operador usado pelo `std::sort` das
  abas.

### `ItemStack` (`include/ItemStack.hpp`, `src/ItemStack.cpp`)

Guarda um slot/stack:

- `std::vector<Item> unidades`, da mais antiga para a mais recente;
- `bool equipado`.

Métodos principais:

- `quantidade`, `pesoTotal`, `identidade`, `unidadeMaisRecente` e `limite`;
- `aceita`, `adicionar` e `removerUltima`;
- `operator<` comparando a identidade do stack. É esse operador que o
  `std::sort` das abas usa por meio de uma função de comparação de ponteiros.

O `std::vector` foi escolhido porque o stack tem no máximo 30 unidades,
precisamos adicionar e remover no fim, e a última posição já é a unidade mais
recente.

### `Calculadora` (`include/Calculadora.hpp`, `src/Calculadora.cpp`)

Classe sem estado, só com contas:

- converter kg para centésimos e voltar, arredondando para duas casas;
- dividir os `N` slots comuns entre as 6 abas e devolver o resto
  (sobressalentes);
- calcular o limite de stack de um item;
- comparar peso atual mais peso novo com o peso máximo;
- descobrir o limiar de peso atual: 0, 25, 50, 75 ou 100;
- somar dinheiro até 9999 e devolver o excedente;
- contar caracteres sem espaço para validar o nome do item.

### `Personagem` (`include/Personagem.hpp`, `src/Personagem.cpp`)

Guarda:

- nome, peso máximo em centésimos e dinheiro (0 a 9999);
- `ultimoLimiar` para não repetir o mesmo aviso de peso;
- `std::map<SlotEquipamento, ItemStack*> equipados`, com no máximo 4 itens.

Métodos principais:

- `ganharDinheiro` e `gastarDinheiro`, respeitando o limite de 9999 e o saldo;
- `atualizarPeso(pesoAtual)`, que devolve um `AlertaPeso` de aumento ou
  redução. No aumento, usa o maior limiar alcançado; na redução, usa o menor
  limiar que ficou para trás. Exemplo: de 75% para 25% avisa "menos de 50%";
  de 50% para 0% avisa "menos de 25%";
- `getEquipado`, `trocarEquipado`, `removerEquipado` e `quantidadeEquipados`.

O mapa é usado porque os slots são fixos e queremos achar um equipamento
direto pelo tipo, sem procurar em uma lista.

### `Inventario` (`include/Inventario.hpp`, `src/Inventario.cpp`)

Guarda:

- `std::list<ItemStack> geral`: todos os stacks, do mais recente para o mais
  antigo, inclusive os equipados;
- `std::map<Categoria, std::vector<ItemStack*> > abas`: as 6 abas
  categorizadas, cada uma com ponteiros para stacks da geral. Os equipados
  ficam de fora dessas abas;
- `std::map<Categoria, int> capacidadeAba`: slots de cada aba;
- `capacidadeComum` (o `N` informado) e `sobressalentes` (o resto da divisão).

Métodos principais:

- `configurar(N)`: divide `N / 6` para cada aba e guarda `N % 6` como
  sobressalentes;
- `adicionar(item, quantidade, pesoMaximo)`: devolve quantos entraram,
  quantos ficaram de fora, o motivo (peso, geral ou aba) e o peso atual.
  Preenche primeiro o stack com menor quantidade; se empatar, o mais novo.
  Se não houver stack, cria um no começo da geral. Se a aba estiver cheia,
  tenta usar um sobressalente;
- `removerUnidade`, `removerSeVazio`, `pesoTotal`, `slotsComunsOcupados`,
  `slotsEquipadosOcupados`, `temEspacoComum` e `temEspacoAba`;
- `pesquisar(prefixo, aba, naGeral)`: devolve os stacks cujo nome normalizado
  começa com o texto digitado;
- `listarGeral`, `listarAba` e `ordenarAba`;
- `removerDaAba` e `adicionarNaAba`, usados ao equipar e desequipar;
- `contem(pilha)`, para as ações conferirem se o item está no inventário.

Regra de capacidade: a soma dos slots ocupados nas abas é igual ao número de
stacks comuns na geral. Equipados ocupam os 4 slots exclusivos da geral e não
entram nessa soma.

### `Acoes` (`include/Acoes.hpp`, `src/Acoes.cpp`)

Não guarda estado; recebe `Inventario&` e `Personagem&` por parâmetro.

- `consumir`: confere presença, se é consumível e se não está equipado.
  Remove uma unidade do stack com menor quantidade; empate usa o mais novo.
  Dentro do stack sai primeiro a unidade mais recente. Devolve o efeito para
  a interface avisar sobre vida, mana ou ambos.
- `descartar`: confere presença. Usa o stack mais recente primeiro; se
  precisar de mais, vai para o próximo mais recente. Remove sempre a última
  unidade do stack e desconta o peso dela. Devolve quantos saíram e o peso
  removido.
- `equipar`: confere se é arma ou armadura, se tem uma unidade e se não está
  equipado. Arma substitui a arma atual; armadura substitui só a peça do
  mesmo slot. O item antigo volta para a aba da categoria e o novo deixa a
  aba, mas os dois continuam na geral. A ordem da geral não muda.
- `desequipar`: exige vaga na geral comum e na aba da categoria (ou um
  sobressalente). Se faltar espaço, bloqueia.

### `Interface` (`include/Interface.hpp`, `src/Interface.cpp`)

Única classe com `cin` e `cout`.

- Criação do personagem: nome (até 10 caracteres), peso máximo (0,01 a
  1000,00), `N` (10 a 999), dinheiro (0 a 9999) e itens iniciais opcionais.
- Menu: abrir/fechar inventário, selecionar aba, pegar, pesquisar, analisar,
  consumir, descartar, equipar, desequipar, ganhar/perder dinheiro, status,
  dormir e morrer.
- Categoria, raridade, subtipo e efeito são escolhidos por menu numérico.
- Valida nomes (99 caracteres sem contar espaços), quantidades maiores que
  zero, confirmações e limites.
- Recebe os resultados das classes e escreve as mensagens e alertas. Nenhuma
  regra de negócio fica na interface.

### `Tipos` (`include/Tipos.hpp`, `src/Tipos.cpp`)

Enums e estruturas compartilhadas:

- `Categoria`, `Raridade`, `Efeito`, `Subtipo` e `SlotEquipamento`;
- `MotivoFalha`, `AlertaPeso` e `ResultadoAcao`;
- funções de nome para exibição, `normalizarTexto` e contagem de caracteres.

`main.cpp` só cria a `Interface` e chama `executar()`.

## Containers e algoritmos da STL

| Onde | O que guarda ou faz | Por quê |
| --- | --- | --- |
| `Inventario::geral` | `std::list<ItemStack>` com todos os stacks, do mais recente para o mais antigo | Inserir no começo é O(1), os ponteiros para os nós não mudam quando outros nós entram ou saem, e não precisamos de acesso por posição. |
| `Inventario::abas` | `std::map<Categoria, std::vector<ItemStack*> >` | O mapa acha a aba direto pela categoria e permite percorrer as 6 categorias. O vetor permite `std::sort`; os ponteiros evitam copiar os stacks. |
| `Inventario::capacidadeAba` | `std::map<Categoria, int>` | Mesma chave fixa do mapa de abas; consulta direta dos slots de cada categoria. |
| `Personagem::equipados` | `std::map<SlotEquipamento, ItemStack*>` | São 4 slots fixos; o mapa acha e substitui a peça certa sem percorrer uma lista. |
| `ItemStack::unidades` | `std::vector<Item>` | Guarda as unidades na ordem de chegada; `push_back` e `pop_back` são simples e a última posição é a unidade mais recente. |
| `std::sort` | Ordena o vetor de cada aba | As abas precisam ficar em ordem alfabética. A comparação usa `ItemStack::operator<`, que por sua vez usa `Item::operator<`. |
| `std::find` | Remove um ponteiro de `std::vector<ItemStack*>` | Ajuda a tirar um stack de uma aba quando ele é equipado ou esvaziado. É um uso extra; o requisito principal é `std::sort` + `operator<`. |
| `std::string` | Nomes, pesquisa e normalização | Texto do nome do item, categoria e mensagens que a interface monta. |

**Requisitos da atividade:** temos `std::map` nas abas e nos equipamentos,
temos `std::list` na aba geral, e temos `std::sort` com sobrecarga de
`operator<` em `Item` e `ItemStack`. Não usamos `set`, `unordered_map` nem
lambda.

## Invariantes que os testes devem conferir

- A soma dos stacks das 6 abas é igual ao número de stacks comuns da geral.
- Equipados ficam na geral, mas não nas abas; no máximo 4.
- Um stack tem `equipado == true` exatamente quando aparece no mapa de
  equipados do `Personagem`.
- A geral tem `N` slots comuns e mais 4 slots exclusivos para equipados.
- A soma das capacidades das abas nunca passa de `N`; os sobressalentes só
  passam de `N % 6` para uma aba quando ela lota.
- Um stack vazio é removido da geral e da aba.
- O peso total é a soma dos pesos de todas as unidades, inclusive equipados.
- A ordem da geral só muda quando um stack novo é criado (entra no começo)
  ou um stack é removido. Completar um stack existente não muda a posição.

## Arquivos previstos

```text
include/Tipos.hpp
include/Calculadora.hpp
include/Item.hpp
include/ItemStack.hpp
include/Personagem.hpp
include/Inventario.hpp
include/Acoes.hpp
include/Interface.hpp
src/Tipos.cpp
src/Calculadora.cpp
src/Item.cpp
src/ItemStack.cpp
src/Personagem.cpp
src/Inventario.cpp
src/Acoes.cpp
src/Interface.cpp
src/main.cpp
exemplos/etapa1_criacao.txt
exemplos/etapa2_item.txt
exemplos/etapa3_pegar.txt
exemplos/etapa4_abas.txt
exemplos/etapa5_pesquisa.txt
exemplos/etapa6_peso_dinheiro.txt
exemplos/etapa7_consumo_descarte.txt
exemplos/etapa8_equipar.txt
exemplos/etapa9_morte.txt
exemplos/etapa10_completo.txt
```

O comando do `README.md` já compila `src/*.cpp`; criar novos `.cpp` em `src/`
não obriga a mudar o comando. Se algo mudar, atualizo só a seção
"Compilar e executar", sem mexer nas seções escritas por você.

## Etapas

### Etapa 1 — Base, personagem e status

Arquivos: `Tipos`, `Calculadora`, `Personagem` (parte básica), `Interface` e
`main`.

O que entra:

- enums, nomes para exibição e conversão de peso para centésimos;
- criação do personagem com nome, peso máximo, `N` e dinheiro;
- validação de `N` (10 a 999), peso (0,01 a 1000,00) e dinheiro (0 a 9999);
- status mostrando capacidade `N + 4`, dinheiro e peso atual zero;
- opção "Dormir" que encerra o programa.

Teste: `./sistema < exemplos/etapa1_criacao.txt`.

Pronto quando: compila sem warnings, cria o personagem, mostra o status e
dormir encerra.

### Etapa 2 — Item, ItemStack e análise

Arquivos: `Item`, `ItemStack`; atualizar `Calculadora` e `Interface`.

O que entra:

- dados de uma unidade: nome, peso, categoria, raridade, efeito e subtipo;
- cálculo do limite de stack e da identidade do item;
- `ItemStack` com adicionar, remover a última unidade e peso total;
- `operator<` e `operator==`;
- opção temporária "criar item de teste" na interface, que monta um item e
  mostra a análise. Essa opção sai quando o "pegar" existir; a função que
  mostra a análise continua sendo usada depois.

Teste: `./sistema < exemplos/etapa2_item.txt`, com um item simples, um raro,
uma poção e uma arma.

Pronto quando: a análise mostra nome, categoria, raridade, consumível,
efeito, subtipo, limite de stack e pesos; um item Lendário ou equipamento
mostra limite 1.

### Etapa 3 — Inventário geral e "pegar"

Arquivos: `Inventario` (primeira versão, só com a geral); atualizar a
`Interface`.

O que entra:

- `std::list<ItemStack> geral`, sempre com o stack novo no começo;
- `adicionar` com preenchimento do menor stack, empate pelo mais novo;
- aceitação parcial por peso: entra o que couber e o resto é recusado;
- bloqueio quando nem uma unidade cabe;
- criação de stack novo quando todos os stacks estão cheios;
- listagem da geral do mais recente para o mais antigo;
- abrir/fechar inventário; pegar abre automaticamente.

Nesta etapa as abas por categoria ainda não limitam slots; o item já guarda a
categoria, mas a divisão de slots fica para a etapa 4. A ordem da geral e as
regras de stack já podem ser testadas.

Teste: `./sistema < exemplos/etapa3_pegar.txt` com 35 itens simples iguais,
uma arma e um item pesado.

Pronto quando: 35 itens simples viram um stack de 30 e outro de 5; a arma
ocupa um slot sozinha; a geral mostra o mais recente primeiro; pedir uma
quantidade que não cabe aceita só a parte possível e avisa o resto.

### Etapa 4 — Abas por categoria, divisão de slots e ordenação

Arquivos: `Inventario` (completar) e `Interface`.

O que entra:

- `std::map<Categoria, std::vector<ItemStack*> > abas`;
- divisão `N / 6` por aba e `N % 6` como sobressalentes;
- uso de sobressalente quando uma aba lota;
- ordenação alfabética com `std::sort` e `operator<`;
- seleção de aba e listagem;
- itens iniciais na criação usando o mesmo `adicionar`, com aviso e
  continuação em caso de item inválido.

Teste: `./sistema < exemplos/etapa4_abas.txt`, colocando itens em todas as
categorias, enchendo uma aba e usando um sobressalente.

Pronto quando: cada item aparece na aba certa e na geral; as abas ficam em
ordem alfabética; a soma dos slots ocupados das abas bate com os stacks
comuns da geral; a aba cheia sem sobressalente bloqueia o item.

### Etapa 5 — Pesquisa e análise

Arquivos: `Tipos` (normalização), `Inventario` (`pesquisar`) e `Interface`.

O que entra:

- normalização de nome: minúsculas e acentos comuns do português;
- pesquisa por prefixo na aba atual, inclusive a geral;
- uma linha por identidade com a quantidade total na aba;
- quando o nome é exato, mostrar também cada stack e sua quantidade;
- itens equipados só aparecem na busca da geral;
- análise completa de um item, bloqueada para equipados.

Teste: `./sistema < exemplos/etapa5_pesquisa.txt` com "Poção de Vida",
"Poção de Mana" e buscas parciais como "poc", "POCAO" e "poção".

Pronto quando: a busca ignora maiúsculas e acentos, mostra todos os stacks,
sugere a geral quando o item não está na aba categorizada e a análise mostra
os campos de `[IA-12]`.

### Etapa 6 — Dinheiro, peso e alertas

Arquivos: `Personagem`, `Calculadora` e `Interface`.

O que entra:

- ganhar dinheiro até 9999, descartando o excedente e avisando;
- gastar dinheiro, bloqueando se faltar saldo e avisando quando zera;
- status completo: peso máximo, capacidade, slots comuns, slots equipados,
  peso total, dinheiro e limiar atual;
- avisos de 25%, 50%, 75% e 100% ao subir, e de redução ao descer;
- o aviso usa o maior limiar no aumento e o menor limiar ultrapassado na
  redução, sem repetir mensagens;
- em 100%, aviso de cansaço: não pode atacar, correr nem pegar.

Teste: `./sistema < exemplos/etapa6_peso_dinheiro.txt`, subindo e descendo
pelos limiares e testando 9900 + 200 moedas e gasto maior que o saldo.

Pronto quando: os avisos aparecem só quando o limiar muda, o dinheiro para em
9999, o saldo zero é avisado e a carga em 100% bloqueia o "pegar".

### Etapa 7 — Consumir e descartar

Arquivos: `Acoes` (primeira versão) e `Interface`.

O que entra:

- consumo de uma unidade por ação, só para Comidas e Poções;
- escolha do stack com menor quantidade; empate pelo mais novo;
- remoção da unidade mais recente do stack e desconto do peso dela;
- aviso de 20% de vida, 20% de mana ou os dois;
- descarte com confirmação;
- descarte de uma unidade, de todos ou de uma quantidade escolhida;
- descarte do stack mais recente primeiro e, dentro dele, da unidade mais
  recente;
- bloqueio se a quantidade não existir ou se o item estiver equipado.

Teste: `./sistema < exemplos/etapa7_consumo_descarte.txt` com poções de vida
e mana, um stack cheio e um item lendário.

Pronto quando: cada consumo gera um aviso, o stack diminui de um em um, o
descarte desconta o peso certo e o item some da geral e da aba quando o stack
fica vazio.

### Etapa 8 — Equipar e desequipar

Arquivos: `Personagem` (mapa de equipados), `Inventario` (helpers de aba),
`Acoes` e `Interface`.

O que entra:

- mapa de 4 slots: arma, capacete, peitoral e calça;
- equipar arma substitui a arma atual, independentemente do subtipo;
- equipar armadura substitui só a peça do mesmo slot;
- troca: o novo sai da aba, o antigo volta para a aba e os dois continuam na
  geral, sem mudar a ordem dela;
- equipados contam na geral e no peso, mas não na aba categorizada;
- desequipar exige vaga na geral comum e na aba da categoria, ou sobressalente;
- análise, descarte e equipar bloqueados para item equipado;
- busca na geral mostra equipados; busca na aba categorizada não;
- itens iniciais equipados na criação, usando o fluxo normal de equipar.

Teste: `./sistema < exemplos/etapa8_equipar.txt` equipando espada, lança,
capacete e calça; trocando a arma; desequipando; enchendo a geral para
bloquear o desequipamento.

Pronto quando: a troca mantém a quantidade de slots, a ordem da geral não
muda, o antigo volta para a aba certa, os 4 slots exclusivos são respeitados
e o desequipamento sem espaço é bloqueado com aviso.

### Etapa 9 — Morrer, dormir e limpar tudo

Arquivos: `Interface` e ajustes de limpeza.

O que entra:

- "Morrer" apaga personagem, inventário, itens, dinheiro e equipamentos;
- depois da morte, perguntar se quer criar outro personagem ou encerrar;
- "Encerrar" só existe nesse fluxo pós-morte;
- "Dormir" faz a mesma limpeza total, escreve a mensagem de encerramento e
  fecha o programa;
- reset seguro: limpar primeiro o mapa de equipados do `Personagem` e depois
  o `Inventario`, para não sobrar ponteiro para item apagado.

Teste: `./sistema < exemplos/etapa9_morte.txt` com morte e novo personagem,
morte e encerramento, e dormir no meio de um inventário cheio.

Pronto quando: nenhum dado do personagem antigo aparece no novo, o programa
encerra nos dois fluxos e não fica ponteiro inválido.

### Etapa 10 — Validações finais e exemplos completos

Arquivos: `Interface`, `Tipos`, `exemplos/*.txt` e ajustes pequenos.

O que entra:

- nome do item com no máximo 99 caracteres sem contar espaços; nome do
  personagem com no máximo 10;
- peso entre 0,01 e 1000,00, com arredondamento para duas casas;
- quantidade de pegar maior que zero;
- categoria, raridade, subtipo e efeito só por menu válido;
- mensagem clara quando o bloqueio é por peso, por inventário cheio ou pelos
  dois;
- itens iniciais inválidos não impedem os próximos de serem analisados;
- revisão das regras de `[IA-1]` a `[IA-21]`;
- arquivo de exemplo completo com criação, itens iniciais, pegar, pesquisar,
  analisar, consumir, descartar, equipar, desequipar, dinheiro, peso, morte e
  novo personagem.

Teste: rodar todos os arquivos de `exemplos/` e conferir as saídas.

Pronto quando: compila com `-Wall -Wextra` sem warnings e todos os exemplos
passam.

## Decisões que preciso confirmar antes da etapa 1

1. **Geral com equipados:** guardar todos os stacks na mesma `std::list`, com
   um `bool equipado`, e o `Personagem` apontar para os equipados. Isso deixa
   a ordem da geral estável e evita cópias. A alternativa é guardar os
   equipados separados e montar a visão da geral na interface.
2. **Peso em centésimos:** guardar `125` para 1,25 kg. Evita erro de soma com
   `double`; a interface continua mostrando e lendo decimais.
3. **Dados gerais:** juntar dinheiro, peso máximo e limiar no `Personagem` e
   deixar as contas na `Calculadora`. Se você quiser uma classe separada só
   para dinheiro/peso, eu divido.
4. **Acentos:** o C++11 padrão não tem normalização Unicode. Vou fazer uma
   tabela manual para os acentos comuns do português (á, à, â, ã, é, ê, í,
   ó, ô, õ, ú, ç). Se aparecer outro caractere, ele fica como está.
5. **Identidade:** nome exato para decidir stack; nome normalizado para
   pesquisa e ordenação. Assim "Poção" e "Pocao" são itens diferentes, mas a
   busca acha os dois.
6. **Nome repetido em ação:** se houver mais de um item com o mesmo nome, a
   interface mostra uma lista numerada e você escolhe. Se houver um só, a
   regra de stack de `[IA-4]` escolhe sozinha.
7. **Análise com pesos diferentes:** mostrar o peso da unidade mais recente e
   o peso total do stack. Se preferir, mostro o menor e o maior peso das
   unidades.
8. **Nome do personagem:** os 10 caracteres contam espaços. No nome do item,
   os espaços não contam os 99, como diz `[IA-14]`.

Se alguma dessas decisões estiver errada, me diga antes de eu começar a
etapa 1.

## Compilar e testar

O comando continua o do `README.md`:

```bash
g++ -std=c++11 -Wall -Wextra src/*.cpp -Iinclude -o sistema
```

Para testar uma etapa:

```bash
./sistema < exemplos/etapa1_criacao.txt
```

Os arquivos de exemplo serão criados junto com cada etapa. Ainda não há
código, então nada foi compilado nesta conversa.

