/* PMSIS includes */
#include "pmsis.h"
#include "NN_Functions.h"

uint32_t cycles;
uint32_t tim_cycles;
uint32_t executed_instructions;
uint32_t load_hazards;
uint32_t jump_hazards;

/* Task executed by cluster cores. */
void cluster_helloworld(void *arg)
{
    uint32_t core_id = pi_core_id(), cluster_id = pi_cluster_id();
    // printf("[%d %d] Hello World!\n", cluster_id, core_id);
    switch (core_id)
    {
    case 0:
        printf("[%d %d] cycles of active cores = %d\n", cluster_id, core_id, cycles);
        break;
    case 1:
        printf("[%d %d] executed instruments = %d\n", cluster_id, core_id, executed_instructions);
        break;
    case 2:
        printf("[%d %d] loaded hazards = %d\n", cluster_id, core_id, load_hazards);
        break;
    case 3:
        printf("[%d %d] jumped hazards = %d\n", cluster_id, core_id, jump_hazards);
        break;
    case 4:
        initialize();
        break;
    case 5:
        training_process();
        prediction_process();
        break;
    default:
        break;
    }
}

/* Cluster main entry, executed by core 0. */
void cluster_delegate(void *arg)
{
    printf("Cluster master core entry\n");
    /* Task dispatch to cluster cores. */
    pi_cl_team_fork(pi_cl_cluster_nb_cores(), cluster_helloworld, arg);
    // initialize();
    // training_process();
    // prediction_process();
    printf("Cluster master core exit\n");
}

void helloworld(void)
{
    printf("Entering main controller\n");

    uint32_t errors = 0;
    uint32_t core_id = pi_core_id(), cluster_id = pi_cluster_id();
    printf("[%d %d] Hello World!\n", cluster_id, core_id);

    struct pi_device cluster_dev;
    struct pi_cluster_conf cl_conf;

    /* Init cluster configuration structure. */
    pi_cluster_conf_init(&cl_conf);
    cl_conf.id = 0; /* Set cluster ID. */
    /* Configure & open cluster. */
    pi_open_from_conf(&cluster_dev, &cl_conf);

    pi_perf_conf(1 << PI_PERF_CYCLES | 1 << PI_PERF_ACTIVE_CYCLES | 1 << PI_PERF_INSTR | 1 << PI_PERF_LD_STALL | 1 << PI_PERF_JR_STALL);
    pi_perf_reset();
    pi_perf_start();

    if (pi_cluster_open(&cluster_dev))
    {
        printf("Cluster open failed !\n");
        pmsis_exit(-1);
    }

    pi_perf_stop();
    cycles = pi_perf_read(PI_PERF_ACTIVE_CYCLES);
    tim_cycles = pi_perf_read(PI_PERF_CYCLES);
    executed_instructions = pi_perf_read(PI_PERF_INSTR);
    load_hazards = pi_perf_read(PI_PERF_LD_STALL);
    jump_hazards = pi_perf_read(PI_PERF_JR_STALL);
    printf("Perf : %d cycles Timer : %d cycles\n", cycles, tim_cycles);

    /* Prepare cluster task and send it to cluster. */
    struct pi_cluster_task cl_task;

    pi_cluster_send_task_to_cl(&cluster_dev, pi_cluster_task(&cl_task, cluster_delegate, NULL));

    pi_cluster_close(&cluster_dev);

    printf("Test success !\n");

    pmsis_exit(errors);
}

/* Program Entry. */
int main(void)
{
    printf("\n\n\t *** PMSIS HelloWorld ***\n\n");
    return pmsis_kickoff((void *)helloworld);
}
