#include "chip8display.h"

chip8display::chip8display(int width, int height) : _width(width), _height(height) {
  window = nullptr;
  screen_surface = nullptr;
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
  } else {
    //Create window
    window = SDL_CreateWindow("Chip 8 Emu", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
      printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
    } else {
      //Get window surface
      screen_surface = SDL_GetWindowSurface(window);
      //Fill the surface white
      SDL_FillRect(screen_surface, nullptr, SDL_MapRGB(screen_surface->format, 0xFF, 0xFF, 0xFF));
      //Update the surface
      SDL_UpdateWindowSurface(window);
      //Wait two seconds
      SDL_Delay(10000);
    }
  }
  //Destroy window
  SDL_DestroyWindow(window);
  //Quit SDL subsystems
  SDL_Quit();
}
bool chip8display::draw(uint8_t x_start, uint8_t y, uint8_t imm4, uint16_t i, chip8memory& memory) {
  uint8_t x;
  bool zeroed = false;
  uint8_t shown_pixel, res_pixel;
  for (auto off = 0; off <= imm4; off++) {
    x = static_cast<uint8_t>(x_start + off % this->width());
    shown_pixel = static_cast<uint8_t>(this->read(x, y));
    res_pixel = shown_pixel ^ memory.read(static_cast<uint8_t>(i + off));
    zeroed = zeroed || (shown_pixel != 0 && res_pixel == 0);
  }
  return zeroed;
}

uint16_t chip8display::read(uint8_t x, uint8_t y) {
  return (uint16_t) ((unsigned int*)screen_surface->pixels)[_width * y + x];
}

int chip8display::width() { return _width; }

int chip8display::height() { return _height; }

