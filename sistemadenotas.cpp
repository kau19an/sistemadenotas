#include <stdio.h>
#include <locale.h>

struct Aluno {
	char nome[20];
	int RGM[8];
	float a1, a2, af;
};

int main() {
	struct Aluno aluno;
	float soma, novaSoma;
	
	// Permite as acentuações em português
	setlocale(LC_ALL, "Portuguese");
	
	// Lê o nome do aluno
	printf("Digite o nome do aluno: ");
	scanf("%s", aluno.nome);
	
	// Lê o RGM do aluno
	printf("Digite o RGM do aluno: ");
	scanf("%d", aluno.RGM);
	
	// Lê a nota da A1 (no raio de 0-5)
	do {
		printf("- Digite a nota da A1: ");
		scanf("%f", &aluno.a1);
	} while (aluno.a1 < 0 || aluno.a1 > 5);
	
	// Lê a nota da A2 (no raio de 0-5)
	do {
		printf("- Digite a nota da A2: ");
		scanf("%f", &aluno.a2);
	} while (aluno.a2 < 0 || aluno.a2 > 5);

	// Soma as duas notas e informa o status do aluno
	soma = aluno.a1 + aluno.a2;
	if (soma >= 6) {
		printf("\n%s foi aprovado com média %.2f.", aluno.nome, soma);
	} else {
		printf("\n%s foi reprovado com média %.2f e deverá fazer AF.", aluno.nome, soma);
		
		// Lê a nota da AF (no raio de 0-5)
		do {
			printf("\n- Digite a nota da AF: ");
			scanf("%f", &aluno.af);
		} while (aluno.af < 0 || aluno.af > 5);
		
		// Substitui a menor nota entre A1 e A2 pela AF
		if (aluno.af > aluno.a1) {
			aluno.a1 = aluno.af;
		} else if (aluno.af > aluno.a2) {
			aluno.a2 = aluno.af;
		}
		
		novaSoma = aluno.a1 + aluno.a2;
		
		// Exibe o status do aluno pós-AF
		if (aluno.af >= 6) {
			printf("\n%s foi aprovado na AF com média %.2f.", aluno.nome, novaSoma);
		} else {
			printf("\n%s foi reprovado com média %.2f mesmo com a AF.", aluno.nome, novaSoma);
		}
	}

	return 0;
}
