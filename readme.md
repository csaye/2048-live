# 2048 Live

"2048" controlled through real-time object detection.

[![YouTube Showcase](https://img.youtube.com/vi/plsA6wMOhsY/mqdefault.jpg)](https://youtu.be/plsA6wMOhsY)

## Dependencies

This project depends on SDL2 to display the game board and OpenCV to process camera input.

Installation with homebrew:

```bash
brew install sdl2 opencv
```

## Compiling

Compiling with g++:

```bash
g++ main.cpp -std=c++17 -lSDL2 `pkg-config --cflags --libs opencv4` -o 2048Live
```

Then either run the executable directly or use:

```bash
./2048Live
```

## Usage

Left click and drag to select an object to track. Pause tracking with p and clear the tracker with c.

When the center of the object (red dot) leaves the center of the screen (green box) the board will update accordingly.

WASD/arrow keys are also functional for shifting the board.
