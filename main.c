#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

// Definição da estrutura
typedef struct
{
    char nome[50];
    float nota;
    int peso;
    int semestre;
} MATERIAS;

// Protótipos de funções
void menu(MATERIAS **materia, int *tamanho);
void cadastrarMaterias(MATERIAS **materia, int *tamanho);
void alterarMaterias(MATERIAS *materia, int tamanho);
void listarMaterias(MATERIAS *materia, int tamanho);
void excluirMaterias(MATERIAS **materia, int *tamanho);
void calcularRendimentoGlobal(MATERIAS *materia, int tamanho);
void calcularRendimentoSemestre(MATERIAS *materia, int tamanho);
void carregarMaterias(MATERIAS **materia, int *tamanho);
void salvarMaterias(MATERIAS *materia, int tamanho);
void limparBuffer();
void clear();
void pause();

// Caminho do arquivo
#define ARQUIVO "dados.txt"

// Função principal
int main(void)
{
    setlocale(LC_ALL, "pt_BR.UTF-8");

    MATERIAS *materia = NULL;
    int tamanho = 0;

    carregarMaterias(&materia, &tamanho);
    menu(&materia, &tamanho);
    salvarMaterias(materia, tamanho);

    free(materia);
    return 0;
}

// Exibe o menu principal
void menu(MATERIAS **materia, int *tamanho)
{
    int opcao;

    do
    {
        clear();
        printf("1 - Cadastrar matérias\n");
        printf("2 - Alterar matérias\n");
        printf("3 - Listar matérias\n");
        printf("4 - Excluir matérias\n");
        printf("5 - Calcular Rendimento Global\n");
        printf("6 - Calcular Rendimento por Semestre\n");
        printf("7 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao)
        {
        case 1:
            cadastrarMaterias(materia, tamanho);
            break;
        case 2:
            alterarMaterias(*materia, *tamanho);
            break;
        case 3:
            listarMaterias(*materia, *tamanho);
            break;
        case 4:
            excluirMaterias(materia, tamanho);
            break;
        case 5:
            calcularRendimentoGlobal(*materia, *tamanho);
            break;
        case 6:
            calcularRendimentoSemestre(*materia, *tamanho);
            break;
        case 7:
            printf("Saindo...\n");
            break;
        default:
            printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 7);
}

// Carrega as matérias do arquivo para a memória
void carregarMaterias(MATERIAS **materia, int *tamanho)
{
    FILE *dados = fopen(ARQUIVO, "r");
    if (dados == NULL)
    {
        printf("Arquivo não encontrado, será criado um novo ao salvar dados.\n");
        return;
    }

    MATERIAS temp;
    while (fscanf(dados, "%49s %f %d %d\n", temp.nome, &temp.nota, &temp.peso, &temp.semestre) != EOF)
    {
        *materia = realloc(*materia, (*tamanho + 1) * sizeof(MATERIAS));
        (*materia)[*tamanho] = temp;
        (*tamanho)++;
    }

    fclose(dados);
}

// Salva as matérias da memória no arquivo
void salvarMaterias(MATERIAS *materia, int tamanho)
{
    FILE *dados = fopen(ARQUIVO, "w");
    if (dados == NULL)
    {
        printf("Erro ao salvar dados no arquivo.\n");
        return;
    }

    for (int i = 0; i < tamanho; i++)
    {
        fprintf(dados, "%s %.2f %d %d\n", materia[i].nome, materia[i].nota, materia[i].peso, materia[i].semestre);
    }

    fclose(dados);
}

// Cadastra uma nova matéria
void cadastrarMaterias(MATERIAS **materia, int *tamanho)
{
    clear();

    *materia = realloc(*materia, (*tamanho + 1) * sizeof(MATERIAS));

    printf("Digite o nome da matéria: ");
    scanf("%49s", (*materia)[*tamanho].nome);
    limparBuffer();

    do
    {
        printf("Digite a nota da matéria (0 a 100): ");
        scanf("%f", &(*materia)[*tamanho].nota);
        limparBuffer();
    } while ((*materia)[*tamanho].nota < 0 || (*materia)[*tamanho].nota > 100);

    do
    {
        printf("Digite o peso da matéria (positivo): ");
        scanf("%d", &(*materia)[*tamanho].peso);
        limparBuffer();
    } while ((*materia)[*tamanho].peso <= 0);

    printf("Digite o semestre da matéria: ");
    scanf("%d", &(*materia)[*tamanho].semestre);
    limparBuffer();

    (*tamanho)++;

    printf("Matéria cadastrada com sucesso!\n");
    pause();
}

// Altera uma matéria existente
void alterarMaterias(MATERIAS *materia, int tamanho)
{
    char nome[50];
    int encontrado = 0;

    clear();
    printf("Digite o nome da matéria a ser alterada: ");
    scanf("%49s", nome);
    limparBuffer();

    for (int i = 0; i < tamanho; i++)
    {
        if (strcmp(materia[i].nome, nome) == 0)
        {
            encontrado = 1;

            printf("Digite o novo nome: ");
            scanf("%49s", materia[i].nome);
            limparBuffer();

            do
            {
                printf("Digite a nova nota (0 a 100): ");
                scanf("%f", &materia[i].nota);
                limparBuffer();
            } while (materia[i].nota < 0 || materia[i].nota > 100);

            do
            {
                printf("Digite o novo peso (positivo): ");
                scanf("%d", &materia[i].peso);
                limparBuffer();
            } while (materia[i].peso <= 0);

            printf("Digite o novo semestre: ");
            scanf("%d", &materia[i].semestre);
            limparBuffer();

            printf("Matéria alterada com sucesso!\n");
            break;
        }
    }

    if (!encontrado)
    {
        printf("Matéria não encontrada.\n");
        pause();
    }
}

// Lista todas as matérias
void listarMaterias(MATERIAS *materia, int tamanho)
{
    clear();

    if (tamanho == 0)
    {
        printf("Nenhuma matéria cadastrada.\n");
        return;
    }

    for (int i = 0; i < tamanho; i++)
    {
        printf("Nome: %s\n", materia[i].nome);
        printf("Nota: %.2f\n", materia[i].nota);
        printf("Peso: %d\n", materia[i].peso);
        printf("Semestre: %d\n\n", materia[i].semestre);
    }

    pause();
}

// Exclui uma matéria
void excluirMaterias(MATERIAS **materia, int *tamanho)
{
    char nome[50];
    int encontrado = 0;

    clear();
    printf("Digite o nome da matéria a ser excluída: ");
    scanf("%49s", nome);
    limparBuffer();

    for (int i = 0; i < *tamanho; i++)
    {
        if (strcmp((*materia)[i].nome, nome) == 0)
        {
            encontrado = 1;

            for (int j = i; j < *tamanho - 1; j++)
            {
                (*materia)[j] = (*materia)[j + 1];
            }

            (*tamanho)--;
            *materia = realloc(*materia, (*tamanho) * sizeof(MATERIAS));

            printf("Matéria excluída com sucesso!\n");
            break;
        }
    }

    if (!encontrado)
    {
        printf("Matéria não encontrada.\n");
    }

    pause();
}

// Calcula o rendimento global
void calcularRendimentoGlobal(MATERIAS *materia, int tamanho)
{
    if (tamanho == 0)
    {
        printf("Nenhuma matéria cadastrada.\n");
        return;
    }

    float soma = 0, peso = 0;

    for (int i = 0; i < tamanho; i++)
    {
        soma += materia[i].nota * materia[i].peso;
        peso += materia[i].peso;
    }

    printf("Rendimento global: %.2f\n", soma / peso);

    pause();
}

// Calcula o rendimento de um semestre
void calcularRendimentoSemestre(MATERIAS *materia, int tamanho)
{
    int semestre;
    float soma = 0, peso = 0;

    printf("Digite o semestre desejado: ");
    scanf("%d", &semestre);
    limparBuffer();

    for (int i = 0; i < tamanho; i++)
    {
        if (materia[i].semestre == semestre)
        {
            soma += materia[i].nota * materia[i].peso;
            peso += materia[i].peso;
        }
    }

    if (peso > 0)
    {
        printf("Rendimento do semestre %d: %.2f\n", semestre, soma / peso);
    }
    else
    {
        printf("Semestre %d não possui matérias cadastradas.\n", semestre);
    }

    pause();
}

// Funções auxiliares
void limparBuffer()
{
    while (getchar() != '\n')
        ;
}

void clear()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pause()
{
    printf("Pressione ENTER para continuar...");
    getchar();
}