# Descrição do sistema

Escreva este arquivo sem IA, antes de qualquer código. Apague as instruções
em itálico quando preencher.

## Nome e ideia

Nome: sistema para inventários de RPG
Oque o sistema faz:
-Ele deve ser um modelo básico para ser usado em qualquer sistema de inventario voltado ao jogos RPG(seguindo padrão de mistico e mineração).
-Ele servirá para organização sobre: oque pode ou não entrar no inventário, quando o mesmo começa a influenciar o peso, acumulação e controle de itens, e emitir alertas/avisos somente.
-Ele deve ser bem acessível e flexível ao jogador(opção para retirar/descartar itens, consumir/usar/buscar itens e acumular alguns).

## O que o sistema guarda

-Itens: possuindo nomes, peso(que vai aumentado a cada unidade que entra no stack/inventário) e caso especial de itens de consumo que recuperem mana e/ou vida(a quantidade de vida ou mana recuperada já é fixa em 20%, o importante é saber se recupera vida ou mana e avisar oque foi recuperado).

-Personagem: possuindo armaduras e arma equipada(ou sem nada equipado) possuindo os tipos de armadura: capacete, peitoral e calças(entenda como que a armadura dos pés já esteja junto das calças, então só ficam esses três espaços/peças), e só uma arma pode ficar equipada(independente se for: ou espada, ou lança, ou arma grande/pesada ou arco/besta), e deve haver o peso que está sendo carregado e peso máximo(em quilo).

-Inventário: deve possuir abas dividindo os itens por categoria(minerios, comidas, poções, armas, unicos/armadura(tanto para peças de armadura como para itens que não se encaixam nas outras abas, até mesmo lendarios) e recursos naturais(madeira, sementes e plantas somente nessa aba)) e uma aba geral(podendo chamar de inventário mesmo) mostrando cada item pego(do mais recente ao mais antigo, e só itens que ainda estão no inventário podem estar ai, itens descartados não podem estar em aba alguma), além de poder ver quanto dinheiro possui, a aba geral não entra na divisão de slots, ela tem o total dado e as outras teram slots a partir da repartição do total da aba geral(ou seja, a aba geral tem o numero maximo de slots escolhido pelo usuario, as outras 6 repartem entre si, e isso não interfere nos slots da aba geral).

## O que dá para fazer

Opções:
-Abrir/Fechar inventário geral e selecionar abas: geral é dos mais recentes aos mais antigos, e caso a opção escolhida seja fechar, deve fechar o inventário imediatamente, já a seleção leva a uma aba filtrada por categoria.

-Pegar: poder pegar itens e, caso haja espaço e não esteja em 100% de carga, levar o item para a mochila/inventario, e o "pegar" deve pegar a quantidade de itens dadas pelo usuario e depois fazer os testes. E o jogador deve informar o nome do item, seu peso(individual), que categoria ele entra, se é uma arma ou armadura, se for consumivel, dizer qual seu efeito e dizer seu tipo(e apenas comidas e poções são consumiveis): se é simples, ou raro ou um lendario, ou mesmo se é uma arma ou que peça é.

-Alternativas filtradas: cada aba possui uma categoria diferente de itens(o inventario geral é a primeira aba que se organiza por ordem de itens mais recentes até os mais velhos, sem ordenar por categoria e ordem alfabetica).

-Pesquisa: poder digitar o nome do item, mesmos itens, como poções, teriam especificação no nome(se é vida ou mana), então todos os itens teriam diferentes nomes e a pesquisa ignora acentuação, maiusculas e minusculas e vai por nome mais proximo do item buscado, mostrando apenas um ou mais(caso o nome esteja incompleto), mas caso hajam mais slots com o mesmo item, deve mostrar também seus stacks e os outros slots quando o nome exato é fornecido. A busca ocorre apenas na aba em que o usuario está usando e deve mostrar todos os itens com o nome(com o nome do item e a quantidade dele no geral, seja na quantidade unitaria em cada slot ou na soma de todos os stacks acumulados).

-Analisar: ver detalhes do item(se é ou não consumível e qual a capacidade individual máxima do item antes que tenha que ocupar mais de um espaço/slot diferente e sua categoria e tipagem), detalhes esses que serão dados pelo usuario(e em relação ao stack, ele será dado com a tipagem, já que cada uma tem um stack máximo).

-Consumir: beber ou comer itens consumíveis ou comestíveis, não havendo essa opção para não consumíveis, e é irrelevante vida ou mana do personagem, a ação deve só consumir o consumível, apagando-o do inventario(o consumo é por unidade, não há como comer/beber/usar algo muitas vezes em uma única ação, e uma unidade do stack é apagada). Usar uma poção de vida ou mana deve apenas notificar/avisar que 20% da vida ou 20% da mana foi restaurada(não havendo necessidade de dados de vida/mana serem acessados pelo inventário), e o aviso é a cada uma poção consumida.

