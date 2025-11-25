#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <unistd.h>
#include <conio.h>

void obterSenhaEscondida(char *senha, int tamanho_max) {
    int i = 0;
    char ch;

    while (1) {
        ch = _getch();
        if (ch == 13) {
            senha[i] = '\0';
            break;
        }
        else if (ch == 8) {
            if (i > 0) {
                i--;
                printf("\b \b");
            }
        }
        else if (i < tamanho_max - 1) {
            senha[i] = ch;
            i++;
            printf("*");
        }
    }
    printf("\n");
}

void realizarCadastro(){
    char nome[80], email[100], senha_digitada[32], turma[5], cargo_texto[20], disciplina[20];
    int tipo_usuario;

    printf("\n--- Novo Cadastro ---\n");
    printf("Selecione o tipo de cadastro pelo número:\n");
    printf("1: Aluno\n2: Docente\n3: Secretaria\n4: Administrador\n");
    printf("Opção: ");
    if (scanf("%d", &tipo_usuario) != 1) {
        printf("Entrada inválida.\n");
        while (getchar() != '\n');
        return;
    }
    while (getchar() != '\n');
    switch(tipo_usuario){
        case 1:
            strcpy(cargo_texto, "Aluno");
            printf("Digite o nome completo do %s: ", cargo_texto);
            fgets(nome, 80, stdin);
            nome[strcspn(nome, "\n")] = '\0';

            printf("Digite o email do %s: ", cargo_texto);
            fgets(email, 100, stdin);
            email[strcspn(email, "\n")] = '\0';

            printf("Digite a turma do %s: ", cargo_texto);
            fgets(turma, 5, stdin);
            turma[strcspn(turma, "\n")] = '\0';
            break;

        case 2:
            strcpy(cargo_texto, "Docente");
            printf("Digite o nome completo do %s: ", cargo_texto);
            fgets(nome, 80, stdin);
            nome[strcspn(nome, "\n")] = '\0';

            printf("Digite o email do %s: ", cargo_texto);
            fgets(email, 100, stdin);
            email[strcspn(email, "\n")] = '\0';

            printf("Digite a turma do %s: ", cargo_texto);
            fgets(turma, 5, stdin);
            turma[strcspn(turma, "\n")] = '\0';

            printf("Digite a disciplina do %s: ", cargo_texto);
            fgets(disciplina, 20, stdin);
            disciplina[strcspn(disciplina, "\n")] = '\0';
            break;

        case 3:
            strcpy(cargo_texto, "Secretaria");
            printf("Digite o nome completo da %s: ", cargo_texto);
            fgets(nome, 80, stdin);
            nome[strcspn(nome, "\n")] = '\0';

            printf("Digite o email da %s: ", cargo_texto);
            fgets(email, 100, stdin);
            email[strcspn(email, "\n")] = '\0';
            turma[0] = '\0';
            break;

        case 4:
            strcpy(cargo_texto, "Administrador");
            printf("Digite o nome completo do %s: ", cargo_texto);
            fgets(nome, 80, stdin);
            nome[strcspn(nome, "\n")] = '\0';

            printf("Digite o email do %s: ", cargo_texto);
            fgets(email, 100, stdin);
            email[strcspn(email, "\n")] = '\0';
            turma[0] = '\0';
            break;

        default:
            printf("Tipo de usuário inválido.\n");
            return;
    }

    printf("(Usuário) Insira sua senha: ");
    obterSenhaEscondida(senha_digitada, 32);

    FILE *arquivo_usuario = fopen("dados_usuarios.txt", "a");
    if (arquivo_usuario != NULL) {
        fprintf(arquivo_usuario, "Cargo: %s\nNome: %s\nEmail: %s\nTurma: %s\n",
                cargo_texto,
                nome,
                email,
                turma);

        if (tipo_usuario == 2) {
            fprintf(arquivo_usuario, "Disciplina: %s\n", disciplina);
        }

        fprintf(arquivo_usuario, "Senha: %s\n\n", senha_digitada);

        fclose(arquivo_usuario);
        printf("\nUsuário cadastrado com sucesso!\n");

    } else {
        perror("Erro ao abrir arquivo dados_usuarios.txt");
    }
}

