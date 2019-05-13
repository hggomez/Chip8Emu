#ifndef CHIP8EMU_CHIP8MEMORY_HPP
#define CHIP8EMU_CHIP8MEMORY_HPP

#include <iostream>
#include <cstdio>

using namespace std;

class chip8memory {
public:
  uint8_t read(uint16_t position) {
    return _memory[position];
  }
  void write(uint16_t position, uint16_t value) {
    _memory[position] = static_cast<uint8_t>(value);
  }
  void load_game(char* game_file) {
    FILE *game;
    game = fopen(game_file, "rb");
    if (nullptr == game) {
      fprintf(stderr, "Unable to open game: %s\n", game_file);
      exit(-1); // TODO: replace with an exception and add handler in main function
    }
    auto read_amount = fread(&_memory[0x200], 1, 0x1000 - 0x200, game);
    printf("%lu", read_amount);
    fclose(game);
  }
  void print() {
    for (int i = 0; i < 4096; ++i)
      cout << "Memory pos " << i << ": " << _memory[i] << endl;
  }
private:
  uint8_t _memory[0x1000];
};


#endif //CHIP8EMU_CHIP8MEMORY_HPP