-Equipar/desequipar: tanto para armas como para armaduras, e caso haja uma arma ou peça de armadura equipada(e a peça for do mesmo tipo de peça a qual está tentando ser equipada) a arma ou peça de armadura(que sofre o comando de equipar) deve substituir a arma ou peça antes equipada(e essa é levada a sua respectiva aba e ocupa um slot que fica fazio na aba após o novo item ser equipado), e armas e peças equipadas contam na aba geral, mas não na aba categorizada; não existe aba de equipamentos, mas ainda contam pro peso(tanto arma como armadura); em caso de desequipar, deve haver analise se há espaço no inventario, caso não, não será possível desequipar a peça e/ou arma. Efeitos de armadura são irrelevantes e as peças e armas não stackam(3 armas ocupam 3 slots diferentes e 6 peças ocupam 6 slots diferentes). Equipar(em caso de retirar uma peça que está equipada e levar ela pro inventario) ocupara o espaço da peça(ou até arma) que substituiu ela(ou seja, a antiga peça ou arma ocupa o slot que a nova peça ou arma equipada tinha). E oque estiver em uma aba deve constar no inventario/aba geral.

-Descartar: simplismente tirar um item do inventário, se a capacidade do item é de uma unidade, o descarte é direto(no sentido de não necessitar saber quantos serão descartados daquele slot, pois um item de stack unico no slot somente um dele podera ser descartado, a pergunta de "certeza" ainda ocorrerá), se pode haver mais de uma unidade do mesmo item no mesmo espaço do inventário, pode-se descartar unidade por unidade ou descartar todos ou descartar uma quantidade de preferencia.

-Dormir: deve imprimir uma mensagem de encerramento do programa e em seguida encerrar o programa.
-Morrer: o usuario avisa e isso ocasiona no apagamento do personagem e tudo relacionado ao seu inventario(incluindo itens), depois deve ser questionado se quer criar um novo personagem ou encerrar o programa.
-Encerrar: usado somente após o usuario dizer que seu personagem morreu e após o apagamento e avisos de erradicação dos dados do personagem morto.

## Regras

-O usuario criará o personagem(onde as coisas basicas devem ser dadas: peso máximo que suporta, tamanho total do inventário, se tem ou não itens no inventario, e se sim, quais). Caso o personagem morra, as opções são encerrar o programa ou crirar um novo personagem.

-Itens distintos(considerando nome, tipo e categoria) não podem ocupar o mesmo espaço/slot.

-Tipagens de item: simples podem ser stackados em até 30 em um slot, no máximo; um raro podem ser stackados em até 20; equipamentos e lendarios não stackam(ambos tipagens para itens que ocupam slots sem stackar no mesmo); os stacks de cada tipo são fixos(o usuario não pode alterar) e qualquer item pode receber qualquer tipagem(quem da a tipagem é o usuario), podendo haver tanto uma comida lendaria como peça ou arma lendaria, isso não interfere na categoria. O caso especial são armas e equipamentos, independente da tipagem, uma arma ou peça sempre ocupará um stack no slot(arma ou equipamento não são tipagens como as outras tres, mas apenas duas categorias de itens).

-Descartar abre antes uma pergunta de certeza(para o jogador ter certeza se deseja descartar o item), isso serve para item acumulativos e itens que ocupem um slot por unidade("não-stackaveis").

-O preço máximo de dinheiro deve ser 9999, não pode passar disso, e o minímo é 0.

-Um inventário só pode ter, no máximo, 999 de capacidade máxima e 10 de mínima(os 4 a mais não contam nesses limites, por causa do seu nivel de exclusividade para equipados e somente para a geral), e o peso do item aumenta a cada unidade(um item de 5kg unidade pesa 5kg, então no mesmo slot se houver 10 unidades, o slot pesará 50kg, o peso vale por unidade, aumentando conforme mais itens, incluso unidades que possam stackar, a não ser que o item seja dado com outro peso, mas de qualquer forma deve-se somar todos os pesos do stack para que esse valor seja contabilizado no valor de peso atual).

-O número máximo de caracteres que podem ser postos na opção de pesquisa(e no nome do item) é 99(no caso, um item pode ter um nome de até 99 caracteres, espaços não contam).

-Cada item só pode possuir uma categoria principal(essa é levada em conta na divisão de abas).

-O inventário(geral) deve ser organizado em ordem do mais recente ao mais antigo, já as abas devem seguir uma ordem alfabética, caso um, ou mais, item(ns) estejam com um(ou mais) stack(s) cheio(s) e com outros(iguais) ocupando slot, mostre-os todos também.  A prioridade de ordenação é a ordem alfabetica.

-Caso o personagem esteja morto/morra(avisado pelo jogador se está vivo ou morto), seu inventario e dados devem ser apagados(não podendo ressuscitar). o usuario pode informar a qualquer momento que o personagem morreu(e além de apagar tudo do inventario, questiona o usuario se ele deseja criar um personagem novo ou encerrar o gerenciamento da mochila).

-Peso: aceita decimal, mas limite são duas casas(usasse a regra básica de arredondamento para decimais que sejam resumidos a duas casas a direita da vírgula, arredonde tanto o peso do item individual, como peso total do stack e peso total da mochila). Caso especial(envolvendo carga): se o peso está proximo do limite e um item corresponde a um peso que, se entrar, ultrapassaria o peso maximo, um alerta é ativado e impresso(além de um bloqueio da ação), onde não pode pegar determinado item devido ao peso total atual. Se um item é dado e já tem um ou mais em stack e este também é igual, mas possui peso diferente, o item deve entrar da mesma forma no stack, e seu peso será somado aos outros(mesmo fugindo do padrão dos mesmos itens). O peso total é a soma de todos os pesos dos itens(com capacidade 1 de stack ou esteja sozinho) e stacks. O peso que o usuario passará é o peso máximo(nada pode ultrapassar os 100%).

