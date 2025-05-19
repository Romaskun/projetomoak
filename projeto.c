#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição de tamanhos máximos
#define NOME 50
#define FILMES 10
#define SESSOES 20
#define INGRESSOS 100
#define ASSENTOS 30

// Estrutura para armazenar informações de um filme
typedef struct {
    int id;
    char titulo[NOME];
    char genero[NOME];
    int duracao;
} Filme;

// Estrutura para armazenar informações de uma sessão
typedef struct {
    int id;
    int id_filme;
    char data[11]; // formato DD/MM/AAAA
    char horario[6]; // formato HH:MM
    char sala[10];
    float preco;
    int assentos_totais;
    int assentos_disponiveis;
    int assentos[ASSENTOS];
} Sessao;

// Estrutura para armazenar informações de um ingresso vendido
typedef struct {
    int id;
    int id_sessao;
    int id_filme;
    int numero_assento;
    float valor;
    char data_venda[11]; // formato DD/MM/AAAA
} Ingresso;

// Variáveis globais para armazenar os dados
Filme filmes[FILMES];
Sessao sessoes[SESSOES];
Ingresso ingressos[INGRESSOS];
int total_filmes = 0;
int total_sessoes = 0;
int total_ingressos = 0;

// Função para listar todos os filmes (KAIO)
void listarFilmes() {
    // TODO: Implementar a listagem de todos os filmes cadastrados
    printf("\n===== LISTA DE FILMES =====\n\n");

}

// Função para cadastrar um novo filme (COUTINHO)
void cadastrarFilme() {
    // TODO: Implementar o cadastro de um novo filme    
    printf("\n===== CADASTRO DE FILME =====\n");

}

// Função para cadastrar uma nova sessão (PEJOTA)
void cadastrarSessao() {
    // TODO: Implementar o cadastro de uma nova sessão
    printf("\n===== CADASTRO DE SESSAO =====\n");

}

// Função para buscar sessões de um filme (RAFAEL)
void buscarSessoesFilme() {
    // TODO: Implementar a busca de sessões de um filme específico
    printf("\n===== BUSCAR SESSOES DE UM FILME =====\n");

}

// Função para exibir o mapa de assentos de uma sessão
void exibirMapaAssentos(int id_sessao) {
    // TODO: Implementar a exibição do mapa de assentos de uma sessão
    printf("\n===== MAPA DE ASSENTOS =====\n\n");
    
}

// Função para vender ingressos (DIEGO)
void venderIngresso() {
    // TODO: Implementar a venda de ingressos    
    printf("\n===== VENDA DE INGRESSOS =====\n");
    

}

// Função para gerar relatório de vendas (ROMEU)
void relatorioVendas() {
    // TODO: Implementar o relatório de vendas    
    printf("\n===== RELATORIO DE VENDAS =====\n\n");
}

// Função principal
int main() {
    int opcao;
    
    do {
        printf("\n===== SISTEMA DE CINEMA =====\n");
        printf("1. Listar todos os filmes (KAIO)\n");
        printf("2. Cadastrar filme (COUTINHO)\n");
        printf("3. Cadastrar sessao (PEJOTA)\n");
        printf("4. Buscar sessoes de um filme (RAFAEL)\n");
        printf("5. Vender ingressos (DIEGO)\n");
        printf("6. Relatorio de vendas (ROMEU)\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        
        switch (opcao) {
            case 1:
                // listarFilmes();
                break;
            case 2:
                // cadastrarFilme();
                break;
            case 3:
                // cadastrarSessao();
                break;
            case 4:
                // buscarSessoesFilme();
                break;
            case 5:
                // venderIngresso();
                break;
            case 6:
                // relatorioVendas();
                break;
            case 0:
                printf("\nSaindo do sistema...\n");
                break;
            default:
                printf("\nOpcao invalida!\n");
        }
        
        if (opcao != 0) {
            printf("\nPressione Enter para continuar...");
            fflush(stdin);
            getchar();
        }
        
    } while (opcao != 0);
    
    return 0;
}