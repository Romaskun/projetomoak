#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define MAX_FILMES 50
#define MAX_SESSOES 100
#define MAX_USUARIOS 100

struct Usuario {
	char email[100];
	char senha[100];
	char tipo[20];
};

struct Usuario usuarios[MAX_USUARIOS];
int total_usuarios = 0;

struct Filme {
    int id;
    char titulo[100];
    char genero[50];
    int duracao;
};

struct Sessao {
    int id;
    int id_filme;
    char data[20];
    char horario[10];
    float preco;
    int ingressos_vendidos;
    int assentos_totais;
    int assentos_disponiveis;
    int assentos[100];
};

struct Filme filmes[MAX_FILMES];
struct Sessao sessoes[MAX_SESSOES];
int total_filmes = 0;
int total_sessoes = 0;
float faturamento_total = 0.0;

int fazer_login(char tipo_usuario[20]) {
    char email[100], senha[100];
    
    carregar_usuarios_do_arquivo();

    while (1) {
        printf("========== LOGIN ==========\n");
        printf("Email: ");
        scanf("%s", email);
        printf("Senha: ");
        scanf("%s", senha);

        for (int i = 0; i < total_usuarios; i++) {
            if (strcmp(usuarios[i].email, email) == 0 &&
                strcmp(usuarios[i].senha, senha) == 0) {
                strcpy(tipo_usuario, usuarios[i].tipo);
                printf("\nLogin realizado com sucesso como %s!\n", tipo_usuario);
                return 1;
            }
        }
        printf("\nEmail ou senha incorretos. Tente novamente.\n\n");
    }
}

void carregar_usuarios_do_arquivo() {
	FILE *arquivo = fopen("usuarios.txt", "r");
	
	if(arquivo == NULL) {
		FILE *novo = fopen("usuarios.txt", "w");
		fprintf(novo, "admin@gmail.com,123456,admin\n");
		fclose(novo);
		arquivo = fopen("usuarios.txt", "r");
	}
	
	total_usuarios = 0;
	while (fscanf(arquivo, "%99[^,],%99[^,],%19[^\n]\n", 
						usuarios[total_usuarios].email,
						usuarios[total_usuarios].senha,
						usuarios[total_usuarios].tipo) == 3) {
		total_usuarios++;							
	}
	fclose(arquivo);
}

void salvar_usuarios_no_arquivo(struct Usuario novo) {
	FILE *arquivo = fopen("usuarios.txt", "a");
	if (arquivo == NULL) {
		printf("Erro ao abrir o arquivos de usuários.\n");
		return;
	}
	fprintf(arquivo, "%s,%s,%s\n", novo.email, novo.senha, novo.tipo);
	fclose(arquivo);
}

void cadastrar_usuario() {
	struct Usuario novo;
	getchar();
	
	carregar_usuarios_do_arquivo();
	
	printf("\n=== Cadastro de Novo Cliente ===\n");
    printf("Email: ");
    fgets(novo.email, sizeof(novo.email), stdin);
    novo.email[strcspn(novo.email, "\n")] = '\0';
    
    for (int i = 0; i < total_usuarios; i++) {
    	if (strcmp(usuarios[i].email, novo.email) == 0) {
    		printf("ERRO: JÁ EXISTE UM USUARIO COM ESTE EMAIL.\n");
    		pausar();
    		return;
		}
	}

    printf("Senha: ");
    fgets(novo.senha, sizeof(novo.senha), stdin);
    novo.senha[strcspn(novo.senha, "\n")] = '\0';

    strcpy(novo.tipo, "cliente");

    salvar_usuarios_no_arquivo(novo);
    printf("Cadastro realizado com sucesso!\n");
    pausar();
}

void limpar_tela() {
    system("cls");
}

void pausar() {
    printf("\nPressione Enter para continuar...");
    getchar();
    getchar();
}

void carregarFilmesDoArquivo() {
    FILE *arquivo = fopen("filmes.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de filmes.\n");
        return;
    }

    total_filmes = 0;
    
    while (fscanf(arquivo, "%d,%99[^,],%49[^,],%d\n",
            &filmes[total_filmes].id,
            filmes[total_filmes].titulo,
            filmes[total_filmes].genero,
            &filmes[total_filmes].duracao) == 4) {
    total_filmes++;
    }
    fclose(arquivo);
}

