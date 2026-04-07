/* Includes ----------------------------------------------------------------- */
#include "bsp/gpio.h"

#include <gpio.h>
#include <main.h>

/* Private typedef ---------------------------------------------------------- */
typedef struct {
  uint16_t pin;
  GPIO_TypeDef *gpio;
} BSP_GPIO_MAP_t;

/* Private variables -------------------------------------------------------- */
static const BSP_GPIO_MAP_t gpio_map[BSP_GPIO_NUM] = {
    {ACCL_CS_Pin, ACCL_CS_GPIO_Port},
    {GYRO_CS_Pin, GYRO_CS_GPIO_Port},
    {HW0_Pin, HW0_GPIO_Port},
    {HW1_Pin, HW1_GPIO_Port},
    {HW2_Pin, HW2_GPIO_Port},
    {ACCL_INT_Pin, ACCL_INT_GPIO_Port},
    {GYRO_INT_Pin, GYRO_INT_GPIO_Port},
    {POWER1_CTRL_Pin, POWER1_CTRL_GPIO_Port},
    {POWER2_CTRL_Pin, POWER2_CTRL_GPIO_Port},
    {POWER3_CTRL_Pin, POWER3_CTRL_GPIO_Port},
    {POWER4_CTRL_Pin, POWER4_CTRL_GPIO_Port},
};

static void (*gpio_callback[16])(void);

/* Exported functions ------------------------------------------------------- */
void HAL_GPIO_EXTI_Callback(uint16_t gpio_pin) {
  uint8_t i = 0;

  for (i = 0; i < 16; ++i) {
    if ((gpio_pin & (1u << i)) != 0u && gpio_callback[i] != NULL) {
      gpio_callback[i]();
    }
  }
}

int8_t BSP_GPIO_RegisterCallback(BSP_GPIO_t gpio, void (*callback)(void)) {
  uint16_t pin = 0;
  uint8_t i = 0;

  if (callback == NULL) {
    return BSP_ERR_NULL;
  }
  if (gpio >= BSP_GPIO_NUM) {
    return BSP_ERR;
  }

  pin = gpio_map[gpio].pin;
  for (i = 0; i < 16; ++i) {
    if ((pin & (1u << i)) != 0u) {
      gpio_callback[i] = callback;
      break;
    }
  }
  return BSP_OK;
}

int8_t BSP_GPIO_EnableIRQ(BSP_GPIO_t gpio) {
  switch (gpio) {
    case BSP_GPIO_ACCL_INT:
      HAL_NVIC_EnableIRQ(EXTI4_IRQn);
      break;
    case BSP_GPIO_GYRO_INT:
      HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
      break;
    default:
      return BSP_ERR;
  }
  return BSP_OK;
}

int8_t BSP_GPIO_DisableIRQ(BSP_GPIO_t gpio) {
  switch (gpio) {
    case BSP_GPIO_ACCL_INT:
      HAL_NVIC_DisableIRQ(EXTI4_IRQn);
      break;
    case BSP_GPIO_GYRO_INT:
      HAL_NVIC_DisableIRQ(EXTI9_5_IRQn);
      break;
    default:
      return BSP_ERR;
  }
  return BSP_OK;
}

int8_t BSP_GPIO_WritePin(BSP_GPIO_t gpio, bool value) {
  if (gpio >= BSP_GPIO_NUM) {
    return BSP_ERR;
  }
  HAL_GPIO_WritePin(gpio_map[gpio].gpio, gpio_map[gpio].pin, value ? GPIO_PIN_SET : GPIO_PIN_RESET);
  return BSP_OK;
}

int8_t BSP_GPIO_TogglePin(BSP_GPIO_t gpio) {
  if (gpio >= BSP_GPIO_NUM) {
    return BSP_ERR;
  }
  HAL_GPIO_TogglePin(gpio_map[gpio].gpio, gpio_map[gpio].pin);
  return BSP_OK;
}

bool BSP_GPIO_ReadPin(BSP_GPIO_t gpio) {
  if (gpio >= BSP_GPIO_NUM) {
    return false;
  }
  return HAL_GPIO_ReadPin(gpio_map[gpio].gpio, gpio_map[gpio].pin) == GPIO_PIN_SET;
}
