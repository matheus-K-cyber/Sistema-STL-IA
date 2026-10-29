# Nome do sistema

Atividade da Unidade 2 de Linguagem de Programação I. Leia `ENUNCIADO.md`
antes de começar.

Uma frase dizendo o que o sistema faz. A descrição completa está em
`DESCRICAO.md`.

Frase: armazenamento de itens e dinheiro, além de ser um gerente de peso e organizador autonomo.

## Arquivos

```text
.
├── AGENTS.md       regras que a IA lê antes de cada pedido
├── DESCRICAO.md    a descrição do sistema, escrita por você
├── ENUNCIADO.md    a atividade
├── PLANO.md        o plano feito com a IA (criado na etapa 3)
├── README.md       este arquivo
├── exemplos/       arquivos de entrada para testar
├── include/        um .hpp por classe
└── src/            um .cpp por classe, mais a interface
```

## Compilar e executar

```bash
g++ -std=c++11 -Wall -Wextra src/*.cpp -Iinclude -o sistema
./sistema
```

Se o comando mudar, atualize esta seção. Na correção eu vou usar o que
estiver escrito aqui.

## Onde uso a STL

Escreva esta seção sem IA. Para cada container ou algoritmo da STL que o
sistema usa: em que classe ele está, o que guarda, e por que você escolheu
ele e não outro.

| Onde | O quê | Por quê |
| ItemStack | Guarda os itens(em stacks) | Acesso facilitado aos elementos para qualquer 'ação' |
| Personagem | Gerenciamento de 'equipamento' | map é mais organizado e, dada a quantidade consideravel de dados, usar a 'tipagem'(não no sentido convencional de programação, mas algo desse programa) para localiza-lo é mais eficiente |
| Inventario | O list para 'geral', 1º map para as 6 abas e o 2º complementa com a organização interna delas | O list é pela escolha de organização cronologica escolhida, facilitando satisfazer o plano de organização da 'Aba geral'; 6 abas separadas por categorias, map acaba por se encaixar perfeitamento ao cenario pela sua organização natural que facilita a divisão por abas; cada aba está sujeita a itens diferentes, novamente um cenario em que map se encaixa pela sua natureza, além de permitir a organização com 'itens em stack' |
| | | |

## Como usei a IA

Escreva com as suas palavras:

- Modelo usado: 
Big Pickle e DeepSeek V4.1 Flash(opção: max).

- Um pedido que deu certo, e por que você acha que deu certo:
O pedido do PLANO.md feito com o DeepSeek, apesar de passar de 500 linhas, estava muito bem organizado, simples de ler e compreender, e eu acredito que deu certo pelas restrições postas no pedido em seguir fielmente o DESCRICAO.md e AGENTS.md, e por causa da qualidade do modelo.

- Um pedido que deu errado, o que veio errado e como você mudou o pedido:
A ultima analise do DESCRICAO.md, com a IA insistindo em erros que haviam sofrido correção, erros que mais soaram como perguntas da IA do que erros propriamente dito. Exigi(no pedido) separação clara sobre oque ela poderia resolver sozinha de forma simples e oque eu deveria fornecer(as que exigiam uma resposta minha de forma direta), e, após as respostas, que ela separasse uma secção com os tópicos que esclareciam o necessário(sinalizando que oram feitos puramente por IA).

- Uma coisa que a IA sugeriu e você recusou, e por quê:
Foi algo mais indireto onde, na primeira parte de PLANO.md ela não usou nenhum list ou map, recusei pois, além de ser um pré-requisito no documento do projeto, eu já tinha uma ideia de onde queria map's e list's dada a forma como planejei o projeto no DESCRICAO.md, pois list seria usado para adiantar organizações por 'cronologia' e a retirada seguindo o mesmo, e como fiz 'camadas' no Inventario(as abas, 'tipagens', categorias, raridades, sub tipos de categoria de armas e armadura e os consumiveis), o map seria perfeito para um gerenciamento mais tranquilo do sistema sem uma necessidade de um código mais complexo, usando ponteiros(de maps) como chave para facilitar as ações do sistema.