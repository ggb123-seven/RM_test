/*
    Init Task
*/

/* Includes ----------------------------------------------------------------- */
#include "task/user_task.h"

#include "bsp/can.h"

/* Exported functions ------------------------------------------------------- */
void Task_Init(void *argument) {
  (void)argument;

  if (BSP_CAN_Init() != BSP_OK) {
    osThreadTerminate(osThreadGetId());
    return;
  }

  osKernelLock();

  task_runtime.thread.RM6020 = osThreadNew(Task_RM6020, NULL, &attr_RM6020);
  task_runtime.msgq.user_msg = osMessageQueueNew(2u, 10u, NULL);

  osKernelUnlock();
  osThreadTerminate(osThreadGetId());
}
