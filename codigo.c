#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

typedef struct {
    char modelo[30];
    char placa[30];
    char cor[30];
} Carro;

void limparBufferEntrada() {
    int ch;
    while ((ch = fgetc(stdin)) != EOF && ch != '\n') {}
}

float calcularValorVenda(float preco, float quantidade) {
    return preco * quantidade;
}

int validarEntradas(float precoEtanol, float precoGasolina, float precoAditivada, float tamanhoFila) {
    if (precoEtanol < 0) printf("\nPreço do Etanol inválido!\n");
    if (precoGasolina < 0) printf("\nPreço da Gasolina inválido!\n");
    if (precoAditivada < 0) printf("\nPreço da Gasolina Aditivada inválido!\n");
    if (tamanhoFila <= 0) printf("\nTamanho da fila inválido!\n");
    return 0;
}

int mostrarMenu() {
    int opcao;
    printf("\n=== Sistema de gerenciamento do posto de gasolina ===\n");
    printf("1 - Adicionar carro na fila\n");
    printf("2 - Abastecer carro\n");
    printf("3 - Chamar próximo cliente\n");
    printf("4 - Relatórios\n");
    printf("5 - Encerrar programa\n");
    printf("Informe a opção: ");
    scanf("%d", &opcao);
    return opcao;
}

int adicionarNaFila(int *fila) {
    (*fila)++;
    printf("Número de carros na fila: %d\n", *fila);
    return *fila;
}

int removerDaFila(int *fila) {
    (*fila)--;
    printf("Número de carros na fila: %d\n", *fila);
    return *fila;
}

int main(void) {
    float precoEtanol = 1, precoGasolina = 1, precoAditivada = 1;
    float qtdEtanol, qtdGasolina, qtdAditivada;
    float valorTotal, carrosAtendidos = 0, tamanhoFila = 1;
    float estoqueEtanol = 200, estoqueGasolina = 200, estoqueAditivada = 200;

    float totalEtanolVendido = 0, totalGasolinaVendida = 0, totalAditivadaVendida = 0;

    int fila = 0, opcaoMenu, opcaoRelatorio, capacidadeMaxima, contadorCarros = 0;

    printf("============================================================\n");
    printf(" Bem-vindo ao sistema de abastecimento do posto de gasolina \n");
    printf("============================================================\n");

    do {
        validarEntradas(precoEtanol, precoGasolina, precoAditivada, tamanhoFila);

        printf("\nDigite o preço do Etanol: ");
        scanf("%f", &precoEtanol);

        printf("Digite o preço da Gasolina: ");
        scanf("%f", &precoGasolina);

        printf("Digite o preço da Gasolina Aditivada: ");
        scanf("%f", &precoAditivada);

        printf("Informe o tamanho máximo da fila: ");
        scanf("%f", &tamanhoFila);

    } while (precoEtanol < 0 || precoGasolina < 0 || precoAditivada < 0 || tamanhoFila <= 0);

    capacidadeMaxima = (int)tamanhoFila;
    Carro carros[capacidadeMaxima];

    do {
        opcaoMenu = mostrarMenu();

        switch (opcaoMenu) {
            case 1:
                system("clear||cls");
                if (fila < capacidadeMaxima) {
                    adicionarNaFila(&fila);
                    limparBufferEntrada();

                    printf("\nDigite o modelo do carro: ");
                    fgets(carros[contadorCarros].modelo, 30, stdin);

                    printf("Digite a cor do carro: ");
                    fgets(carros[contadorCarros].cor, 30, stdin);

                    printf("Digite a placa do carro: ");
                    fgets(carros[contadorCarros].placa, 30, stdin);

                    printf("\nCarro adicionado:\n Modelo: %s Cor: %s Placa: %s\n",
                           carros[contadorCarros].modelo,
                           carros[contadorCarros].cor,
                           carros[contadorCarros].placa);

                    contadorCarros++;
                } else {
                    printf("\nFila cheia!\n");
                }
                break;

            case 2:
                system("clear||cls");
                if (fila > 0) {
                    printf("\nDigite a quantidade vendida de Etanol: ");
                    scanf("%f", &qtdEtanol);
                    estoqueEtanol -= qtdEtanol;
                    totalEtanolVendido += qtdEtanol;

                    printf("Digite a quantidade vendida de Gasolina Comum: ");
                    scanf("%f", &qtdGasolina);
                    estoqueGasolina -= qtdGasolina;
                    totalGasolinaVendida += qtdGasolina;

                    printf("Digite a quantidade vendida de Gasolina Aditivada: ");
                    scanf("%f", &qtdAditivada);
                    estoqueAditivada -= qtdAditivada;
                    totalAditivadaVendida += qtdAditivada;

                    carrosAtendidos++;
                    printf("\nCarros atendidos: %.f\n", carrosAtendidos);
                    printf("Carro abastecido com sucesso.\n");
                    removerDaFila(&fila);
                } else {
                    printf("A fila está vazia! Adicione um carro antes de abastecer.\n");
                }
                break;

            case 3:
                system("clear||cls");
                if (fila > 0) {
                    removerDaFila(&fila);
                    printf("Próximo cliente chamado.\n");
                } else {
                    printf("A fila está vazia! Adicione um carro antes de chamar o próximo.\n");
                }
                break;

            case 4:
                do {
                    printf("\n=== Relatórios ===\n");
                    printf("1 - Litros vendidos (por combustível)\n");
                    printf("2 - Valor total arrecadado\n");
                    printf("3 - Quantidade de carros atendidos\n");
                    printf("4 - Combustível restante nos tanques\n");
                    printf("5 - Voltar ao menu\n");
                    printf("Informe a opção: ");
                    scanf("%d", &opcaoRelatorio);

                    switch (opcaoRelatorio) {
                        case 1:
                            system("clear||cls");
                            printf("Litros vendidos:\n Etanol: %.2f\n Gasolina Comum: %.2f\n Gasolina Aditivada: %.2f\n",
                                   totalEtanolVendido, totalGasolinaVendida, totalAditivadaVendida);
                            break;

                        case 2:
                            system("clear||cls");
                            valorTotal = calcularValorVenda(precoEtanol, totalEtanolVendido) +
                                         calcularValorVenda(precoGasolina, totalGasolinaVendida) +
                                         calcularValorVenda(precoAditivada, totalAditivadaVendida);
                            printf("Valor total arrecadado: R$ %.2f\n", valorTotal);
                            break;

                        case 3:
                            system("clear||cls");
                            printf("Total de carros atendidos: %.f\n", carrosAtendidos);
                            break;

                        case 4:
                            system("clear||cls");
                            printf("Estoque restante:\n Etanol: %.2f L\n Gasolina Comum: %.2f L\n Gasolina Aditivada: %.2f L\n",
                                   estoqueEtanol, estoqueGasolina, estoqueAditivada);
                            break;

                        case 5:
                            break;

                        default:
                            printf("Opção inválida!\n");
                    }
                } while (opcaoRelatorio != 5);
                break;

            case 5:
                system("clear||cls");
                printf("\nPrograma encerrado.\n");
                break;

            default:
                system("clear||cls");
                printf("\nOpção inválida!\n");
        }
    } while (opcaoMenu != 5);

    return 0;
}