void registro_notas(void) {
    char busca[100];
    char linha[256];
    char nome_aluno[100] = "";
    char email_aluno[100] = "";
    char turma[10] = "";
    char cargo[20] = "";
    char disciplina[50];
    float nota;

    printf("\n====================\n");
    printf("REGISTRO DE NOTAS\n");
    printf("====================\n");

    printf("Digite parte do nome ou email do aluno: ");
    fgets(busca, sizeof(busca), stdin);
    busca[strcspn(busca, "\n")] = '\0'; // remove o \n

    FILE *arquivo_usuarios = fopen("dados_usuarios.txt", "r");
    if (arquivo_usuarios == NULL) {
        perror("Erro ao abrir dados_usuarios.txt");
        return;
    }

    int encontrado = 0;

    while (fgets(linha, sizeof(linha), arquivo_usuarios)) {
        if (strncmp(linha, "Cargo:", 6) == 0) {
            sscanf(linha, "Cargo: %[^\n]", cargo);
        } else if (strncmp(linha, "Nome:", 5) == 0) {
            sscanf(linha, "Nome: %[^\n]", nome_aluno);
        } else if (strncmp(linha, "Email:", 6) == 0) {
            sscanf(linha, "Email: %[^\n]", email_aluno);
        } else if (strncmp(linha, "Turma:", 6) == 0) {
            sscanf(linha, "Turma: %[^\n]", turma);
        } else if (linha[0] == '\n') {
            if (strcmp(cargo, "Aluno") == 0 &&
                (strstr(email_aluno, busca) || strstr(nome_aluno, busca))) {
                encontrado = 1;
                break;
            }
        }
    }

    fclose(arquivo_usuarios);

    if (!encontrado) {
        printf("\nAluno não encontrado!\n");
        printf("\nPressione Enter para voltar ao menu...");
        getchar();
        return;
    }

    printf("\nAluno encontrado: %s\n", nome_aluno);
    printf("Turma: %s\n", turma);

    printf("Digite a disciplina: ");
    fgets(disciplina, sizeof(disciplina), stdin);
    disciplina[strcspn(disciplina, "\n")] = '\0';

    printf("Digite a nota com vírgula: ");
    scanf("%f", &nota);
    while (getchar() != '\n');

    FILE *arquivo_notas = fopen("notas_registradas.txt", "a");
    if (arquivo_notas == NULL) {
        perror("Erro ao abrir notas_registradas.txt");
        return;
    }

    fprintf(arquivo_notas, "Aluno: %s\nEmail: %s\nTurma: %s\nDisciplina: %s\nNota: %.2f\n\n",
            nome_aluno, email_aluno, turma, disciplina, nota);

    fclose(arquivo_notas);

    printf("\nNota registrada com sucesso!\n");
}


void incluir_atividade(void) {
    char titulo_atividade[50];
    char descricao_atividade[256];
    char turma[10];
    char disciplina[50];

    printf("\n==============================\n");
    printf(" CADASTRO DE NOVA ATIVIDADE\n");
    printf("==============================\n");

    printf("Digite o título da atividade: ");
    fgets(titulo_atividade, sizeof(titulo_atividade), stdin);
    titulo_atividade[strcspn(titulo_atividade, "\n")] = '\0'; // remover \n

    printf("Digite a turma: ");
    fgets(turma, sizeof(turma), stdin);
    turma[strcspn(turma, "\n")] = '\0';

    printf("Digite a disciplina: ");
    fgets(disciplina, sizeof(disciplina), stdin);
    disciplina[strcspn(disciplina, "\n")] = '\0';

    printf("Digite a descrição da atividade: ");
    fgets(descricao_atividade, sizeof(descricao_atividade), stdin);
    descricao_atividade[strcspn(descricao_atividade, "\n")] = '\0';

    FILE *arquivo_atividade = fopen("dados_atividades.txt", "a");
    if (arquivo_atividade == NULL) {
        perror("Erro ao abrir dados_atividades.txt");
        return;
    }

    fprintf(arquivo_atividade, "%s,%s,%s,%s\n",
            titulo_atividade,
            turma,
            disciplina,
            descricao_atividade);

    fclose(arquivo_atividade);

    printf("\nAtividade cadastrada com sucesso!\n");
    printf("Título: %s\nTurma: %s\nDisciplina: %s\n", titulo_atividade, turma, disciplina);
}

