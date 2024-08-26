#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>

#define MAX_FUNCIONARIOS 500
#define MAX_PROJETOS 2000
#define MAX_EMAILS 500

// Estrutura pra funcionário
typedef struct {
    int numero_funcional;
    char nome[100];
    float salario;
} Funcionario;

// Estrutura pra projeto
typedef struct {
    char nome[100];
    char data_inicio[11];
    time_t data_termino;
    int tempo_estimado_projeto;
    float valor_estimado;
    int numero_funcional_responsavel;
    int p_finalizado;
} Projeto;

Funcionario funcionarios[MAX_FUNCIONARIOS];
Projeto projetos[MAX_PROJETOS];
char emails[MAX_EMAILS][100];
int num_funcionarios = 0;
int num_projetos = 0;

// Ordenar funcionários por número funcional
void ordenar_funcionarios() {
    for (int i = 0; i < num_funcionarios - 1; i++) {
        for (int j = 0; j < num_funcionarios - i - 1; j++) {
            if (funcionarios[j].numero_funcional > funcionarios[j + 1].numero_funcional) {
                Funcionario temp = funcionarios[j];
                funcionarios[j] = funcionarios[j + 1];
                funcionarios[j + 1] = temp;
            }
        }
    }
}

// Ordenação de projetos por nome
void ordenar_projetos() {
    for (int i = 0; i < num_projetos - 1; i++) {
        for (int j = 0; j < num_projetos - i - 1; j++) {
            if (strcmp(projetos[j].nome, projetos[j + 1].nome) > 0) {
                Projeto temp = projetos[j];
                projetos[j] = projetos[j + 1];
                projetos[j + 1] = temp;
            }
        }
    }
}

// Adicionar um funcionário
void adicionar_funcionario() {
    if (num_funcionarios >= MAX_FUNCIONARIOS) {
        printf("Número máximo de funcionários alcançado.\n");
        return;
    }
    Funcionario f;
    printf("Digite o número funcional: ");
    scanf("%d", &f.numero_funcional);
    printf("Digite o nome: ");
    scanf(" %[^\n]s", f.nome);
    printf("Digite o salário: ");
    scanf("%f", &f.salario);

    for (int i = 0; i < num_funcionarios; i++) {
        if (funcionarios[i].numero_funcional == f.numero_funcional) {
            printf("Número funcional já cadastrado.\n");
            return;
        }
    }

    funcionarios[num_funcionarios++] = f;
    ordenar_funcionarios();
    printf("Funcionário adicionado com sucesso.\n");
}

// Remover funcionário do programa
void remover_funcionario() {
    int numero_funcional;
    printf("Digite o número funcional do funcionário a ser removido: ");
    scanf("%d", &numero_funcional);

    for (int i = 0; i < num_funcionarios; i++) {
        if (funcionarios[i].numero_funcional == numero_funcional) {
            for (int j = i; j < num_funcionarios - 1; j++) {
                funcionarios[j] = funcionarios[j + 1];
            }
            num_funcionarios--;
            ordenar_funcionarios();
            printf("Funcionário removido com sucesso.\n");
            return;
        }
    }
    printf("Número funcional não encontrado.\n");
}

// Alterar funcionário
void alterar_funcionario() {
    int numero_funcional;
    printf("Digite o número funcional do funcionário a ser alterado: ");
    scanf("%d", &numero_funcional);

    for (int i = 0; i < num_funcionarios; i++) {
        if (funcionarios[i].numero_funcional == numero_funcional) {
            printf("Digite o novo nome (ou pressione Enter para manter): ");
            char novo_nome[100];
            scanf(" %[^\n]s", novo_nome);
            if (strlen(novo_nome) > 0) {
                strcpy(funcionarios[i].nome, novo_nome);
            }

            printf("Digite o novo salário (ou -1 para manter): ");
            float novo_salario;
            scanf("%f", &novo_salario);
            if (novo_salario >= 0) {
                funcionarios[i].salario = novo_salario;
            }
            printf("Funcionário alterado com sucesso.\n");
            return;
        }
    }
    printf("Número funcional não encontrado.\n");
}

