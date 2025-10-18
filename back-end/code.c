#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

int main() {
    setlocale(LC_ALL, "pt_BR.UTF-8");
    char nome[80], email[100], senha[32], disciplina[50],
    turma[7], cargo[15];
    int num_id;
    int matricula; // Adiciona a declaração da variável matricula
    float nota, media;
    puts("Tela de Cadastro");
    printf("Selecione o tipo de cadastro: ");
    scanf("%s", cargo);
    if (strcmp(cargo, "Aluno") == 0) {
        // código para cadastro de aluno
    } else if (strcmp(cargo, "Docente") == 0) {
        // código para cadastro de docente
    } else if (strcmp(cargo, "Secretaria") == 0) {
        // código para cadastro de secretaria
    } else {
        printf("Tipo de cadastro inválido.\n");
    }
    FILE *arquivo_usuario;
    arquivo_usuario = fopen("dados_usuarios.txt", "w");
    if (arquivo_usuario != NULL) {
        fprintf(arquivo_usuario, "Nome: %s\nEmail: %s\nCargo: %s\n", nome, email, cargo);
        fclose(arquivo_usuario);
    } else {
        printf("Erro ao abrir o arquivo para escrita.\n");
    }
    return 0;
}
