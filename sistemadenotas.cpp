#include <ctype.h>  // Para 'toupper()'
#include <locale.h> // Para 'setlocale()'
#include <stdio.h>  // Para a entrada e saída e dados
#include <stdlib.h> // Para 'exit()'
#include <string.h> // Para 'strcpy()'

struct Aluno {
	char nome[50];
	int RGM;
	float a1, a2, af, media;
    char situacao[10]; // Para "Aprovado" ou "Reprovado"
};

// Funções do programa
int abrirMenu() {
    int escolha;

    printf("------- MENU -------\n");
    printf("(1) Cadastrar aluno\n"); // C
    printf("(2) Listar alunos\n");   // R
    printf("(3) Atualizar aluno\n"); // U
    printf("(4) Deletar aluno\n");   // D
    printf("(5) Atribuir notas\n");
    printf("(6) Corrigir notas\n");
    printf("(7) Deletar notas\n");
    printf("(0) Sair\n\n");
    printf("> Escolha uma opção: ");
    scanf("%d", &escolha);

    return escolha;
}

// Opção 1 do menu
void cadastrarAluno(struct Aluno aluno[], int *total) {
    aluno[*total];
    int valido = 1;
    
    do {
        printf("\n> Digite o nome completo do aluno (sem espaços): ");
        scanf("%s", aluno[*total].nome);
        
        // Passa por cada letra do nome e verifica se são caracteres A-Z/a-z
        for (int i = 0; aluno[*total].nome[i] != '\0'; i++) {
            char c = aluno[*total].nome[i];
            // Se forem, continua
            if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
                valido = 1;
                continue;
            } else {
                // Se possuir algum outro caractere além de A-Z/a-z, é considerado inválido (0)
                valido = 0;
                break;
            }
        }

        if (!valido) {
            printf("  (!) Por favor, informe apenas caracteres A-Z. Símbolos não são permitidos.\n");
        } else { // Se não possuir, prossegue
            // Joga o nome para maiúsculo (letra por letra)
            for (int i = 0; aluno[*total].nome[i] != '\0'; i++) {
                aluno[*total].nome[i] = toupper(aluno[*total].nome[i]);
            }
        }
    } while (!valido); // Pede o nome do aluno até todos os caracteres serem A-Z/a-z, ou seja, válido (1)

    printf("> Digite o RGM: ");
    scanf("%d", &aluno[*total].RGM);
    printf("\nVocê cadastrou:");
    printf("\n- %s (RGM: %d)\n\n", aluno[*total].nome, aluno[*total].RGM);
    (*total)++;
}

// Opção 2 do menu
void listarAlunos(struct Aluno aluno[], int total) {    
    // Caso o usuário deseja ver a lista mas não há nenhum aluno cadastrado
    if (total == 0) {
        printf("\n(!) Nenhum aluno foi cadastrado até o momento.\n\n");
        return; // Para não continuar com as linhas abaixo
    }

    printf("\nLista de alunos cadastrados:\n");
    for (int i = 0; i < total; i++) {
        printf("(%d) Aluno: %s (RGM: %d)\n", i, aluno[i].nome, aluno[i].RGM);
        printf("    Situação: %s com média %.2f.\n\n", aluno[i].situacao, aluno[i].media);
    }
}

// Opção 3 do menu
void atualizarAluno(struct Aluno aluno[], int total) {
    int indice;

    printf("\n> Digite o índice do aluno a ser atualizado: ");
    scanf("%d", &indice);

    if (indice >= 0 && indice < total) {
        int valido = 1;
        do {
            printf("  Digite o novo nome completo (sem espaços): ");
            scanf("%s", aluno[indice].nome);

            // Passa por cada letra do nome e verifica se são caracteres A-Z/a-z
            for (int i = 0; aluno[indice].nome[i] != '\0'; i++) {
                char c = aluno[indice].nome[i];
                if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
                    // Se forem, continua
                    valido = 1;
                    continue;
                } else {
                    // Se possuir algum outro caractere além de A-Z/a-z, é considerado inválido (0)
                    valido = 0;
                    break;
                }
            }

            if (!valido) {
                printf("  (!) Por favor, informe apenas caracteres A-Z. Símbolos não são permitidos.\n\n");
            } else { // Se não possuir, prossegue
                // Joga o nome para maiúsculo (letra por letra)
                for (int i = 0; aluno[indice].nome[i] != '\0'; i++) {
                    aluno[indice].nome[i] = toupper(aluno[indice].nome[i]);
                }
            }

        } while (!valido); // Pede o nome do aluno até todos os caracteres serem A-Z/a-z, ou seja, válido (1)

        printf("  Digite o novo RGM: ");
        scanf("%d", &aluno[indice].RGM);

        printf("  (*) Aluno atualizado com sucesso!\n\n");
    } else {
        printf("  (!) Índice inválido ou não existente.\n\n");
    }
}

