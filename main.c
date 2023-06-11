#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

struct Tempo {
  int horas;
  int minutos;
};

struct Tempo incrementarMinutos(struct Tempo tempo, double numeroAleatorio) {
  tempo.minutos += numeroAleatorio;
  tempo.horas += tempo.minutos / 60;
  tempo.minutos %= 60;
  return tempo;
}

double gerarNumeroNormal(int Pizza, char momento) {
  double u1 = 1.0 - rand() / (RAND_MAX + 1.0);
  double u2 = 1.0 - rand() / (RAND_MAX + 1.0);
    
  double z = sqrt(-2.0 * log(u1)) * cos(2.0 * M_PI * u2);
  double media;
  double desvio;
  
  if (momento == 'M') {
    if (Pizza == 1) {
      media = 3;
      desvio = 0.5;
    } else {
      media = 2;
      desvio = 0.5;
    }
  } else if (momento == 'F') {
    if (Pizza == 3) {
      media = 5;
      desvio = 1;
    } else {
      media = 6;
      desvio = 1;
    }
  } else if (momento == 'E') {
      media = 2;
      desvio = 0.5;
  }
  return media + (desvio * z);
}

int geraNumeroAleatorio(char tipo, int hora) {
  int numeroAleatorio = rand() % 100 + 1;
  // Números Aleatórios para Chegada até as 19h
  if (tipo == 'C' && hora < 19) {
    if (numeroAleatorio <= 10) {
      numeroAleatorio = 3;
    } else if (numeroAleatorio <= 20) {
      numeroAleatorio = 4;
    } else if (numeroAleatorio <= 40) {
      numeroAleatorio = 5;
    } else if (numeroAleatorio <= 80) {
      numeroAleatorio = 6;
    } else {
      numeroAleatorio = 7;
    }
  }
  // Números Aleatórios para Chegada até as 22h
  else if (tipo == 'C' && hora < 22) {
    if (numeroAleatorio <= 10) {
      numeroAleatorio = 0;
    } else if (numeroAleatorio <= 40) {
      numeroAleatorio = 1;
    } else if (numeroAleatorio <= 70) {
      numeroAleatorio = 2;
    } else if (numeroAleatorio <= 90) {
      numeroAleatorio = 3;
    } else {
      numeroAleatorio = 5;
    }
  }
  // Números Aleatórios para tipos de Pizza
  else if (tipo == 'P') {
    if (numeroAleatorio <= 30) {
      numeroAleatorio = 1; // Especial
    } else if (numeroAleatorio <= 50) {
      numeroAleatorio = 2; // Luxo
    } else {
      numeroAleatorio = 3; // Super
    }
  }
  return numeroAleatorio;
}

