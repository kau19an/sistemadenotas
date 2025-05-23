#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

struct Aluno {
	char nome[20];
	int RGM[8];
	float a1, a2, af; 
};

struct Login {
	char usuario[10];
	int senha;
};

int main() {
	// Permite as acentuações em português
	setlocale(LC_ALL, "Portuguese");
	
	printf("/---------- MENU ---------\\\n");
	printf("|  (1) Criar usuário      |\n");
	printf("|  (2) Listar usuários    |\n");
	printf("|  (3) Atualizar usuário  |\n");
	printf("|  (4) Deletar usuário    |\n");
	printf("|  (0) Sair               |\n");
	printf("\\-------------------------/\n");
	
	int escolha;
	printf("   Escolha uma opção: ");
	scanf("%d", &escolha);
	
	switch (escolha) {
		case 1:
			struct Login dados;
			
			printf("\n- Digite o nome do usuário (até 9 letras): ");
			scanf("%9s", &dados.usuario);
			printf("- Digite a senha (apenas números): ");
			scanf("%d", &dados.senha);
			printf("\nVocê cadastrou:");
			printf("\n- Nome de usuário: %s", dados.usuario);
			printf("\n- Senha: %d", dados.senha);
			break;
		case 2:
			printf("\nEm andamento...");
			break;
		case 3:
			printf("\nEm andamento...");
			break;
		case 4:
			printf("\nEm andamento...");
			break;
		case 0:
			printf("\nSaindo...");
			exit(0);
	}

/*
	struct Aluno aluno;
	float soma, novaSoma;
	
	// Lê o nome do aluno
	printf("\n- Digite o nome do aluno: ");
	scanf("%s", aluno.nome);
	
	// Lê o RGM do aluno
	printf("- Digite o RGM do aluno: ");
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
		if (novaSoma >= 6) {
			printf("\n%s foi aprovado na AF com média %.2f.", aluno.nome, novaSoma);
		} else {
			printf("\n%s foi reprovado com média %.2f mesmo com a AF.", aluno.nome, novaSoma);
		}
	}
*/
	return 0;
}
