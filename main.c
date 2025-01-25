#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
typedef struct
{
    char nome[50];
    float nota;
    int peso;
    int semestre;
} MATERIAS;

void menu(FILE *dados, MATERIAS *materia, int *tamanho);
void cadastrarMaterias(FILE *dados, MATERIAS *materia, int *tamanho);
void alterarMaterias(FILE *dados, MATERIAS *materia, int *tamanho);
void listarMaterias(MATERIAS *materia);
void excluirMaterias(FILE *dados);
void adicionarNota(FILE *dados);
void alterarNota(FILE *dados);
void calcularRendimentoGlobal(FILE *dados);
void calcularRendimentoSemestre(FILE *dados);
int lerMaterias(FILE *dados, MATERIAS *materia);
void menuAlterarMaterias(FILE *dados, MATERIAS *materia, int *tamanho);
void pause();
void clear();

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
        clear();

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
            menuAlterarMaterias(dados, materia, tamanho);
            break;
        case 3:
            listarMaterias(materia);
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

    clear();
}

int lerMaterias(FILE *dados, MATERIAS *materia)
{
    int i = 0;
    char linha[100];

    while (fgets(linha, sizeof(linha), dados) != NULL)
    {
        sscanf(linha, " %49[^0-9] %f %d %d", materia[i].nome, &materia[i].nota, &materia[i].peso, &materia[i].semestre);

        materia[i].nome[strcspn(materia[i].nome, "\n")] = '\0';

        i++;
    }

    return i;
}

void cadastrarMaterias(FILE *dados, MATERIAS *materia, int *tamanho)
{
    int tam = *tamanho;

    clear();

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

void menuAlterarMaterias(FILE *dados, MATERIAS *materia, int *tamanho) {
    int opcao;

    do {
        clear();

        printf("1- Listar materias\n");
        printf("2- Alterar materias\n");
        printf("3 - Sair\n");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                listarMaterias(materia);
                break;
            case 2:
                alterarMaterias(dados, materia, tamanho);
                break;
            case 3:
                break;
            default:
                printf("Opcao invalida\n");
                break;
        }
    } while (opcao != 3);
}

void alterarMaterias(FILE *dados, MATERIAS *materia, int *tamanho) {
    MATERIAS temp;
    int i = 0, indicador = 0;
    char nome[50];

    clear();

    printf("Digite o nome da materia que deseja alterar: ");
    scanf("%s", nome);

    while (fscanf(dados, "%s %.2f %d %d", materia[i].nome, &materia[i].nota, &materia[i].peso, &materia[i].semestre) != EOF) {
        if (strcmp(nome, materia[i].nome) == 0) {
            
            indicador = 1;

            printf("Digite o novo nome da materia: ");
            scanf(" %s", temp.nome);
            printf("Digite a nova nota da materia: ");
            scanf("%f", &temp.nota);
            printf("Digite o novo peso da materia: ");
            scanf("%d", &temp.peso);
            printf("Digite o novo semestre da materia: ");
            scanf("%d", &temp.semestre);

            fprintf(dados, "%s %.2f %d %d\n", temp.nome, temp.nota, temp.peso, temp.semestre);
        } else {
            fprintf(dados, "%s %.2f %d %d\n", materia[i].nome, materia[i].nota, materia[i].peso, materia[i].semestre);
        }
        i++;
    }
    
    if (indicador == 0) {
        printf("Materia nao encontrada\n");
        getchar();
        pause();
    }
}

void listarMaterias(MATERIAS *materia) {
    int i = 0;

    clear();

    while (*materia[i].nome != '\0') {
        printf("Nome: %s\n", materia[i].nome);
        printf("Nota: %.2f\n", materia[i].nota);
        printf("Peso: %d\n", materia[i].peso);
        printf("Semestre: %d\n", materia[i].semestre);
        printf("\n");
        i++;
    }

    getchar();
    pause();
}

void excluirMaterias(FILE *dados) {}
void adicionarNota(FILE *dados) {}
void alterarNota(FILE *dados) {}
void calcularRendimentoGlobal(FILE *dados) {}
void calcularRendimentoSemestre(FILE *dados) {}

void clear() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void pause() {
    printf("Pressione qualquer tecla para continuar...");
    getchar();
}