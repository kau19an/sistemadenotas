#include <ctype.h>  // Para 'toupper()'
#include <locale.h> // Para 'setlocale()'
#include <stdio.h>  // Para a entrada e saída e dados
#include <stdlib.h> // Para 'exit()'
#include <string.h> // Para 'strcpy()', 'strcmp()' e 'strlen()'

struct Aluno {
	char nome[50];
	int RGM;
	float a1, a2, af, media;
	char situacao[10]; // Para "Aprovado" ou "Reprovado"
};

// Funções do programa
// "Limpa" a tela pulando 50 linhas
void limparTela() {
    printf("\nPressione Enter para continuar...");
    getchar(); // "Gasta" o Enter dado nas opções
    getchar(); // Espera o Enter para continuar de fato
    for (int i = 0; i < 50; i++) printf("\n");
}

// Menu
int abrirMenu() {
    int escolha;

    printf("------- MENU -------\n");
    printf("(1) Cadastrar aluno\n"); // C
    printf("(2) Listar alunos\n");   // R
    printf("(3) Atualizar aluno\n"); // U
    printf("(4) Deletar aluno\n");   // D
    printf("(5) Atribuir notas\n");
    printf("(6) Corrigir notas\n");
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

    do {
        printf("> Digite o RGM (até 8 dígitos): ");
        scanf("%d", &aluno[*total].RGM);

        // Se certifica que o RGM tem 8 dígitos limitando-o entre o menor e maior número com 8 dígitos
        if (aluno[*total].RGM < 10000000 || aluno[*total].RGM > 99999999) {
            printf("  (!) RGM inválido. Ele deve possuir 8 dígitos.\n\n");
        }
    } while (aluno[*total].RGM < 10000000 || aluno[*total].RGM > 99999999);

    // Garante que a média e a situação do aluno iniciem zeradas
    aluno[*total].media = 0;
    strcpy(aluno[*total].situacao, "");

    printf("\nVocê cadastrou:");
    printf("\n- %s (RGM: %d)\n", aluno[*total].nome, aluno[*total].RGM);
    (*total)++;
}

// Opção 2 do menu
void listarAlunos(struct Aluno aluno[], int total) {    
    // Caso o usuário deseja ver a lista mas não há nenhum aluno cadastrado
    if (total == 0) {
        printf("\n(!) Nenhum aluno foi cadastrado até o momento.\n");
        return; // Para não continuar com as linhas abaixo
    }

    printf("\nLista de alunos cadastrados:\n");
    for (int i = 0; i < total; i++) {
        printf("(%d) Aluno: %s (RGM: %d)\n", i, aluno[i].nome, aluno[i].RGM);
        
        // Caso o aluno não possua notas atribuídas ainda
        if (strlen(aluno[i].situacao) == 0) {
            printf("    Situação: Atribua notas para que a média seja exibida.\n");
        } else { // Exibe a situação e a média caso já possua
            printf("    Situação: %s com média %.2f.\n", aluno[i].situacao, aluno[i].media);
        }
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
            printf("\n> Digite o novo nome completo (sem espaços): ");
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
                printf("  (!) Por favor, informe apenas caracteres A-Z. Símbolos não são permitidos.\n");
            } else { // Se não possuir, prossegue
                // Joga o nome para maiúsculo (letra por letra)
                for (int i = 0; aluno[indice].nome[i] != '\0'; i++) {
                    aluno[indice].nome[i] = toupper(aluno[indice].nome[i]);
                }
            }

        } while (!valido); // Pede o nome do aluno até todos os caracteres serem A-Z/a-z, ou seja, válido (1)

    do {
        printf("> Digite o novo RGM (até 8 dígitos): ");
        scanf("%d", &aluno[indice].RGM);

        // Se certifica que o RGM tem 8 dígitos limitando-o entre o menor e maior número com 8 dígitos
        if (aluno[indice].RGM < 10000000 || aluno[indice].RGM > 99999999) {
            printf("  (!) RGM inválido. Ele deve possuir 8 dígitos.\n\n");
        }
    } while (aluno[indice].RGM < 10000000 || aluno[indice].RGM > 99999999);

    printf("  (*) Aluno atualizado com sucesso!\n");

    // Reseta todas as notas e a situação do aluno anterior após atualizar
    if (aluno[indice].media > 0 || strlen(aluno[indice].situacao) > 0) {
        aluno[indice].a1 = aluno[indice].a2 = aluno[indice].af = aluno[indice].media = 0;
        strcpy(aluno[indice].situacao, "");
        printf("  (!) As notas do aluno anterior foram deletadas, atribua-as novamente.\n");
    }
    } else {
        printf("  (!) Índice inválido ou não existente.\n");
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

        printf("  (*) Aluno deletado com sucesso!\n");
    } else {
        printf("  (!) Índice inválido ou não existente.\n");
    }
}

