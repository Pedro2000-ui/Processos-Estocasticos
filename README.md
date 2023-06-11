<h1 align="center"> Processos Estocásticos - Teoria das Filas </h1>
<h2> Introdução </h2>
A teoria das filas estuda o comportamento de filas de espera em sistemas, como serviços de atendimento ao cliente, redes de computadores, linhas de produção e etc.

Utiliza de análise matemática e estatística e aplica nesses sistemas para entender e quantificar métricas importantes, como o tempo médio de <b>espera</b>, o tempo médio de <b>serviço</b>, a taxa de <b>chegada</b> de clientes e a taxa de <b>atendimento</b>. O objetivo principal é encontrar medidas eficazes para melhorar o desempenho do sistema, reduzir o tempo de espera dos clientes e otimizar a utilização dos recursos disponíveis.

Existem vários componentes essenciais em um sistema de filas:
- Chegada: Processo de chegada de clientes ao sistema de filas. A taxa de chegada é a frequência com que os clientes chegam ao sistema.
- Serviço: Processo de atendimento aos clientes na fila. O tempo de serviço é o tempo necessário para atender a um cliente.
- Capacidade: Número de clientes que o sistema de filas pode atender simultaneamente. Pode ser representado por servidores disponíveis para o atendimento.
- Disciplina: Regras que governam a ordem de atendimento dos clientes na fila. Pode seguir uma política como "primeiro a chegar, primeiro a ser atendido" (FIFO), prioridades ou outras políticas específicas.

<h2> Problema </h2>
A pizzaria do Zé vende três tipos de pizza, a Especial, a Super e a Luxo. O gerente da pizzaria quer entender melhor o tempo para atender um pedido e saber como ele pode determinar esse tempo.

A produção de qualquer pizza passa por três etapas:
 - Montagem
 - Forno
 - Embalagem

Para cada tipo de pizza os tempos seguem uma distribuição normal. O tempo médio e o desvio padrão estão em minutos para cada uma das etapas.

<table align="center">
  <tr>
    <th></th>
    <th colspan="2">Montagem</th>
    <th colspan="2">Forno</th>
    <th colspan="2">Embalagem</th>
  </tr>
  <tr>
    <th>Pizza</th>
    <th>Média</th>
    <th>Desvio</th>
    <th>Média</th>
    <th>Desvio</th>
    <th>Média</th>
    <th>Desvio</th>
  </tr>
  <tr>
    <td>Especial</td>
    <td>3</td>
    <td>0.5</td>
    <td>6</td>
    <td>1</td>
    <td>2</td>
    <td>0.5</td>
  </tr>
  <tr>
    <td>Super</td>
    <td>2</td>
    <td>0.5</td>
    <td>5</td>
    <td>1</td>
    <td>2</td>
    <td>0.5</td>
  </tr>
  <tr>
    <td>Luxo</td>
    <td>2</td>
    <td>0.5</td>
    <td>6</td>
    <td>1</td>
    <td>2</td>
    <td>0.5</td>
  </tr>
</table>

Historicamente 30% dos pedidos são da pizza Especial, 50% da pizza Super e 20% da pizza Luxo.

A distribuição de probabilidade do intervalo entre os pedidos está no quadro a seguir:

<table align="center">
  <tr>
    <th colspan="2">Horário entre 17h e 19h</th>
    <th colspan="2">Horário entre 19h e 22h</th>
  </tr>
  <tr>
    <td>3</td>
    <td>10%</td>
    <td>0</td>
    <td>10%</td>
  </tr>
  <tr>
    <td>4</td>
    <td>10%</td>
    <td>1</td>
    <td>30%</td>
  </tr>
  <tr>
    <td>5</td>
    <td>20%</td>
    <td>2</td>
    <td>30%</td>
  </tr>
  <tr>
    <td>6</td>
    <td>40%</td>
    <td>3</td>
    <td>20%</td>
  </tr>
  <tr>
    <td>7</td>
    <td>20%</td>
    <td>5</td>
    <td>10%</td>
  </tr>
</table>

O Forno da pizzaria tem capacidade para 5 pizzas e na cozinha há somente 3 funcionários, cada um responsável por uma etapa do processo.

