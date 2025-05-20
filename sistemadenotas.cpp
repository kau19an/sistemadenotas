#include <stdio.h>

int main() {
	float a1, a2, af, soma;
	
	do {
		printf("Digite a nota da A1: ");
		scanf("%f", &a1);
	} while (a1 < 0 || a1 > 5);
	
	do {
		printf("Digite a nota da A2: ");
		scanf("%f", &a2);
	} while (a2 < 0 || a2 > 5);

	soma = a1 + a2;
	if (soma >= 6) {
		printf("\nO aluno foi aprovado com média %.2f.", soma);
	} else {
		printf("\nO aluno foi reprovado com média %.2f.", soma);
	}

	return 0;
}