// Opção 4 do menu
void deletarAluno(struct Aluno aluno[], int *total) {
    int indice;

    printf("\n> Digite o índice do aluno a ser deletado: ");
    scanf("%d", &indice);

    if (indice >= 0 && indice < *total) {
        for (int i = indice; i < *total - 1; i++) {
            aluno[i] = aluno[i + 1];
        }

        (*total)--;

        printf("  (*) Aluno deletado com sucesso!\n\n");
    } else {
        printf("  (!) Índice inválido ou não existente.\n\n");
    }
}

// Opção 5 do menu
void atribuirNotas(struct Aluno aluno[], int total) {
    int indice;
    float soma, novaSoma;

    printf("\n> Digite o índice do aluno que receberá a média: ");
    scanf("%d", &indice);

    if (indice >= 0 && indice < total) {
        // Lê a nota da A1
        do {
            printf("  Digite a nota da A1 (0-5): ");
            scanf("%f", &aluno[indice].a1);
        } while (aluno[indice].a1 < 0 || aluno[indice].a1 > 5);

        // Lê a nota da A2
        do {
            printf("  Digite a nota da A2 (0-5): ");
            scanf("%f", &aluno[indice].a2);
        } while (aluno[indice].a2 < 0 || aluno[indice].a2 > 5);

        // Calcula a média
        soma = aluno[indice].a1 + aluno[indice].a2;

        // Se a média for 6 ou mais, é aprovado
        if (soma >= 6) {
            printf("\n(*) %s foi aprovado com média %.2f.\n\n", aluno[indice].nome, soma);
            aluno[indice].media = soma;
            strcpy(aluno[indice].situacao, "Aprovado"); // Atribui "Aprovado" à situação do aluno
        } else { // Senão, pede a AF
            printf("\n(*) %s foi reprovado com média %.2f e deverá fazer AF.\n", aluno[indice].nome, soma);

            // Lê a nota da AF
            do {
                printf("> Digite a nota da AF (0-5): ");
                scanf("%f", &aluno[indice].af);
            } while (aluno[indice].af < 0 || aluno[indice].af > 5);

            // Substitui a menor nota entre A1 e A2 pela AF
            if (aluno[indice].a1 < aluno[indice].a2) {
                aluno[indice].a1 = aluno[indice].af;
            } else {
                aluno[indice].a2 = aluno[indice].af;
            }

            // Calcula a nova média
            novaSoma = aluno[indice].a1 + aluno[indice].a2;

            // Se a média for 6 ou mais, é aprovado
            if (novaSoma >= 6) {
                printf("\n(*) %s foi aprovado na AF com média %.2f.\n\n", aluno[indice].nome, novaSoma);
                aluno[indice].media = novaSoma;
                strcpy(aluno[indice].situacao, "Aprovado"); // Atribui "Aprovado" à situação do aluno
            } else { // Senão, é reprovado
                printf("\n(*) %s foi reprovado com média %.2f mesmo após a AF.\n\n", aluno[indice].nome, novaSoma);
                aluno[indice].media = novaSoma;
                strcpy(aluno[indice].situacao, "Reprovado"); // Atribui "Reprovado" à situação do aluno
            }
        }
    } else {
        printf("  (!) Índice inválido ou não existente.\n\n");
    }
}

// Opção 6 do menu
void atualizarNotas(struct Aluno aluno[], int total) {
    int indice;

    printf("\n> Digite o índice do aluno que terá suas notas atualizadas: ");
    scanf("%d", &indice);

    // TODO
}

// Opção 7 do menu
void deletarNotas(struct Aluno aluno[], int total) {
    int indice;

    printf("\n> Digite o índice do aluno que terá suas notas deletadas: ");
    scanf("%d", &indice);

    // TODO
}

int main() {
    // Permite as acentuações em português
    setlocale(LC_ALL, "Portuguese");

    struct Aluno aluno[100];
    int totalAlunos = 0;
    int escolha;

    do {
        // Sempre que a opção escolhida for concluída, o menu é reaberto novamente
        escolha = abrirMenu();

        switch (escolha) {
            case 1:
                cadastrarAluno(aluno, &totalAlunos);
                break;
            case 2:
                listarAlunos(aluno, totalAlunos);
                break;
            case 3:
                atualizarAluno(aluno, totalAlunos);
                break;
            case 4:
                deletarAluno(aluno, &totalAlunos);
                break;
            case 5:
                atribuirNotas(aluno, totalAlunos);
                break;
            case 6:
                printf("Em andamento...\n\n");
                break;
            case 7:
                printf("Em andamento...\n\n");
                break;
            case 0:
                // Opção 0 do menu
                printf("\nSaindo...");
                exit(0);
        }
    } while (escolha != 0);

    return 0;
}
