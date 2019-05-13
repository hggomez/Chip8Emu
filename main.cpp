#include "cpu.h"
#include "chip8stack.hpp"
#include "chip8memory.hpp"
#include "chip8display.h"
#include <cstdio>
#include <random>

using namespace std;

int main(int argc, char** argv) {

  if (argc != 2) {
    fprintf(stderr, "%s\n","Usage: ./Chip8Emu game_file");
    exit(-1);
  }

  char* game_file = argv[1];
  chip8memory memory8 = chip8memory();
  chip8stack stack8 = chip8stack();
  chip8display display8(64, 32);
  stack8.print();
  cpu cpu8(memory8, stack8, display8, game_file);
  cpu8.print_regs();
  cpu8.print_stack();
  return 0;
}