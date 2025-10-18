#include <stdio.h>
#include <locale.h>

int main(void)
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
