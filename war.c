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
// nivel aventureiro
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Definição da Estrutura
typedef struct
{
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// --- Protótipos das Funções ---
void cadastrarTerritorios(Territorio *vetor, int qtd);
void listarTerritorios(Territorio *vetor, int qtd);
void realizarAtaque(Territorio *atacante, Territorio *defensor);
int validarIndice(int indice, int qtd);

int main()
{
    srand(time(NULL)); // Semente para números aleatórios

    Territorio *mapaDoJogo = NULL; // Ponteiro inicializado
    int qtdTerritorios;
    int opcao;

    printf("=== PROJETO WAR: SISTEMA DE BATALHA (ADS) ===\n");
    printf("Quantos territórios deseja criar? ");
    scanf("%d", &qtdTerritorios);

    // ALOCAÇÃO DINÂMICA
    // Usamos calloc para garantir que a memória venha limpa (zerada)
    mapaDoJogo = (Territorio *)calloc(qtdTerritorios, sizeof(Territorio));

    if (mapaDoJogo == NULL)
    {
        printf("Erro crítico: Falha na alocação de memória.\n");
        return 1; // Encerra o programa com erro
    }

    // Etapa 1: Cadastro
    cadastrarTerritorios(mapaDoJogo, qtdTerritorios);

    // Etapa 2: Loop do Jogo (Menu)
    do
    {
        printf("\n--- MENU DE AÇÕES ---\n");
        printf("1. Listar Territórios\n");
        printf("2. Atacar um Território\n");
        printf("0. Sair e Liberar Memória\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            listarTerritorios(mapaDoJogo, qtdTerritorios);
            break;

        case 2:
        {
            int idAtq, idDef;
            listarTerritorios(mapaDoJogo, qtdTerritorios); // Mostra lista para facilitar

            printf("\nDigite o ID do Atacante: ");
            scanf("%d", &idAtq);
            printf("Digite o ID do Defensor: ");
            scanf("%d", &idDef);

            // Validação simples dos índices
            if (validarIndice(idAtq, qtdTerritorios) && validarIndice(idDef, qtdTerritorios))
            {
                // Verifica auto-ataque ou fogo amigo
                if (idAtq == idDef)
                {
                    printf("\n[!] Erro: Não pode atacar a si mesmo.\n");
                }
                else if (strcmp(mapaDoJogo[idAtq].cor, mapaDoJogo[idDef].cor) == 0)
                {
                    printf("\n[!] Erro: Ataque proibido a aliados (mesma cor).\n");
                }
                else
                {
                    // PASSAGEM POR REFERÊNCIA (PONTEIROS)
                    // Passamos o endereço (&) para que a função altere os dados originais
                    realizarAtaque(&mapaDoJogo[idAtq], &mapaDoJogo[idDef]);
                }
            }
            else
            {
                printf("\n[!] Erro: ID de território inválido.\n");
            }
            break;
        }

        case 0:
            printf("Encerrando sistema...\n");
            break;

        default:
            printf("Opção inválida!\n");
        }

    } while (opcao != 0);

    // Etapa 3: Limpeza de Memória (Essencial em C)
    free(mapaDoJogo);
    printf("Memória liberada com sucesso. Até logo!\n");

    return 0;
}

// --- Implementação das Funções ---

void cadastrarTerritorios(Territorio *vetor, int qtd)
{
    for (int i = 0; i < qtd; i++)
    {
        printf("\nConfigurando Território ID [%d]:\n", i);
        printf("Nome: ");
        scanf(" %29[^\n]", vetor[i].nome); // Lê string com espaços
        printf("Cor: ");
        scanf(" %s", vetor[i].cor);
        printf("Tropas iniciais: ");
        scanf("%d", &vetor[i].tropas);
    }
}

void listarTerritorios(Territorio *vetor, int qtd)
{
    printf("\n--- MAPA ATUAL ---\n");
    for (int i = 0; i < qtd; i++)
    {
        // Exibe: ID | Nome (Cor) - Tropas
        printf("[%d] %-15s (%s) \t-> %d tropas\n",
               i, vetor[i].nome, vetor[i].cor, vetor[i].tropas);
    }
}

// Função principal de lógica com PONTEIROS
void realizarAtaque(Territorio *atacante, Territorio *defensor)
{
    printf("\n>>> Batalha: %s (Atq) vs %s (Def) <<<\n", atacante->nome, defensor->nome);

    // Simulando dados (d6)
    int dadoAtq = (rand() % 6) + 1;
    int dadoDef = (rand() % 6) + 1;

    printf("Dados: Atacante [%d] x [%d] Defensor\n", dadoAtq, dadoDef);

    if (dadoAtq > dadoDef)
    {
        printf("Resultado: VITÓRIA DO ATACANTE!\n");
        printf("O território %s foi conquistado pelo exército %s.\n", defensor->nome, atacante->cor);

        // Lógica de conquista:
        // 1. Muda a cor
        strcpy(defensor->cor, atacante->cor);

        // 2. Move tropas (metade avança)
        int tropasMovidas = atacante->tropas / 2;
        defensor->tropas = tropasMovidas;
        atacante->tropas -= tropasMovidas;
    }
    else
    {
        printf("Resultado: DEFESA BEM SUCEDIDA.\n");
        // Penalidade para o atacante
        if (atacante->tropas > 0)
        {
            atacante->tropas--;
            printf("O atacante perdeu 1 unidade na tentativa.\n");
        }
    }
}

// Função auxiliar para validação (Clean Code)
int validarIndice(int indice, int qtd)
{
    if (indice >= 0 && indice < qtd)
    {
        return 1; // Verdadeiro
    }
    return 0; // Falso
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