-Uma aba equivale a um container(mas o inventario geral é um caso a parte pois sua organização deve ser do item mais recente até o item mais antigo adicionado, onde os mais recentes ficam no inicio e os mais antigos no fim), e o inventário não intefere em coisas além dele, que é basicamente qualquer coisa que não esteja relacionada a armazenamento, peso e equipamentos equipados(dando no máximo avisos). E um slot deve ocupar de 1 até 30(e os limitadores devem ser com base nas limitações de stack de cada tipo possível de item).

-O usuario fornece os itens e a divisão de categoria deve ser feita com base na categoria que o usuario escolher(já necessitando a existencia de containers com as abas categorizadas, e caso a categoria dada não exista, deve haver um aviso de que a categoria dada bão existe). O item deve ser primeiro catalogado pelo sistema(trabalho das funções das classes e sendo repassado e recebido pela interface) e só depois considerado pego(repassando para a aba geral e também para a aba especifica), esse catalogo deve ocorrer logo após repasse das informações(passando também pelos testes para validar sua adição ao inventario) e só depois é "pego"/adicionado de vez ao inventario e a sua aba.

-O tamanho do inventário geral(dado pelo usuario, mas possui 4 slots a mais do que for dados, porém sao slots exclusivos para equipados, não podem ser doados e não entram na conta de divisão que define slots das catalogadas e sobressalentes) deve ser repartido igualmente entre as abas de categoria(mas o inventario em si não entra na divisão, ele é apenas uma "janela"/acesso geral para mostrar e acessar itens, portanto a divisão das 6 abas não interfere na capacidade da aba geral), em caso de numero que não reparta igualmente entre todas as abas, pode deixar o(s) espaços a mais apenas no inventário, e caso uma aba lote seus slots, o espaço sobressalente deve ser dado a aba lotada. Em suma: o inventario/aba geral tem todos os itens pegos, nas abas também terão, mas apenas os encaixados na categoria de determinada aba; o numero de slots total é o valor total do inventário, a repartição é apenas entre as abas catalogadas(mas cada slot ocupado deve contar como um slot ocupado na aba geral também, já que a aba geral detem o exato numero de slots total e deve ter todos os itens), em caso de divisão que não divida igualmete entre as abas, tira o resto e deixa na aba geral, onde de lá pode ser dado esses slots sobressalentes a uma aba lotada e que receberá outro item nela.

-Tudo que estiver em comidas e poções deve ser considerada como consumivel(e apenas essas categorias possuem consumiveis e podem ser consumiveis), o usuario informa se o item ou poção é para mana ou vida ou ambos, e no momento que entrar como poção ou comida, o item deve ser considerado um consumivel.

-Dinheiro: assim como há indicador de que ganhou, o usuario também pode avisar que gastou ou perdeu(qualquer um deve ser aceito) dinheiro, dando em seguida a quantia.

## Quando algo dá errado

-Caso o nome digitado não exista, o sistema deve notificar a inexistência dele.

-Caso uma aba fique cheia, se necessário e possível, ela pode ganhar um slot sobressalente com base nos slots maximos mostardos na aba geral(como a geral possui o maximo possivel de slots, até os sobressalentes, o sistema pode permmitir que essa aba tenha mais um slot ou mais de um se necessario), isso deve ocorrer caso um item vá para essa aba e haja um espaço vazio disponivel, qualquer aba(com excessão do inventario) está propensa a receber um slot vazio. Mas o numero de slots não pode passar do maximo possivel(ou seja, a soma do numero de slots das seis abas não deve passar no numero de slots da aba geral que detem o maximo possivel de slots). Caso não hajam slots sobressalentes(houve distribuição igualitaria) deve haver um aviso de que o inventario esta cheio e o item não pode ser pego(havendo também um bloqueio do sistema para isso).

-Caso o nome exceda 99 digitos, o sistema não pode permitir que mais de 99 sejam escritos, bloqueando e notificando o usuário da capacidade máxima atingida.

-Não se pode fazer nada com um container vazio(além de preenchê-lo), e não pode acessar algo(e nem há) que não esteja nesse container, apenas os espaços nele para preencher(e apenas preenchido é possivel usar mais ações).

-Caso o inventário esteja cheio ou a carga já esteja em 100%, um aviso alerta que nâo é possível pegar o item, deixando claro se é devido a carga ou inventario cheio, em caso de ambos, notifica que a causa são ambos. Isso vale para todas as abas(desde a geral até mesmo as abas categorizadas).

-Caso a carga esteja em 100%, deve haver alerta de cansaço e de que não será possível atacar ou correr(apenas um aviso) e nem pegar itens.

-Caso o dinheiro esteja em 9999, o sistema deve aceitar ainda qualquer dinheiro pego, mas não o somara ao dinheiro guardado(o dinheiro pego a mais deve ser descartado após ser recebido).

