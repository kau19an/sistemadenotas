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

int menu() {
    int escolha;

    printf("/---------- MENU ---------\\\n");
    printf("|  (1) Criar usuário      |\n");
    printf("|  (2) Listar usuários    |\n");
    printf("|  (3) Atualizar usuário  |\n");
    printf("|  (4) Deletar usuário    |\n");
    printf("|  (0) Sair               |\n");
    printf("\\-------------------------/\n");
    printf("   Escolha uma opção: ");
    scanf("%d", &escolha);

    return escolha;
}

int main() {
    // Permite as acentuações em português
    setlocale(LC_ALL, "Portuguese");

    struct Login usuarios[100];
    int totalUsuarios = 0;
    int escolha;

    do {
        // Sempre que a opção escolhida for concluída, o menu é reaberto novamente
        escolha = menu();

        switch (escolha) {
            case 1:
                usuarios[totalUsuarios];

                printf("\n- Digite o nome do usuário (até 9 letras): ");
                scanf("%9s", usuarios[totalUsuarios].usuario);
                printf("- Digite a senha (apenas números): ");
                scanf("%d", &usuarios[totalUsuarios].senha);
                printf("\nVocê cadastrou:");
                printf("\n- Nome de usuário: %s", usuarios[totalUsuarios].usuario);
                printf("\n- Senha: %d\n\n", usuarios[totalUsuarios].senha);
                totalUsuarios++;
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
    } while (escolha != 0);

    return 0;
}