void carregarSessoesDoArquivo() {
    FILE *arquivo = fopen("sessoes.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de sessões.\n");
        return;
    }

    total_sessoes = 0;
    while (1) {
        char preco_str[16];
        int res = fscanf(arquivo, "%d %d %10s %5s %15s %d %d %d",
                         &sessoes[total_sessoes].id,
                         &sessoes[total_sessoes].id_filme,
                         sessoes[total_sessoes].data,
                         sessoes[total_sessoes].horario,
                         preco_str,
                         &sessoes[total_sessoes].ingressos_vendidos,
                         &sessoes[total_sessoes].assentos_totais,
                         &sessoes[total_sessoes].assentos_disponiveis);
        if (res != 8) break;

        for (int i = 0; preco_str[i]; i++) {
            if (preco_str[i] == ',') preco_str[i] = '.';
        }
        sessoes[total_sessoes].preco = atof(preco_str);

        for (int i = 0; i < sessoes[total_sessoes].assentos_totais; i++) {
            fscanf(arquivo, "%d,", &sessoes[total_sessoes].assentos[i]);
        }

        total_sessoes++;
    }

    fclose(arquivo);
    
    faturamento_total = 0.0;
    for (int i = 0; i < total_sessoes; i++) {
        faturamento_total += sessoes[i].ingressos_vendidos * sessoes[i].preco;
    }
}

void salvarSessoesNoArquivo() {
    FILE *arquivo = fopen("sessoes.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao salvar sessões.\n");
        return;
    }

    for (int i = 0; i < total_sessoes; i++) {
        fprintf(arquivo, "%d %d %s %s %.2f %d %d %d\n",
            sessoes[i].id,
            sessoes[i].id_filme,
            sessoes[i].data,
            sessoes[i].horario,
            sessoes[i].preco,
            sessoes[i].ingressos_vendidos,
            sessoes[i].assentos_totais,
            sessoes[i].assentos_disponiveis);

        for (int j = 0; j < 100; j++) {
            fprintf(arquivo, "%d%c", sessoes[i].assentos[j], j == 99 ? '\n' : ' ');
        }
    }

    fclose(arquivo);
}

void mostrar_menu() {
    printf("\n========================================\n");
    printf("\tCINE SENIVIS\n");
    printf("========================================\n");
    printf("1. Cadastrar Filme\n");
    printf("2. Listar Filmes\n");
    printf("3. Cadastrar Sessao\n");
    printf("4. Listar Sessoes\n");
    printf("5. Vender Ingresso\n");
    printf("6. Relatorio de Vendas\n");
    printf("7. Apagar Filme\n");
    printf("8. Apagar Sessão\n");
    printf("0. Sair\n");
    printf("========================================\n");
    printf("Escolha uma opcao: ");
}

void cadastrar_filme() {
    limpar_tela();
    carregarFilmesDoArquivo();
    printf("\n=== CADASTRAR FILME ===\n");
    
    if (total_filmes >= MAX_FILMES) {
        printf("Limite de filmes atingido!\n");
        pausar();
        return;
    }
    
    struct Filme novo_filme;
    novo_filme.id = (total_filmes == 0) ? 1 : filmes[total_filmes - 1].id + 1;
    getchar();
    
    printf("Digite o titulo do filme: ");
    fgets(novo_filme.titulo, sizeof(novo_filme.titulo), stdin);
    novo_filme.titulo[strlen(novo_filme.titulo) - 1] = '\0'; 
    
    printf("Digite o genero: ");
    fgets(novo_filme.genero, sizeof(novo_filme.genero), stdin);
    novo_filme.genero[strlen(novo_filme.genero) - 1] = '\0'; 
    
    printf("Digite a duracao (em minutos): ");
    scanf("%d", &novo_filme.duracao);
    
    filmes[total_filmes] = novo_filme;
    
    FILE *arquivo = fopen("filmes.txt", "a");
    if (arquivo == NULL) {
    	printf("Erro ao abrir o arquivo!");
    	return;
	}
	
	fprintf(arquivo,"%d,%s,%s,%d\n",
	novo_filme.id,
	novo_filme.titulo,
	novo_filme.genero,
	novo_filme.duracao);
	
	fclose(arquivo);
    
    total_filmes++;
    
    printf("\nFilme cadastrado com sucesso!\n");
    pausar();
}

