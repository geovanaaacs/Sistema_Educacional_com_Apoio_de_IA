#include <stdio.h>
#include <locale.h>

int main(void)
{
    setlocale(LC_ALL, "pt_BR.UTF-8");
    puts("Área do aluno");
    puts("Notas e média");
    puts("Atividades");
    return 0;
}
