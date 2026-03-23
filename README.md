# 3DOF Based Robotic Arm Project - Dummy Bot

![DummyBot](https://github.com/user-attachments/assets/a840bac3-4e79-4815-9bcd-0ea9678084c0)

## Project Overview
Dummy Bot is a 3DOF robotic arm platform developed as an integrated mechatronics project.
The system combines embedded control, inverse/forward kinematics, and image processing (using YOLOv12) for pick-and-place style tasks.

Dummy Bot supports two operation modes:
- `Manual mode`: movement is controlled in real time using a DualSense joystick.
- `Auto mode`: objects are automatically sorted by color.

This repository is organized into two core parts:
- `DummyBot_mainboard_vs/`: STM32 firmware and low-level robot control.
- `DummyBot_img_processing/`: Python-based image processing and detection workflow.

## Demo Media
- Video 1: https://github.com/user-attachments/assets/63c57ed2-1b23-4ab9-931d-a7e0c35d11c9
- Video 2: https://github.com/user-attachments/assets/74bc9608-352a-4692-836a-d715cc78f4d8

## System Highlights
- 3DOF robotic arm kinematic control.
- Embedded firmware running on STM32 mainboard.
- Computer-vision module for object/color detection with YOLOv12.
- Dual operation modes: manual joystick control and automatic color sorting.
- Modular project split between control firmware and high-level image processing.

## Repository Structure
```text
DummyBot_Project/
├── DummyBot_mainboard_vs/      # STM32 firmware (control, drivers, tasks)
├── DummyBot_img_processing/    # Python image-processing pipeline
└── Docs/                        # Project documents (PDF, reports)
```

## Main Components
### 1. Mainboard Firmware (`DummyBot_mainboard_vs`)
- Kinematics and robot-control logic (`Algorithm/`).
- Peripheral abstraction and board support (`Bsp/`, `Hardware/`).
- Task scheduling and runtime behavior (`Task/`).
- STM32Cube-generated startup/HAL/CMSIS infrastructure.

### 2. Image Processing (`DummyBot_img_processing`)
- Detection and tracking scripts for camera-based operation.
- Utility modules for frame processing.
- Optional model weight support (`best.pt`) for learned detection workflows.

## Getting Started
### Firmware Side
1. Open `DummyBot_mainboard_vs` in your STM32/CMake workflow.
2. Configure toolchain and build:

```bash
cmake -S DummyBot_mainboard_vs -B DummyBot_mainboard_vs/build
cmake --build DummyBot_mainboard_vs/build
```

### Image Processing Side
1. Open `DummyBot_img_processing`.
2. Create/activate a Python virtual environment.
3. Install required dependencies.
4. Run the main script:

```bash
python DummyBot_img_processing/Dummy.py
```

## Dependency Note
The image-processing/control integration references:
- https://github.com/yesbotics/dualsense-controller-python.git

## Documentation
- Project document: `Docs/Dummy bot.pdf`
- PCB Schematic: `Docs/Mainboard_F4_Schematic.pdf`