// Opção 5 do menu
void atribuirNotas(struct Aluno aluno[], int total) {
    int indice;
    float soma, novaSoma;

    printf("\n> Digite o índice do aluno que receberá a média: ");
    scanf("%d", &indice);

    if (indice >= 0 && indice < total) {
        // Evita com que o usuário possa sobrescrever notas já atribuídas a um aluno
        if (aluno[indice].media > 0 || strlen(aluno[indice].situacao) > 0) {
            printf("  (!) Este aluno já possui notas atribuídas. Em vez disso, corrija-as na opção 6.\n");
            return; // Para não continuar com as linhas abaixo
        }

        // Lê a nota da A1 (aceitando apenas entre 0 a 5)
        do {
            printf("\n> Digite a nota da A1 (0-5): ");
            scanf("%f", &aluno[indice].a1);

            // Caso o usuário coloque um número não aceito
            if (aluno[indice].a1 < 0 || aluno[indice].a1 > 5) {
                printf("  (!) Nota inválida. Ela deve estar entre 0 e 5.\n");
            }
        } while (aluno[indice].a1 < 0 || aluno[indice].a1 > 5);

        // Lê a nota da A2 (aceitando apenas entre 0 a 5)
        do {
            printf("> Digite a nota da A2 (0-5): ");
            scanf("%f", &aluno[indice].a2);

            // Caso o usuário coloque um número não aceito
            if (aluno[indice].a2 < 0 || aluno[indice].a2 > 5) {
                printf("  (!) Nota inválida. Digite um valor entre 0 e 5.\n\n");
            }
        } while (aluno[indice].a2 < 0 || aluno[indice].a2 > 5);

        // Calcula a média
        soma = aluno[indice].a1 + aluno[indice].a2;

        // Se a média for 6 ou mais, é aprovado
        if (soma >= 6) {
            printf("\n(*) %s foi aprovado com média %.2f.\n", aluno[indice].nome, soma);
            aluno[indice].media = soma;
            strcpy(aluno[indice].situacao, "Aprovado");
        } else {
            printf("\n(*) %s foi reprovado com média %.2f e deverá fazer AF.\n", aluno[indice].nome, soma);

            // Lê a nota da AF (aceitando apenas entre 0 a 5)
            do {
                printf("    > Digite a nota da AF (0-5): ");
                scanf("%f", &aluno[indice].af);

                // Caso o usuário coloque um número não aceito
                if (aluno[indice].af < 0 || aluno[indice].af > 5) {
                    printf("      (!) Nota inválida. Digite um valor entre 0 e 5.\n\n");
                }
            } while (aluno[indice].af < 0 || aluno[indice].af > 5);

            // Verifica se a AF pode ajudar na nota da A1 e A2 e só as substituem se ela for maior
            if (aluno[indice].af > aluno[indice].a1 || aluno[indice].af > aluno[indice].a2) {
                if (aluno[indice].a1 < aluno[indice].a2) {
                    aluno[indice].a1 = aluno[indice].af;
                } else {
                    aluno[indice].a2 = aluno[indice].af;
                }

                // Calcula a nova média
                novaSoma = aluno[indice].a1 + aluno[indice].a2;
                aluno[indice].media = novaSoma;

                // Se a média for 6 ou mais, é aprovado
                if (novaSoma >= 6) {
                    printf("\n(*) %s foi aprovado na AF com média %.2f.\n", aluno[indice].nome, novaSoma);
                    strcpy(aluno[indice].situacao, "Aprovado"); // Atribui "Aprovado" à situação do aluno
                } else { // Senão, é reprovado
                    printf("\n(*) %s foi reprovado com média %.2f mesmo após a AF.\n", aluno[indice].nome, novaSoma);
                    strcpy(aluno[indice].situacao, "Reprovado"); // Atribui "Reprovado" à situação do aluno
                }
            } else {
                aluno[indice].media = soma;
                strcpy(aluno[indice].situacao, "Reprovado");
                printf("\n(!) A AF é menor que a A1 e A2 e o aluno permanece reprovado com média %.2f.\n", soma);
            }
        }
    } else {
        printf("  (!) Índice inválido ou não existente.\n");
    }
}

