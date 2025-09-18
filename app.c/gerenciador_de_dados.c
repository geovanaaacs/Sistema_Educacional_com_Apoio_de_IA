#include <stdio.h>
#include <stdlib.h> // Para malloc, realloc, free
#include <string.h> // Para strcpy

#define MAX_STRING_SIZE 100
#define MAX_ROLE_STRING_SIZE 15
#define MAX_PASSWORD_STRING_SIZE 20

// Define a estrutura do usuário com varios tipos de dados
typedef struct{
    char nome[MAX_STRING_SIZE];
    char email[MAX_STRING_SIZE];
    char tipo[MAX_ROLE_STRING_SIZE];
    char senha[MAX_PASSWORD_STRING_SIZE]; // hash da senha
    int id;
} UsuarioC; // aluno, professor, admin

typedef struct{
    char nome[MAX_STRING_SIZE];
    char disciplina[MAX_STRING_SIZE];
    float nota1;
    float nota2;
    float media;
}   NotaAlunoC;

typedef struct{
    char email_professor[MAX_STRING_SIZE];
    char disciplina[MAX_STRING_SIZE];
} DisciplinaC;

// Declaração de funções

// Carrega os usuários do armazenamento.
// Retorna ponteiro para array de Usuario e armazena o número de usuários em num_usuarios.
// Retorno: ponteiro para array de Usuario, ou NULL em caso de erro.
UsuarioC* carregar_usuarios(int* num_usuarios);

// Salva o array de usuários em um arquivo.
// Entrada: ponteiro para array de Usuario, número de usuários.
// Retorno: 0 em caso de sucesso, -1 em caso de erro.
int salvar_usuarios(UsuarioC* usuarios, int num_usuarios);

// Libera a memória alocada para o array de usuários.
// Parâmetros:
// usuarios - ponteiro para o array de usuários a ser liberado.
void liberar_usuarios(UsuarioC* usuarios);

NotaAlunoC* carregar_notas(int* num_notas);
int salvar_notas(NotaAlunoC* notas, int num_notas);
void liberar_notas(NotaAlunoC* notas);

DisciplinaC* carregar_disciplinas_c(int* num_disciplinas);
int salvar_disciplinas_c(DisciplinaC disciplinas[], int num_disciplinas);
void liberar_memoria_disciplinas_c(DisciplinaC* disciplinas);

// Função para adicionar um novo usuário ao array de usuários.
int adicionar_usuario_c(const char* nome, const char* email, const char* senha, const char* tipo);

// ============== CADASTRO DE USUÁRIOS =======================

int adicionar_usuario_c(const char* nome, const char* email, const char* senha, const char* role) {
    // 1. Abrir o arquivo em modo "append" (a).
    // Se o arquivo não existir, o modo "a" o cria.
    // Se existir, o cursor é posicionado no final do arquivo.
    FILE* f = fopen("usuarios.txt", "a");

    // 2. Verificar se a abertura do arquivo foi bem-sucedida.
    if (f == NULL) {
        perror("C (adicionar_usuario): Nao foi possivel abrir usuarios.txt");
        return -1; // Retorna código de erro
    }

    // 3. Escrever a nova linha de usuário no final do arquivo.
    // Usamos fprintf, assim como na função de salvar.
    fprintf(f, "%s %s %s %s\n", nome, email, senha, role);

    // 4. Fechar o arquivo para garantir que a escrita foi concluída.
    fclose(f);

    // 5. Retornar sucesso.
    return 0;
}

// Funções usuários

UsuarioC* carregar_usuarios_c(int* num_usuarios) {
    FILE* f = fopen("usuarios.txt", "r");
    if (f == NULL) { *num_usuarios = 0; return NULL; }

    UsuarioC* usuarios = NULL;
    int capacidade = 0;
    *num_usuarios = 0;

    char linha[350];
    while (fgets(linha, sizeof(linha), f)) {
        if (*num_usuarios >= capacidade) {
            capacidade = (capacidade == 0) ? 2 : capacidade * 2;
            usuarios = (UsuarioC*)realloc(usuarios, capacidade * sizeof(UsuarioC));
            if (usuarios == NULL) { perror("Falha ao alocar memoria para usuarios"); fclose(f); return NULL; }
        }
        sscanf(linha, "%99s %99s %99s %19s", 
               usuarios[*num_usuarios].nome, usuarios[*num_usuarios].email,
               usuarios[*num_usuarios].senha, usuarios[*num_usuarios].tipo);
        (*num_usuarios)++;
    }
    fclose(f);
    return usuarios;
}

int salvar_usuarios_c(UsuarioC usuarios[], int num_usuarios) {
    FILE* f = fopen("usuarios.txt", "w");
    if (f == NULL) { perror("Nao foi possivel abrir usuarios.txt para escrita"); return -1; }

    for (int i = 0; i < num_usuarios; i++) {
        fprintf(f, "%s %s %s %s\n", usuarios[i].nome, usuarios[i].email, usuarios[i].senha, usuarios[i].tipo);
    }
    fclose(f);
    return 0;
}

void liberar_memoria_usuarios_c(UsuarioC* usuarios) {
    if (usuarios != NULL) { free(usuarios); }
}