# Oct_24_C_Scheduler

[🇧🇷 Leia em Português](#português) | [🇺🇸 Read in English](#english)

## Português

**Data:** Outubro, 2024

**Autores:**

- Guilherme Riechert Senko
- Pedro de Almeida Barizon

## Simulação de Escalonamento Preemptivo de Processos com Chamadas de Sistema

**Objetivo:** desenvolver, em linguagem C e utilizando as primitivas de processos Unix/Linux, como `fork`, `exec`, sinais e comunicação entre processos, um simulador de _kernel_ que gerencie de 3 a 6 processos de aplicação e intercale sua execução com base em eventos simulados de interrupção do tempo e finalização de operações de entrada e saída (E/S). Além disso, implementar um controlador de interrupções para gerar sinais que indiquem o término do _time slice_ e o fim das operações de E/S.

### 1. Estrutura

O sistema simulado, denominado KernelSim, gerencia processos de aplicação que podem ser bloqueados enquanto esperam a finalização de uma operação de E/S ou a chegada de um sinal de término de _time slice_. O controlador de interrupções, InterControllerSim, é responsável por gerar as interrupções ao _kernel_: a cada 1 segundo para o _time slice_ e depois 3 segundos para as operações de E/S, representando operações em um certo dispositivo, chamado D1.

Para a implementação do sistema descrito acima, estruturou-se o projeto da seguinte forma:

### 1.1. `inter_control.c`

Módulo responsável pela implementação do InterControllerSim, que simula o controlador de interrupções. Gera dois tipos de sinais:
`IRQ0` (_TimeSlice_): Interrupção que ocorre a cada 1 segundo, indicando que o tempo máximo de execução de um processo foi atingido.
`IRQ1` (Dispositivo D1): Interrupção que ocorre 3 segundos depois de recebida uma requisição de E/S para D1, simulando, assim, o término da operação requisitada.

O InterControllerSim usa `sleep` de 1 segundo dentro de um _loop_ para gerar as interrupções periódicas de fim de _time slice_ na forma de um `kill` com `IRQ0` destinado ao núcleo. Quando a interrupção de _time slice_ ocorre, o KernelSim é notificado para suspender o processo em execução e ativar o próximo da fila de prontos (_ready state_). Para isso, salva-se o contexto do processo atual — recolocado ao final da fila de prontos, conforme prescreve a política _round robin_ —, e troca-se para o contexto do próximo processo, que será, então, executado.

Quanto às interrupções de E/S, quando uma operação é requisitada, é preparado um alarme de 3 segundos, cujo término acionará o envio de `IRQ1` ao _kernel_, de maneira a avisá-lo do fim da operação. As operações de E/S são simuladas, bloqueando os processos, que terão o seu contexto salvo e, logo após, serão colocados ao final da fila de processos bloqueados (_wait state_). Ao término da operação, liberam-se os processos ao serem recolocados na fila de prontos, para que possam ser novamente executados.

### 1.2. `pcbqueue.c`

Módulo responsável pela implementação das filas de controle dos processos, além das _Process Control Boards_ (PCBs), que armazenam o contexto de processos. Por meio das estruturas aqui definidas, o KernelSim organiza os processos em duas categorias:

- Fila de prontos (`ready_q`): Processos aptos a serem executados.
- Fila de bloqueados por E/S (`wait_q`): Processos em aguardo pelo término de uma operação de E/S.

As filas armazenam as PCBs dos processos, que, nesta versão simplificada, possuem:

- **PID:** identificador do processo (_Process ID_);
- **PC:** contador de programa (_Program Counter_);
- **_syscallargs_** (System Call Arguments): argumentos da última chamada ao sistema requisitada, que, nesta simulação, correspondia exclusivamente a operações de entrada e saída com D1.

O controle do escalonamento é feito por meio de uma fila circular, a `ready_q`, e o KernelSim escolhe o próximo processo pronto para ser executado após a interrupção de _time slice_. Quando um processo realiza uma chamada ao sistema (_system call_ ou, abreviadamente, _syscall_) para E/S, ele é removido da fila de prontos e colocado na fila de bloqueados, `wait_q`. Por fim, ao receber a interrupção de finalização de E/S, o processo é retirado da fila de bloqueados e recolocado na fila de prontos.

### 1.3. `mysem.c`

Trata da criação e gerenciamento de semáforos, que controlam o acesso aos recursos compartilhados pelos processos. O uso de semáforos é crucial para garantir que a troca de contexto entre processos ocorra de maneira segura, sem condições de corrida. A ideia deste módulo é simplificar chamadas às funções da biblioteca nativa Unix `<sys/sem.h>`, cuja sintaxe é um tanto complexa.

A lógica de funcionamento não é totalmente evidente, porque depende de como os programadores do sistema operacional decidiram implementar os semáforos. Apesar disso, pode-se elucidar o funcionamento com uma explicação de alto nível.

Inicialmente, cria-se um semáforo passando-lhe um valor, que indicará o número máximo de processos que podem acessar simultaneamente um certo recurso compartilhado. Em geral, tal valor é 1. Quando um processo executa `sem_down`, decrementa o valor do semáforo. Verifica-se, então, se o decremento produz um valor negativo. Se sim, deve esperar, pois, do contrário, o recurso excederia sua capacidade de processos em simultâneo; do contrário, poderá acessar o recurso. Ao terminar de acessá-lo, incrementa o valor com `sem_up`, indicando ter sido aberta uma vaga.

Neste simulador, os semáforos foram usados para impedir que um processo fosse interrompido antes de terminar de copiar informações para a área de memória compartilhada. Sem este uso, o escalonador apresentava erros de segmentação (_segmentation faults_). Antes de acessar a _shared memory_, o processo executa `sem_down`, que, por sua vez, bloqueava o escalonador do KernelSim. Ao sair, fazia `sem_up`, desbloqueando-o.

### 1.4. `a.c`

Corresponde ao _script_ a ser executado pelos processos a serem escalonados pelo KernelSim. Implementa a simulação de uma chamada ao sistema, denominada `systemcall(char* stream, char* mode)`, em que `stream` é o nome do dispositivo (sempre `"D1"` nesta simulação) a realizar E/S, e mode o tipo de operação: `"R"` (_read_) ou `"W"` (_write_).

Inicialmente, o processo anexa-se à memória compartilhada com o escalonador e compartilha com este um semáforo, chamado `mutex_syscall`, cujo valor máximo é 1 (por definição de _mutex_). Em seguida, realiza 10 iterações em um _loop_ com `sleep` de 1 segundo. Na terceira iteração, faz-se uma chamada de leitura para D1: `syscall(“D1”, “R”)`. Na sexta, uma chamada de escrita: `syscall(“D1”, “W”)`. Ao final, o processo desanexa dos recursos e encerra com `exit(EXIT_SUCCESS)`.

Ao executar `systemcall`, o processo faz um `sem_down` e copia os argumentos da chamada de sistema para locais na memória compartilhada. Ao terminar, envia um `SIGSYS` ao escalonador (indica _syscall_) e, em seguida, faz um `sem_up`. Ao final, fica em pausa com `pause` esperando o `SIGCONT` que virá quando for reescalonado.

### 1.5. `kernel_sim.c`

Implementa o KernelSim. Congrega o escalonador e a implementação de funções auxiliares ao escalonamento. Como este é o principal módulo e aquele que se relaciona com todos os outros, faremos uma explicação geral da simulação nesta seção, em vez de uma específica. Para mais informações, acesse as subseções acima.

Inicialmente, o `kernel_sim` define e inicializa variáveis globais que o auxiliarão no escalonamento, em especial as variáveis de semáforos e de memória compartilhada, e as filas `ready_q` e `wait_q`. Em seguida, cria-se o interControllerSim via `fork`-`exec`, e passa-lhe via `argv` as chaves dos semáforos e da _shared memory_. As informações do interControllerSim são armazenadas em sua respectiva PCB. Em seguida, algo análogo é feito com os processos a serem escalonados, que são postos em pausa com `SIGSTOP` e têm suas PCBs — à exceção da primeira criada — armazenadas na `ready_q`.

O _kernel_, então, inicializa o escalonamento ao exibir mensagem apropriada e ao enviar `SIGCONT` ao primeiro dos processos criados. A partir disso, estando em _loop_ eterno, executará apenas os _handlers_ com base nos sinais recebidos do InterControllerSim e dos processos escalonados.

Quando um processo é encerrado, decrementa-se o contador de processos em escalonamento. Quando este chega a 0, o _kernel_ manda a si mesmo um `SIGINT`, que acionará a `end_scheduling`, de maneira a finalizar o escalonamento.

### 2 Testes

A bem da verdade, o escalonador foi capaz de escalonar inclusive sete processos sem quaisquer erros, apesar de não o ter feito consistentemente. Houve situações em que uma ou outra mensagem referente a uma _syscall_ saía impressa pela metade ou com os argumentos faltando (e.g., `PID XXX requests syscall(,`). Isso se explica pelo fato de que os argumentos a serem exibidos devem ser coletados da PCB, que, por sua vez, é atualizada com dados da memória compartilhada, cuja sincronização não é imediata, o que atrapalha a exibição via `printf`.

Além disso, muito raramente (cerca de 5% dos casos), o escalonador simplesmente entraria em um impasse, ou deixaria um processo em escalonamento _ad aeternum_.

Por fim, um pouco menos raramente (cerca de 10% dos casos), o escalonador não se autoenviaria `SIGINT`, de modo que, em vez de encerrar, ficaria exibindo `Idle` no console eternamente.

### 3 Conclusões

Admitimos ter sido um pouco frustrante não termos conseguido corrigir plenamente as inconsistências apontadas. Nós tentamos (e como!). Seja como for, podemos nos orgulhar do uso de semáforos no acesso de memória compartilhada, que reduziu a incidência dos erros de impressão e eliminou os erros de segmentação. Enfim, foi muito gratificante e edificante construir este escalonador. Se, por um lado, não o recomendaríamos para escalonar os procedimentos de rotina de uma aeronave comercial, é, por outro, uma peça de _software_ que pode figurar em um portfólio.

## English

**Date:** October, 2024

**Authors:**

- Guilherme Riechert Senko
- Pedro de Almeida Barizon

## Preemptive Process Scheduling Simulation with System Calls

**Objective:** Develop, using the C programming language and Unix/Linux process primitives such as `fork`, `exec`, signals, and inter-process communication, a kernel simulator that manages 3 to 6 application processes and switches their execution based on simulated time interrupt events and I/O operation completion. Additionally, implement an interrupt controller to generate signals indicating the end of the time slice and the completion of I/O operations.

### 1 Structure

The simulated system, named KernelSim, manages application processes that can be blocked while waiting for an I/O operation to complete or for a time slice termination signal. The interrupt controller, InterControllerSim, is responsible for generating interrupts for the kernel every 1 second for the time slice and every 3 seconds for operations on a specific device called D1.

For the implementation of the described system, the project was structured as follows:

### 1.1 `inter_control.c`

This module implements InterControllerSim, which simulates the interrupt controller. It generates two types of signals:

- **IRQ0 (TimeSlice):** An interrupt occurring every 1 second, indicating that the maximum execution time of a process has been reached.
- **IRQ1 (Device D1):** An interrupt occurring 3 seconds after an I/O request for D1, simulating the completion of the operation.

InterControllerSim uses a 1-second `sleep` within a loop to generate periodic time slice interrupts in the form of a `kill` with `IRQ0` directed to the kernel. When the time slice interrupt occurs, KernelSim is notified to suspend the running process and activate the next one in the _ready state_ queue. The current process context is saved and placed at the end of the ready queue according to the _round-robin_ policy, and the next process context is loaded for execution.

For I/O interruptions, upon receiving a request, a 3-second alarm is set, triggering an `IRQ1` signal to the kernel to notify it of the operation's completion. I/O operations are simulated by blocked processes, which have their context saved and are placed in the I/O waiting queue. Once completed, processes are released and return to the ready queue for execution.

### 1.2 `pcbqueue.c`

This module implements the process control queues and Process Control Blocks (PCBs) that store process contexts. KernelSim organizes processes into two categories:

- **Ready queue (`ready_q`):** Processes ready for execution.
- **I/O waiting queue (`wait_q`):** Processes waiting for the completion of an I/O operation.

The queues store PCBs that contain:

- **PID:** Process identifier.
- **PC:** Program counter.
- **_syscallargs_ (System Call Arguments):** Arguments of the last system call, which in this simulation exclusively involve I/O operations with D1.

Scheduling control is managed through a circular queue `ready_q`, and KernelSim selects the next ready process for execution after a time slice interruption. When a process makes an I/O system call (_syscall_), it is removed from the ready queue and placed in the waiting queue. Once the I/O completion interrupt occurs, the process is removed from the waiting queue and returns to the ready queue.

### 1.3 `mysem.c`

Manages the creation and control of semaphores for shared resource access between processes. The use of semaphores is crucial to ensure safe context switching without race conditions. This module simplifies calls to the native Unix `<sys/sem.h>` library.

Initially, a semaphore is created with a value indicating the maximum number of processes that can access a resource simultaneously, usually set to 1. When a process performs `sem_down`, it decrements the semaphore value. If the decrement results in a negative value, the process must wait; otherwise, it can access the resource. Upon completion, it calls `sem_up`, signaling the release of the resource.

In this simulation, semaphores are used to prevent a process from being interrupted before completing data copying to shared memory, avoiding segmentation faults.

### 1.4 `a.c`

This script is executed by the processes scheduled by KernelSim. It simulates a system call function `systemcall(char* stream, char* mode)`, where `stream` is the device name (always "D1" in this simulation) and `mode` specifies the type of operation: `"R"` (_read_) or `"W"` (_write_).

The process connects to shared memory and shares a semaphore named `mutex_syscall`, with a maximum value of 1 (acting as a mutex). It then performs 10 iterations in a loop with a 1-second `sleep`. In the third iteration, a read request for D1 is made, and in the sixth, a write request. At the end, the process releases the resources and terminates.

When executing `systemcall`, the process performs `sem_down`, copies arguments to shared memory, sends a `SIGSYS` signal to the scheduler, and calls `sem_up`. It then waits with `pause` until it receives a `SIGCONT` signal.

### 1.5 `kernel_sim.c`

Implements KernelSim, the scheduler, and auxiliary scheduling functions. It initializes global variables, creates InterControllerSim via `fork`-`exec`, and stores its information in a PCB. Similarly, application processes are created and stored in the `ready_q`.

Scheduling starts by sending `SIGCONT` to the first process. KernelSim then enters an infinite loop, responding to signals from InterControllerSim and scheduled processes.

When a process terminates, the process counter is decremented. When it reaches zero, the kernel sends itself a `SIGINT`, triggering `end_scheduling` to stop the scheduler.

### 2 Tests

The scheduler handled up to seven processes successfully, albeit inconsistently. Occasional errors included incomplete syscall messages and rare deadlocks or indefinitely running processes.

### 3 Conclusions

Despite inconsistencies, the use of semaphores significantly improved stability by reducing print errors and eliminating segmentation faults. The project was challenging but rewarding, demonstrating solid scheduling concepts.
