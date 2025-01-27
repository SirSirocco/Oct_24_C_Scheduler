# Oct_24_C_Scheduler

[🇧🇷 Leia em Português](#português) | [🇺🇸 Read in English](#english)

## Português

**Data:** Outubro, 2024

**Autores:**

- Guilherme Riechert Senko
- Pedro de Almeida Barizon

## Simulação de Escalonamento Preemptivo de Processos com Chamadas de Sistema

**Objetivo:** desenvolver, em linguagem C e utilizando as primitivas de processos Unix/Linux, como `fork`, `exec`, sinais e comunicação entre processos, um simulador de _kernel_ que gerencie de 3 a 6 processos de aplicação e intercale sua execução com base em eventos simulados de interrupção do tempo e finalização de operações de entrada e saída (E/S). Além disso, implementar um controlador de interrupções para gerar sinais que indiquem o término do _time slice_ e o fim das operações de E/S.

### Estrutura

O sistema simulado, denominado KernelSim, gerencia processos de aplicação que podem ser bloqueados enquanto esperam a finalização de uma operação de E/S ou a chegada de um sinal de término de _time slice_. O controlador de interrupções, InterControllerSim, é responsável por gerar as interrupções ao _kernel_: a cada 1 segundo para o _time slice_ e depois 3 segundos para as operações de E/S, representando operações em um certo dispositivo, chamado D1.

O projeto é composto de cinco módulos, a serem descritos abaixo:

1.1. inter_control.c
Módulo responsável pela implementação do InterControllerSim, que simula o controlador de interrupções. Gera dois tipos de sinais:
IRQ0 (TimeSlice): Interrupção que ocorre a cada 1 segundo, indicando que o tempo máximo de execução de um processo foi atingido.
IRQ1 (Dispositivo D1): Interrupção que ocorre 3 segundos depois de recebida uma requisição de E/S para D1, simulando, assim, o término da operação requisitada.

Funcionamento
O InterControllerSim usa sleep de 1 segundo dentro de um loop para gerar as interrupções periódicas de fim _time slice_ na forma de um kill com IRQ0 destinado ao núcleo. Quando a interrupção de _time slice_ ocorre, o KernelSim é notificado para suspender o processo em execução e ativar o próximo da fila de prontos (ready state). Para isso, salva-se o contexto do processo atual — recolocado ao final da fila de prontos, conforme prescreve a política round robin —, e troca-se para o contexto do próximo processo, que será, então, executado.
Quanto às interrupções de E/S, quando uma operação é requisitada, é preparado um alarme de 3 segundos, cujo término acionará o envio de IRQ1 ao _kernel_, de maneira a avisá-lo do fim da operação. As operações de E/S são simuladas, bloqueando os processos, que terão o seu contexto salvo e, logo após, serão colocados ao final da fila de processos bloqueados (wait state). Ao término da operação, liberam-se os processos ao serem recolocados na fila de prontos, para que possam ser novamente executados.

1.2. pcbqueue.c
Módulo responsável pela implementação das filas de controle dos processos, além das Process Control Boards (PCBs), que armazenam o contexto de processos. Por meio das estruturas aqui definidas, o KernelSim organiza os processos em duas categorias:
Fila de prontos (ready_q): Processos aptos a serem executados.
Fila de bloqueados por E/S (wait_q): Processos em aguardo pelo término de uma operação de E/S.

As filas armazenam as PCBs dos processos, que, nesta versão simplificada, possuem:
PID: identificador do processo (Process ID);
PC: contador de programa (Program Counter);
syscallargs (System Call Arguments): argumentos da última chamada ao sistema requisitada, que, nesta simulação, correspondia exclusivamente a operações de entrada e saída com D1.

Funcionamento
O controle do escalonamento é feito por meio de uma fila circular, a ready_q, e o KernelSim escolhe o próximo processo pronto para ser executado após a interrupção de time slice. Quando um processo realiza uma chamada ao sistema (system call ou, abreviadamente, syscall) para E/S, ele é removido da fila de prontos e colocado na fila de bloqueados, wait_q. Por fim, ao receber a interrupção de finalização de E/S, o processo é retirado da fila de bloqueados e recolocado na fila de prontos.

1.3. mysem.c
Trata da criação e gerenciamento de semáforos, que controlam o acesso aos recursos compartilhados pelos processos. O uso de semáforos é crucial para garantir que a troca de contexto entre processos ocorra de maneira segura, sem condições de corrida. A ideia deste módulo é simplificar chamadas às funções da biblioteca nativa Unix sys/sem.h, cuja sintaxe é um tanto complexa.

Funcionamento
A lógica de funcionamento não é totalmente evidente, porque depende de como os programadores do sistema operacional decidiram implementar os semáforos. Apesar disso, pode-se elucidar o funcionamento com uma explicação de alto nível.
Inicialmente, cria-se um semáforo passando-lhe um valor, que indicará o número máximo de processos que podem acessar simultaneamente um certo recurso compartilhado. Em geral, tal valor é 1. Quando um processo executa sem_down, decrementa o valor do semáforo. Verifica-se, então, se o decremento produz um valor negativo. Se sim, deve esperar, pois, do contrário, o recurso excederia sua capacidade de processos em simultâneo; do contrário, poderá acessar o recurso. Ao terminar de acessá-lo, incrementa o valor com sem_up, indicando ter sido aberta uma vaga.
Neste simulador, os semáforos foram usados para impedir que um processo fosse interrompido antes de terminar de copiar informações para a área de memória compartilhada. Sem este uso, o escalonador apresentava erros de segmentação (segmentation faults). Antes de acessar a shared memory, o processo executa sem_down, que, por sua vez, bloqueava o escalonador do KernelSim. Ao sair, fazia sem_up, desbloqueando-o.

1.4. a.c
Corresponde ao script a ser executado pelos processos a serem escalonados pelo KernelSim. Implementa a simulação de uma chamada ao sistema, denominada systemcall(char* stream, char* mode), em que stream é o nome do dispositivo (sempre “D1” nesta simulação) a realizar E/S, e mode o tipo de operação: “R” (read) ou “W” (write).

Funcionamento
Inicialmente, o processo anexa-se à memória compartilhada com o escalonador e compartilha com este um semáforo, chamado mutex_syscall, cujo valor máximo é 1 (por definição de mutex). Em seguida, realiza 10 iterações em um loop com sleep de 1 segundo. Na terceira iteração, faz-se uma chamada de leitura para D1: syscall(“D1”, “R”). Na sexta, uma chamada de escrita: syscall(“D1”, “W”). Ao final, o processo desanexa dos recursos e encerra com exit(EXIT_SUCCESS).
Ao executar systemcall, o processo faz um sem_down e copia os argumentos da chamada de sistema para locais na memória compartilhada. Ao terminar, envia um SIGSYS ao escalonador (indica syscall) e, em seguida, faz um sem_up. Ao final, fica em pausa com pause esperando o SIGCONT que virá quando for reescalonado.

1.5. kernel_sim.c
Implementa o KernelSim. Congrega o escalonador e a implementação de funções auxiliares ao escalonamento, dentre as quais se destacam:
context_save(Queue* enq): responsável pela interrupção e pelo salvamento do processo em execução. Enfileira sua PCB na fila enq.
context_swap(Queue* deq): responsável pela recuperação do contexto e pela execução do processo por meio da PCB extraída da fila deq.
(SIGIRQ0) timeslice_handler(int signal): escalona ciclicamente processos da ready_q com context_save(ready_q) e context_swap(ready_q).
(SIGSYS) syscall_handler(int signal): handler para SIGSYS (syscall). Salva o processo atual na fila de bloqueados com context_save(wait_q) e escalona novo processo com context_swap(ready_q). Faz uso do mutex_syscall, porque as operações com contexto acessam à memória compartilhada. Ao final, envia SIGIRQ1 para o InterControllerSim, a fim de indicar requisição E/S.
(SIGIRQ1) io_interrupt_handler(int signal): handler para IRQ1. Apenas retira o processo no início da fila de bloqueados e o recoloca ao final de prontos. Usa as funções context.
(SIGINT) end_scheduling(int signal): handler para SIGINT (Ctrl + C). Responsável pela liberação dos semáforos e da memória compartilhada. Exibe mensagem adequada e encerra o KernelSim com exit(EXIT_SUCCESS).

Funcionamento geral
Como este é o principal módulo e aquele que se relaciona com todos os outros, faremos uma explicação geral da simulação nesta seção, em vez de uma específica. Para mais informações, acesse as subseções acima.
Inicialmente, o kernel*sim define e inicializa variáveis globais que o auxiliarão no escalonamento, em especial as variáveis de semáforos e de memória compartilhada, e as filas ready_q e wait_q. Em seguida, cria-se o interControllerSim via fork-exec, e passa-lhe via argv as chaves dos semáforos e da shared memory. As informações do interControllerSim são armazenadas em sua respectiva PCB. Em seguida, algo análogo é feito com os processos a serem escalonados, que são postos em pausa com SIGSTOP e têm suas PCBs — à exceção da primeira criada — armazenadas na ready_q.
O \_kernel*, então, inicializa o escalonamento ao exibir mensagem apropriada e ao enviar SIGCONT ao primeiro dos processos criados. A partir disso, estando em loop eterno, executará apenas os handlers com base nos sinais recebidos do InterControllerSim e dos processos escalonados. Para evitar redundância, a descrição dos handlers não será repetida.
Quando um processo é encerrado, decrementa-se o contador de processos em escalonamento. Quando este chega a 0, o _kernel_ manda a si mesmo um SIGINT, que acionará a end_scheduling, de maneira a finalizar o escalonamento.

2. Saída
   Para facilitarmos a visualização, consideraremos o caso de dois processos em escalonamento — casos mais complexos serão mostrados em sala de aula.

Conforme visto acima, verificamos que o escalonamento seguirá esta política:
Round robin, com fatia de tempo de 1 segundo;
Duas interrupções de E/S: uma com 3 segundos de burst time (tempo de execução), outra com 6 segundos de burst time.
As interrupções de E/S demorarão 3 segundos.
Como todas interrupções envolvem o mesmo dispositivo, uma operação só poderá ser iniciada depois de a anterior ter sido terminada.
Cada processo executará, no total, por 10 segundos.
O sistema em questão possui apenas uma UCP.

Supondo dois processos, teremos esta linha de tempo:

Figura 1 - Linha do tempo de processos

Nas próximas páginas, vemos o log produzido pelo escalonador para dois processos.

Figura 2.1 - Parte inicial do log do escalonamento de dois processos

Figura 2.2 - Parte final do log do escalonamento de dois processos

### Observações e conclusões

#### Observações

Comparando-se a linha do tempo com a saída do escalonador, percebemos que, apesar de semelhantes, apresentam nítidas divergências. O escalonador, por exemplo, ficou com a UCP desocupada (Idle) em duas ocasiões, ao passo que a linha do tempo mostra apenas um momento de ociosidade. Outra diferença se observa no fato de que, depois de passada uma fatia de tempo, o contador de iterações do processo 1 (PID 30185) saltou de 0 para 2. Como a duração de uma iteração é igual a de uma fatia, isso parece contradizer a linha do tempo.

A explicação para todas as supostas contradições baseia-se no fato de que a linha do tempo representa uma situação ideal, em que o tempo de troca de contexto é desprezado. Além disso, não nos esqueçamos de que o próprio escalonador nosso estava sendo escalonado pelo do sistema operacional. Todas essas condições implicam flutuações nas fatias de tempo e nas operações de E/S, de modo que não se possa prevê-las. Eis, pois, o motivo das diferenças.

Por outro lado, assim como na linha do tempo, foram respeitadas as ordens das chamadas ao sistemas e do término dos processos, demonstrando-se a validade de nosso escalonador.

### Testes

A bem da verdade, o escalonador foi capaz de escalonar inclusive sete processos sem quaisquer erros, apesar de não o ter feito consistentemente. Houve situações em que uma ou outra mensagem referente a uma _syscall_ saía impressa pela metade ou com os argumentos faltando (e.g., `PID XXX requests syscall(,`). Isso se explica pelo fato de que os argumentos a serem exibidos devem ser coletados da PCB, que, por sua vez, é atualizada com dados da memória compartilhada, cuja sincronização não é imediata, o que atrapalha a exibição via `printf`.

Além disso, muito raramente (cerca de 5% dos casos), o escalonador simplesmente entraria em um impasse, ou deixaria um processo em escalonamento _ad aeternum_.

Por fim, um pouco menos raramente (cerca de 10% dos casos), o escalonador não se autoenviaria SIGINT, de modo que, em vez de encerrar, ficaria exibindo `Idle` no console eternamente.

#### Conclusões

Admitimos ter sido um pouco frustrante não termos conseguido corrigir plenamente as inconsistências apontadas. Nós tentamos (e como!). Seja como for, podemos nos orgulhar do uso de semáforos no acesso de memória compartilhada, que reduziu a incidência dos erros de impressão e eliminou os erros de segmentação. Enfim, foi muito gratificante e edificante construir este escalonador. Se, por um lado, não o recomendaríamos para escalonar os procedimentos de rotina de uma aeronave comercial, é, por outro, uma peça de _software_ que pode figurar em um portfólio.
