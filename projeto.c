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
    char data[11]; 
    char horario[6]; 
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
    char data_venda[11];
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
    // O que fazer: Implementar a listagem de todos os filmes cadastrados
    if (total_filmes == 0) {
        printf("Nenhum filme cadastrado.\n");
    } else {
       printf("\n===== LISTA DE FILMES =====\n\n");
       for (int i = 0; i < total_filmes; i++) {
        printf("%d. %s (%s, %d min)\n", filmes[i].id, filmes[i].titulo, filmes[i].genero, filmes[i].duracao);
    }   
         printf("\nTotal de filmes cadastrados: %d\n", total_filmes);
    }
}
        
// Função para cadastrar um novo filme (COUTINHO)
void cadastrarFilme() {
    if (total_filmes >= FILMES) {
    	printf("Limite de Filmes Atingido");
    	return;
	}    
	
	filmes[total_filmes].id = total_filmes + 1;
	
    printf("\n===== CADASTRO DE FILME =====\n");
    printf("ID: %d\n", filmes[total_filmes].id);
    printf("Digite os dados do filme:\n");

    printf("Titulo: ");
    fflush(stdin);
    scanf(" %[^\n]", filmes[total_filmes].titulo);

    printf("Genero: ");
    fflush(stdin);
    scanf(" %[^\n]", filmes[total_filmes].genero);

    printf("Duracao (minutos): ");
    scanf("%d", &filmes[total_filmes].duracao);
    total_filmes++;

    printf("\nFilme cadastrado com sucesso!\n");
    
    printf("\nDeseja cadastrar outro filme? (S/N): ");
	char resposta;
    fflush(stdin);
    scanf("%c", &resposta);
    if (resposta == 'S' || resposta == 's') {
        cadastrarFilme();
    }
}


// Função para cadastrar uma nova sessão (PEJOTA)
void cadastrarSessao() {
    // O que fazer: Implementar o cadastro de uma nova sessão
    printf("\n===== CADASTRO DE SESSAO =====\n");

}

// Função para buscar sessões de um filme (RAFAEL)
void buscarSessoesFilme() {
    // O que fazer: Implementar a busca de sessões de um filme específico
    printf("\n===== BUSCAR SESSOES DE UM FILME =====\n");

}

// Função para exibir o mapa de assentos de uma sessão
void exibirMapaAssentos(int id_sessao) {
    // O que fazer: Implementar a exibição do mapa de assentos de uma sessão
    printf("\n===== MAPA DE ASSENTOS =====\n\n");
    
}

// Função para vender ingressos (DIEGO)
void venderIngresso() {
    // O que fazer: Implementar a venda de ingressos    
    printf("\n===== VENDA DE INGRESSOS =====\n");
    

}

// Função para gerar relatório de vendas (ROMEU)
void relatorioVendas() {
    // O que fazer: Implementar o relatório de vendas    
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
