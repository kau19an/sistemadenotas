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

// Funções do programa
int abrirMenu() {
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

// Opção 1 do menu
void criarUsuarios(struct Login usuarios[], int *total) {
    usuarios[*total];
    
    printf("\n- Digite o nome do usuário (máx. 9 letras): ");
    scanf("%9s", usuarios[*total].usuario);
    printf("- Digite a senha (apenas números): ");
    scanf("%d", &usuarios[*total].senha);
    printf("\nVocê cadastrou:");
    printf("\n- Nome de usuário: %s", usuarios[*total].usuario);
    printf("\n- Senha: %d\n\n", usuarios[*total].senha);
    (*total)++;
}

// Opção 2 do menu
void listarUsuarios(struct Login usuarios[], int total) {    
    // Caso o usuário deseja ver a lista mas não há nenhum cadastrado
    if (total == 0) {
        printf("\nNenhum usuário foi cadastrado até o momento.\n\n");
        return; // Para não continuar com as linhas abaixo
    }

    printf("\nLista de usuários cadastrados:\n");
    for (int i = 0; i < total; i++) {
        printf("(%d) Usuário: %s - Senha: %d\n", i, usuarios[i].usuario, usuarios[i].senha);
    }
    printf("\n");
}

// Opção 3 do menu
void atualizarUsuarios(struct Login usuarios[], int total) {
    int indice;

    printf("\nDigite o índice do usuário a ser atualizado: ");
    scanf("%d", &indice);

    if (indice >= 0 && indice < total) {
        printf("\nNovo nome de usuário (máx. 9 letras): ");
        scanf("%9s", usuarios[indice].usuario);
        
        printf("Nova senha: ");
        scanf("%d", &usuarios[indice].senha);

        printf("\nUsuário atualizado com sucesso!\n\n");
    } else {
        printf("- Índice inválido ou não existente.\n\n");
    }
}

// Opção 4 do menu
void deletarUsuarios(struct Login usuarios[], int *total) {
    int indice;

    printf("\nDigite o índice do usuário a ser deletado: ");
    scanf("%d", &indice);

    if (indice >= 0 && indice < *total) {
        for (int i = indice; i < *total - 1; i++) {
            usuarios[i] = usuarios[i + 1];
        }

        (*total)--;

        printf("\nUsuário deletado com sucesso!\n\n");
    } else {
        printf("- Índice inválido ou não existente.\n\n");
    }
}

int main() {
    // Permite as acentuações em português
    setlocale(LC_ALL, "Portuguese");

    struct Login usuarios[100];
    int totalUsuarios = 0;
    int escolha;

    do {
        // Sempre que a opção escolhida for concluída, o menu é reaberto novamente
        escolha = abrirMenu();

        switch (escolha) {
            case 1:
                criarUsuarios(usuarios, &totalUsuarios);
                break;
            case 2:
                listarUsuarios(usuarios, totalUsuarios);
                break;
            case 3:
                atualizarUsuarios(usuarios, totalUsuarios);
                break;
            case 4:
                deletarUsuarios(usuarios, &totalUsuarios);
                break;
            case 0:
                // Opção 0 do menu
                printf("\nSaindo...");
                exit(0);
        }
    } while (escolha != 0);

    return 0;
}