// Adicionar projeto
void adicionar_projeto() {
    if (num_projetos >= MAX_PROJETOS) {
        printf("Número máximo de projetos alcançado.\n");
        return;
    }
    Projeto p;

    char datas[20];

    printf("Digite o nome do projeto: ");
    scanf(" %[^\n]s", p.nome);
    printf("Digite a data de início (dd-mm-aaaa): ");
    scanf(" %[^\n]s", p.data_inicio);
    printf("Digite a data de término (dd-mm-aaaa): ");
    scanf(" %19s", datas);
    struct tm termino_tm = {0};
    sscanf(datas, "%d-%d-%d", &termino_tm.tm_mday, &termino_tm.tm_mon, &termino_tm.tm_year);
    termino_tm.tm_mon -= 1;
    termino_tm.tm_year -= 1900;
    p.data_termino = mktime(&termino_tm);
    printf("Digite o tempo estimado do projeto (em meses): ");
    scanf("%d", &p.tempo_estimado_projeto);
    printf("Digite o valor estimado: ");
    scanf("%f", &p.valor_estimado);
    printf("Digite o número funcional do responsável: ");
    scanf("%d", &p.numero_funcional_responsavel);
    printf("O projeto está finalizado? (Digite 1 para sim, e 0 para não) ");
    scanf("%d", &p.p_finalizado);

    for (int i = 0; i < num_projetos; i++) {
        if (strcmp(projetos[i].nome, p.nome) == 0) {
            printf("Nome do projeto já cadastrado.\n");
            return;
        }
    }

    projetos[num_projetos++] = p;
    ordenar_projetos();
    printf("Projeto adicionado com sucesso.\n");
}

// Remover projeto
void remover_projeto() {
    char nome[100];
    printf("Digite o nome do projeto a ser removido: ");
    scanf(" %[^\n]s", nome);

    for (int i = 0; i < num_projetos; i++) {
        if (strcmp(projetos[i].nome, nome) == 0) {
            for (int j = i; j < num_projetos - 1; j++) {
                projetos[j] = projetos[j + 1];
            }
            num_projetos--;
            ordenar_projetos();
            printf("Projeto removido com sucesso.\n");
            return;
        }
    }
    printf("Nome do projeto não encontrado.\n");
}

// Alterar um projeto
void alterar_projeto() {
    char nome[100];
    printf("Digite o nome do projeto a ser alterado: ");
    scanf(" %[^\n]s", nome);

    for (int i = 0; i < num_projetos; i++) {
        if (strcmp(projetos[i].nome, nome) == 0) {
            printf("Digite a nova data de início (ou pressione Enter para manter): ");
            char nova_data_inicio[11];
            scanf(" %[^\n]s", nova_data_inicio);
            if (strlen(nova_data_inicio) > 0) {
                strcpy(projetos[i].data_inicio, nova_data_inicio);
            }

            printf("Digite a nova data de término (ou pressione Enter para manter): ");
            char nova_data_termino[20];
            fgets(nova_data_termino, sizeof(nova_data_termino), stdin);
            nova_data_termino[strcspn(nova_data_termino, "\n")] = 0;

            if (strlen(nova_data_termino) > 0) {
                struct tm termino_tm = {0};
                sscanf(nova_data_termino, "%d-%d-%d", &termino_tm.tm_mday, &termino_tm.tm_mon, &termino_tm.tm_year);
                // aqui ta arrumando o calculo de ano e mês, parece que a função funciona assim
                termino_tm.tm_mon -= 1;
                termino_tm.tm_year -= 1900;
                projetos[i].data_termino = mktime(&termino_tm);
            }

            printf("Digite o novo tempo estimado do projeto (ou -1 para manter): ");
            int novo_tempo_estimado;
            scanf("%d", &novo_tempo_estimado);
            if (novo_tempo_estimado >= 0) {
                projetos[i].tempo_estimado_projeto = novo_tempo_estimado;
            }

            printf("Digite o novo valor estimado (ou -1 para manter): ");
            float novo_valor_estimado;
            scanf("%f", &novo_valor_estimado);
            if (novo_valor_estimado >= 0) {
                projetos[i].valor_estimado = novo_valor_estimado;
            }

            printf("Digite o novo número funcional do responsável (ou -1 para manter): ");
            int novo_numero_funcional_responsavel;
            scanf("%d", &novo_numero_funcional_responsavel);
            if (novo_numero_funcional_responsavel > 0) {
                projetos[i].numero_funcional_responsavel = novo_numero_funcional_responsavel;
            }
            printf("Projeto alterado com sucesso.\n");
            return;
        }
    }
    printf("Nome do projeto não encontrado.\n");
}

// Buscar funcionário
void buscar_funcionario() {
    int numero_funcional;
    printf("Digite o número funcional do funcionário a ser buscado: ");
    scanf("%d", &numero_funcional);

    for (int i = 0; i < num_funcionarios; i++) {
        if (funcionarios[i].numero_funcional == numero_funcional) {
            printf("Funcionário encontrado: %s, Salário: R$%.2f\n", funcionarios[i].nome, funcionarios[i].salario);
            return;
        }
    }
    printf("Número funcional não encontrado.\n");
}

