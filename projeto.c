#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// Definição de tamanhos máximos
#define NOME 50
#define FILMES 10
#define SESSOES 20
#define INGRESSOS 100
#define ASSENTOS 30


#define RESET   "\033[0m"
#define BOLD    "\033[1m"
#define UNDERLINE "\033[4m"
#define BLACK   "\033[30m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"

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
    if (total_filmes == 0) {
        printf("Nenhum filme cadastrado.\n");
    } else {
       printf(RED "\n===== LISTA DE FILMES =====\n\n" RESET);
       for (int i = 0; i < total_filmes; i++) {
       		printf("ID Filme: %d\n", filmes[i].id);
       		printf("Titulo do Filme: %s\n", filmes[i].titulo);
       		printf("Genero do Filme: %s\n", filmes[i].genero);
       		printf("Duração do Filme: %d (Minutos)\n", filmes[i].duracao);
       		printf("\n===================SESSÕES======================\n");
       		
       	int encontrou = 0;
       	for(int s = 0; s < total_sessoes; s++) {
       		if(sessoes[s].id_filme == filmes[i].id) {
       		printf("ID Sessão: %d\n", sessoes[s].id);
       		printf("Data: %s\n", sessoes[s].data);
       		printf("Horário : %s\n", sessoes[s].horario);
       		printf("Sala: %s\n", sessoes[s].sala);
       		printf("\n-----------------------------------\n");
       		encontrou = 1;
			}
		} 
		if (!encontrou) {
                printf("Nenhuma sessão cadastrada para este filme.\n");
            }
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
	
    printf(BLUE "\n===== CADASTRO DE FILME =====\n" RESET);
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
    printf(RED "\n===== CADASTRO DE SESSAO =====\n" RESET);
    
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
   
    printf(MAGENTA "\n===== BUSCAR SESSOES DE UM FILME =====\n" RESET);
    
       if (total_filmes == 0) {
        printf("Nenhum filme cadastrado.\n");
        return;
    }

    int id_busca = 0;
    int encontrado = 0;

    printf(YELLOW "Digite o codigo ID do filme: " RESET);
    fflush(stdin);
    scanf("%d", &id_busca);

    // Procurar filme pelo ID
    for (int i = 0; i < total_filmes; i++) {
        if (filmes[i].id == id_busca) {
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

// Função para exibir o mapa de assentos de uma sessão
void exibirMapaAssentos(int id_sessao) {
    // TODO: Implementar a exibição do mapa de assentos de uma sessão
    printf(CYAN "\n===== MAPA DE ASSENTOS =====\n\n" RESET);
    
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
	printf(GREEN "\n===== VENDA DE INGRESSOS =====\n" RESET);

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


// Função para remover um filme pelo ID
void removerFilme() {
    if (total_filmes == 0) {
        printf("Nenhum filme cadastrado.\n");
        return;
    }
    int id;
    printf(RED "\n===== REMOVER FILME =====\n" RESET);
    printf("Digite o ID do filme a remover: ");
    scanf("%d", &id);
    int encontrado = 0;
    for (int i = 0; i < total_filmes; i++) {
        if (filmes[i].id == id) {
            encontrado = 1;
            // Remove o filme deslocando os próximos
            for (int j = i; j < total_filmes - 1; j++) {
                filmes[j] = filmes[j + 1];
            }
            total_filmes--;
            printf("Filme removido com sucesso!\n");
            break;
        }
    }
    if (!encontrado) {
        printf("Filme não encontrado.\n");
    }
}

// Função para remover uma sessão pelo ID
void removerSessao() {
    if (total_sessoes == 0) {
        printf("Nenhuma sessão cadastrada.\n");
        return;
    }
    int id;
    printf(RED "\n===== REMOVER SESSAO =====\n" RESET);
    printf("Digite o ID da sessão a remover: ");
    scanf("%d", &id);
    int encontrado = 0;
    for (int i = 0; i < total_sessoes; i++) {
        if (sessoes[i].id == id) {
            encontrado = 1;
            for (int j = i; j < total_sessoes - 1; j++) {
                sessoes[j] = sessoes[j + 1];
            }
            total_sessoes--;
            printf("Sessão removida com sucesso!\n");
            break;
        }
    }
    if (!encontrado) {
        printf("Sessão não encontrada.\n");
    }
}

// Função para buscar filmes por gênero ---- MEIO INUTIL NAO??
void buscarFilmeGenero() {
    if (total_filmes == 0) {
        printf("Nenhum filme cadastrado.\n");
        return;
    }
    char genero[NOME];
    printf(BLUE "\n===== BUSCAR FILMES POR GENERO =====\n" RESET);
    printf("Digite o gênero: ");
    fflush(stdin);
    scanf(" %[^\n]", genero);
    int encontrou = 0;
    for (int i = 0; i < total_filmes; i++) {
        if (strcmp(filmes[i].genero, genero) == 0) {
            printf("%d. %s (%d min)\n", filmes[i].id, filmes[i].titulo, filmes[i].duracao);
            encontrou = 1;
        }
    }
    if (!encontrou) {
        printf("Nenhum filme encontrado para o gênero informado.\n");
    }
}

// Função para exibir todos os ingressos vendidos
void listarIngressosVendidos() {
    if (total_ingressos == 0) {
        printf("Nenhum ingresso vendido ainda.\n");
        return;
    }
    printf(GREEN "\n===== INGRESSOS VENDIDOS =====\n" RESET);
    for (int i = 0; i < total_ingressos; i++) {
        printf("ID: %d | Sessão: %d | Filme: %d | Assento: %d | Valor: R$%.2f | Data: %s\n",
            ingressos[i].id, ingressos[i].id_sessao, ingressos[i].id_filme,
            ingressos[i].numero_assento, ingressos[i].valor, ingressos[i].data_venda);
    }
}

// Função para relatório de vendas (completo)
void relatorioVendas() {
    printf(YELLOW "\n===== RELATORIO DE VENDAS =====\n\n" RESET);
    float total = 0;
    for (int i = 0; i < total_ingressos; i++) {
        total += ingressos[i].valor;
    }
    printf("Total de ingressos vendidos: %d\n", total_ingressos);
    printf("Total arrecadado: R$%.2f\n", total);
}

// Função principal
int main() {
    setlocale(LC_ALL, "Portuguese");
    int opcao;
    
    do {
        printf(YELLOW "\n|======== SISTEMA DE CINEMA ========|\n" RESET);
        printf(BLUE "|1. Listar todos os filmes          |\n" RESET);
        printf(BLUE "|2. Cadastrar filme                 |\n" RESET);
        printf(BLUE "|3. Cadastrar sessao                |\n" RESET);
        printf(BLUE "|4. Buscar sessoes de um filme      |\n" RESET);
        printf(BLUE "|5. Vender ingressos                |\n" RESET);
        printf(BLUE "|6. Relatorio de vendas             |\n" RESET);
        printf(BLUE "|7. Remover filme                   |\n" RESET);
        printf(BLUE "|8. Remover sessão                  |\n" RESET);
        printf(BLUE "|9. Buscar filme por gênero         |\n" RESET);
        printf(BLUE "|10. Listar ingressos vendidos      |\n" RESET);
        printf(BLUE "|0. Sair                            |\n" RESET);
        printf("|Escolha uma opcao: ");
        scanf("%d", &opcao);
        
        switch (opcao) {
            case 1:
                listarFilmes();
                break;
            case 2:
                cadastrarFilme();
				break;
            case 3:
                cadastrarSessao();
                break;
            case 4:
                buscarSessoesFilme();
                break;
            case 5:
                venderIngresso();
                break;
            case 6:
                relatorioVendas();
                break;
            case 7:
                removerFilme();
                break;
            case 8:
                removerSessao();
                break;
            case 9:
                buscarFilmeGenero();
                break;
            case 10:
                listarIngressosVendidos();
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