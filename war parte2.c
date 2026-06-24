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
// int main() {
    // 1. Configuração Inicial (Setup):
    // - Define o locale para português.
    // - Inicializa a semente para geração de números aleatórios com base no tempo atual.
    // - Aloca a memória para o mapa do mundo e verifica se a alocação foi bem-sucedida.
    // - Preenche os territórios com seus dados iniciais (tropas, donos, etc.).
    // - Define a cor do jogador e sorteia sua missão secreta.

    // 2. Laço Principal do Jogo (Game Loop):
    // - Roda em um loop 'do-while' que continua até o jogador sair (opção 0) ou vencer.
    // - A cada iteração, exibe o mapa, a missão e o menu de ações.
    // - Lê a escolha do jogador e usa um 'switch' para chamar a função apropriada:
    //   - Opção 1: Inicia a fase de ataque.
    //   - Opção 2: Verifica se a condição de vitória foi alcançada e informa o jogador.
    //   - Opção 0: Encerra o jogo.
    // - Pausa a execução para que o jogador possa ler os resultados antes da próxima rodada.

    // 3. Limpeza:
    // - Ao final do jogo, libera a memória alocada para o mapa para evitar vazamentos de memória.

   // return 0;
//}

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




// segunda parte do desafio 23/06/26


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Definição da estrutura do Território
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// Protótipos das funções
void cadastrarTerritorios(Territorio* mapa, int total);
void exibirMapa(Territorio* mapa, int total);
void atacar(Territorio* atacante, Territorio* defensor);
void liberarMemoria(Territorio* mapa);

int main() {
    // Inicializa o gerador de números aleatórios com base no tempo atual
    srand(time(NULL));

    int totalTerritorios;
    printf("--- SISTEMA DE GUERRA: ALOCAÇÃO E ATAQUE ---\n\n");
    printf("Digite a quantidade de territórios a cadastrar: ");
    scanf("%d", &totalTerritorios);
    getchar(); // Limpa o buffer do teclado

    if (totalTerritorios <= 0) {
        printf("Quantidade inválida. Encerrando programa.\n");
        return 1;
    }

    // Alocação dinâmica de memória usando calloc (limpa a memória com zeros)
    Territorio* mapa = (Territorio*) calloc(totalTerritorios, sizeof(Territorio));
    if (mapa == NULL) {
        printf("Erro Crítico: Falha na alocação de memória.\n");
        return 1;
    }

    // Cadastro inicial dos territórios
    cadastrarTerritorios(mapa, totalTerritorios);

    int continuar = 1;
    while (continuar) {
        exibirMapa(mapa, totalTerritorios);

        int idxAtacante, idxDefensor;
        printf("\n--- MENU DE ATAQUE ---\n");
        printf("Escolha o índice do território ATACANTE (0 a %d): ", totalTerritorios - 1);
        scanf("%d", &idxAtacante);
        printf("Escolha o índice do território DEFENSOR (0 a %d): ", totalTerritorios - 1);
        scanf("%d", &idxDefensor);

        // Validações básicas de índice
        if (idxAtacante < 0 || idxAtacante >= totalTerritorios || idxDefensor < 0 || idxDefensor >= totalTerritorios) {
            printf("\n[ERRO] Índices inválidos! Tente novamente.\n");
            continue;
        }

        // Passagem de ponteiros específicos para a função de ataque
        atacar(&mapa[idxAtacante], &mapa[idxDefensor]);

        printf("\nDeseja realizar outro ataque? (1 - Sim / 0 - Não): ");
        scanf("%d", &continuar);
    }

    // Exibição do estado final do mapa antes de encerrar
    printf("\n=== ESTADO FINAL DO MAPA ===\n");
    exibirMapa(mapa, totalTerritorios);

    // Liberação da memória alocada
    liberarMemoria(mapa);
    mapa = NULL; // Boa prática para evitar ponteiros soltos

    printf("\nMemória liberada com sucesso. Obrigado por jogar!\n");
    return 0;
}

