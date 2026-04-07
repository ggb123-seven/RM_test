/*
    RM6020 Task
    Open-loop test task for a single GM6020 on CAN2.
*/

/* Includes ----------------------------------------------------------------- */
#include "task/user_task.h"

#include "device/motor_rm.h"

/* Private define ----------------------------------------------------------- */
#define RM6020_TEST_MOTOR_ID         0x205u
#define RM6020_TEST_OUTPUT           0.90f
#define RM6020_TEST_START_DELAY_MS   1000u

/* Private variables -------------------------------------------------------- */
static MOTOR_RM_Param_t rm6020_test_motor = {
    .can = BSP_CAN_2,
    .id = RM6020_TEST_MOTOR_ID,
    .module = MOTOR_GM6020,
    .reverse = false,
    .gear = false,
};

/* Exported functions ------------------------------------------------------- */
void Task_RM6020(void *argument) {
  uint32_t delay_tick = 0;
  uint32_t tick = 0;
  uint32_t start_tick = 0;
  int8_t register_ret = DEVICE_ERR;

  (void)argument;

  delay_tick = osKernelGetTickFreq() / RM6020_FREQ;
  if (delay_tick == 0u) {
    delay_tick = 1u;
  }

  osDelay(RM6020_INIT_DELAY);

  register_ret = MOTOR_RM_Register(&rm6020_test_motor);
  if (register_ret != DEVICE_OK && register_ret != DEVICE_ERR_INITED) {
    osThreadTerminate(osThreadGetId());
    return;
  }

  start_tick = osKernelGetTickCount();
  tick = start_tick;

  while (1) {
    float output = 0.0f;

    tick += delay_tick;

    (void)MOTOR_RM_Update(&rm6020_test_motor);

    if ((osKernelGetTickCount() - start_tick) >= RM6020_TEST_START_DELAY_MS) {
      output = RM6020_TEST_OUTPUT;
    }

    (void)MOTOR_RM_SetOutput(&rm6020_test_motor, output);
    (void)MOTOR_RM_Ctrl(&rm6020_test_motor);

    osDelayUntil(tick);
  }
}
