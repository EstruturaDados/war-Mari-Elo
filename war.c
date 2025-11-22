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

// --- Definição da Struct ---
typedef struct
{
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// --- Banco de Missões (Constante Global para facilitar o exemplo) ---
const char *LISTA_MISSOES[] = {
    "Dominar todos os territorios",
    "Ter pelo menos 50 tropas no total",
    "Conquistar o territorio base (Indice 0)"};
const int TOTAL_MISSOES = 3;

// --- Protótipos das Funções ---
void cadastrarTerritorios(Territorio *mapa, int qtd);
void exibirMapa(Territorio *mapa, int qtd);
void atribuirMissao(char **missaoDestino);
void atacar(Territorio *atacante, Territorio *defensor);
int verificarMissao(char *missao, Territorio *mapa, int qtd, char *corJogador);
void liberarMemoria(Territorio *mapa, char *missao);

// --- Função Principal ---
int main()
{
    srand(time(NULL));

    Territorio *mapa = NULL;
    char *missaoDoJogador = NULL; // Ponteiro para a string da missão
    char corDoJogador[10];
    int qtdTerritorios, opcao;
    int jogoAtivo = 1;

    printf("=== WAR: O DESAFIO FINAL ===\n");

    // 1. Configuração Inicial
    printf("Escolha a sua cor (ex: Azul, Vermelho): ");
    scanf("%s", corDoJogador);

    printf("Quantos territórios existem no mapa? ");
    scanf("%d", &qtdTerritorios);

    // 2. Alocação Dinâmica do Mapa
    mapa = (Territorio *)calloc(qtdTerritorios, sizeof(Territorio));
    if (mapa == NULL)
        return 1;

    cadastrarTerritorios(mapa, qtdTerritorios);

    // 3. Atribuição de Missão (Alocação Dinâmica da String)
    // Passamos o endereço do ponteiro (&missaoDoJogador) para alterá-lo
    atribuirMissao(&missaoDoJogador);

    printf("\n[SECRETO] Sua Missão: %s\n", missaoDoJogador);
    printf("Pressione ENTER para começar...");
    getchar();
    getchar(); // Pausa para leitura

    // 4. Loop do Jogo
    while (jogoAtivo)
    {
        exibirMapa(mapa, qtdTerritorios);

        printf("\n--- MENU ---\n");
        printf("1. Atacar\n");
        printf("2. Ver minha missão\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
        {
            int idAtq, idDef;
            printf("ID do Atacante: ");
            scanf("%d", &idAtq);
            printf("ID do Defensor: ");
            scanf("%d", &idDef);

            // Validações básicas
            if (idAtq >= 0 && idAtq < qtdTerritorios && idDef >= 0 && idDef < qtdTerritorios)
            {
                // Verifica se o jogador é dono do atacante
                if (strcmp(mapa[idAtq].cor, corDoJogador) != 0)
                {
                    printf("Erro: Voce so pode atacar com exercitos %s!\n", corDoJogador);
                }
                else if (strcmp(mapa[idAtq].cor, mapa[idDef].cor) == 0)
                {
                    printf("Erro: Nao pode atacar aliados!\n");
                }
                else
                {
                    atacar(&mapa[idAtq], &mapa[idDef]);

                    // Após o ataque, verifica vitória
                    if (verificarMissao(missaoDoJogador, mapa, qtdTerritorios, corDoJogador))
                    {
                        printf("\n******************************************\n");
                        printf("PARABÉNS! VOCÊ CUMPRIU A MISSÃO: %s\n", missaoDoJogador);
                        printf("VITÓRIA DO EXÉRCITO %s!\n", corDoJogador);
                        printf("******************************************\n");
                        jogoAtivo = 0; // Encerra o loop
                    }
                }
            }
            else
            {
                printf("IDs inválidos.\n");
            }
            break;
        }
        case 2:
            printf("\n[LEMBRETE] Missão: %s\n", missaoDoJogador);
            break;
        case 0:
            jogoAtivo = 0;
            break;
        default:
            printf("Opção inválida.\n");
        }
    }

    // 5. Liberação de Memória
    liberarMemoria(mapa, missaoDoJogador);

    return 0;
}

// --- Implementação das Funções ---

void atribuirMissao(char **missaoDestino)
{
    // Sorteia um índice
    int indice = rand() % TOTAL_MISSOES;

    // Aloca memória exata para a string da missão (+1 para o terminador \0)
    *missaoDestino = (char *)malloc((strlen(LISTA_MISSOES[indice]) + 1) * sizeof(char));

    if (*missaoDestino != NULL)
    {
        strcpy(*missaoDestino, LISTA_MISSOES[indice]);
    }
}

int verificarMissao(char *missao, Territorio *mapa, int qtd, char *corJogador)
{
    // Lógica 1: Dominar todos
    if (strcmp(missao, "Dominar todos os territorios") == 0)
    {
        int contagem = 0;
        for (int i = 0; i < qtd; i++)
        {
            if (strcmp(mapa[i].cor, corJogador) == 0)
            {
                contagem++;
            }
        }
        return (contagem == qtd); // Retorna 1 (verdadeiro) se tiver tudo
    }

    // Lógica 2: Ter 50 tropas
    if (strcmp(missao, "Ter pelo menos 50 tropas no total") == 0)
    {
        int totalTropas = 0;
        for (int i = 0; i < qtd; i++)
        {
            if (strcmp(mapa[i].cor, corJogador) == 0)
            {
                totalTropas += mapa[i].tropas;
            }
        }
        return (totalTropas >= 50);
    }

    // Lógica 3: Conquistar base (índice 0)
    if (strcmp(missao, "Conquistar o territorio base (Indice 0)") == 0)
    {
        return (strcmp(mapa[0].cor, corJogador) == 0);
    }

    return 0;
}

void atacar(Territorio *atacante, Territorio *defensor)
{
    printf("\n>>> Batalha! %s vs %s <<<\n", atacante->nome, defensor->nome);
    int dAtq = (rand() % 6) + 1;
    int dDef = (rand() % 6) + 1;
    printf("Dados: Atq [%d] - Def [%d]\n", dAtq, dDef);

    if (dAtq > dDef)
    {
        printf("Vitoria! Territorio conquistado.\n");
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = atacante->tropas / 2;
        atacante->tropas -= defensor->tropas;
    }
    else
    {
        printf("Derrota! Recuando...\n");
        if (atacante->tropas > 0)
            atacante->tropas--;
    }
}

void cadastrarTerritorios(Territorio *mapa, int qtd)
{
    for (int i = 0; i < qtd; i++)
    {
        // Preenchimento automático para teste rápido (opcional, pode voltar para scanf)
        sprintf(mapa[i].nome, "Territorio_%d", i);
        if (i == 0)
            strcpy(mapa[i].cor, "Azul"); // Garante que o jogador tem um inicio
        else
            strcpy(mapa[i].cor, "Vermelho");
        mapa[i].tropas = 10 + (rand() % 20);
    }
    printf("Territórios gerados automaticamente para teste rápido.\n");
}

void exibirMapa(Territorio *mapa, int qtd)
{
    printf("\nStatus do Mundo:\n");
    for (int i = 0; i < qtd; i++)
    {
        printf("[%d] %s (%s) - Tropas: %d\n", i, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}

void liberarMemoria(Territorio *mapa, char *missao)
{
    if (mapa != NULL)
        free(mapa);
    if (missao != NULL)
        free(missao);
    printf("\nMemória limpa. Jogo encerrado.\n");
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
