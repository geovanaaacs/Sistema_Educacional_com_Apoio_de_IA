#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <unistd.h>

int main() {
    setlocale(LC_ALL, "pt_BR.UTF-8");
    char nome[80], email[100], senha[32], disciplina[50],
    turma[7], cargo[15];
    int num_id;
    int matricula;
    float nota, media;
    puts("Tela de Cadastro");
    puts("Aluno(1), Docente(2), Secretaria(3), Administrador(4)");
    printf("Selecione o tipo de cadastro pelo número: ");
    scanf("%s", cargo);
    switch (cargo):
        case 1:
            printf("Digite o nome completo do aluno: %s", nome);
            scanf("%s", &nome);
            printf("Digite o email do aluno: %s", email);
            scanf("%s", &email);
            printf("Digite a turma do aluno: %s", turma);
            scanf("%s", &turma);
            senha = getpass("Insira sua senha: ");

            return nome, email, turma, senha;

        case 2:
            printf("Digite o nome completo do aluno: %s", nome);
            scanf("%s", &nome);
            printf("Digite o email do aluno: %s", email);
            scanf("%s", &email);
            printf("Digite a turma do aluno: %s", turma);
            scanf("%s", &turma);
            senha = getpass("Insira sua senha: ");

            return nome, email, turma, senha;


    FILE *arquivo_usuario;
    arquivo_usuario = fopen("dados_usuarios.txt", "w");
    if (arquivo_usuario != NULL) {
        fprintf(arquivo_usuario, "Nome: %s\nEmail: %s\nCargo: %s\n\n", nome, email, cargo);
        fclose(arquivo_usuario);
    } else {
        printf("Erro ao abrir o arquivo para escrita.\n");
    }
    return 0;

    {
    float nota1, nota2, media;
    setlocale(LC_ALL, "pt_BR.UTF-8");
    puts("Área do professor");
    puts("Notas e média");
    scanf("%f", &nota1);
    scanf("%f", &nota2);
    media = (nota1 + nota2) / 2;
    printf("%.2f\n", media);
    puts("Atividades");

    return 0;
    }

    {
    setlocale(LC_ALL, "pt_BR.UTF-8");
    puts("Área do aluno");
    puts("Notas e média");
    puts("Atividades");
    return 0;
    }
}