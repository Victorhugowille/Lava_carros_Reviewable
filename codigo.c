#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

// Struct para armazenar informações de um carro
struct Carro {
  char modelo[30];
  char placa[30];
  char cor[30];
};

// Funções
void limparBufferEntrada();
float calcularValorVenda(float preco, float quantidade);
int validarEntradas(float precoEtanol, float precoGasolina, float precoAditivada, float tamanhoFila);
int mostrarMenu();
int adicionarNaFila(int *fila);
int removerDaFila(int *fila);

// MAIN
int main(void) {

  // VARIÁVEIS
  float precoEtanol = 1, precoGasolina = 1, precoAditivada = 1;
  float qtdEtanol, qtdGasolina, qtdAditivada;
  float valorTotal, carrosAtendidos = 0, tamanhoFila = 1;
  float estoqueEtanol = 200, estoqueGasolina = 200, estoqueAditivada = 200;
  int fila = 0, opcaoMenu, opcaoRelatorio, capacidadeMaxima, contadorCarros = 1;

  printf("---------------------------------------------------------------------------------------------------------\n");
  printf("Bem-vindo ao sistema de abastecimento do posto de gasolina!\n");
  printf("Este programa facilita o gerenciamento de clientes e abastecimentos.\n");
  printf("---------------------------------------------------------------------------------------------------------\n");

  do {
    validarEntradas(precoEtanol, precoGasolina, precoAditivada, tamanhoFila);

    printf("\nDigite o preço do Etanol: ");
    scanf("%f", &precoEtanol);

    printf("\nDigite o preço da Gasolina: ");
    scanf("%f", &precoGasolina);

    printf("\nDigite o preço da Gasolina Aditivada: ");
    scanf("%f", &precoAditivada);

    printf("\nInforme o tamanho da fila suportada pelo estabelecimento: ");
    scanf("%f", &tamanhoFila);

  } while (precoEtanol < 0 || precoGasolina < 0 || precoAditivada < 0 || tamanhoFila <= 0);

  struct Carro carros[capacidadeMaxima];

  do {
    opcaoMenu = mostrarMenu();

    switch (opcaoMenu) {
      case 1:
        system("clear");
        if (fila <= tamanhoFila) {
          adicionarNaFila(&fila);
          limparBufferEntrada();

          printf("\nDigite o modelo do carro: ");
          fgets(carros[contadorCarros].modelo, 30, stdin);

          printf("\nDigite a cor do carro: ");
          fgets(carros[contadorCarros].cor, 30, stdin);

          printf("\nDigite a placa do carro: ");
          fgets(carros[contadorCarros].placa, 30, stdin);

          printf("\nModelo: %s\nCor: %s\nPlaca: %s",
                 carros[contadorCarros].modelo,
                 carros[contadorCarros].cor,
                 carros[contadorCarros].placa);

          contadorCarros++;
          printf("\nCarro adicionado na fila.\n");

        } else {
          printf("\nFila cheia!\n");
        }
      break;

      case 2:
        system("clear");
        if (fila > 0) {
          printf("\nDigite a quantidade vendida de Etanol: ");
          scanf("%f", &qtdEtanol);
          estoqueEtanol -= qtdEtanol;

          printf("\nDigite a quantidade vendida de Gasolina Comum: ");
          scanf("%f", &qtdGasolina);
          estoqueGasolina -= qtdGasolina;

          printf("\nDigite a quantidade vendida de Gasolina Aditivada: ");
          scanf("%f", &qtdAditivada);
          estoqueAditivada -= qtdAditivada;

          carrosAtendidos++;
          printf("\nCarros atendidos: %.f\n", carrosAtendidos);
          printf("Carro abastecido com sucesso.\n");
          removerDaFila(&fila);
        } else {
          printf("A fila está vazia! Adicione um carro antes de abastecer.");
        }
      break;

      case 3:
        system("clear");
        if (fila > 0) {
          fila -= 1;
          printf("Próximo cliente chamado.\n");
        } else {
          printf("A fila está vazia! Adicione um carro antes de chamar o próximo.");
        }
      break;

      case 4:
        do {
          printf("------------------------------------------------------------------\n");
          printf("1 - Quantidade de litros vendidos (por tipo de combustível)\n");
          printf("2 - Valor total arrecadado\n");
          printf("3 - Quantidade de carros atendidos\n");
          printf("4 - Combustível restante nos tanques\n");
          printf("5 - Voltar ao menu\n");
          printf("------------------------------------------------------------------\n");
          printf("Informe a opção: ");
          scanf("%d", &opcaoRelatorio);

          switch (opcaoRelatorio) {
            case 1:
              system("clear");
              printf("Litros vendidos:\nEtanol: %.2f\nGasolina Comum: %.2f\nGasolina Aditivada: %.2f\n", qtdEtanol, qtdGasolina, qtdAditivada);
              break;

            case 2:
              system("clear");
              valorTotal = calcularValorVenda(precoEtanol, qtdEtanol) +
                           calcularValorVenda(precoGasolina, qtdGasolina) +
                           calcularValorVenda(precoAditivada, qtdAditivada);
              printf("Valor total arrecadado: R$ %.2f\n", valorTotal);
              break;

            case 3:
              system("clear");
              printf("Total de carros atendidos: %.f\n", carrosAtendidos);
              break;

            case 4:
              system("clear");
              printf("Estoque restante:\nEtanol: %.2f L\nGasolina Comum: %.2f L\nGasolina Aditivada: %.2f L\n",
                      estoqueEtanol, estoqueGasolina, estoqueAditivada);
              break;

            default:
              printf("Opção inválida!\n");
          }
        } while (opcaoRelatorio != 5);
      break;

      case 5:
        system("clear");
        printf("\nPrograma encerrado.\n");
      break;

      default:
        system("clear");
        printf("\nOpção inválida!\n");
    }
  } while (opcaoMenu != 5);

  return 0;
}

// Funções auxiliares
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
  printf("\nSistema de gerenciamento do posto de gasolina\n");
  printf("------------------------------------------------------------------\n");
  printf("1 - Adicionar carro na fila\n");
  printf("2 - Abastecer carro\n");
  printf("3 - Chamar próximo cliente\n");
  printf("4 - Relatórios\n");
  printf("5 - Encerrar programa\n");
  printf("------------------------------------------------------------------\n");
  printf("Informe a opção: ");
  scanf("%d", &opcao);
  return opcao;
}

void limparBufferEntrada() {
  int ch;
  while ((ch = fgetc(stdin)) != EOF && ch != '\n') {}
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
