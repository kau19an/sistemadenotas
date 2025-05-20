#include <stdio.h>

int main() {
	float a1, a2, af, soma;
	printf("Digite a nota da A1: ");
	scanf("%f", &a1);
	printf("Digite a nota da A2: ");
	scanf("%f", &a2);
	
	soma = a1 + a2;
	if (soma >= 6) {
		printf("Aprovado.");
	} else {
		printf("Reprovado.");
	}

	return 0;
}