void listar_filmes() {
    limpar_tela();
    carregarFilmesDoArquivo();
    printf("\n=== LISTA DE FILMES ===\n");
    
    if (total_filmes == 0) {
        printf("Nenhum filme cadastrado.\n");
        pausar();
        return;
    }
    
    printf("ID | Titulo                    | Genero        | Duracao\n");
    printf("---|---------------------------|---------------|--------\n");
    
    for (int i = 0; i < total_filmes; i++) {
        printf("%-2d | %-25s | %-13s | %d min\n", 
               filmes[i].id, 
               filmes[i].titulo, 
               filmes[i].genero, 
               filmes[i].duracao);
    }
    
    pausar();
}

void cadastrar_sessao() {
    limpar_tela();
    carregarFilmesDoArquivo();
    carregarSessoesDoArquivo();
    printf("\n=== CADASTRAR SESSAO ===\n");
    
    if (total_filmes == 0) {
        printf("Nenhum filme cadastrado! Cadastre um filme primeiro.\n");
        pausar();
        return;
    }
    if (total_sessoes >= MAX_SESSOES) {
        printf("Limite de sessoes atingido!\n");
        pausar();
        return;
    }
    printf("Filmes disponiveis:\n");
    for (int i = 0; i < total_filmes; i++) {
        printf("%d - %s\n", filmes[i].id, filmes[i].titulo);
    }
    
    struct Sessao nova_sessao;
   	nova_sessao.id = (total_sessoes == 0) ? 1 : sessoes[total_sessoes - 1].id + 1;
    
    printf("\nDigite o ID do filme: ");
    scanf("%d", &nova_sessao.id_filme);
    int filme_existe = 0;
    for (int i = 0; i < total_filmes; i++) {
        if (filmes[i].id == nova_sessao.id_filme) {
            filme_existe = 1;
            break;
        }
    }
    if (!filme_existe) {
        printf("Filme nao encontrado!\n");
        pausar();
        return;
    }
    
    printf("Digite a data (ex: 15/12/2024): ");
    scanf("%s", nova_sessao.data);
    
    printf("Digite o horario (ex: 19:30): ");
    scanf("%s", nova_sessao.horario);
    
    printf("Digite o preco do ingresso: R$ ");
    scanf("%f", &nova_sessao.preco);
    
    nova_sessao.ingressos_vendidos = 0;
    nova_sessao.assentos_totais = 100; 
    nova_sessao.assentos_disponiveis = 100;
    for (int i = 0; i < 100; i++) {
        nova_sessao.assentos[i] = 0;
    }
    
    sessoes[total_sessoes] = nova_sessao;
    
    FILE *arquivo = fopen("sessoes.txt", "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para salvar a sessão.\n");
        return;
    }
    
    fprintf(arquivo, "%d %d %s %s %.2f %d %d %d\n",
    	nova_sessao.id,
    	nova_sessao.id_filme,
    	nova_sessao.data,
    	nova_sessao.horario,
    	nova_sessao.preco,
    	nova_sessao.ingressos_vendidos,
    	nova_sessao.assentos_totais,
    	nova_sessao.assentos_disponiveis);
    	
    for (int i = 0; i < 100; i++) {
    fprintf(arquivo, "%d%c", nova_sessao.assentos[i], i == 99 ? '\n' : ' ');
	}
	
	fclose(arquivo);

    total_sessoes++;
    
    printf("\nSessao cadastrada com sucesso!\n");
    pausar();
}

void listar_sessoes() {
    limpar_tela();
    carregarFilmesDoArquivo();
    carregarSessoesDoArquivo();
    printf("\n=== LISTA DE SESSOES ===\n");
    
    if (total_sessoes == 0) {
        printf("Nenhuma sessao cadastrada.\n");
        pausar();
        return;
    }
    
    printf("ID | Filme                     | Data       | Horario | Preco   | Vendidos\n");
    printf("---|---------------------------|------------|---------|---------|----------\n");
    
    for (int i = 0; i < total_sessoes; i++) {
        char nome_filme[100] = "Filme nao encontrado";
        for (int j = 0; j < total_filmes; j++) {
            if (filmes[j].id == sessoes[i].id_filme) {
                strcpy(nome_filme, filmes[j].titulo);
                break;
            }
        }
        
        printf("%-2d | %-25s | %-10s | %-7s | R$%-6.2f | %d\n", 
               sessoes[i].id, 
               nome_filme, 
               sessoes[i].data, 
               sessoes[i].horario, 
               sessoes[i].preco, 
               sessoes[i].ingressos_vendidos);
    }
    pausar();
}

