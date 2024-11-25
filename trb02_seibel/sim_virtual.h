/*
TURMA: 3WA

INTEGRANTES:
    * Guilherme Riechert Senko 2011478
    * Pedro de Almeida Barizon 2211350

PROFESSOR: Luiz Fernando Seibel

DATA: 24-11-2024
*/

/**
 * Gets data stored in argv inputted by user.
 */
void get_data(int argc, char** argv);

/**
 * Updates global variables accordingly to the info
 * obtained in get_data.
 */
void configure_sim();

/**
 * Runs the paging simulation.
 */
void paging_sim();

/**
 * Logs the result of the memory simulation.
 * Prints the values of relevant global variables.
 */
void log_result();