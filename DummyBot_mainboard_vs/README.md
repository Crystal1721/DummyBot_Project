# DummyBot Mainboard (STM32)

Firmware project for the DummyBot mainboard using STM32 and CMake/STM32Cube-generated sources.

## Project Structure

- `Core/`: application and HAL startup code.
- `Drivers/`: CMSIS and STM32 HAL drivers.
- `Algorithm/`: kinematics and robot-specific logic.
- `Hardware/`: hardware abstraction/modules.
- `Task/`: task-level application logic.
- `USB_DEVICE/`: USB device stack and configuration.

## Build

Use your configured STM32 toolchain and CMake workflow in this folder.

Typical local flow:

```bash
cmake -S . -B build
cmake --build build
```

## Notes

- Build outputs (`build/`, `Debug/`, `Release/`) are ignored by git.
- `.settings/` is intentionally kept tracked for workspace consistency.
