#ifndef CHIP8EMU_CHIP8STACK_HPP
#define CHIP8EMU_CHIP8STACK_HPP

#pragma once
#include <iostream>
using namespace std;

class chip8stack {
public:
  uint16_t read(uint8_t position) {
    return _stack[position];
  }
  void write(uint8_t position, uint16_t value) {
    _stack[position] = value;
  }
  void print() {
    for (int i = 0; i < 16; ++i)
      cout << "Stack pos " << i << ": " << _stack[i] << endl;
  }
private:
  uint16_t _stack[16];
};

#endif //CHIP8EMU_CHIP8STACK_HPP
