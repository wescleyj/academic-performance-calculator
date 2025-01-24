#include <stdio.h>

typedef struct
{
    char nome[50];
    int nota;
    int peso;
    int semestre;
} MATERIAS;

void menu(FILE *dados);
void cadastrarMaterias(FILE *dados);
void alterarMaterias(FILE *dados);
void listarMaterias(FILE *dados);
void excluirMaterias(FILE *dados);
void adicionarNota(FILE *dados);
void alterarNota(FILE *dados);
void calcularRendimentoGlobal(FILE *dados);
void calcularRendimentoSemestre(FILE *dados);

int main(void)
{
    FILE *dados;

    dados = fopen("dados.txt", "r+");

    if (dados == NULL)
    {
        printf("Erro ao abrir o arquivo");
    }

    menu(dados);

    fclose(dados);

    return 0;
}

void menu(FILE *dados)
{
    int opcao;

    do
    {
        printf("1 - Cadastrar materias\n");
        printf("2 - Alterar materias\n");
        printf("3 - Listar materias\n");
        printf("4 - Excluir materias\n");
        printf("5 - Adicionar nota\n");
        printf("6 - Alterar nota\n");
        printf("7 - Calcular Rendimento Global\n");
        printf("8 - Calcular Rendimento por Semestre\n");
        printf("9 - Sair\n");

        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            cadastrarMaterias(dados);
            break;
        case 2:
            alterarMaterias(dados);
            break;
        case 3:
            listarMaterias(dados);
            break;
        case 4:
            excluirMaterias(dados);
            break;
        case 5:
            adicionarNota(dados);
            break;
        case 6:
            alterarNota(dados);
            break;
        case 7:
            calcularRendimentoGlobal(dados);
            break;
        case 8:
            calcularRendimentoSemestre(dados);
            break;
        case 9:
            fclose(dados);
            break;
        default:
            printf("Opcao invalida\n");
            break;
        }

    } while (opcao != 9);
}

void cadastrarMaterias(FILE *dados) {}
void alterarMaterias(FILE *dados) {}
void listarMaterias(FILE *dados) {}
void excluirMaterias(FILE *dados) {}
void adicionarNota(FILE *dados) {}
void alterarNota(FILE *dados) {}
void calcularRendimentoGlobal(FILE *dados) {}
void calcularRendimentoSemestre(FILE *dados) {}