// Listar funcionários com salários altos
void listar_funcionarios_salario_alto() {
    printf("Funcionários com salário maior que R$10.000,00:\n");
    for (int i = 0; i < num_funcionarios; i++) {
        if (funcionarios[i].salario > 10000) {
            printf("%s: R$%.2f\n", funcionarios[i].nome, funcionarios[i].salario);
        }
    }
}

// Listar projetos em andamento com alto valor
void listar_projetos_valor_alto() {
    printf("Projetos em andamento com valor acima de R$500.000,00:\n");
    for (int i = 0; i < num_projetos; i++) {
        // aqui só simula que ta em andamento, precisa arrumar
        if (projetos[i].valor_estimado > 500000) {
            printf("%s: R$%.2f\n", projetos[i].nome, projetos[i].valor_estimado);
        }
    }
}

// Listar projetos atrasados
void listar_projetos_atrasados() {
    time_t tempo_sistema = time(NULL);
    struct tm *tm_sistema = localtime(&tempo_sistema);

    printf("Projetos atrasados:\n");
    for (int i = 0; i < num_projetos; i++) {
        if (difftime(tempo_sistema, projetos[i].data_termino) > 0) {
            struct tm *tm_data_termino = localtime(&projetos[i].data_termino);

            int anos_atraso = tm_sistema->tm_year - tm_data_termino->tm_year;
            int meses_atraso = tm_sistema->tm_mon - tm_data_termino->tm_mon;
            int dias_atraso = tm_sistema->tm_mday - tm_data_termino->tm_mday;

            if (dias_atraso < 0) {
                meses_atraso--;
                int dias_no_mes_anterior = 30;
                dias_atraso += dias_no_mes_anterior;
            }

            if (meses_atraso < 0) {
                anos_atraso--;
                meses_atraso += 12;
            }

            printf("%s: %d anos, %d meses e %d dias de atraso\n", projetos[i].nome, anos_atraso, meses_atraso, dias_atraso);
        }
    }
}

// Listar responsável por projeto em andamento
void listar_funcionarios_responsaveis() {
    printf("Funcionários responsáveis por projetos em andamento:\n");
    for (int i = 0; i < num_projetos; i++) {
        int numero_funcional = projetos[i].numero_funcional_responsavel;
        for (int j = 0; j < num_funcionarios; j++) {
            if (funcionarios[j].numero_funcional == numero_funcional) {
                printf("%s\n", funcionarios[j].nome);
                break;
            }
        }
    }
}

// Adicionar/Buscar e-mail de responsável
void adicionar_email() {
    int numero_funcional_responsavel;
    char email[100];
    printf("Digite o número funcional do gerente: ");
    scanf("%d", &numero_funcional_responsavel);
    printf("Digite o e-mail: ");
    scanf(" %[^\n]s", email);

    for (int i = 0; i < MAX_EMAILS; i++) {
        if (strlen(emails[i]) == 0) {
            sprintf(emails[i], "%d: %s", numero_funcional_responsavel, email);
            printf("E-mail adicionado com sucesso.\n");
            return;
        }
    }
    printf("Número máximo de e-mails alcançado.\n");
}

// Exibir o menu
void exibir_menu() {
    int opcao;
    do {
        printf("\nMenu:\n");
        printf("1. Adicionar Funcionário\n");
        printf("2. Remover Funcionário\n");
        printf("3. Alterar Funcionário\n");
        printf("4. Adicionar Projeto\n");
        printf("5. Remover Projeto\n");
        printf("6. Alterar Projeto\n");
        printf("7. Buscar Funcionário\n");
        printf("8. Listar Funcionários com Salário Alto\n");
        printf("9. Listar Projetos com Valor Alto\n");
        printf("10. Listar Projetos Atrasados\n");
        printf("11. Listar Funcionários Responsáveis\n");
        printf("12. Adicionar E-mail\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: adicionar_funcionario(); break;
            case 2: remover_funcionario(); break;
            case 3: alterar_funcionario(); break;
            case 4: adicionar_projeto(); break;
            case 5: remover_projeto(); break;
            case 6: alterar_projeto(); break;
            case 7: buscar_funcionario(); break;
            case 8: listar_funcionarios_salario_alto(); break;
            case 9: listar_projetos_valor_alto(); break;
            case 10: listar_projetos_atrasados(); break;
            case 11: listar_funcionarios_responsaveis(); break;
            case 12: adicionar_email(); break;
            case 0: printf("Saindo...\n"); break;
            default: printf("Opção inválida.\n"); break;
        }
    } while (opcao != 0);
}

int main() {
    setlocale(LC_ALL, "pt-br.UTC-8"); // Bugou em alguns compiladores, melhor não mexer
    exibir_menu();
    return 0;
}