## Classes que eu imagino

-Uma classe que receba conteiners e itens, e seja responsavel por analisar e separar os itens nos conteiners(as abas), usando de uma função para receber os itens e analisar para qual aba/container será enviado e se a aba ainda tem espaço.

-Uma classe deve ser responsavel pelo consumo/equipagem/descarte de itens, e sempre, antes de "consumir ou equipar ou descartar", deve testar se esse(s) item(ns) estão no inventário.

-Uma classe responsavel por todos os calculos necessarios para ser usada por qualquer classe(nela os dados que devem entrar são relacionados aos pesos dos slots com itens ou stacks de itens, pro peso total do inventario e calcular para os casos que necessitam comparar valores), deve servir basicamente para qualquer calculo mais trabalhoso ou longo(que não se resolva com poucos passos, mesmo que somas).

-Uma classe deve gerenciar os dados gerais(dinheiro e peso), essa sendo responsável pelos alertas em caso de dinheiro zerado ou se houve ganho de dinheiro(avisado antes pelo jogador se ganhou dinheiro, o 'como' não é relevante), ou peso elevado e notificando, que o personagem está ficando mais lento(a lentidão atingindo o máximo quando o peso total atual se iguala ao peso maximo) ou que esta ficando mais rapido se perder o peso no inventario, e a cada aviso também deve-se notificar que o personagem está mais lento(são apenas avisos). Não se deve repetir as mensagens a cada limite cruzado(seja por aumento ou redução), ela deve sair apenas quando o peso atual chega ou passa de um limite. E em casos que ultrapasse dois/tres limites ou reduza a baixo de dois/tres, use o maior/menor(dependendo se houve um incremento ou redução) para notificar(exemplo: passou de 25% e 50%: mais de 50% do peso maximo; reduziu para algo menor que os 75% e 50%: peso reduziu para menos de 50% do peso maximo).

-Uma classe para receber os dados do personagem e passá-los para as variaveis(e onde haveria os equipamentos e armas equipados pelo personagem, dividindo também que tipo de peça está ou não equipada e que tipo de arma está equipada ou se não há arma equipada, e onde haveria a função responsavel pela troca de equipamentos).

-Uma interface que escreva mensagens e receba dados(recebendo retornos  de funções testes para poder escrever os avisos), podendo chamar as funções de cada classe, passando dados e recebendo e usando os resultados de retorno, também escrevendo avisos em casos de ações, limites, erros de busca e os outros erros. É a interface que questiona e recebe dados de criação, das ações e também escreve os alertas e avisos de ações(repassando os dados para as classes e usando as funções das mesmas para criar, guardar, modificar, receber indicadores e repassar mensagens indicando exito na ação ou aviso/alerta).

## Exemplo de uso

Uso: Personagem aguenta 30kg de peso, seu inventario tem 30 slots e 15 dos 30 estão ocupados(e está carregando 20kg), e possui 110 de dinheiro.
Em tela: "Carga máxima do personagem: 30kg, capacidade do inventario: 30, slots ocupados: 15, peso total da mochila: 20kg(mais de 50% do peso!) moedas: 110."
Uso: buscar algum item que não existe(como buscar um computador).
Em tela: "Este item não está no seu inventário...".
Uso: personagem ganhou 100 moedas.
Em tela: "O personagem ganhou 100 moeadas! agora possui 210 moedas!".
Uso: personagem morreu.
Em tela: "Personagem teve sua vida zerada, agora ele está morto e seus dados serão descartados e inventario esvaziado...".

## Esclarecimentos(tome como "Respostas Absolutas" da descrição)

-A aba geral(ou inventario) é como um deposito, ele tem espaço proprio e nele podemos pegar algo, o mesmo está organizado de forma cronologica(mais recente até mais antigo), as abas seriam como pratilheiras, estas estão filtradas. Portanto, a capacidade maxima de slots fica para o inventario, já as abas teram o tamanho de forma igualitário com base na divisão pela capacidade/tamanho máximo de slots do inventário. E oque estiver em uma aba, deve constar na geral(uma aba com N slots teria 1/N e a geral 1/TAM_MAX).

-A aba de armas é apenas para armas, a de armaduras/unicos é tanto para peças de armadura como itens lendarios que não foram encaixados em nenhuma outra aba(o usuario saberá categorizar os itens).

-O peso individual dos itens(quando já dentro de um stack) devem ser dissolvidos no peso total daquele slot em que o stack está(que é a soma de todos os itens naquela stack). Itens são considerados iguais se tem mesmo nome, mesmo tipo(simples e raro) e fazem parte da mesma categoria. Armas e peças de armaduras não conseguem stackar, um arma ou peça pode ser lendária, mas continuam sem capacidade de stackar. Os limites estabelecidos pelas tipagens devem ser seguidos a risca(independente do item, se for lendário só pode haver um dele no slot), a excessão são armas e peças que independentes da tipagem não stackaram(uma arma ocupa um slot, um capacete um slot, um peitoral um slot e um a calça um slot).

