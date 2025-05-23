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
    if(total_sessoes >= SESSOES) {
    	printf("LIMITE DE SESSOES ATINGIDO!!");
    	return;
	}
    printf("\n===== CADASTRO DE SESSAO =====\n");
    
    if(total_filmes == 0) {
    	printf("Nenhum filme em Cartaz neste momento. Cadastre um filme para inicar uma sessão de cinema");
    	return;
	}
	
	printf("\n---------FILMES EM CARTAZ-----------\n");
	for(int i = 0; i < total_filmes; i++) {
		printf("ID: %d |\n TITULO: %s |\n",filmes[i].id, filmes[i].titulo);
	}
	
	sessoes[total_sessoes].id = total_sessoes + 1;
	printf("\nID SESSÃO: %d\n", sessoes[total_sessoes].id);
	
	printf("Informe o ID do filme para a sessão: ");
	scanf("%d", &sessoes[total_sessoes].id_filme);
	
	printf("Data da sessão (DD/MM/AAAA): ");
	scanf(" %10[^\n]", sessoes[total_sessoes].data);
	
	printf("Horário da sessão (HH:MM): ");
	scanf(" %5[^\n]", sessoes[total_sessoes].horario);
	
	printf("Sala: ");
	scanf(" %9[^\n]", sessoes[total_sessoes].sala);
	
	printf("Preço do ingresso: ");
	scanf("%f", &sessoes[total_sessoes].preco);
	
	sessoes[total_sessoes].assentos_totais = ASSENTOS;
	sessoes[total_sessoes].assentos_disponiveis = ASSENTOS;
	
	for (int i = 0; i < ASSENTOS; i++) {
		sessoes[total_sessoes].assentos[i] = 0;
	}
	total_sessoes++;
	printf("\nSessão cadastrada com sucesso!!\n");
}


    // Função para buscar sessões de um filme (RAFAEL)
void buscarSessoesFilme() {
   
    printf("\n===== BUSCAR SESSOES DE UM FILME =====\n");
    
       if (total_filmes == 0) {
        printf("Nenhum filme cadastrado.\n");
        return;
    }

    char titulo_busca[NOME];
    int encontrado = 0;

    printf("Digite o título do filme: ");
    fflush(stdin);
    scanf(" %[^\n]", titulo_busca);

    // Procurar filme pelo título
    for (int i = 0; i < total_filmes; i++) {
        if (strcmp(filmes[i].titulo, titulo_busca) == 0) {
            int id_filme = filmes[i].id;
            encontrado = 1;
            printf("\nSessões do filme \"%s\":\n", filmes[i].titulo);

            int encontrou_sessao = 0;
            for (int j = 0; j < total_sessoes; j++) {
                if (sessoes[j].id_filme == id_filme) {
                    printf("ID Sessão: %d\n", sessoes[j].id);
                    printf("Data: %s\n", sessoes[j].data);
                    printf("Horário: %s\n", sessoes[j].horario);
                    printf("Sala: %s\n", sessoes[j].sala);
                    printf("Preço: R$ %.2f\n", sessoes[j].preco);
                    printf("Assentos Disponíveis: %d\n", sessoes[j].assentos_disponiveis);
                    printf("--------------------------\n");
                    encontrou_sessao = 1;
                }
            }

            if (!encontrou_sessao) {
                printf("Nenhuma sessão encontrada para este filme.\n");
            }

            break;
        }
    }

    if (!encontrado) {
        printf("Filme não encontrado.\n");
    }
}

}

// Função para exibir o mapa de assentos de uma sessão
void exibirMapaAssentos(int id_sessao) {
    // TODO: Implementar a exibição do mapa de assentos de uma sessão
    printf("\n===== MAPA DE ASSENTOS =====\n\n");
    
     // Verifica se a sessão existe
    int encontrada = 0;
    for (int i = 0; i < total_sessoes; i++) {
        if (sessoes[i].id == id_sessao) {
            encontrada = 1;
            printf("Sessão ID: %d | Sala: %s | Horário: %s | Data: %s\n", 
                    sessoes[i].id, sessoes[i].sala, sessoes[i].horario, sessoes[i].data);
            printf("Assentos (0 = Livre | 1 = Ocupado):\n\n");

            // Exibe os assentos como uma lista numerada
            for (int j = 0; j < sessoes[i].assentos_totais; j++) {
                printf("%02d[%d]  ", j + 1, sessoes[i].assentos[j]);

                // Quebra de linha a cada 10 assentos para melhor visualização
                if ((j + 1) % 10 == 0) {
                    printf("\n");
                }
            }

            printf("\n\nLegenda: [0] Livre  [1] Ocupado\n");
            break;
        }
    }

    if (!encontrada) {
        printf("Sessão com ID %d não encontrada.\n", id_sessao);
    }
}
 

