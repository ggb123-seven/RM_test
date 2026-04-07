# Repository Guidelines

## Project Structure & Module Organization
This repository is an STM32F407 firmware workspace generated from STM32CubeMX and built with Keil MDK-ARM. Core generated application files live in `Src/` and `Inc/`. Vendor code is under `Drivers/` and `Middlewares/` and should be treated as external unless you are intentionally patching upstream HAL, USB, or FreeRTOS sources.

Custom application code is organized in `User/`:
- `User/bsp/` for board support wrappers such as GPIO, CAN, flash, and timing.
- `User/device/` for device-facing drivers such as motors.
- `User/task/` for CMSIS-RTOS2 / FreeRTOS tasks and runtime configuration.

Keil project files are in `MDK-ARM/`. The CubeMX source of truth is `zero_program.ioc`.

## Build, Test, and Development Commands
- `UV4.exe -b MDK-ARM\\zero_program.uvprojx -t zero_program`
  Builds the Keil target from the command line.
- Open `MDK-ARM/zero_program.uvprojx` in Keil uVision
  Use this for interactive build, debug, and flash.
- `keilkilll.bat`
  Removes Keil-generated intermediates such as `.o`, `.d`, `.map`, and `.htm`.

Build outputs are written under `MDK-ARM/zero_program/` and include `zero_program.hex`.

## Coding Style & Naming Conventions
Follow the existing C style: 2-space indentation, opening braces on the same line, and short guard clauses. Keep filenames in lowercase with underscores for custom modules, for example `user_task.c` and `motor_rm.c`.

Preserve established prefixes:
- `MX_` and `HAL_` for Cube/HAL-generated interfaces
- `BSP_` for board support functions
- `Task_` for RTOS entry points

When editing generated files in `Src/` or `Inc/`, stay inside `/* USER CODE BEGIN */` blocks whenever possible.

## Testing Guidelines
There is no automated test suite in this workspace. Validate changes by rebuilding in Keil and running on target hardware. For peripheral changes, document the hardware path you exercised, such as CAN, USB CDC, GPIO interrupt, or FreeRTOS task startup.

## Hardware Configuration Notes
This project was built on top of the framework at `E:\honor\RM\未命名文件夹(1)\未命名文件夹`. When changing CubeMX settings, GPIO assignments, or peripheral pin mappings, review that reference project first and keep pin usage aligned unless this repository explicitly requires a different hardware layout.

## Commit & Pull Request Guidelines
Git history is not included in this workspace export, so no project-specific commit convention can be inferred reliably. Use short imperative subjects with a clear scope, for example `task: fix CAN startup ordering`.

Pull requests should summarize the affected module, note `.ioc` or middleware changes explicitly, and include the manual verification performed. Add screenshots, serial logs, or bus traces when the change affects debug views or external interfaces.
