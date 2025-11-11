void registro_notas(void) {
    char busca[80];
    char linha[256];
    char email[100], senha[32], cargo[20], nome[80], turma[10], disciplina[50];
    char nome_encontrado[80] = "";
    char turma_encontrada[10] = "";
    char disciplina_encontrada[50] = "";
    float nota;

    FILE *arquivo_usuarios = fopen("dados_usuarios.txt", "r");
    if (arquivo_usuarios == NULL) {
        perror("Erro ao abrir dados_usuarios.txt");
        return;
    }

    printf("\n=========================\n");
    printf(" REGISTRO DE NOTAS\n");
    printf("=========================\n");
    printf("Digite parte do nome ou email do aluno: ");
    fgets(busca, sizeof(busca), stdin);
    busca[strcspn(busca, "\n")] = '\0';

    // Percorrer o arquivo procurando aluno
    while (fgets(linha, sizeof(linha), arquivo_usuarios)) {
        // Formato: email,senha,cargo,nome,turma\n
        if (sscanf(linha, "%99[^,],%31[^,],%19[^,],%79[^,],%9[^\n]",
                   email, senha, cargo, nome, turma) >= 4) {

            if (strstr(nome, busca) != NULL || strstr(email, busca) != NULL) {
                strcpy(nome_encontrado, nome);
                strcpy(turma_encontrada, turma);
                // disciplina vazia — aluno não tem; docente sim
                break;
            }
        }
    }

    fclose(arquivo_usuarios);

    if (strlen(nome_encontrado) == 0) {
        printf("\nAluno não encontrado!\n");
        return;
    }

    printf("\nAluno encontrado: %s\n", nome_encontrado);
    printf("Turma: %s\n", turma_encontrada);

    printf("Digite a disciplina: ");
    fgets(disciplina_encontrada, sizeof(disciplina_encontrada), stdin);
    disciplina_encontrada[strcspn(disciplina_encontrada, "\n")] = '\0';

    printf("Digite a nota: ");
    if (scanf("%f", &nota) != 1) {
        printf("Nota inválida.\n");
        while (getchar() != '\n');
        return;
    }
    while (getchar() != '\n');

    FILE *arquivo_notas = fopen("dados_notas.txt", "a");
    if (arquivo_notas == NULL) {
        perror("Erro ao abrir dados_notas.txt");
        return;
    }

    fprintf(arquivo_notas, "%s,%s,%s,%.2f\n",
            nome_encontrado,
            turma_encontrada,
            disciplina_encontrada,
            nota);

    fclose(arquivo_notas);

    printf("\n✅ Nota registrada com sucesso para o aluno %s!\n", nome_encontrado);
}