// Opção 6 do menu
void corrigirNotas(struct Aluno aluno[], int total) {
    int indice;
    float soma, novaSoma;
    char situacaoAnterior[10];

    printf("\n> Digite o índice do aluno que terá suas notas atualizadas: ");
    scanf("%d", &indice);

    if (indice >= 0 && indice < total) {
        // Evita com que o usuário corrija notas que nem sequer foram atribuídas ainda ao aluno
        if (aluno[indice].media == 0 && strlen(aluno[indice].situacao) == 0) {
            printf("  (!) Este aluno ainda não possui notas. Em vez disso, atribua-as na opção 5.\n");
            return; // Para não continuar com as linhas abaixo
        }

        // Copia a situação atual do aluno numa nova variável para futura comparação
        strcpy(situacaoAnterior, aluno[indice].situacao);

        // Lê novamente a nota da A1 (aceitando apenas entre 0 a 5)
        do {
            printf("  > Digite a nova nota da A1 (0-5): ");
            scanf("%f", &aluno[indice].a1);

            // Caso o usuário coloque um número não aceito
            if (aluno[indice].a1 < 0 || aluno[indice].a1 > 5) {
                printf("    (!) Nota inválida. Digite um valor entre 0 e 5.\n\n");
            }
        } while (aluno[indice].a1 < 0 || aluno[indice].a1 > 5);

        // Lê novamente a nota da A2 (aceitando apenas entre 0 a 5)
        do {
            printf("  > Digite a nova nota da A2 (0-5): ");
            scanf("%f", &aluno[indice].a2);

            // Caso o usuário coloque um número não aceito
            if (aluno[indice].a2 < 0 || aluno[indice].a2 > 5) {
                printf("    (!) Nota inválida. Digite um valor entre 0 e 5.\n\n");
            }
        } while (aluno[indice].a2 < 0 || aluno[indice].a2 > 5);

        // Calcula novamente a média
        soma = aluno[indice].a1 + aluno[indice].a2;

        // Se a média for 6 ou mais, é aprovado
        if (soma >= 6) {
            aluno[indice].media = soma;
            strcpy(aluno[indice].situacao, "Aprovado"); // Atribui "Aprovado" à situação do aluno
        } else { // Senão, pede a AF
            printf("\n(*) %s foi reprovado com nova média %.2f e deverá fazer AF.\n", aluno[indice].nome, soma);

            // Lê novamente a nota da AF (aceitando apenas entre 0 a 5)
            do {
                printf("    > Digite a nova nota da AF (0-5): ");
                scanf("%f", &aluno[indice].af);

                // Caso o usuário coloque um número não aceito
                if (aluno[indice].af < 0 || aluno[indice].af > 5) {
                    printf("      (!) Nota inválida. Digite um valor entre 0 e 5.\n\n");
                }
            } while (aluno[indice].af < 0 || aluno[indice].af > 5);

            // Verifica se a AF pode ajudar na nota da A1 e A2 e só as substituem se ela for maior
            if (aluno[indice].af > aluno[indice].a1 || aluno[indice].af > aluno[indice].a2) {
                if (aluno[indice].a1 < aluno[indice].a2) {
                    aluno[indice].a1 = aluno[indice].af;
                } else {
                    aluno[indice].a2 = aluno[indice].af;
                }

                // Recalcula a nova média
                novaSoma = aluno[indice].a1 + aluno[indice].a2;
                aluno[indice].media = novaSoma;

                // Atualiza a situação do aluno
                if (novaSoma >= 6) {
                    strcpy(aluno[indice].situacao, "Aprovado");
                } else {
                    strcpy(aluno[indice].situacao, "Reprovado");
                }
            } else {
                aluno[indice].media = soma;
                strcpy(aluno[indice].situacao, "Reprovado");
            }
        }

        // Verifica se a situação mudou
        if (strcmp(situacaoAnterior, aluno[indice].situacao) != 0) {
            printf("\n(*) %s obteve a média %.2f e sua situação foi alterada para \"%s\".\n", aluno[indice].nome, aluno[indice].media, aluno[indice].situacao);
        } else {
            printf("\n(*) %s obteve a média %.2f e sua situação permanece \"%s\".\n", aluno[indice].nome, aluno[indice].media, aluno[indice].situacao);
        }
    } else {
        printf("  (!) Índice inválido ou não existente.\n");
    }
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
                limparTela();
                break;
            case 2:
                listarAlunos(aluno, totalAlunos);
                limparTela();
                break;
            case 3:
                atualizarAluno(aluno, totalAlunos);
                limparTela();
                break;
            case 4:
                deletarAluno(aluno, &totalAlunos);
                limparTela();
                break;
            case 5:
                atribuirNotas(aluno, totalAlunos);
                limparTela();
                break;
            case 6:
                corrigirNotas(aluno, totalAlunos);
                limparTela();
                break;
            case 0:
                // Opção 0 do menu
                printf("\nSaindo...");
                exit(0);
            default:
                // Caso o usuário digite outro número que não esteja entre 0-6
                printf("  (!) Digite uma opção válida.\n");
                limparTela();
                break;
        }
    } while (escolha != 0);

    return 0;
}