void vender_ingresso() {
    limpar_tela();
    carregarSessoesDoArquivo();
    printf("\n=== VENDER INGRESSO ===\n");
    
    if (total_sessoes == 0) {
        printf("Nenhuma sessao cadastrada.\n");
        pausar();
        return;
    }
    
    printf("Sessoes disponiveis:\n");
    for (int i = 0; i < total_sessoes; i++) {
        char nome_filme[100] = "Filme nao encontrado";
        for (int j = 0; j < total_filmes; j++) {
            if (filmes[j].id == sessoes[i].id_filme) {
                strcpy(nome_filme, filmes[j].titulo);
                break;
            }
        }
        
        printf("%d - %s (%s %s) - R$ %.2f\n", 
               sessoes[i].id, 
               nome_filme, 
               sessoes[i].data, 
               sessoes[i].horario, 
               sessoes[i].preco);
    }
    
    int id_sessao, quantidade;
    printf("\nDigite o ID da sessao: ");
    scanf("%d", &id_sessao);
    int indice_sessao = -1;
    for (int i = 0; i < total_sessoes; i++) {
        if (sessoes[i].id == id_sessao) {
            indice_sessao = i;
            break;
        }
    }
    if (indice_sessao == -1) {
        printf("Sessao nao encontrada!\n");
        pausar();
        return;
    }
    printf("Digite a quantidade de ingressos: ");
    scanf("%d", &quantidade);
    if (quantidade <= 0) {
        printf("Quantidade invalida!\n");
        pausar();
        return;
    }
    float valor_total = quantidade * sessoes[indice_sessao].preco;
    
    printf("\nResumo da compra:\n");
    printf("Quantidade: %d ingresso(s)\n", quantidade);
    printf("Valor total: R$ %.2f\n", valor_total);
    
    char confirmacao;
    printf("Confirmar venda? (s/n): ");
    scanf(" %c", &confirmacao);
    
    if (confirmacao == 's' || confirmacao == 'S') {
        sessoes[indice_sessao].ingressos_vendidos += quantidade;
        faturamento_total += valor_total;
        
        salvarSessoesNoArquivo();
        
        printf("\nVenda realizada com sucesso!\n");
    } else {
        printf("\nVenda cancelada.\n");
    }   
    pausar();
}

void relatorio_vendas() {
    limpar_tela();
    carregarFilmesDoArquivo();
    carregarSessoesDoArquivo();
    printf("\n=== RELATORIO DE VENDAS ===\n");
    
    if (total_sessoes == 0) {
        printf("Nenhuma sessao cadastrada.\n");
        pausar();
        return;
    }
    
    printf("Resumo de vendas por sessao:\n\n");
    printf("Filme                     | Data       | Horario | Vendidos | Arrecadacao\n");
    printf("--------------------------|------------|---------|----------|------------\n");
    
    int total_ingressos = 0;
    
    for (int i = 0; i < total_sessoes; i++) {
        if (sessoes[i].ingressos_vendidos > 0) {
            char nome_filme[100] = "Filme nao encontrado";
            for (int j = 0; j < total_filmes; j++) {
                if (filmes[j].id == sessoes[i].id_filme) {
                    strcpy(nome_filme, filmes[j].titulo);
                    break;
                }
            }
            
            float arrecadacao = sessoes[i].ingressos_vendidos * sessoes[i].preco;
            
            printf("%-25s | %-10s | %-7s | %-8d | R$ %.2f\n", 
                   nome_filme, 
                   sessoes[i].data, 
                   sessoes[i].horario, 
                   sessoes[i].ingressos_vendidos, 
                   arrecadacao);
            
            total_ingressos += sessoes[i].ingressos_vendidos;
        }
    }
    
    printf("\n");
    printf("Total de ingressos vendidos: %d\n", total_ingressos);
    printf("Faturamento total: R$ %.2f\n", faturamento_total);
    
    pausar();
}

void apagar_filme() {
    limpar_tela();
    carregarFilmesDoArquivo();
    
    if (total_filmes == 0) {
        printf("Nenhum filme cadastrado para apagar.\n");
        pausar();
        return;
    }
    
    printf("=== Apagar Filme ===\n");
    listar_filmes();
    
    int id_apagar;
    printf("Digite o ID do filme que deseja apagar: ");
    scanf("%d", &id_apagar);
    
    int indice = -1;
    for (int i = 0; i < total_filmes; i++) {
        if (filmes[i].id == id_apagar) {
            indice = i;
            break;
        }
    }
    
    if (indice == -1) {
        printf("Filme com ID %d nao encontrado.\n", id_apagar);
        pausar();
        return;
    }
    
    for (int i = indice; i < total_filmes - 1; i++) {
        filmes[i] = filmes[i + 1];
    }
    total_filmes--;
    
    FILE *arquivo = fopen("filmes.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo para salvar.\n");
        pausar();
        return;
    }
    for (int i = 0; i < total_filmes; i++) {
        fprintf(arquivo, "%d,%s,%s,%d\n", filmes[i].id, filmes[i].titulo, filmes[i].genero, filmes[i].duracao);
    }
    fclose(arquivo);

    printf("Filme apagado com sucesso!\n");
    pausar();
}

