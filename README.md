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
    <td>2/td>
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
- Faça um gráfico do número do pedido e tempo de sistema.
- O que acontece se dobrarmos o número de funcionários?
- Sugira uma forma de reduzir em até 30% o tempo máximo de espera.


<h2> Modelagem </h2>

Para realizarmos as simulações, primeiro modelamos o problema com o intuito de estudá-lo melhor.

![image](https://github.com/Pedro2000-ui/Processos-Estocasticos/assets/76501071/56721cad-ce01-4331-9d88-23372185e034)

Para esse primeiro caso, como temos apenas 1 funcionário por etapa, a pizza só avançará para a próxima etapa quando o pedido anterior já tiver avançado. Por exemplo, ao chegar o pedido número 3 ele irá de imediato para fila de montagem, mas só irá para montagem quando o pedido anterior (nesse caso o 2) já estiver avançado para fila do forno, e assim sucessivamente.
A única etapa do processo que independe da quantidade de funcionários é a etapa do forno, onde não analisamos a quantidade de funcionários que trabalham naquela parte, e sim, a capacidade máxima do forno, onde para esse caso é de 5 pizzas.

<h2> Explicando cada etapa... </h2>
<h3> Chegadas </h3>