int main() {
  int qtdDiasSimulacao = 1;
  int numPostos = 2;
  srand(time(NULL));
  printf("Funcionários por Etapa: %d\n", numPostos);
  for(int dias = 0; dias < qtdDiasSimulacao; dias++) {
    struct Tempo tempo = {17, 0};
    int qtdPizzas = 0;
  
    int tamanhoInicial = 1; // Tamanho inicial do chegadas
  
    struct Tempo *chegadas =
        malloc(tamanhoInicial * sizeof(struct Tempo)); // Alocação inicial
    int valor;
  
    while (tempo.horas < 22) {
      int numeroAleatorio = geraNumeroAleatorio('C', tempo.horas);
      // printf("Tempo inicial: %02d:%02d\n", tempo.horas, tempo.minutos);
      tempo = incrementarMinutos(tempo, numeroAleatorio);
      if (qtdPizzas >= tamanhoInicial) {
        tamanhoInicial++; // Dobra o tamanho do chegadas
        struct Tempo *novachegada =
            realloc(chegadas,
                    tamanhoInicial * sizeof(struct Tempo)); // Realoca o chegadas
        if (novachegada == NULL) {
          printf("Erro ao realocar o chegadas.\n");
          break;
        }
        chegadas = novachegada;
      }
      chegadas[qtdPizzas] = tempo;
      // printf("Tempo incrementado: %02d:%02d\n", tempo.horas, tempo.minutos);
      qtdPizzas++;
    }
    struct Tempo filaMontagem[qtdPizzas];
    struct Tempo Montagem[qtdPizzas];
    struct Tempo filaForno[qtdPizzas];
    struct Tempo Forno[qtdPizzas];
    struct Tempo filaEmbalagem[qtdPizzas];
    struct Tempo Embalagem[qtdPizzas];
    struct Tempo saidas[qtdPizzas];
    struct Tempo tempoSistema[qtdPizzas];
    
    int tipoPizzas[qtdPizzas];
    
    printf("Dia nº %d\n", dias + 1);
    // printf("Chegadas de Pedidos:\n");
    // printf("\n");
    
    for (int i = 0; i < qtdPizzas; i++) {
      // Assim que chegam os pedidos eles já vão pra fila de Montagem
      filaMontagem[i] = chegadas[i];
      // Se o pedido atual ainda não atingiu o número de funcionários alocados naquele posto, ele já vai pra Montagem direto, pois não existe
      // ninguém na fila
      if (i < numPostos) {
        Montagem[i] = filaMontagem[i];
      } else {

        // Caso contrário, teremos que verificar n pedidos anteriores (que se baseiam no número de funcionários alocados por posto)
        struct Tempo menorTempo = filaForno[i - numPostos];
        bool entrou = false;

        
        for(int j = 1; j <= numPostos; j++) {
          if((menorTempo.horas == filaForno[i - j].horas && menorTempo.minutos > filaForno[i - j].minutos) || menorTempo.horas > filaForno[i - j].horas) {
            menorTempo = filaForno[i - j];
          }
          // Se quando o pedido chegou na filaMontagem já havia saído algum outro pedido da Montagem, então ele vai pra Montagem no exato momento em que chegou
          if ((filaMontagem[i].horas == filaForno[i - j].horas && filaMontagem[i].minutos >= filaForno[i - j].minutos) || filaMontagem[i].horas > filaForno[i - j].horas) {
            Montagem[i] = filaMontagem[i];
            entrou = true;
          } 
        }
        // Caso contrário ele irá pra montagem no momento que o primeiro pedido que estiver lá, sair
        if (!entrou) {
          Montagem[i] = menorTempo;
        }
      }
  
      tipoPizzas[i] = geraNumeroAleatorio('P', 0);
      filaForno[i] = incrementarMinutos(Montagem[i], gerarNumeroNormal(tipoPizzas[i], 'M'));

      int qtdPorForno = 5;
      // Os primeiros 5 pedidos vão para o forno direto, pois cabem 5 pizzas no forno
      if (i < qtdPorForno) {
        Forno[i] = filaForno[i];
      } else {
        struct Tempo menorTempo = filaEmbalagem[i - qtdPorForno];
        bool entrou = false;
        for(int j = 1; j <= qtdPorForno; j++) {
          if((menorTempo.horas == filaEmbalagem[i - j].horas && menorTempo.minutos > filaEmbalagem[i - j].minutos) || menorTempo.horas > filaEmbalagem[i - j].horas) {
            menorTempo = filaForno[i - j];
          }
          // Se quando o pedido chegou na filaForno já havia saído algum outro pedido do Forno, então ele vai pro Forno no exato momento em que chegou
          if ((filaForno[i].horas == filaEmbalagem[i - j].horas && filaForno[i].minutos >= filaEmbalagem[i - j].minutos) || filaForno[i].horas > filaEmbalagem[i - j].horas) {
            Forno[i] = filaForno[i];
            entrou = true;
          } 
        }
        // Caso contrário ele irá pro Forno no momento que o primeiro pedido que estiver lá, sair
        if (!entrou) {
          Forno[i] = menorTempo;
        }
      }

      filaEmbalagem[i] = incrementarMinutos(Forno[i], gerarNumeroNormal(tipoPizzas[i], 'F'));

      if (i < numPostos) {
        Embalagem[i] = filaEmbalagem[i];
      } else {
        struct Tempo menorTempo = saidas[i - numPostos];
        bool entrou = false;
        for(int j = 1; j <= numPostos; j++) {
          if((menorTempo.horas == saidas[i - j].horas && menorTempo.minutos > saidas[i - j].minutos) || menorTempo.horas > saidas[i - j].horas) {
            menorTempo = saidas[i - j];
          }
          if ((filaEmbalagem[i].horas == saidas[i - j].horas && filaEmbalagem[i].minutos >= saidas[i - j].minutos) || filaEmbalagem[i].horas > saidas[i - j].horas) {
            Embalagem[i] = filaEmbalagem[i];
            entrou = true;
          } 
        }
        if (!entrou) {
          Embalagem[i] = menorTempo;
        }
      }

      saidas[i] = incrementarMinutos(Embalagem[i], gerarNumeroNormal(tipoPizzas[i], 'E'));

      if(saidas[i].minutos == chegadas[i].minutos) {
        tempoSistema[i].horas = saidas[i].horas - chegadas[i].horas;
        tempoSistema[i].minutos = 00;
      } else {
        tempoSistema[i].horas = 00;
        tempoSistema[i].minutos = saidas[i].minutos - chegadas[i].minutos;
      }
      
      if(tempoSistema[i].minutos < 0) {
        tempoSistema[i].minutos = tempoSistema[i].minutos + 60;
      } 
      
      printf("Pedido nº %d\n", i + 1);
      printf("Tipo de Pizza: %d\n", tipoPizzas[i]);
      printf("Chegada: %02d:%02d\n", chegadas[i].horas, chegadas[i].minutos);
      printf("Fila Montagem: %02d:%02d\n", filaMontagem[i].horas, filaMontagem[i].minutos);
      printf("Montagem: %02d:%02d\n", Montagem[i].horas, Montagem[i].minutos);
      printf("Fila Forno: %02d:%02d\n", filaForno[i].horas, filaForno[i].minutos);
      printf("Forno: %02d:%02d\n", Forno[i].horas, Forno[i].minutos);
      printf("Fila Embalagem: %02d:%02d\n", filaEmbalagem[i].horas, filaEmbalagem[i].minutos);
      printf("Embalagem: %02d:%02d\n", Embalagem[i].horas, Embalagem[i].minutos);
      printf("Saída: %02d:%02d\n", saidas[i].horas, saidas[i].minutos);
      printf("Tempo de Sistema: %02d:%02d\n", tempoSistema[i].horas, tempoSistema[i].minutos);
      printf("\n");
    }

    
    float somaMin = 0;
    float somaHr = 0;
    float menor = 0;
    float maior = 0;

    menor = tempoSistema[0].minutos + (tempoSistema[0].horas * 60);
    maior = menor;
    for(int horarios = 0; horarios < qtdPizzas; horarios++) {
      somaHr += tempoSistema[horarios].horas;
      somaMin += tempoSistema[horarios].minutos + (somaHr * 60);
      if(tempoSistema[horarios].minutos + (tempoSistema[horarios].horas * 60) < menor) {
        menor = tempoSistema[horarios].minutos + (tempoSistema[horarios].horas * 60);
      } else if (tempoSistema[horarios].minutos + (tempoSistema[horarios].horas * 60) > maior) {
        maior = tempoSistema[horarios].minutos + (tempoSistema[horarios].horas * 60);
      }
    }

    printf("Menor tempo: %.2f min\n", menor);
    printf("Tempo médio: %.2f min\n", somaMin/qtdPizzas);
    printf("Maior tempo: %.2f min\n", maior);
    printf("\n");
    free(chegadas); // Libera a memória alocada
  }

  return 0;
}