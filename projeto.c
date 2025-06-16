#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>

#define MAX_FILMES 50
#define MAX_SESSOES 100
#define MAX_USUARIOS 100
#define LINHAS_ASSENTOS 7
#define COLUNAS_ASSENTOS 12

struct Usuario {
    char email[100];
    char senha[100];
    char tipo[20];
};

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
    int assentos[LINHAS_ASSENTOS][COLUNAS_ASSENTOS];
};

struct Usuario usuarios[MAX_USUARIOS];
int total_usuarios = 0;
struct Filme filmes[MAX_FILMES];
struct Sessao sessoes[MAX_SESSOES];
int total_filmes = 0;
int total_sessoes = 0;
float faturamento_total = 0.0;

void carregar_usuarios_do_arquivo();
void listar_filmes();
void listar_filmes_sem_pausa();
void listar_sessoes();
void pausar();
void mostrar_assentos(struct Sessao s);

int fazer_login(char tipo_usuario[20]) {
    char email[100], senha[100];

    carregar_usuarios_do_arquivo();

    while (1) {
        printf("========== LOGIN ==========\n");
        printf("Email: ");
        fflush(stdin);
        scanf(" %[^\n]", email);
        printf("Senha: ");
        fflush(stdin);
        scanf(" %[^\n]", senha);

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

    if (arquivo == NULL) {
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

    carregar_usuarios_do_arquivo();

    printf("\n=== Cadastro de Novo Cliente ===\n");
    printf("Email: ");
    fflush(stdin);
    scanf(" %[^\n]", novo.email);

    for (int i = 0; i < total_usuarios; i++) {
        if (strcmp(usuarios[i].email, novo.email) == 0) {
            printf("ERRO: JÁ EXISTE UM USUÁRIO COM ESTE EMAIL.\n");
            pausar();
            return;
        }
    }

    printf("Senha: ");
    fflush(stdin);
    scanf(" %[^\n]", novo.senha);

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
    fflush(stdin);
    getchar();
}

void carregarFilmesDoArquivo() {
    FILE *arquivo = fopen("filmes.txt", "r");
    if (arquivo == NULL) {
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
        return;
    }

    total_sessoes = 0;
    while (fscanf(arquivo, "%d %d %s %s %f %d %d %d",
                  &sessoes[total_sessoes].id,
                  &sessoes[total_sessoes].id_filme,
                  sessoes[total_sessoes].data,
                  sessoes[total_sessoes].horario,
                  &sessoes[total_sessoes].preco,
                  &sessoes[total_sessoes].ingressos_vendidos,
                  &sessoes[total_sessoes].assentos_totais,
                  &sessoes[total_sessoes].assentos_disponiveis) == 8) {

        for (int i = 0; i < LINHAS_ASSENTOS; i++) {
            for (int j = 0; j < COLUNAS_ASSENTOS; j++) {
                fscanf(arquivo, "%d", &sessoes[total_sessoes].assentos[i][j]);
            }
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
        fprintf(arquivo, "%d %d %s %s %.2f %d %d %d",
                sessoes[i].id, sessoes[i].id_filme, sessoes[i].data,
                sessoes[i].horario, sessoes[i].preco, sessoes[i].ingressos_vendidos,
                sessoes[i].assentos_totais, sessoes[i].assentos_disponiveis);

        for (int l = 0; l < LINHAS_ASSENTOS; l++) {
            for (int c = 0; c < COLUNAS_ASSENTOS; c++) {
                fprintf(arquivo, " %d", sessoes[i].assentos[l][c]);
            }
        }
        fprintf(arquivo, "\n");
    }
    fclose(arquivo);
}

void mostrar_menu() {
    printf("\n========================================\n");
    printf("\tCINE SENIVIS (ADMIN)\n");
    printf("========================================\n");
    printf("1. Cadastrar Filme\n");
    printf("2. Listar Filmes\n");
    printf("3. Cadastrar Sessao\n");
    printf("4. Consultar Sessoes de um Filme\n");
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

    printf("Digite o titulo do filme: ");
    fflush(stdin);
    scanf(" %[^\n]", novo_filme.titulo);

    printf("Digite o genero: ");
    fflush(stdin);
    scanf(" %[^\n]", novo_filme.genero);

    printf("Digite a duracao (em minutos): ");
    scanf("%d", &novo_filme.duracao);

    filmes[total_filmes] = novo_filme;

    FILE *arquivo = fopen("filmes.txt", "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!");
        return;
    }

    fprintf(arquivo, "%d,%s,%s,%d\n",
            novo_filme.id, novo_filme.titulo,
            novo_filme.genero, novo_filme.duracao);

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

    printf("ID | Titulo                      | Genero        | Duracao\n");
    printf("---|-----------------------------|---------------|--------\n");

    for (int i = 0; i < total_filmes; i++) {
        printf("%-2d | %-27s | %-13s | %d min\n",
               filmes[i].id, filmes[i].titulo,
               filmes[i].genero, filmes[i].duracao);
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

    listar_filmes_sem_pausa();

    struct Sessao nova_sessao;
    nova_sessao.id = (total_sessoes == 0) ? 1 : sessoes[total_sessoes - 1].id + 1;

    printf("\nDigite o ID do filme: ");
    scanf("%d", &nova_sessao.id_filme);

    printf("Digite a data (ex: 15/12/2024): ");
    scanf("%s", nova_sessao.data);

    printf("Digite o horario (ex: 19:30): ");
    scanf("%s", nova_sessao.horario);

    printf("Digite o preco do ingresso: R$ ");
    scanf("%f", &nova_sessao.preco);

    nova_sessao.ingressos_vendidos = 0;
    nova_sessao.assentos_totais = LINHAS_ASSENTOS * COLUNAS_ASSENTOS;
    nova_sessao.assentos_disponiveis = LINHAS_ASSENTOS * COLUNAS_ASSENTOS;
    for (int i = 0; i < LINHAS_ASSENTOS; i++) {
        for (int j = 0; j < COLUNAS_ASSENTOS; j++) {
            nova_sessao.assentos[i][j] = 0;
        }
    }

    sessoes[total_sessoes] = nova_sessao;
    total_sessoes++;

    salvarSessoesNoArquivo();

    printf("\nSessao cadastrada com sucesso!\n");
    pausar();
}

void listar_sessoes() {
    limpar_tela();
    carregarFilmesDoArquivo();
    carregarSessoesDoArquivo();
    printf("\n=== CONSULTAR SESSOES POR FILME ===\n");

    if (total_filmes == 0) {
        printf("Nenhum filme cadastrado.\n");
        pausar();
        return;
    }

    listar_filmes_sem_pausa();

    int id_filme_escolhido;
    printf("\nDigite o ID do filme para ver suas sessoes: ");
    scanf("%d", &id_filme_escolhido);

    limpar_tela();

    char nome_filme_escolhido[100] = "";
    int encontrou_filme = 0;
    for (int i = 0; i < total_filmes; i++) {
        if (filmes[i].id == id_filme_escolhido) {
            strcpy(nome_filme_escolhido, filmes[i].titulo);
            encontrou_filme = 1;
            break;
        }
    }

    if (!encontrou_filme) {
        printf("Filme com ID %d nao encontrado.\n", id_filme_escolhido);
        pausar();
        return;
    }

    printf("Mostrando sessoes para o filme: %s\n", nome_filme_escolhido);
    printf("==================================================\n");

    int encontrou_sessao = 0;
    for (int i = 0; i < total_sessoes; i++) {
        if (sessoes[i].id_filme == id_filme_escolhido) {
            encontrou_sessao = 1;
            printf("\n>> Sessao ID: %d | Data: %s | Horario: %s | Preco: R$%.2f\n",
                   sessoes[i].id, sessoes[i].data, sessoes[i].horario, sessoes[i].preco);

            mostrar_assentos(sessoes[i]);
            printf("--------------------------------------------------\n");
        }
    }

    if (!encontrou_sessao) {
        printf("\nNenhuma sessao encontrada para este filme.\n");
    }

    pausar();
}

void mostrar_assentos(struct Sessao s) {
    printf("\n=============== T E L A ===============\n");
    printf("    ");
    for (int j = 1; j <= COLUNAS_ASSENTOS; j++) {
        printf("%-3d", j);
    }
    printf("\n");

    for (int i = 0; i < LINHAS_ASSENTOS; i++) {
        printf(" %c |", 'A' + i);
        for (int j = 0; j < COLUNAS_ASSENTOS; j++) {
            if (s.assentos[i][j] == 0) {
                printf("[ ]");
            } else {
                printf("[X]");
            }
        }
        printf("\n");
    }
    printf("=======================================\n");
    printf("[X] = Ocupado | [ ] = Livre\n");
}

void vender_ingresso() {
    limpar_tela();
    carregarFilmesDoArquivo();
    carregarSessoesDoArquivo();

    if (total_sessoes == 0) {
        printf("Nenhuma sessao cadastrada.\n");
        pausar();
        return;
    }

    printf("--- Sessoes Disponiveis ---\n");
    for (int i = 0; i < total_sessoes; i++) {
        char nome_filme[100] = "N/A";
        for (int j = 0; j < total_filmes; j++) {
            if (filmes[j].id == sessoes[i].id_filme) {
                strcpy(nome_filme, filmes[j].titulo);
                break;
            }
        }
        printf("ID: %d | Filme: %s | Data: %s | Horario: %s | Assentos: %d\n",
               sessoes[i].id, nome_filme, sessoes[i].data, sessoes[i].horario, sessoes[i].assentos_disponiveis);
    }
    printf("---------------------------\n");

    int id_sessao;
    printf("\nDigite o ID da sessao para comprar ingressos: ");
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

    int quantidade;
    printf("Digite a quantidade de ingressos: ");
    scanf("%d", &quantidade);

    if (quantidade <= 0 || quantidade > sessoes[indice_sessao].assentos_disponiveis) {
        printf("Quantidade invalida ou nao ha assentos suficientes (%d disponiveis).\n", sessoes[indice_sessao].assentos_disponiveis);
        pausar();
        return;
    }

    for (int i = 0; i < quantidade; i++) {
        mostrar_assentos(sessoes[indice_sessao]);

        char assento_str[4];
        int linha, coluna;
        int valido = 0;

        while (!valido) {
            printf("\nEscolha o assento para o ingresso %d de %d (ex: A5, C12): ", i + 1, quantidade);
            fflush(stdin);
            scanf("%s", assento_str);

            linha = toupper(assento_str[0]) - 'A';
            coluna = atoi(&assento_str[1]) - 1;

            if (linha < 0 || linha >= LINHAS_ASSENTOS || coluna < 0 || coluna >= COLUNAS_ASSENTOS) {
                printf("Assento invalido. Por favor, tente novamente.\n");
            } else if (sessoes[indice_sessao].assentos[linha][coluna] == 1) {
                printf("Este assento ja esta ocupado. Escolha outro.\n");
            } else {
                sessoes[indice_sessao].assentos[linha][coluna] = 1;
                sessoes[indice_sessao].assentos_disponiveis--;
                sessoes[indice_sessao].ingressos_vendidos++;
                valido = 1;
            }
        }
    }

    float valor_total = quantidade * sessoes[indice_sessao].preco;
    faturamento_total += valor_total;

    salvarSessoesNoArquivo();
    printf("\nCompra de %d ingresso(s) realizada com sucesso! Valor total: R$ %.2f\n", quantidade, valor_total);
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

    printf("Filme                         | Data       | Horario | Vendidos | Arrecadacao\n");
    printf("------------------------------|------------|---------|----------|------------\n");

    int total_ingressos_geral = 0;

    for (int i = 0; i < total_sessoes; i++) {
        if (sessoes[i].ingressos_vendidos > 0) {
            char nome_filme[100] = "N/A";
            for (int j = 0; j < total_filmes; j++) {
                if (filmes[j].id == sessoes[i].id_filme) {
                    strcpy(nome_filme, filmes[j].titulo);
                    break;
                }
            }
            float arrecadacao = sessoes[i].ingressos_vendidos * sessoes[i].preco;
            printf("%-29s | %-10s | %-7s | %-8d | R$ %.2f\n",
                   nome_filme, sessoes[i].data, sessoes[i].horario,
                   sessoes[i].ingressos_vendidos, arrecadacao);
            total_ingressos_geral += sessoes[i].ingressos_vendidos;
        }
    }

    printf("\n");
    printf("Total de ingressos vendidos: %d\n", total_ingressos_geral);
    printf("Faturamento total geral: R$ %.2f\n", faturamento_total);
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

    listar_filmes_sem_pausa();

    int id_apagar;
    printf("\nDigite o ID do filme que deseja apagar: ");
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
    carregarFilmesDoArquivo();
    if (total_sessoes == 0) {
        printf("Nenhuma sessão cadastrada para apagar.\n");
        pausar();
        return;
    }
    printf("=== Apagar Sessao ===\n");

    for (int i = 0; i < total_sessoes; i++) {
        char nome_filme[100] = "N/A";
        for (int j = 0; j < total_filmes; j++) {
            if (filmes[j].id == sessoes[i].id_filme) {
                strcpy(nome_filme, filmes[j].titulo);
            }
        }
        printf("ID %d: %s (%s %s)\n", sessoes[i].id, nome_filme, sessoes[i].data, sessoes[i].horario);
    }

    int id_apagar;
    printf("\nDigite o ID da sessão que deseja apagar: ");
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
    salvarSessoesNoArquivo();
    printf("Sessao apagada com sucesso!\n");
    pausar();
}

void listar_filmes_sem_pausa() {
    printf("\n--- Filmes em Cartaz ---\n");
    if (total_filmes == 0) {
        printf("Nenhum filme cadastrado.\n");
        return;
    }

    printf("ID | Titulo                      \n");
    printf("---|-----------------------------\n");

    for (int i = 0; i < total_filmes; i++) {
        printf("%-2d | %-27s\n",
               filmes[i].id, filmes[i].titulo);
    }
    printf("---------------------------\n");
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
                case 1: 
                cadastrar_filme(); 
                break;

                case 2: 
                listar_filmes(); 
                break;

                case 3: 
                cadastrar_sessao(); 
                break;

                case 4: 
                listar_sessoes(); 
                break;

                case 5: 
                vender_ingresso(); 
                break;

                case 6: 
                relatorio_vendas(); 
                break;

                case 7: 
                apagar_filme(); 
                break;

                case 8: 
                apagar_sessao(); 
                break;

                case 0: 
                printf("\nSaindo do sistema...\n"); 
                break;

                default: 
                printf("\nOpção inválida!\n"); 
                pausar();
            }
        } else if (strcmp(tipo_usuario, "cliente") == 0) {
            printf("\n===== MENU CLIENTE =====\n");
            printf("1. Listar Filmes\n");
            printf("2. Consultar Sessoes de um Filme\n");
            printf("3. Comprar Ingresso\n");
            printf("0. Sair\n");
            printf("Escolha: ");
            scanf("%d", &opcao);
            
            switch (opcao) {
                case 1: 
                listar_filmes(); 
                break;

                case 2: 
                listar_sessoes(); 
                break;

                case 3: 
                vender_ingresso(); 
                break;

                case 0: 
                printf("Saindo...\n"); 
                break;

                default: 
                printf("Opção inválida.\n"); 
                pausar();
            }
        }
    } while (opcao != 0);
    return 0;
}
