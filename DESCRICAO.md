# Descrição do sistema

Escreva este arquivo sem IA, antes de qualquer código. Apague as instruções
em itálico quando preencher.

## Nome e ideia

Nome: sistema para inventários de personagens em RPG
Oque o sistema faz:
-Ele deve ser um modelo coringa para ser usado em qualquer sistema de inventario voltado ao jogos RPG.
-Ele servirá para organização sobre: oque pode ou não entrar no inventário e quando o mesmo começa a influenciar o peso.
-Ele deve ser bem acessível e flexível ao jogador(opção para retirar/descartar itens, consumir/usar itens e acumular alguns).

## O que o sistema guarda

-Itens: possuindo nomes, quantia máxima de "stack"(acúmulo), valor de venda e caso especial de itens de consumo que recuperem
mana e/ou vida(assim precisando possuir dados que informe quanta vida e/ou mana regeneram).
-Personagem: possuindo vida e mana(numero atual e máximo, com no máximo uma casa depois da vírgula), peso que está carregando e peso máximo(em quilo), e se possui "buffs" e/ou "debuffs".
-Inventário: deve possuir abas dividindo os itens por categoria(minerios, comidas, poções, armas, vestes/armadura e recursos naturais) e uma aba geral mostrando cada item pego(do mais recente ao mais antigo, e só itens que ainda estão no inventário podem estar ai, itens vendidos e descartados não podem estar em aba alguma), além de poder ver quanto dinheiro possui.

## O que dá para fazer

Opções:
-Abrir/Fechar inventário: aba dos mais recentes aos mais antigos, e caso a opção escolhida seja fechar, deve fechar o inventário imediatamente.
-Alternativas filtradas: cada aba possui uma categoria diferente de itens.
-Pesquisa: poder digitar o nome do item ou um número representando quantas unidades há dele(em um único espaço/slot).
-Analisar: ver detalhes do item(se é ou não consumível, efeitos ao consumir ou efeitos ao equipar ou vestir, e qual a capacidade individual máxima do item antes que tenha que ocupar mais de um espaço/slot diferente).
-Consumir: beber ou comer itens consumíveis ou comestíveis, não havendo opção para não consumíveis.
-Equipar: tanto para armas como para armaduras, e caso haja uma arma ou peça de armadura equipada(e a peça for do mesmo tipo de peça a qual está tentando ser equipada) a arma ou peça de armadura(que sofre o comando de equipar) deve substituir a arma ou peça antes equipada(e essa é levada ao inventário).
-Descartar: simplismente tirar um item do inventário(se a capacidade do item é de uma unidade, o descarte é direto, se pode haver mais de uma unidade do mesmo item no mesmo espaço do inventário, pode-se descartar unidade por unidade ou descartar todos).
-Vender: exclusivo para apenas quando o personagem está em uma loja ou comércio(e deve mostrar o valor em moedas do item).

## Regras

-Dois itens distintos(considerando nome e categoria) não podem ocupar o mesmo espaço/slot.
-Descartar/Vender sem antes levantar a pergunta de certeza(para o jogador ter certeza se deseja vender ou descartar o item).
-O preço máximo de dinheiro deve ser 9999, não pode passar disso, e o minímo é 0.
-Pontos de vida e de mana não podem ser menores que 0 e o máximo de cada um é 999.
-Um item só pode ter, no máximo, 99 de capacidade máxima e 1 de mínima, e o peso do item aumenta a cada unidade.
-O número máximo de caracteres que podem ser postos na opção de pesquisa é 99.
-Cada item só pode possuir uma categoria principal(essa é levada em conta na divisão de abas), sub-categorias não são relevantes para a organização de abas.
-O inventário deve ser organizado em ordem alfabética e(levando em conta o número de unidades do item) em ordem crescente(da esquerda para a direita).

## Quando algo dá errado

-Caso o nome digitado não exista, o sistema deve notificar q inexistência dele.
-Caso o nome exceda 99 digitos, o sistema não pode permitir que mais de 99 sejam escritos, bloqueando e notificando o usuário da capacidade máxima atingida.
-Não se pode fazer nada com um container vazio(além de preenchê-lo), e não pode acessar algo que não esteja nesse container.

## Classes que eu imagino

Uma classe que receba conteiners e itens, e seja responsavel por analisar e separar os itens nos conteiners(as abas).
-Uma classe deve ser responsavel pelo consumo/equipagem/venda/descarte de itens, e sempre, antes de "consumir ou equipar ou vender ou descartar", deve testar se esse(s) item(ns) estão no inventário.
-Uma classe deve gerenciar os status gerais(buffs, debuffs, vida, mana, dinheiro e peso), essa sendo responsável pelos alertas em caso de vida zerada ou próxima do fim, ou dinheiro insuficiente para compra ou peso elevado e notificando, a cada 25% do peso total sendo atingido, que o personagem está ficando mais lento(a lentidão atingindo o máximo em 100%).
-Uma classe para receber os dados do personagem e passá-los para as variaveis.


## Exemplo de uso

Uso: Personagem tem 60 de vida, aguenta 30kg de peso, seu inventario tem 30 slots e 15 dos 30 estão ocupados, e possui 110 de dinheiro.
Em tela: "Vida máxima: 60, carga máxima do personagem: 30kg, capacidade do inventario: 30, slots ocupados: 15, moedas: 110."
Uso: buscar algum item que não existe(como buscar um computador).
Em tela: "Este item não está no seu inventário...".
Uso: personagem cai e toma 999 de dano.
Em tela: "Personagem teve sua vida zerada, agora ele está morto e seus dados serão descartados e inventario esvaziado..."