/**
 * Função responsável pelo cadastro interativo dos territórios utilizando ponteiros.
 */
void cadastrarTerritorios(Territorio* mapa, int total) {
    printf("\n--- CADASTRO DE TERRITÓRIOS ---\n");
    for (int i = 0; i < total; i++) {
        // (mapa + i) é a aritmética de ponteiros equivalente a &mapa[i]
        Territorio* t = mapa + i; 
        
        printf("\nTerritório [%d]:\n", i);
        printf("Nome: ");
        fgets(t->nome, sizeof(t->nome), stdin);
        t->nome[strcspn(t->nome, "\n")] = '\0'; // Remove a quebra de linha do fgets

        printf("Cor do Exército: ");
        fgets(t->cor, sizeof(t->cor), stdin);
        t->cor[strcspn(t->cor, "\n")] = '\0';

        printf("Quantidade de Tropas: ");
        scanf("%d", &(t->tropas));
        getchar(); // Limpa o buffer
    }
}

/**
 * Função que exibe todos os territórios cadastrados no sistema.
 */
void exibirMapa(Territorio* mapa, int total) {
    printf("\n================ MAPA ATUAL ================\n");
    printf("%-5s | %-20s | %-12s | %-6s\n", "ID", "Território", "Exército", "Tropas");
    printf("--------------------------------------------\n");
    for (int i = 0; i < total; i++) {
        Territorio* t = &mapa[i];
        printf("%-5d | %-20s | %-12s | %-6d\n", i, t->nome, t->cor, t->tropas);
    }
    printf("============================================\n");
}

/**
 * Função de simulação de batalha entre dois territórios através de ponteiros.
 */
void atacar(Territorio* atacante, Territorio* defensor) {
    // Regra de Negócio: Não é permitido atacar a si mesmo ou territórios aliados
    if (strcmp(atacante->cor, defensor->cor) == 0) {
        printf("\n[AÇÃO INVÁLIDA] Você não pode atacar um território da sua própria cor (%s)!\n", atacante->cor);
        return;
    }

    // Regra de Negócio: Atacante precisa de tropas suficientes para atacar
    if (atacante->tropas < 2) {
        printf("\n[AÇÃO INVÁLIDA] O território %s não tem tropas suficientes para atacar (mínimo 2).\n", atacante->nome);
        return;
    }

    printf("\n[BATALHA] %s (%s) está atacando %s (%s)!\n", atacante->nome, atacante->cor, defensor->nome, defensor->cor);

    // Simulação da rolagem de dados (valores de 1 a 6)
    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor = (rand() % 6) + 1;

    printf("-> Dado do Atacante: %d\n", dadoAtacante);
    printf("-> Dado do Defensor: %d\n", dadoDefensor);

    // Resolução do combate
    if (dadoAtacante > dadoDefensor) {
        printf("\n[VITÓRIA DO ATACANTE] %s conquistou %s!\n", atacante->nome, defensor->nome);
        
        // Transferência de território e atualização de tropas
        strcpy(defensor->cor, atacante->cor);
        
        int tropasTransferidas = atacante->tropas / 2;
        defensor->tropas = tropasTransferidas;
        atacante->tropas -= tropasTransferidas;
        
        printf("-> %d tropas se moveram para o novo território.\n", tropasTransferidas);
    } else {
        // Empate ou Vitória do defensor favorece a defesa
        printf("\n[VITÓRIA DA DEFESA] %s resistiu ao ataque!\n", defensor->nome);
        atacante->tropas -= 1;
        printf("-> %s perdeu 1 tropa (Restantes: %d).\n", atacante->nome, atacante->tropas);
    }
}

/**
 * Função para liberação segura da memória alocada dinamicamente.
 */
void liberarMemoria(Territorio* mapa) {
    if (mapa != NULL) {
        free(mapa);
    }
}