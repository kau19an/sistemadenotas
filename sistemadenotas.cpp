#include <stdio.h>
#include <locale.h>

int main() {
	setlocale(LC_ALL, "Portuguese");
	
	float a1, a2, af, soma;
	char nomeAluno[20];
	int RGM[8];
	
	printf("Digite o nome do aluno: ");
	scanf("%s", nomeAluno);
	
	printf("Digite o RGM do aluno: ");
	scanf("%d", RGM);
	
	do {
		printf("- Digite a nota da A1: ");
		scanf("%f", &a1);
	} while (a1 < 0 || a1 > 5);
	
	do {
		printf("- Digite a nota da A2: ");
		scanf("%f", &a2);
	} while (a2 < 0 || a2 > 5);

	soma = a1 + a2;
	if (soma >= 6) {
		printf("\n%s foi aprovado com média %.2f.", nomeAluno, soma);
	} else {
		printf("\n%s foi reprovado com média %.2f.", nomeAluno, soma);
	}

	return 0;
}
