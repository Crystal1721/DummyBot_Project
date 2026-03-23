# DummyBot Image Processing

Python project for camera/image processing and object color tracking used in the DummyBot workflow.

## Project Structure

- `Dummy.py`: main script entry.
- `color_detection.py`: color-detection helper script.
- `img_processing/`: image-processing modules.
- `test.py`: quick local test script.
- `best.pt`: model weights used by the project.

## Setup

1. Create and activate a Python virtual environment.
2. Install dependencies used by your scripts.
3. Run your main script:

```bash
python Dummy.py
```

## External Dependency

This project uses code/resources from:

- https://github.com/yesbotics/dualsense-controller-python.git

## Notes

- Runtime outputs under `runs/` are ignored by git.
- Local virtual environments (`venv/`, `.venv/`) are ignored by git.
