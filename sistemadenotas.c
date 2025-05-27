#include <ctype.h>  // Para 'toupper()'
#include <locale.h> // Para 'setlocale()'
#include <stdio.h>  // Para a entrada e saída e dados
#include <stdlib.h> // Para 'exit()', 'system()' e 'atoi()'
#include <string.h> // Para 'strcpy()', 'strcmp()' e 'strlen()'

#define max_alunos 100 // Define a quantidade máxima de alunos que podem ser cadastrados (padrão: 100)

struct Aluno {
	char nome[50];
	int RGM;
	float a1, a2, af, media;
	char situacao[10]; // Para "Aprovado" ou "Reprovado"
};

// Funções do programa
// Limpar a tela
void limparTela() {
    system("pause");
	system("cls");
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
    int valido, RGMTemp;
    char nomeTemp[50], RGMTempString[9];

    if (*total >= max_alunos) {
        printf("\n(!) Limite máximo de alunos atingido. Não é possível cadastrar mais.\n");
        return; // Para não continuar com as linhas abaixo
    }

    // Lê e valida o nome
    do {
        valido = 1;

        printf("\n> Digite o nome completo do aluno (sem espaços): ");
        scanf("%s", nomeTemp);
        
        // Passa por cada letra do nome e verifica se são caracteres A-Z/a-z
        for (int i = 0; nomeTemp[i] != '\0'; i++) {
            char c = nomeTemp[i];
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
            for (int i = 0; nomeTemp[i] != '\0'; i++) {
                nomeTemp[i] = toupper(nomeTemp[i]);
            }

            // Verifica se o nome já está cadastrado para evitar duplicidade
            for (int i = 0; i < *total; i++) {
                if (strcmp(aluno[i].nome, nomeTemp) == 0) {
                    printf("  (!) Já existe um aluno com esse nome cadastrado. Escolha outro.\n");
                    valido = 0;
                    break;
                }
            }
        }
    } while (!valido); // Pede o nome do aluno até todos os caracteres serem A-Z/a-z, ou seja, válido (1)

    // Lê e valida o RGM
	do {
	    valido = 1;
	
	    printf("> Digite o RGM (até 8 dígitos): ");
	    scanf("%s", RGMTempString); // Para armazenar o RGM primeiro como string e permitir as verificações
	
	    // Verifica se todos os caracteres são dígitos
	    for (int i = 0; RGMTempString[i] != '\0'; i++) {
	        if (!isdigit(RGMTempString[i])) {
	            printf("  (!) Por favor, informe apenas números. Letras ou símbolos não são permitidos.\n\n");
	            valido = 0;
	            break;
	        }
	    }
	
	    // Se todos forem números, verifica se tem exatamente 8 dígitos
	    if (valido) {
	        if (strlen(RGMTempString) != 8) {
	            printf("  (!) RGM inválido. Ele deve possuir 8 dígitos.\n\n");
	            valido = 0;
	        } else { // Se sim, converte o RGM (string) para RGM (inteiro)
	            RGMTemp = atoi(RGMTempString);
	
	            for (int i = 0; i < *total; i++) {
	            	// Verifica se o RGM já está cadastrado para evitar duplicidade
	                if (aluno[i].RGM == RGMTemp) {
	                    printf("  (!) Já existe um aluno com esse RGM cadastrado. Escolha outro.\n\n");
	                    valido = 0;
	                    break;
	                }
	            }
	        }
	    }
	} while (!valido);

    // Armazena os dados já validados e garante que a média e a situação do aluno iniciem zeradas
    strcpy(aluno[*total].nome, nomeTemp);
    aluno[*total].RGM = RGMTemp;
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
        int valido;
        char nomeTemp[50];
        int RGMTemp;

        // Lê e valida o nome
        do {
            valido = 1;
            printf("\n> Digite o novo nome completo (sem espaços): ");
            scanf("%s", nomeTemp);

            // Passa por cada letra do nome e verifica se são caracteres A-Z/a-z
            for (int i = 0; nomeTemp[i] != '\0'; i++) {
                char c = nomeTemp[i];
                if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))) {
                    // Se não forem, é considerado inválido (0)
                    valido = 0;
                    break;
                }
            }

            if (!valido) {
                printf("  (!) Por favor, informe apenas caracteres A-Z. Símbolos não são permitidos.\n");
            } else { // Se forem, prossegue
                // Joga o nome para maiúsculo (letra por letra)
                for (int i = 0; nomeTemp[i] != '\0'; i++) {
                    nomeTemp[i] = toupper(nomeTemp[i]);
                }

                for (int i = 0; i < total; i++) {
                    // Verifica se o nome já está cadastrado para evitar duplicidade
                    if (i != indice && strcmp(aluno[i].nome, nomeTemp) == 0) {
                        printf("  (!) Já existe um aluno com esse nome cadastrado. Escolha outro.\n");
                        valido = 0;
                        break;
                    }
                }
            }
        } while (!valido);

        // Lê e valida o RGM
		do {
		    valido = 1;
		    char RGMTempString[9]; // Para armazenar o RGM primeiro como string e permitir as verificações
		
		    printf("> Digite o novo RGM (até 8 dígitos): ");
		    scanf("%s", RGMTempString);
		
		    // Verifica se todos os caracteres são dígitos
		    for (int i = 0; RGMTempString[i] != '\0'; i++) {
		        if (!isdigit(RGMTempString[i])) {
		            printf("  (!) Por favor, informe apenas números. Letras ou símbolos não são permitidos.\n\n");
		            valido = 0;
		            break;
		        }
		    }
		
		    // Se todos forem números, verifica se tem exatamente 8 dígitos
		    if (valido) {
		        if (strlen(RGMTempString) != 8) {
		            printf("  (!) RGM inválido. Ele deve possuir 8 dígitos.\n\n");
		            valido = 0;
		        } else { // Se sim, converte o RGM (string) para RGM (inteiro)
		            RGMTemp = atoi(RGMTempString);
		
		            for (int i = 0; i < total; i++) {
		                // Verifica se o RGM já está cadastrado para evitar duplicidade
		                if (i != indice && aluno[i].RGM == RGMTemp) {
		                    printf("  (!) Já existe um aluno com esse RGM cadastrado. Escolha outro.\n\n");
		                    valido = 0;
		                    break;
		                }
		            }
		        }
		    }
		} while (!valido);

        // Armazena os dados já validados
        strcpy(aluno[indice].nome, nomeTemp);
        aluno[indice].RGM = RGMTemp;

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

    // Deleta e passa o índice dos alunos anteriores uma casa para trás
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
            } else { // A mesma mensagem de reprovado acima mas para caso a AF não ajude
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
            printf("\n(*) %s foi reprovado com média %.2f e deverá fazer AF.\n", aluno[indice].nome, soma);

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
            } else { // A mesma atribuição de reprovado acima mas para caso a AF não ajude
                aluno[indice].media = soma;
                strcpy(aluno[indice].situacao, "Reprovado");
            }
        }

        // Verifica se a situação mudou
        if (strcmp(situacaoAnterior, aluno[indice].situacao) != 0) {
            printf("\n(*) %s obteve a média %.2f e sua situação foi alterada para \"%s\".\n", aluno[indice].nome, aluno[indice].media, aluno[indice].situacao);
        } else { // Caso a situação continue igual mesmo após a correção
            printf("\n(*) %s obteve a média %.2f e sua situação permanece \"%s\".\n", aluno[indice].nome, aluno[indice].media, aluno[indice].situacao);
        }
    } else {
        printf("  (!) Índice inválido ou não existente.\n");
    }
}

int main() {
    // Permite as acentuações em português
    setlocale(LC_ALL, "Portuguese");

    struct Aluno aluno[max_alunos];
    int totalAlunos = 0; // Inicia a contagem de alunos em 0
    int escolha;

    do {
        // Sempre que a opção escolhida for concluída, o menu é reaberto novamente
        escolha = abrirMenu();
        
        switch (escolha) {
            case 1:
                cadastrarAluno(aluno, &totalAlunos);
                limparTela();
                break; // Para voltar ao menu
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
