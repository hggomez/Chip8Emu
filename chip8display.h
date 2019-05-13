#ifndef CHIP8EMU_CHIP8DISPLAY_H
#define CHIP8EMU_CHIP8DISPLAY_H

#include<SDL2/SDL.h>
#include <iostream>
#include <vector>
#include "chip8memory.hpp"

using namespace std;

class chip8display {

public:

  chip8display(int width, int height);
  bool draw(uint8_t x_start, uint8_t y, uint8_t imm4, uint16_t i, chip8memory& memory);
  uint16_t read(uint8_t x, uint8_t y);
  int width();
  int height();

private:

  int _width, _height;
  SDL_Window* window;
  SDL_Surface* screen_surface;

};

#endif //CHIP8EMU_CHIP8DISPLAY_H
