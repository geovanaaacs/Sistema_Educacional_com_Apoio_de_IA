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
    char nome[80], email[100], senha_digitada[32], turma[25], cargo_texto[20];
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
            fgets(turma, 25, stdin);
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
            fgets(turma, 25, stdin);
            turma[strcspn(turma, "\n")] = '\0';
            break;

        case 3:
            strcpy(cargo_texto, "Secretaria");
            printf("Digite o nome completo da %s: ", cargo_texto);
            fgets(nome, 80, stdin);
            nome[strcspn(nome, "\n")] = '\0';

            printf("Digite o email da %s: ", cargo_texto);
            fgets(email, 100, stdin);
            email[strcspn(email, "\n")] = '\0';
            break;

        case 4:
            strcpy(cargo_texto, "Administrador");
            printf("Digite o nome completo do %s: ", cargo_texto);
            fgets(nome, 80, stdin);
            nome[strcspn(nome, "\n")] = '\0';

            printf("Digite o email do %s: ", cargo_texto);
            fgets(email, 100, stdin);
            email[strcspn(email, "\n")] = '\0';
            break;

        default:
            printf("Tipo de usuário inválido.\n");
            return;
    }

    printf("(Usuário) Insira sua senha: ");
    obterSenhaEscondida(senha_digitada, 32);

    FILE *arquivo_usuario = fopen("dados_usuarios.txt", "a");
    if (arquivo_usuario != NULL) {
        fprintf(arquivo_usuario, "Cargo: %s\n", cargo_texto);
        fprintf(arquivo_usuario, "Nome: %s\n", nome);
        fprintf(arquivo_usuario, "Email: %s\n", email);

        if (tipo_usuario == 1 || tipo_usuario == 2) {
            fprintf(arquivo_usuario, "Turma: %s\n", turma);
        }

        fprintf(arquivo_usuario, "Senha: %s\n", senha_digitada);
        fprintf(arquivo_usuario, "\n");

        fclose(arquivo_usuario);
        printf("\nUsuário cadastrado com sucesso!\n", nome);

    } else {
        perror("Erro ao abrir arquivo dados_usuarios.txt");
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
                printf("Função 'Inserir notas' ainda não implementada.\n");
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
