## Projeto - EDA

## Grupo

| Nome               | Email                          | Github    |
| ------------------ | ------------------------------ | --------- |
| Eduardo Lima Ribeiro     | eduardolimrib@gmail.com | [@Eduardolimr](https://github.com/eduardolimr)             |
| Samuel Barros Borges     | <coloca e-mail aqui>           | [@SamuelMordred](https://github.com/SamuelMordred)  |


## Objetivo
 O objetivo desse projeto é simular o funcionamento de um sistema operacional com processos e buracos na memória por meio de uma lista duplamente encadeada circular, com inserção, remoção e manipulação de memória para tais fins.

## Requisitos

* Listas encadeadas
* Listas circulares
* Alocação dinâmica
* Ponteiros
* Manuseio de arquivos


## Projeto
 Foi implementada uma lista duplamente encadeada circular, com alocação dinâmica para o tamanho limite a ser usado durante o programa como parâmetro inicial dado pelo usuário. Após isso, é apresentado um menu com as opções de adicionar, remover ou imprimir processos, escrever em arquivo e ler em arquivo.


## Diário
| Dia               | Atividade                          | Observações    |
| ------------------ | ------------------------------ | --------- |
| 5/10/2017    | Conceito original do projeto | Dificuldade do escopo do projeto, como seria implementadas todas as funcionalidades. Pesquisa sobre sistemas operacionais e monitoria.            |
| 7/10/2017     | Protótipo base          | Estrutura básica da lista encadeada, ainda sem buracos de memória implementados.   |
| 8/10/2017    | Testes com realocação de memória, base para contador de tempo |  Dificuldades com implementação do contador. Implementação de uma função previsória usando time.h e clock() |
| 10/10/2017 | Ajustes na estrutura da lista | Refazer funções de manipulação de cabeçalho |
| 11/10/2017 | Refatoração do projeto | Reescrita da maior parte das funções do código, passando a limpo vários dos problemas anteriores. |
| 12/10/2017 | Funções de remover, menu e reorganização de buracos. | Função de reorganização de buracos ainda dá problemas. Tentar consertar e ajuda com monitor. |
| 13/10/2017 | Leitura de arquivos, finalização das funções principais | Função de reorganização ainda tem problemas relacionados ao realloc. Foco em terminar a leitura de arquivo e se possível consertar função. |


## Falhas/Limitações
O programa apresenta algumas falhas em algumas partes do mesmo, mais especificamente na função _reOrganize()_ usada para reorganizar os buracos de memória, causadas pela função _realloc()_, sem causa encontrada ainda. Uma potencial solução seria reavaliar como foram feitas as alocações de memórias para encontrar a causa do erro, já que o terminal do compilador não traz informações suficientes para resolvê-lo.


O tamanho mínimo para um processo é de cerca de 17 bytes, que é o tamanho da struct criada para o processo. Logo, se o usuário disponibilizar um número não (múltiplo de 17)+1 (em testes nunca foi possível realocar toda a memória do buraco) os _chunks_ de memória menor que 17 bytes serão inutilizáveis para a alocação de um processo. Uma solução seria avisar ao usuário quando esse caso vá acontecer e alertar que potenticalmente pode estar perdendo o uso de memória no programa.


Outro erro na função reOrganize() está que por vezes ocorre um erro nos apontamentos dos ponteiros e some parte da memória. Uma revisão das relações dos ponteiros poderia ser uma potencial solução para esse problema. 