void fazer_login(void){
    char email_digitado[100];
    char senha_digitada[32];

    puts("====================================================");
    puts("REALIZAR LOGIN ANTES DE INSERIR A NOTA OU ATIVIDADE");
    puts("====================================================");

    printf("Digite seu email: %s", email_digitado);
    scanf("%99s", &email_digitado);

    while (getchar() != '\n');
        printf("Digite sua senha: %s", senha_digitada);
        obterSenhaEscondida(senha_digitada, 32);
        // VER PORQUE ESTÁ ESCREVENDO CARACTERES ESTRANHOS ANTES DE COLOCAR SENHA

    FILE *arquivo_usuario = fopen("dados_usuarios.txt", "r");
    if (arquivo_usuario == NULL){
        perror("Erro ao abrir dados_usuarios.txt");
        return;
    }

    int login_sucesso = 0;
    char linha_do_arquivo[256];

    char email_bloco_atual[100] = "";
    char senha_bloco_atual[32] = "";
    char cargo_bloco_atual[20] = "";
    char cargo_LOGADO[20] = "";

    while (fgets(linha_do_arquivo, sizeof(linha_do_arquivo), arquivo_usuario)){
        if (linha_do_arquivo[0] == '\n'){
            if (strcmp(email_digitado, email_bloco_atual) == 0 && strcmp(senha_digitada, senha_bloco_atual) == 0){
                login_sucesso = 1;
                strcpy(cargo_LOGADO, cargo_bloco_atual);
                break;
            }
            strcpy(email_bloco_atual, "");
            strcpy(senha_bloco_atual, "");
            strcpy(cargo_bloco_atual, "");
            continue;
        }
        char chave[100];
        char valor[100];

        if(sscanf(linha_do_arquivo, "%99[^:]: %[^\n]", chave, valor) == 2) {
            if (strcmp(chave, "Email") == 0) {
                strcpy(email_bloco_atual, valor);
            } else if (strcmp(chave, "Senha") == 0) {
                strcpy(senha_bloco_atual, valor);
            } else if (strcmp(chave, "Cargo")== 0){
                strcpy(cargo_bloco_atual, valor);
            }
        }
    }

    fclose(arquivo_usuario);

    if (login_sucesso == 1) {
        if (strcmp(email_digitado, email_bloco_atual) == 0 &&
            strcmp(senha_digitada, senha_bloco_atual) == 0){
            login_sucesso = 1;
            strcpy(cargo_LOGADO, cargo_bloco_atual);
        }

    if (login_sucesso == 1){
        printf("\nLogin realizado com sucesso! (Cargo: %s)\n", cargo_LOGADO);
        if (strcmp(cargo_LOGADO, "Docente") == 0 ||
            strcmp(cargo_LOGADO, "Administrador") == 0){
                printf("\nLogin realizado com sucesso! Bem-vindo(a)!");
                puts("==============================================");
                puts("Selecione uma opção:\n");
                int opcao_sub_menu;
                printf("(1) Inserir notas\n(2) Inserir atividades\nOpção: %d", opcao_sub_menu);
                if (scanf("%d", &opcao_sub_menu) != 1) {
                    printf("Entrada inválida. Digite um número.\n");
                    while (getchar() != '\n');
                    return;
                }
                while (getchar() != '\n');
                    if (opcao_sub_menu == 1){
                        registro_notas();
                    } else if (opcao_sub_menu == 2){
                        incluir_atividade();
                    } else {
                        printf("Opção inválida. Escolha 1 ou 2.\n");
                    }
                }
            } else {
                printf("\nAcesso negado. Esta função é reservada para Docentes e Admin.\n");
            }

        } else {
            puts("\nEmail ou senha incorretos.");
        }
}

int main() {
    setlocale(LC_ALL, "pt_BR.UTF-8");
    int opcao_menu;
    int rodando = 1;
    while (rodando == 1) {
        puts("\n==================================");
        puts("BEM VINDO(A) AO SISTEMA ACADêMICO");
        puts("==================================");

        printf("Selecione o que deseja fazer:\n");
        printf("1: Realizar Cadastro\n");
        printf("2: Inserir notas ou atividades\n");
        printf("3: Sair\n");
        printf("Opção: ");

        if (scanf("%d", &opcao_menu) != 1) {
             printf("Entrada inválida. Digite um número.\n");
             while (getchar() != '\n');
             continue;
        }

        while (getchar() != '\n');

        switch (opcao_menu) {
            case 1:
                realizarCadastro();
                break;
            case 2:
                fazer_login();
                break;
            case 3:
                printf("Saindo...\n");
                rodando = 0;
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
                break;
        }

        if (rodando == 1) { // Só pausa se não for sair
             printf("\nPressione Enter para voltar ao menu...");
             getchar(); // Espera o usuário apertar Enter
        }

    }
    return 0;
}