- Faça uma simulação para cinco dias determinando para cada dia o tempo médio, máximo e mínimo de espera do cliente.
- O que acontece se dobrarmos o número de funcionários?
- Sugira uma forma de reduzir em até 30% o tempo máximo de espera.


<h2> Modelagem </h2>

Para realizarmos as simulações, primeiro modelamos o problema com o intuito de estudá-lo melhor.

![image](https://github.com/Pedro2000-ui/Processos-Estocasticos/assets/76501071/56721cad-ce01-4331-9d88-23372185e034)

Para esse primeiro caso, como temos apenas 1 funcionário por etapa, a pizza só avançará para a próxima etapa quando o pedido anterior já tiver avançado. Por exemplo, ao chegar o pedido número 3 ele irá de imediato para fila de montagem, mas só irá para montagem quando o pedido anterior (nesse caso o 2) já estiver avançado para fila do forno, e assim sucessivamente.
A única etapa do processo que independe da quantidade de funcionários é a etapa do forno, onde não analisamos a quantidade de funcionários que trabalham naquela parte, e sim, a capacidade máxima do forno, onde para esse caso é de 5 pizzas.

<h2> Explicando cada etapa... </h2>
<h3> Chegadas </h3>
O primeiro passo é simular as chegadas dos pedidos na pizzaria, onde usamos a tabela de probabilidade (que se encontra em <b>Problema</b>) com base nos horários entre 17h e 19h, e 19h e 22h. Para isso sorteamos números entre 1 e 100 e definimos quais números representarão tal probabilidade.

Por exemplo: Entre 17h e 19h temos 10% de chance de um pedido chegar no intervalo de 3 minutos, logo em um sorteio de 100 números, podemos considerar que se sortear um número x <= 10 ele representará os 3 minutos. Assim temos os seguintes casos:
- 0 < x <= 10 representará 3min
- 10 < x <= 20 representará 4min
- 20 < x <= 40 representará 5min
- 40 < x <= 80 representará 6min
- 80 < x <= 100 representará 7min

Com isso, partimos do ponto 17h e vamos sorteando os números, obtendo qual intervalo ele representará, acrescentamos esse intervalo ao tempo atual e verificamos se já é igual ou maior que 19h. Quando ocorrer esse caso, mantemos a mesma lógica, porém aplicamos agora a tabela de probabilidade com base nos horários entre 19h e 22h.

Após gerarmos todas as chegadas entre 17h e 22h, teremos a quantidade total de pedidos feitos em um dia.

<h3> Tipos de Pizza </h3>
Para simular quais tipos de pizza estão chegando utilizamos a mesma lógica acima, porém com valores diferentes onde:

- 0 < x <= 30 representará o número 1
- 30 < x <= 50 representará o número 2
- 50 < x <= 100 representará o número 3

Cada número representará um tipo de pizza, sendo 1 para pizza Especial, 2 para pizza Luxo e 3 para pizza Super. É importante sabermos qual tipo de pizza está chegando para aplicar a lógica de probabilidade em cada etapa, pois cada tipo de pizza possui uma distribuição normal diferente para cada etapa.

#### Trecho de código referente as duas etapas citadas acima (Chegadas e Tipos de pizza)

```c
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
```

<h3> Montagem, Forno e Embalagem </h3>
Para todas essas etapas, utilizamos uma lógica semelhante, porém diferente dos casos acima, a distribuição de probabilidade nessas etapas é baseada em uma distribuição normal, então para isso utlizamos a técnica de Box-Muller para sorteamos números aleatórios com base nessa distribuição.

<h4> Box Muller </h4>
A técnica da transformação de Box-Muller é um método comumente usado para gerar números aleatórios com distribuição normal a partir de números aleatórios uniformemente distribuídos. A técnica envolve as seguintes etapas:

- Geração de dois números aleatórios independentes e uniformemente distribuídos, u1 e u2, no intervalo [0, 1].
- Aplicação das transformações matemáticas para obter dois números independentes e normalmente distribuídos, z1 e z2.

As fórmulas para a transformação de Box-Muller são as seguintes:

$$
z_1 = \sqrt{-2 \cdot \log(u_1)} \cdot \cos(2 \pi \cdot u_2)
$$

$$
z_2 = \sqrt{-2 \cdot \log(u_1)} \cdot \sin(2 \pi \cdot u_2)
$$

Os números z1 e z2 gerados pelas transformações de Box-Muller seguem uma distribuição normal padrão (com média 0 e desvio padrão 1). Para obter uma distribuição normal com média μ e desvio padrão σ, basta multiplicar z1 e z2 por σ e adicionar μ:

$$
x_1 = \sigma \cdot z_1 + \mu
$$

$$
x_2 = \sigma \cdot z_2 + \mu
$$

##### Trecho do código em C:

```c
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
```
Por ser uma função que retorna um valor, ela é chamada em <b>momentos</b> diferentes do código. Então a função verifica qual momento é esse (Montagem, Forno ou Embalagem) e qual tipo de pizza está passando por tal processo.

Com essa técnica conseguimos gerar o tempo que irá demorar em cada etapa do processo com base em uma média e desvio padrão que são dados que possuem valores específicos com base no tipo de pizza.

<h4> Montagem e Embalagem </h4>
Para um pedido chegar nessa etapa, precisamos verificar se o pedido anterior já se encontra na fila Forno e o número de pedidos anteriores que vamos verificar é baseado no números de funcionários que temos por etapa:

```c
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
```

O código acima se refere apenas a parte da Montagem, porém na parte da Embalagem segue a mesma lógica.

<h4> Forno </h4>
Na parte do forno, segue-se uma lógica similar, tendo como única diferença que não verificamos os pedidos com base no números de funcionários alocados naquela tarefa, e sim, na capacidade máxima do forno.

```c
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
```

<h3> Dados Coletados </h3>
 Realizamos diversos testes e tivemos os seguintes resultados:
 
 <h4> 5 dias e 1 funcionário por etapa </h4> 
 
 ```
Funcionários por Etapa: 1

Dia nº 1
Menor tempo: 5.00 min
Tempo médio: 37.41 min
Maior tempo: 46.00 min

Dia nº 2
Menor tempo: 5.00 min
Tempo médio: 14.39 min
Maior tempo: 27.00 min

Dia nº 3
Menor tempo: 6.00 min
Tempo médio: 30.51 min
Maior tempo: 37.00 min

Dia nº 4
Menor tempo: 5.00 min
Tempo médio: 22.39 min
Maior tempo: 50.00 min

Dia nº 5
Menor tempo: 5.00 min
Tempo médio: 23.01 min
Maior tempo: 48.00 min
```

```
Pedido nº 18
Tipo de Pizza: 1
Chegada: 18:40
Fila Montagem: 18:40
Montagem: 18:40
Fila Forno: 18:42
Forno: 18:42
Fila Embalagem: 18:48
Embalagem: 18:48
Saída: 18:49
Tempo de Sistema: 00:09

Pedido nº 19
Tipo de Pizza: 3
Chegada: 18:47
Fila Montagem: 18:47
Montagem: 18:47
Fila Forno: 18:47
Forno: 18:47
Fila Embalagem: 18:53
Embalagem: 18:53
Saída: 18:55
Tempo de Sistema: 00:08

Pedido nº 20
Tipo de Pizza: 3
Chegada: 18:53
Fila Montagem: 18:53
Montagem: 18:53
Fila Forno: 18:54
Forno: 18:54
Fila Embalagem: 18:59
Embalagem: 18:59
Saída: 19:00
Tempo de Sistema: 00:07

Pedido nº 21
Tipo de Pizza: 2
Chegada: 18:58
Fila Montagem: 18:58
Montagem: 18:58
Fila Forno: 19:00
Forno: 19:00
Fila Embalagem: 19:05
Embalagem: 19:05
Saída: 19:07
Tempo de Sistema: 00:09
```

```
Pedido nº 89
Tipo de Pizza: 3
Chegada: 21:31
Fila Montagem: 21:31
Montagem: 21:38
Fila Forno: 21:39
Forno: 21:39
Fila Embalagem: 21:44
Embalagem: 21:48
Saída: 21:50
Tempo de Sistema: 00:19

Pedido nº 90
Tipo de Pizza: 3
Chegada: 21:31
Fila Montagem: 21:31
Montagem: 21:39
Fila Forno: 21:40
Forno: 21:40
Fila Embalagem: 21:42
Embalagem: 21:50
Saída: 21:51
Tempo de Sistema: 00:20

Pedido nº 91
Tipo de Pizza: 1
Chegada: 21:31
Fila Montagem: 21:31
Montagem: 21:40
Fila Forno: 21:43
Forno: 21:43
Fila Embalagem: 21:48
Embalagem: 21:51
Saída: 21:53
Tempo de Sistema: 00:22

Pedido nº 92
Tipo de Pizza: 1
Chegada: 21:31
Fila Montagem: 21:31
Montagem: 21:43
Fila Forno: 21:46
Forno: 21:46
Fila Embalagem: 21:52
Embalagem: 21:53
Saída: 21:54
Tempo de Sistema: 00:23
```

 <h4> 5 dias e 2 funcionários por etapa </h4> 

```
Funcionários por Etapa: 2
Dia nº 1
Menor tempo: 5.00 min
Tempo médio: 14.34 min
Maior tempo: 22.00 min

Dia nº 2
Menor tempo: 3.00 min
Tempo médio: 13.30 min
Maior tempo: 20.00 min

Dia nº 3
Menor tempo: 5.00 min
Tempo médio: 9.39 min
Maior tempo: 15.00 min

Dia nº 4
Menor tempo: 4.00 min
Tempo médio: 16.31 min
Maior tempo: 23.00 min

Dia nº 5
Menor tempo: 5.00 min
Tempo médio: 15.04 min
Maior tempo: 25.00 min

```
```
Dia nº 1
Pedido nº 1
Tipo de Pizza: 3
Chegada: 17:04
Fila Montagem: 17:04
Montagem: 17:04
Fila Forno: 17:05
Forno: 17:05
Fila Embalagem: 17:07
Embalagem: 17:07
Saída: 17:08
Tempo de Sistema: 00:04

Pedido nº 2
Tipo de Pizza: 3
Chegada: 17:09
Fila Montagem: 17:09
Montagem: 17:09
Fila Forno: 17:11
Forno: 17:11
Fila Embalagem: 17:15
Embalagem: 17:15
Saída: 17:17
Tempo de Sistema: 00:08

Pedido nº 3
Tipo de Pizza: 3
Chegada: 17:13
Fila Montagem: 17:13
Montagem: 17:13
Fila Forno: 17:15
Forno: 17:15
Fila Embalagem: 17:19
Embalagem: 17:19
Saída: 17:20
Tempo de Sistema: 00:07

Pedido nº 4
Tipo de Pizza: 2
Chegada: 17:18
Fila Montagem: 17:18
Montagem: 17:18
Fila Forno: 17:19
```
```
Pedido nº 117
Tipo de Pizza: 3
Chegada: 21:53
Fila Montagem: 21:53
Montagem: 21:53
Fila Forno: 21:54
Forno: 21:54
Fila Embalagem: 21:57
Embalagem: 21:59
Saída: 22:00
Tempo de Sistema: 00:07

Pedido nº 118
Tipo de Pizza: 1
Chegada: 21:58
Fila Montagem: 21:58
Montagem: 21:58
Fila Forno: 22:01
Forno: 22:01
Fila Embalagem: 22:09
Embalagem: 22:09
Saída: 22:10
Tempo de Sistema: 00:12

Pedido nº 119
Tipo de Pizza: 3
Chegada: 21:59
Fila Montagem: 21:59
Montagem: 21:59
Fila Forno: 22:00
Forno: 22:00
Fila Embalagem: 22:05
Embalagem: 22:05
Saída: 22:07
Tempo de Sistema: 00:08

Pedido nº 120
Tipo de Pizza: 3
Chegada: 22:02
Fila Montagem: 22:02
Montagem: 22:02
Fila Forno: 22:04
Forno: 22:04
Fila Embalagem: 22:09
Embalagem: 22:09
Saída: 22:10
Tempo de Sistema: 00:08
```

Note que para 1 funcionário por posto, o tempo médio e máximo são maiores, e apresentam uma alta nos valores após as 19h onde a incidência de chegadas de pedidos é maior.
Quando colocamos 2 funcionários por posto o tempo máximo reduz mais que 50% e temos um tempo médio de sistema bem menor também. Sendo uma solução viável para o problema de "reduzir em até 30% o tempo máximo de espera".





