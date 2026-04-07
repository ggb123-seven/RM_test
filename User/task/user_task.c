#include "task/user_task.h"

Task_Runtime_t task_runtime;

const osThreadAttr_t attr_init = {
    .name = "Task_Init",
    .priority = osPriorityRealtime,
    .stack_size = 256 * 4,
};

/* User_task */
const osThreadAttr_t attr_RM6020 = {
    .name = "RM6020",
    .priority = osPriorityNormal,
    .stack_size = 256 * 4,
};