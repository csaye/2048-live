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