-Se uma arma ou peça vai substituir uma arma ou peça ue já estava equipada, a nova(que será equipada) deixa de ocupar seu slot na aba, e a antiga(antes equipada) passa a ocupar esse slot, armas ou peças equipadas deixam de ser contabilizados nas abas(apesar do número de ocupação se manter o mesmo, já que outra arma ou peça ficará naquela posição), porém tudo(até oque está em status de equipado(assim como o status de consumivel)) está contabilizado na aba geral/inventario(todo item que estivr em uma aba, deve estar e sua presença constar também, na aba geral/inventario).

-O usuario dita qual o status do item(equipado ou não), mas caso ele coloque em comida ou poção, deve-se assumir automaticamente que aquilo é consumivel(não havendo necessidade de esperar esse dado do usuario), e para arma ou armadura que for passada, mas não haver esclarecimento se está equipado ou não, deve-se assumir que não está equipada.

-A cada poção(ou até comida) consumida, deve haver um aviso, se algo recupera vida e mana, um aviso contem ambos(e segue a regra anterior, se consumir N coisas que recuperam vida e mana, então N avisos de que houve restauração de vida e mana).

-Só podem haver as 6 abas/categorias, uma categoria dada que não exista deve emitir um aviso e aquele item não deve entrar no inventario, e nem em nenhuma categoria, até que o usuario escolha uma categoria que exista.

-O usuario dirá a situação inicial de dinheiro(não pode ser um valor negativo). Os itens que ele passar devem passar pelo mesmo tratamento dos itens de "pegar", porém, em casos invalidos(por peso ou categoria inexistente ou tipagem inexistente), deve-se emitir um aviso do erro e aquele item não entra no inventario(mas caso seja um conjunto de itens iguais que stackam, o sistema deve analisar se parte daquela quantia pode entrar no inventario, se sim, aceite a quantidade que cabe e avise a recusa do resto), mas o fluxo de catalogação e adição deve seguir, erro não deve impactar quem já foi analisado e entrou e nem quem será analisado ainda. Não podem existir limitem minimos negativos e os limites máximos ja estabelecidos devem ser seguidos a risca, e não pode haver nada cujo peso seja 0(o minimo seria 0,01 já que vamos considerar apenas duas casas decimais, e o máximo de peso seria até 1000). Quando houver slots sobressalentes, não precisar por eles mo inventario,o inventario possui o numero máximo de slots, portanto apenas deve haver um aviso se houve sobresalentes(se sim, quantos) e, caso um slot sobressalente precise ser dado, ai você apenas o adiciona na aba que o necessita e conta, na aba geral que há um slot em uso(esse sendo o sobressalente). Ou seja, aba geral tem o número máximo de slots fornecido, enquanto as outras 6 dividem entre si o numero total(isso não deve influenciar a capacidade de slots do inventario).

-A pesquisa deve usar do nome e seguir com proximidade(mantendo a trava de ignorar acentuação e maiusculas), além disso, caso seja um item com stack acima de 1, deve mostrar que o item existe e quantos tem(nessa quantidade devem entrar todos que estão na aba), na ordem: nome e quantidade(incluindo todos os slots onde o item sozinho ou em stacks aparece). E o nome buscado deve começar com o texto digitado. Não precisa de uma ordem(caso o nome dado esteja incompleto), a pesquisa deve apenas fornecer ou o item(caso nome completo e um alerta de inexistencia caso o nome nem esteja no inventario) ou os itens com nomes similares.

-Quando o usuario diz que o personagem morreu, tudo relacionado ao personagem deve ser apagado e a interface questionaria se ele deseja fazer um novo personagem ou encerrar(em caso de novo, apenas recomece, mas caso queira encerrar, o programa também deve encerrar).

## Respostas

1- A aba geral é a unica com acesso a capacidade total de slots, pois cada item nas abas também está nela(exemplo: 1/5 itens ocupados em uma aba qualquer, na aba geral ficaria assim: 1/30), e da mesma forma que posso acessar o item na aba categorizada, posso acessar ele na aba geral; trate o "slot que a nova tinha" como um slot vazioem sua respectiva aba(mesmo que não seja exatamente o mesmo, esse slot que surge na troca de peças e/ou armas é apenas um slot que ficou desocupado quando a peça ou arma foi equipada, e é esse slot que deve ser preenchido pela antiga arma ou peça), e trate da mesma forma os "slots sobressalentes", eles não tem um endereço fixo, "slots sobressalentes" é só um termo para slots que não estão em alguma aba categorizada e podem entrara em uma caso necessário(e removi a ideia de slot mais proximo, pode ignorar isso).

2-Nenhuma aba deve chegar a 0 slots, a "doadora" principal é a aba geral(não há redução do numero de abas da geral, a aba que precisa de um slot a mais ganha apenas mais um slot, esse que já existe na principal, ela que fornece abas a mais para qualquer outra), uma aba só ganha uma a mais caso: esteja cheia e um item novo é adicionado a aba geral e será designado a essa aba(e como ele ja esta em um slot da principal, basta dar um slot/espaço a mais para esta que precisa), e as abas sobressalentes ficam na aba geral sem uso até que seja necessario. Mas esse ganho só ocorre se existirem abas sobressalentes(então em casos de divisão igualitaria, não haveria doação em caso de lotação); E sim, a antiga entra na vaga da nova, mas essas mudanças só ocorrem na aba da categoria, nada muda na geral; É permmitido pegar enquanto um stack não encher, visto que um stack de 20 ou 30 ocupa 1 slot da aba categorizada e da geral.