// Função para vender ingressos (DIEGO)
void venderIngresso() {
	if (total_sessoes == 0) {
		printf("\nSem sessões cadastradas...\n");
		return;
	}
	
	if (total_ingressos >= INGRESSOS) {
		printf("\nLimite máximo de inregssos atingido.\n");
		return;
	}
	
	int id_sessao, numero_assento;
	printf("\n===== VENDA DE INGRESSOS =====\n");

    printf("\nSessões Disponíveis:\n");
    for (int i = 0; i < total_sessoes; i++) {
        printf("ID: %d | Filme ID: %d | Data: %s | Horário: %s | Sala: %s | Preço: R$%.2f | Assentos Disponíveis: %d\n",
               sessoes[i].id, sessoes[i].id_filme, sessoes[i].data, sessoes[i].horario,
               sessoes[i].sala, sessoes[i].preco, sessoes[i].assentos_disponiveis);
   }
   
   printf("\nDigite o ID da sessão desejada: ");
   scanf("%d", &id_sessao);
   
   int index_sessao = -1;
   for (int i = 0; i < total_sessoes; i++) {
   	if (sessoes[i].id == id_sessao) {
   		index_sessao = i;
   		break;
		}
	}
	
	if (index_sessao == -1) {
		printf("\nSessão não encontrada.\n");
		return;
	}
	
	if (sessoes[index_sessao].assentos_disponiveis == 0) {
		printf("\nSessão lotada! Não há assentos disponíveis.\n");
		return;
	}
	
	printf("\nMapa de assentos (0 = livre, 1 = ocupado):\n");
	for (int i = 0; i < sessoes[index_sessao].assentos_totais; i++) {
		printf("[%02d:%d] ", i + 1, sessoes[index_sessao].assentos[i]);
		if ((i + 1) % 5 == 0) 
		printf("\n");
	}
	
	printf("\n\nInforme o número do assento (1-%d): ", sessoes[index_sessao].assentos_totais);
	scanf("%d", &numero_assento);
	
	if (numero_assento < 1 || numero_assento > sessoes[index_sessao].assentos_totais ||
	    sessoes[index_sessao].assentos[numero_assento - 1] == 1) {
	    printf("\nAssento inválido ou ocupado.\n");
		 return;	
		 } 
		 
	char confirmacao;
	printf("\nConfirmar compra do assento %d por R$%2.f? (S/N): ",numero_assento, sessoes[index_sessao].preco);
	scanf(" %c", &confirmacao);
	
	if (confirmacao != 'S' && confirmacao != 's') {
		printf("\nCompra cancelada.\n");
		return;
	}
	
	 ingressos[total_ingressos].id = total_ingressos + 1;
	 ingressos[total_ingressos].id_sessao = id_sessao;
	 ingressos[total_ingressos].id_filme = sessoes[index_sessao].id_filme;
	 ingressos[total_ingressos].numero_assento = numero_assento;
	 ingressos[total_ingressos].valor = sessoes[index_sessao].preco;
	 strcpy(ingressos[total_ingressos].data_venda, "20/05/2025");
	 
	 sessoes[index_sessao].assentos[numero_assento - 1] = 1;
	 sessoes[index_sessao].assentos_disponiveis--;
	 total_ingressos++;
	 
	 printf("\nIngresso vendido com sucesso!\n");
	 printf("Sessão: %s | Horário: %s | Assento: %d | Valor: R$%.2f | Data: %s\n",
	        sessoes[index_sessao].data,
           sessoes[index_sessao].horario,
           numero_assento,
           sessoes[index_sessao].preco,
           ingressos[total_ingressos - 1].data_venda);    
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
