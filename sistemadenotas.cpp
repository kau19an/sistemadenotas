#include <stdio.h>
#include <locale.h>

int main() {
	// Permite as acentuações em português
	setlocale(LC_ALL, "Portuguese");
	
	float a1, a2, af, soma;
	char nomeAluno[20];
	int RGM[8];
	
	// Lê o nome do aluno
	printf("Digite o nome do aluno: ");
	scanf("%s", nomeAluno);
	
	// Lê o RGM do aluno
	printf("Digite o RGM do aluno: ");
	scanf("%d", RGM);
	
	// Lê a nota da A1 (no raio de 0-5)
	do {
		printf("- Digite a nota da A1: ");
		scanf("%f", &a1);
	} while (a1 < 0 || a1 > 5);
	
	// Lê a nota da A2 (no raio de 0-5)
	do {
		printf("- Digite a nota da A2: ");
		scanf("%f", &a2);
	} while (a2 < 0 || a2 > 5);

	// Soma as duas notas e informa o status do aluno
	soma = a1 + a2;
	if (soma >= 6) {
		printf("\n%s foi aprovado com média %.2f.", nomeAluno, soma);
	} else {
		printf("\n%s foi reprovado com média %.2f e deverá fazer AF.", nomeAluno, soma);
		
		// Lê a nota da AF (no raio de 0-5)
		do {
			printf("\n- Digite a nota da AF: ");
			scanf("%f", &af);
		} while (af < 0 || af > 5);
		
		// Substitui a menor nota entre A1 e A2 pela AF
		float novaSoma;
		if (af > a1) {
			a1 = af;
		} else if (af > a2) {
			a2 = af;
		}
		
		novaSoma = a1 + a2;
		
		// Exibe o status do aluno pós-AF
		if (af >= 6) {
			printf("\n%s foi aprovado na AF com média %.2f.", nomeAluno, novaSoma);
		} else {
			printf("\n%s foi reprovado com média %.2f mesmo com a AF.", nomeAluno, novaSoma);
		}
	}

	return 0;
}
