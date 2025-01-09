#include "epidemic_sim.h"
#include "simulation_memory.h"


void destroy_shared_memory(int mem, city_t *c) {
    if (munmap(c, sizeof(city_t)) < 0) {
        perror("Error when calling munmap()\n");
    }
    if (close(mem) < 0) {
        perror("Error when calling close(city_mem)\n");
    }
    if (shm_unlink(SHARED_MEM_CITY) < 0) {
        perror("Error when calling shm_unlink()\n");
    }
}

void end_press_agency() {
    mqd_t mq;
    char buffer[BUFFER_SIZE];
    strcpy(buffer, "end");
    mq = mq_open("/news", O_WRONLY | O_CREAT, 0644, NULL);
    mq_send(mq, buffer, sizeof(buffer), 100);
}

void write_evolution(FILE *fptr, int evo[4]) {
    fprintf(fptr, "%d ", evo[0]);
    fprintf(fptr, "%d ", evo[1]);
    fprintf(fptr, "%d ", evo[2]);
    fprintf(fptr, "%d \n", evo[3]);
}

int *get_numbers(city_t *city) {
    static int tmp[4];

    tmp[0] = get_number_of_healthy(city);
    tmp[1] = get_number_of_sick(city);
    tmp[2] = get_number_of_dead(city);
    tmp[3] = get_number_of_burned(city);
    return tmp;
}