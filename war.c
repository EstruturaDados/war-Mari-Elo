// ============================================================================
//         PROJETO WAR ESTRUTURADO - DESAFIO DE CÓDIGO
// ============================================================================
//
// ============================================================================
//
// OBJETIVOS:
// - Modularizar completamente o código em funções especializadas.
// - Implementar um sistema de missões para um jogador.
// - Criar uma função para verificar se a missão foi cumprida.
// - Utilizar passagem por referência (ponteiros) para modificar dados e
//   passagem por valor/referência constante (const) para apenas ler.
// - Foco em: Design de software, modularização, const correctness, lógica de jogo.
//
// ============================================================================

// Inclusão das bibliotecas padrão necessárias para entrada/saída, alocação de memória, manipulação de strings e tempo.

// --- Constantes Globais ---
// Definem valores fixos para o número de territórios, missões e tamanho máximo de strings, facilitando a manutenção.

// --- Estrutura de Dados ---
// Define a estrutura para um território, contendo seu nome, a cor do exército que o domina e o número de tropas.

// --- Protótipos das Funções ---
// Declarações antecipadas de todas as funções que serão usadas no programa, organizadas por categoria.
// Funções de setup e gerenciamento de memória:
// Funções de interface com o usuário:
// Funções de lógica principal do jogo:
// Função utilitária:

// --- Função Principal (main) ---
// Função principal que orquestra o fluxo do jogo, chamando as outras funções em ordem.

// Nivel novato
// criando estruturando uma struct em C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char nome[50];
    int tropas;
    char cor[10];
} territorio;

int main()
{

    territorio Territorios[5];

    // loop para preencher os dados dos territórios
    for (int i = 0; i < 5; i++)
    {
        // nome do território
        printf("Digite o nome do território %d: ", i + 1);
        fgets(Territorios[i].nome, sizeof(Territorios[i].nome), stdin);
        Territorios[i].nome[strcspn(Territorios[i].nome, "\n")] = '\0'; // remover o \n do final
                                                                        // cor da tropa
        printf("Digite a cor da tropa do território %d: ", i + 1);
        fgets(Territorios[i].cor, sizeof(Territorios[i].cor), stdin);
        Territorios[i].cor[strcspn(Territorios[i].cor, "\n")] = '\0'; // remover o \n do final
                                                                      // número de tropas
        printf("Digite o número de tropas do território %d: ", i + 1);
        scanf("%d", &Territorios[i].tropas);
        getchar(); // limpar o buffer do teclado
    }

    // exibição dos dados dos territórios

    printf("\n=== Dados dos Territórios Cadastrados ===\n");
    for (int i = 0; i < 5; i++)
    {
        printf("\nTerritório %d:\n", i + 1);
        printf("Nome: %s\n", Territorios[i].nome);
        printf("Cor do exército: %s\n", Territorios[i].cor);
        printf("Quantidade de tropas: %d\n", Territorios[i].tropas);
    }

    return 0;
}
// --- Implementação das Funções ---

// alocarMapa():
// Aloca dinamicamente a memória para o vetor de territórios usando calloc.
// Retorna um ponteiro para a memória alocada ou NULL em caso de falha.

// inicializarTerritorios():
// Preenche os dados iniciais de cada território no mapa (nome, cor do exército, número de tropas).
// Esta função modifica o mapa passado por referência (ponteiro).

// liberarMemoria():
// Libera a memória previamente alocada para o mapa usando free.

// exibirMenuPrincipal():
// Imprime na tela o menu de ações disponíveis para o jogador.

// exibirMapa():
// Mostra o estado atual de todos os territórios no mapa, formatado como uma tabela.
// Usa 'const' para garantir que a função apenas leia os dados do mapa, sem modificá-los.

// exibirMissao():
// Exibe a descrição da missão atual do jogador com base no ID da missão sorteada.

// faseDeAtaque():
// Gerencia a interface para a ação de ataque, solicitando ao jogador os territórios de origem e destino.
// Chama a função simularAtaque() para executar a lógica da batalha.

// simularAtaque():
// Executa a lógica de uma batalha entre dois territórios.
// Realiza validações, rola os dados, compara os resultados e atualiza o número de tropas.
// Se um território for conquistado, atualiza seu dono e move uma tropa.

// sortearMissao():
// Sorteia e retorna um ID de missão aleatório para o jogador.

// verificarVitoria():
// Verifica se o jogador cumpriu os requisitos de sua missão atual.
// Implementa a lógica para cada tipo de missão (destruir um exército ou conquistar um número de territórios).
// Retorna 1 (verdadeiro) se a missão foi cumprida, e 0 (falso) caso contrário.

// limparBufferEntrada():
// Função utilitária para limpar o buffer de entrada do teclado (stdin), evitando problemas com leituras consecutivas de scanf e getchar.
