#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

typedef struct
{
    char nome[50];
    float nota;
    int peso;
    int semestre;
} MATERIAS;

void menu(FILE *dados, MATERIAS *materia, int *tamanho);
void cadastrarMaterias(FILE *dados, MATERIAS *materia, int *tamanho);
void alterarMaterias(FILE *dados);
void listarMaterias(FILE *dados);
void excluirMaterias(FILE *dados);
void adicionarNota(FILE *dados);
void alterarNota(FILE *dados);
void calcularRendimentoGlobal(FILE *dados);
void calcularRendimentoSemestre(FILE *dados);
int lerMaterias(FILE *dados, MATERIAS *materia);

int main(void)
{
    setlocale(LC_ALL, NULL);

    FILE *dados;
    MATERIAS *materia = calloc(100, sizeof(MATERIAS));
    int tamanho = 0;

    dados = fopen("dados.txt", "r+");

    if (dados == NULL)
    {
        printf("Erro ao abrir o arquivo");
    }

    if (materia == NULL)
    {
        printf("Erro ao alocar memoria");
    }
    

    tamanho = lerMaterias(dados, materia);

    menu(dados, materia, &tamanho);

    fclose(dados);

    return 0;
}

void menu(FILE *dados, MATERIAS *materia, int *tamanho)
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
            cadastrarMaterias(dados, materia, tamanho);
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

int lerMaterias(FILE *dados, MATERIAS *materia)
{
    int i = 0;

    while (fscanf(dados, "%s %.2f %d %d", materia[i].nome, &materia[i].nota, &materia[i].peso, &materia[i].semestre) != EOF)
    {
        i++;   
    }

    return i;
}

void cadastrarMaterias(FILE *dados, MATERIAS *materia, int *tamanho)
{
    int tam = *tamanho;
    // Adicionar materia
    printf("Digite o nome da materia: ");
    scanf("%s", materia[tam].nome);
    printf("Digite a nota da materia: ");
    scanf("%f", &materia[tam].nota);
    printf("Digite o peso da materia: ");
    scanf("%d", &materia[tam].peso);
    printf("Digite o semestre da materia: ");
    scanf("%d", &materia[tam].semestre);
    
    fprintf(dados, "%s %.2f %d %d\n", materia[tam].nome, materia[tam].nota, materia[tam].peso, materia[tam].semestre);

    tam++;
    *tamanho = tam;
}

void alterarMaterias(FILE *dados) {}
void listarMaterias(FILE *dados) {}
void excluirMaterias(FILE *dados) {}
void adicionarNota(FILE *dados) {}
void alterarNota(FILE *dados) {}
void calcularRendimentoGlobal(FILE *dados) {}
void calcularRendimentoSemestre(FILE *dados) {}