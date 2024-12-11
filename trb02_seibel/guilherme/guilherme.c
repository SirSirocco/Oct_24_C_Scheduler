#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

// Estrutura para representar um quadro de página
typedef struct {
    unsigned int pagina;  // Índice da página
    bool referenciada;    // Flag para o algoritmo de Segunda Chance
    bool modificada;      // Flag para páginas sujas
    int tempo_uso;        // Instante de último uso (para LRU)
} Quadro;

#define MAX_QUADROS 256  // Máximo de quadros de página
Quadro quadros[MAX_QUADROS];
int total_quadros;       // Número de quadros disponíveis
int contador_tempo = 0;  // Simula o tempo para o algoritmo LRU
int page_faults = 0;     // Contador de Page Faults
int paginas_sujas = 0;   // Contador de páginas sujas escritas no disco

// Variáveis gerais
int bits_deslocamento; // Número de bits do deslocamento para o tamanho da página
int ponteiro = 0;      // Ponteiro circular para Segunda Chance

// Função para inicializar os quadros
void inicializarQuadros(int num_quadros) {
    total_quadros = num_quadros;
    for (int i = 0; i < total_quadros; i++) {
        quadros[i].pagina = -1;
        quadros[i].referenciada = false;
        quadros[i].modificada = false;
        quadros[i].tempo_uso = 0;
    }
}

// Função para calcular o número de bits do deslocamento
int calcularBitsDeslocamento(int tamanho_pagina_kb) {
    return (int)log2(tamanho_pagina_kb * 1024);
}

// Função para verificar se a página já está carregada
int buscarPagina(unsigned int pagina) {
    for (int i = 0; i < total_quadros; i++) {
        if (quadros[i].pagina == pagina) {
            return i;  // Retorna o índice do quadro
        }
    }
    return -1;  // Página não encontrada
}

// Algoritmo LRU
int substituirLRU(unsigned int nova_pagina, char tipo_acesso) {
    int indice_menor_tempo = 0;  // Índice da página menos usada
    for (int i = 1; i < total_quadros; i++) {
        if (quadros[i].tempo_uso < quadros[indice_menor_tempo].tempo_uso) {
            indice_menor_tempo = i;
        }
    }

    // Substitui a página no quadro encontrado
    if (quadros[indice_menor_tempo].modificada) {
        paginas_sujas++;
    }
    quadros[indice_menor_tempo].pagina = nova_pagina;
    quadros[indice_menor_tempo].modificada = (tipo_acesso == 'W');
    quadros[indice_menor_tempo].tempo_uso = contador_tempo++;

    return indice_menor_tempo;
}

void acessarPaginaLRU(unsigned int pagina, char tipo_acesso) {
    int indice = buscarPagina(pagina);

    if (indice == -1) {  // Page fault
        page_faults++;
        if (contador_tempo < total_quadros) {  // Espaço livre
            quadros[contador_tempo].pagina = pagina;
            quadros[contador_tempo].modificada = (tipo_acesso == 'W');
            quadros[contador_tempo].tempo_uso = contador_tempo++;
        } else {  // Substituição
            substituirLRU(pagina, tipo_acesso);
        }
    } else {  // Página já está na memória
        quadros[indice].tempo_uso = contador_tempo++;
        if (tipo_acesso == 'W') {
            quadros[indice].modificada = true;
        }
    }
}

// Algoritmo Segunda Chance
int substituirSegundaChance(unsigned int nova_pagina, char tipo_acesso) {
    while (true) {
        if (!quadros[ponteiro].referenciada) {
            // Página sem segunda chance, substituir
            if (quadros[ponteiro].modificada) {
                paginas_sujas++;
            }
            quadros[ponteiro].pagina = nova_pagina;
            quadros[ponteiro].referenciada = true;
            quadros[ponteiro].modificada = (tipo_acesso == 'W');
            return ponteiro;
        } else {
            // Dá uma segunda chance à página
            quadros[ponteiro].referenciada = false;
            ponteiro = (ponteiro + 1) % total_quadros;
        }
    }
}

void acessarPaginaSegundaChance(unsigned int pagina, char tipo_acesso) {
    int indice = buscarPagina(pagina);

    if (indice == -1) {  // Page fault
        page_faults++;
        if (contador_tempo < total_quadros) {  // Espaço livre
            quadros[contador_tempo].pagina = pagina;
            quadros[contador_tempo].referenciada = true;
            quadros[contador_tempo].modificada = (tipo_acesso == 'W');
            contador_tempo++;
        } else {  // Substituição
            substituirSegundaChance(pagina, tipo_acesso);
        }
    } else {  // Página já está na memória
        quadros[indice].referenciada = true;
        if (tipo_acesso == 'W') {
            quadros[indice].modificada = true;
        }
    }
}

// Função principal do simulador
int main(int argc, char *argv[]) {
    if (argc != 5) {
        printf("Uso: %s <algoritmo> <arquivo.log> <tamanho_pagina_kb> <tamanho_memoria_mb>\n", argv[0]);
        return 1;
    }

    char *algoritmo = argv[1];
    char *arquivo_log = argv[2];
    int tamanho_pagina_kb = atoi(argv[3]);
    int tamanho_memoria_mb = atoi(argv[4]);

    bits_deslocamento = calcularBitsDeslocamento(tamanho_pagina_kb);
    total_quadros = (tamanho_memoria_mb * 1024) / tamanho_pagina_kb;

    inicializarQuadros(total_quadros);

    FILE *file = fopen(arquivo_log, "r");
    if (!file) {
        printf("Erro ao abrir o arquivo %s\n", arquivo_log);
        return 1;
    }

    unsigned int endereco;
    char tipo_acesso;

    while (fscanf(file, "%x %c", &endereco, &tipo_acesso) == 2) {
        unsigned int pagina = endereco >> bits_deslocamento;

        if (strcmp(algoritmo, "LRU") == 0) {
            acessarPaginaLRU(pagina, tipo_acesso);
        } else if (strcmp(algoritmo, "SegundaChance") == 0) {
            acessarPaginaSegundaChance(pagina, tipo_acesso);
        } else {
            printf("Algoritmo %s não suportado.\n", algoritmo);
            fclose(file);
            return 1;
        }
    }

    fclose(file);

    // Exibe o relatório final
    printf("Simulação finalizada\n");
    printf("Algoritmo: %s\n", algoritmo);
    printf("Tamanho da memória: %d MB\n", tamanho_memoria_mb);
    printf("Tamanho da página: %d KB\n", tamanho_pagina_kb);
    printf("Page Faults: %d\n", page_faults);
    printf("Páginas Sujas Escritas: %d\n", paginas_sujas);

    return 0;
}