void apagar_sessao() {
    limpar_tela();
    carregarSessoesDoArquivo();
    
    if (total_sessoes == 0) {
        printf("Nenhuma sessão cadastrada para apagar.\n");
        pausar();
        return;
    }
    
    printf("=== Apagar Sessao ===\n");
    listar_sessoes();
    
    int id_apagar;
    printf("Digite o ID da sessão que deseja apagar: ");
    scanf("%d", &id_apagar);
    
    int indice = -1;
    for (int i = 0; i < total_sessoes; i++) {
        if (sessoes[i].id == id_apagar) {
            indice = i;
            break;
        }
    }
    
    if (indice == -1) {
        printf("Sessao com ID %d nao encontrada.\n", id_apagar);
        pausar();
        return;
    }
    
    for (int i = indice; i < total_sessoes - 1; i++) {
        sessoes[i] = sessoes[i + 1];
    }
    total_sessoes--;
    
    FILE *arquivo = fopen("sessoes.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo para salvar.\n");
        pausar();
        return;
    }
    
    for (int i = 0; i < total_sessoes; i++) {
        fprintf(arquivo, "%d %d %s %s %.2f %d %d %d\n",
                sessoes[i].id,
                sessoes[i].id_filme,
                sessoes[i].data,
                sessoes[i].horario,
                sessoes[i].preco,
                sessoes[i].ingressos_vendidos,
                sessoes[i].assentos_totais,
                sessoes[i].assentos_disponiveis);
        
        for (int j = 0; j < sessoes[i].assentos_totais; j++) {
            fprintf(arquivo, "%d%c", sessoes[i].assentos[j], (j == sessoes[i].assentos_totais - 1) ? '\n' : ' ');
        }
    }
    
    fclose(arquivo);
    
    printf("Sessao apagada com sucesso!\n");
    pausar();
}

int main() {
    setlocale(LC_ALL, "portuguese");
    char tipo_usuario[20];
    int escolha_login;

    do {
        limpar_tela();
        printf("=== CINE SENIVIS ===\n");
        printf("1. Fazer Login\n");
        printf("2. Cadastrar-se (cliente)\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &escolha_login);

        if (escolha_login == 1) {
            if (fazer_login(tipo_usuario)) break;
        } else if (escolha_login == 2) {
            cadastrar_usuario();
        } else if (escolha_login != 0) {
            printf("Opção inválida!\n");
            pausar();
        }
    } while (escolha_login != 0);

    if (escolha_login == 0) {
        printf("Saindo do sistema...\n");
        return 0;
    }
    
 int opcao;
 
    do {
        limpar_tela();

        if (strcmp(tipo_usuario, "admin") == 0) {
            mostrar_menu();
            scanf("%d", &opcao);

            switch (opcao) {
                case 1: cadastrar_filme(); break;
                case 2: listar_filmes(); break;
                case 3: cadastrar_sessao(); break;
                case 4: listar_sessoes(); break;
                case 5: vender_ingresso(); break;
                case 6: relatorio_vendas(); break;
                case 7: apagar_filme(); break;
                case 8: apagar_sessao(); break;
                case 0: printf("\nSaindo do sistema...\n"); break;
                default: printf("\nOpcao invalida!\n"); pausar();
            }

        } else if (strcmp(tipo_usuario, "cliente") == 0) {
            printf("\n===== MENU CLIENTE =====\n");
            printf("1. Listar Filmes\n");
            printf("2. Listar Sessoes\n");
            printf("3. Comprar Ingresso\n");
            printf("0. Sair\n");
            printf("Escolha: ");
            scanf("%d", &opcao);

            switch (opcao) {
                case 1: listar_filmes(); break;
                case 2: listar_sessoes(); break;
                case 3: vender_ingresso(); break;
                case 0: printf("Saindo...\n"); break;
                default: printf("Opção inválida.\n"); pausar();
            }
        }

    } while (opcao != 0);

    return 0;
} 