3-Todo item(indepedente de seu status, "tipagem", categorias etc...) conta na aba geral(no minimo), "equipados" seriam esse caso, já que não devem contar na aba de arma ou armaduras, porem ainda estão contabilizados na geral; o efeito não é relevante no stack(apenas para notificação de uso em caso de consumo), então pode guardar pesos e efeitos(de preferencia com algo que esteja atrelado ao item que entrou no inventario), além disso, consumiveis com efeitos diferentes não entram na mesma stack(caso sejam acumulaveis); Para o caso de equipados, fixe no sistema um plus de 4 slots na geral(independente da quantidade máxima), esses 4 são apenas para equipados(ou seja, não são sobressalentes, portanto não podem ser doados e não entram na divisão dos slots para as abas, eles são exclusivos da geral, o numero de slots dividido e de onde podem vim sobressalentes é apenas o numero que o usuario informar).

4-Não há aba para equipados, trate de forma semelhante aos consumidos, mas ao inves de excluir do inventario, voce apenas deixa de contabilizar o(s) equipado(s) na aba categorizada, mas mantem contando na aba geral. Itens equipados não sofrem ação de: analise, descartar e equipar, para qualquer ação com eles é necessario desequipar primeiro. Caso haja o comando de desequipar(sem que uma arma ou peça substitua e ceda lugar) o(s) itens desequipados devem ocupar algum slot em sua respectiva aba(ou seja, exige slot na aba de sua categoria), já que na geral já existem(e sim, como armas e peças não podem stackar, independente do tipo, cada peça e arma ocupa um slot inteiro). E caso a aba estej cheia, na ação de desequipar o sistema deve criar mais um slot para a aba(caso haja slot sobressalente), mas caso não, deve haver um aviso de que não espaço o suficiente para desequipar(assim bloqueando a ação de desequipar); o aviso para recuperação simultanea de vida e mana deve ser unico, avisando que ambos foram recuperados; O peso maximo é definido pelo usuario.

5-O usuario deve ser avisado previamente de "levar o rpg a serio" em relação tanto a montagem do personagem, aquisição dos itens e futuras adições de itens, a partir dai confie totalmente na categoria que ele desejar(ou no caso dele não passar a categoria desse item, o sistema emite um alerta, cancela o pedido do usuario e pede que a categoria seja dada, mostrando as categorias possiveis/existentes para ele); Uma aba categorizada receberá o numero necessario(e possivel) de sobressalentes(estas ficarão com a aba até o fim do programa), então até mesmo um caso de um "pegar" exigir mais de um sobressalente pode fazer o sistema adicionar a quantidade necessaria de sobressalentes a aba em questão, e a aba geral só ficara cheia se todas as categorizadas estiverem cheias(já que todas possuem repartirções de slots do numero maximo, e a geral detem o numero maximo de slots e oque está em uma categorizada, estará na geral).

6-Sim, nome parcial deve mostrar todas as opções aproximadas(usando de medida o prefixo), e a busca ocorre na aba em que o usuario tenha selecionado para ficar naquele momento, isso inclui a aba gerla(caso ele esteja atualmente nela); os 25%/50%/75%/100% são limites ficos(para que não haja necessidade de usar numeros fixos nos avisos).

7-Em casos de redução(ou mesmo aumento) extremo, use o menor limite(no caso de aumento o maior) limite que a carga total atual(soma de todos os pesos no inventario) cruzou(lembrando que 100% não pode ser cruzado e não há peso abaixo de 0%), assim dando apenas um aviso, as comparações é com o valor total atual da carga comparado ao peso máximo do personagem(os 100%/valor maximo de carga), e sempre que o usuario tentar pegar algo que ultrapasse 100%(o maximo de carga suportavel), deve ser emitido o alerta e haver um bloqueio no comando de pegar(não entrando nem no inventario e nem em aba catalogada); Em caso de ações em itens com mais de um stack nos slots, usasse aquele com a menor quantidade nos stacks, mas se todos os stacks estiverem cheios(unica forma de todos os stacks estarem na mesma quantidade, já que para um novo stack começar, outro já deve estar cheio), use o mais novo(o que foi recentemente stackado ao máximo). Em caso de descartar ser usado para todos os itens, todos os stacks devem ser descartados, e em caso de um numero fixo de descarte, deve haver o teste se aquela quantia existe(se não, avisar o usuario que não há aquela quantia e bloqueia-se a ação) e caso exista, o descarte deve ser feito do stack mais recente(mesmo que não esteja cheio) até o restante(se necessario) no stack mais antigo.

8-Se o usuario tentar gastar mais que o saldo, o sistema deve bloquear a ação e emitir o alerta do motivo, o dinheiro é inteiro(trate como moedas genericas sem nenhum tipo de hierarquia de valor como ouro ou prata ou centavos), o alerta de saldo zero deve sair caso o usuario gaste e o saldo crave em zero; A quantidade mostrada deve somar nome + tipo, itens equipadas podem aparecer na pesquisa(mas apenas na aba geral), sim, pode ignorar acentuação e maiusculas/minusculas, focando totalmente em ordem puramente alfabetica, e no caso de um item não encontrado em uma aba categorizada, deve notificar que ele não existe naquela aba(sugerindo o usuario procurar em outra aba ou na geral).

9-Quando o "descarte" é usado em um stack com mais de um item, descarte o mais recém adicionado(avisando o usuario de que foi o mais recente), e separe um container para os pesos, pois o peso do item descartado deve ser descontado tanto do peso total do stack como(por consequência) do peso total atual.

Adicionais: caso a ação de pegar venha com uma quantidade maior(seja extrapolando o stack existente ou os slots) aceite apenas a quantidade que pode entrar sem que passe do peso máximo suportavel, emitindo um aviso de quantos puderam ser pegos e quantos foram largados(do numero de itens que o usuario tentou pegar, ou seja, ele só pega a quantidade que não passe do limite, e caso só um já ultrapasse, não pega nenhum e emite o aviso), ou seja, pegue apenas oque da antes de ou lotar os slots ou atingir o peso maximo(ou se aproximar) ou mesmo ambos os casos ocorrerem, e caso sejam itens stackaveis, pegue até que o stack seja preenchido(e caso não haja mais slot para o resto entrar, descarta esses que não entraram e avisa qiantos ficaram de fora), e tanto faz que slot usar(afinal, oque for catalogado em uma aba também conta na geral); no campo do item(exposto somente na "analise") deve mostrar seu nome, tipagem, se stacka ou não e, em caso de armadura ou arma, que tipo de arma ou peça é; na criação do personagem deve ser pedido nome(maximo de 10 caracteres), dinheiro inicial(mesmo que zero, mas não pode ser negativo e nem extrapolar o limite), a ordem de itens iniciais não influencia em nada no geral, e pode-se começar com algo equipado(sendo necessario passar nome, tipagem e, se armadura qual ou quais peças e se for arma qual arma); só pode usar algo com inventario aberto(seja no proprio ou em alguma aba), pegar item ativa o "abrir" do inventario(caso já não esteja aberto), fechar apenas impede interações com os itens armazenados, para parar o programa o usuario tambem pode usar a ação "dormir".

## Ajustes finais aceitos da sugestão de IA

> Origem: as regras desta seção foram acrescentadas com **sugestão de IA permitida e aceita pelo autor**. Em caso de conflito com o texto anterior, valem estas regras.

### [IA-1] Slots de itens comuns e equipados

A aba geral tem `N` slots para itens comuns e mais 4 slots exclusivos para itens equipados, totalizando `N+4`. Os 4 slots de equipados não entram na divisão entre as abas, não podem ser doados e não podem ser usados por itens comuns. Ao desequipar, o item precisa de vaga na aba da sua categoria; se não houver vaga nem slot sobressalente, a ação é bloqueada.

### [IA-2] Peso em stack com pesos diferentes

Cada unidade ou lote adicionado guarda o próprio peso. O peso do stack é a soma dos pesos das unidades que estão nele. Ao consumir ou descartar, retira-se primeiro a unidade mais recente do stack escolhido e desconta-se o peso dessa unidade do stack e do peso total.

### [IA-3] Pegar quantidade parcial

Se o usuário pedir uma quantidade que não cabe inteira, entra a maior quantidade que couber sem ultrapassar o peso máximo nem os slots. A interface informa quantos entraram e quantos ficaram de fora. Se nem uma unidade couber, a ação é bloqueada e o item não entra.

### [IA-4] Ordem dos stacks nas ações

- Pegar: completa primeiro o stack com menor quantidade; se houver empate, usa o mais novo.
- Consumir: usa o stack com menor quantidade; se houver empate, usa o mais novo.
- Descartar: usa o stack mais recente; se precisar de mais unidades, continua no próximo stack mais recente.
- Em todos os casos, dentro do stack sai primeiro a unidade mais recente.

### [IA-5] Identidade do item

Dois itens são iguais quando têm o mesmo nome, a mesma categoria, a mesma raridade, o mesmo efeito (quando consumível) e o mesmo subtipo (quando arma ou armadura). O peso não faz parte da identidade. Exemplos: "Poção" de vida e "Poção" de mana não stackam; uma arma e uma peça de armadura de mesmo nome são distintas.

### [IA-6] Troca de equipamento

Equipar uma arma sempre substitui a arma atualmente equipada, mesmo que o subtipo seja diferente. Equipar uma armadura substitui apenas a peça do mesmo slot (capacete, peitoral ou calça); peças de slots diferentes coexistem. A peça ou arma antiga ocupa o slot que o novo item deixou na aba da categoria.

### [IA-7] Limites do peso máximo do personagem

O peso máximo do personagem deve ficar entre 0,01 kg e 1000,00 kg, com no máximo duas casas decimais.

### [IA-8] Dinheiro acima de 9999

Ao ganhar dinheiro, soma-se até o limite de 9999 e o excedente é descartado. Exemplo: 9900 + 200 resulta em 9999; 101 moedas são descartadas.

### [IA-9] Limiares de peso

Os limiares 25%, 50%, 75% e 100% são atingidos quando o peso total é maior ou igual ao valor (`>=`). A mensagem deve usar "25% ou mais", "50% ou mais", etc. O limiar de 100% continua bloqueando o ato de pegar.

### [IA-10] Ordem da aba geral ao completar stack

Quando uma unidade entra em um stack que já existe, o stack permanece na posição antiga da aba geral. Apenas um stack novo é colocado no início (mais recente).

### [IA-11] Resultado da pesquisa

A pesquisa mostra uma linha por identidade de item (nome + raridade + efeito/subtipo, conforme [IA-5]) com a quantidade total encontrada na aba. Quando o nome exato é pesquisado, também lista cada stack/slot com sua quantidade. Itens equipados aparecem apenas na aba geral.

### [IA-12] Campos da análise

A análise mostra nome, categoria, raridade, se é consumível, efeito (se houver), se stacka, limite máximo do stack, peso unitário e, para arma ou armadura, o subtipo.

### [IA-13] Entrada por menu

Categoria, raridade e subtipo de arma/armadura são escolhidos por menu numerado na interface, para evitar erro de acento, plural ou nome inválido.

### [IA-14] Nome do item

Espaços são permitidos no nome do item e não contam no limite de 99 caracteres.

### [IA-15] Quantidade ao pegar

A quantidade informada em "pegar" deve ser um número inteiro maior que zero. Zero ou negativo é rejeitado com aviso e nada é adicionado.

### [IA-16] Dormir e encerrar

"Dormir" pode ser usado a qualquer momento. "Encerrar" só pode ser usado depois que o personagem morre e seus dados são apagados.

### [IA-17] Definição de N e slots exclusivos (adição de IA)

- `N` é o "tamanho total do inventário" passado na criação e corresponde **apenas** aos slots para itens comuns. 
- A aba geral possui `N` slots para itens comuns + **4 slots exclusivos para itens equipados**, totalizando `N+4`. 
- Os **4 slots exclusivos** não entram na divisão entre as 6 abas categorizadas, não podem ser doados, não podem ser usados por itens comuns e não contam nos limites de mínimo/máximo citados para "inventário" (regra 57). 
- Itens equipados ocupam **obrigatoriamente** esses 4 slots exclusivos; eles ficam vazios até que algo seja equipado.

### [IA-18] Divisão, resto e sobressalentes (adição de IA)

- Os `N` slots comuns são divididos **igualmente** entre as 6 abas categorizadas. 
- Caso a divisão não seja exata, o **resto não é somado à aba geral**. Ele é guardado como **sobressalentes disponíveis** para as abas categorizadas. 
- Quando uma aba categorizada ficar cheia e houver sobressalentes disponíveis, ela pode receber slots adicionais (um ou mais, conforme necessário) vindos desse resto guardado. Esses sobressalentes ficam com a aba até o fim do programa. 
- Se não houver sobressalentes (divisão igualitária), não há doação em caso de lotação e, se não couber, o item não entra com aviso de inventário cheio. 
- A soma das abas categorizadas pode crescer com sobressalentes, mas **não pode ultrapassar** o número de slots da aba geral referentes aos comuns (`N`); os 4 slots exclusivos nunca são usados para isso.

### [IA-19] Comportamento de Dormir/Encerrar (adição de IA)

- **Dormir** pode ser usado a qualquer momento. Ao usar "Dormir", o programa deve executar **exatamente o mesmo processo de limpeza total** que "Encerrar" faria após a morte (apagar personagem, apagar inventário e todos os dados relacionados), imprimir a mensagem de encerramento e **encerrar o programa**.
- **Encerrar** só pode ser usado depois que o personagem morre, seus dados já foram apagados e a pergunta pós-morte já foi tratada. É o comando que indica o encerramento do programa nesse fluxo pós-morte.

### [IA-20] Alocação e stack com pesos diferentes (adição de IA - prático)

- Ao adicionar uma unidade com peso diferente a um stack já existente (mesma identidade conforme [IA-5]), ela entra no mesmo stack. O peso do stack passa a ser a **soma** dos pesos de todas as unidades nele ([IA-2]). Para simplificar a implementação, trate o stack como uma coleção de unidades em ordem (mais recente no topo/última adicionada) para saber qual unidade sai primeiro em consumir/descartar.
- Para ações ([IA-4]): **pegar** prioriza completar stack com menor quantidade (empate -> mais novo); **consumir** usa stack com menor quantidade (empate -> mais novo); **descartar** usa stack mais recente primeiro. **Dentro do stack, sempre sai a unidade mais recente**.

### [IA-21] Categoria obrigatória e consistência (adição de IA)

- Categoria, raridade e subtipo (arma/armadura) **devem** ser escolhidos por **menu numérico** na interface ([IA-13]). 
- Se a categoria informada não existir entre as 6 categorias válidas, o sistema emite aviso, **cancela a ação de pegar/adicionar** e pede para escolher uma categoria válida. O item não entra no inventário nem em nenhuma aba até que uma categoria válida seja fornecida.
- Apenas **comidas e poções** são consumíveis. Armas e peças de armadura **não stackam** independente da raridade. Itens equipados ficam nos **4 slots exclusivos** da aba geral e **não** são contabilizados nas abas categorizadas, mas **sempre** contam na aba geral e no peso.