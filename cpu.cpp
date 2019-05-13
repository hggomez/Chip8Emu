#include <cstdint>
#include "cpu.h"


void cpu::sys(uint16_t addr) {
}

void cpu::cls() {
}

void cpu::ret() {
  pc = sp;
  sp -= 1;
}

void cpu::jp(uint16_t addr) {
  pc = addr;
}

void cpu::call(uint16_t addr) {
  sp += 1;
  _stack.write(sp, pc);
  pc = addr;
}

void cpu::se_imm8(uint8_t reg, uint8_t imm) {
  if ( vs[reg] == imm ) pc += 2;
}

void cpu::sne_imm8(uint8_t reg, uint8_t imm) {
  if ( vs[reg] != imm ) pc += 2;
}

void cpu::se_reg(uint8_t reg1, uint8_t reg2) {
  if ( vs[reg1] == vs[reg2] ) pc += 2;
}

void cpu::ld_imm8(uint8_t reg, uint8_t imm) {
  vs[reg] = imm;
}

void cpu::add_imm8(uint8_t reg, uint8_t imm) {
  vs[reg] = vs[reg] + imm;
}

void cpu::ld_reg(uint8_t reg1, uint8_t reg2) {
  vs[reg1] = vs[reg2];
}

void cpu::or_reg(uint8_t reg1, uint8_t reg2) {
  vs[reg1] = reg1 | reg2;
}

void cpu::and_reg(uint8_t reg1, uint8_t reg2) {
  vs[reg1] = reg1 & reg2;
}

void cpu::xor_reg(uint8_t reg1, uint8_t reg2) {
  vs[reg1] = reg1 ^ reg2;
}

void cpu::add_reg(uint8_t reg1, uint8_t reg2) {
  vs[reg1] = vs[reg1] + vs[reg2];
  vs[0xF] = uint8_t(vs[reg1] < vs[reg2]);
}

void cpu::sub(uint8_t reg1, uint8_t reg2) {
  vs[0xF] = uint8_t(vs[reg1] > vs[reg2]);
  vs[reg1] -= vs[reg2];
}

void cpu::shr(uint8_t reg) {
  vs[0xF] = vs[reg] % 2_u8;
  vs[reg] >>= 1;
}

void cpu::subn(uint8_t reg1, uint8_t reg2) {
  vs[0xF] = uint8_t(vs[reg2] > vs[reg1]);
  vs[reg1] = vs[reg2] - vs[reg1];
}

void cpu::shl(uint8_t reg) {
  vs[0xF] = vs[reg] / 128_u8;
  vs[reg] <<= 1;
}

void cpu::sne_reg(uint8_t reg1, uint8_t reg2) {
  if ( vs[reg1] != vs[reg2] ) pc += 2;
}

void cpu::ld_i(uint16_t addr) {
  i = addr;
}

void cpu::jp_v0(uint16_t addr) {
  pc = addr + vs[0];
}

void cpu::rnd(uint8_t reg, uint8_t imm) {
  vs[reg] = (rand() % 256_u8) & imm;
}

void cpu::drw(uint8_t regx, uint8_t regy, uint8_t imm4) {

  uint8_t x_start = vs[regx];
  uint8_t y = vs[regy];
  bool zeroed = _display.draw(x_start, y, imm4, i, _memory);
  vs[0xF] = uint8_t(zeroed);

}

//Ex9E - SKP Vx
//Skip next instruction if key with the value of Vx is pressed.
//Checks the keyboard, and if the key corresponding to the value of Vx is currently in the down position, PC is increased by 2.
void cpu::skp(uint8_t reg) {
  this->pc += 2;
}

// /ExA1 - SKNP Vx
//Skip next instruction if key with the value of Vx is not pressed.
//Checks the keyboard, and if the key corresponding to the value of Vx is currently in the up position, PC is increased by 2.
void cpu::sknp(uint8_t reg) {}


void cpu::reg_to_dt(uint8_t reg) {
  dt = vs[reg];
}


void cpu::ld_key_press(uint8_t reg) {}
//Fx0A - LD Vx, K
//Wait for a key press, store the value of the key in Vx.
//All execution stops until a key is pressed, then the value of that key is stored in Vx.
//void ld_key_press(uint8_t reg) {
// vs[reg] = get_input();
//}


void cpu::dt_to_reg(uint8_t reg) {
  vs[reg] = dt;
}

void cpu::reg_to_st(uint8_t reg) {
  st = vs[reg];
}

void cpu::add_i(uint8_t reg) {
  i += vs[reg];
}

//Fx29 - LD F, Vx
//Set I = location of sprite for digit Vx.
//The value of I is set to the location for the hexadecimal sprite corresponding to the value of Vx. See section 2.4, Display, for more information on the Chip-8 hexadecimal font.
//The value of I is set to the location for the hexadecimal sprite corresponding to the value of Vx. See section 2.4, Display, for more information on the Chip-8 hexadecimal font.
void cpu::ld_f(uint8_t reg) {}

//Fx33 - LD B, Vx
//Store BCD representation of Vx in memory locations I, I+1, and I+2.
//The interpreter takes the decimal value of Vx, and places the hundreds digit in memory at location in I, the tens digit at location I+1, and the ones digit at location I+2.
void cpu::ld_b(uint8_t reg) {}

//Fx55 - LD [I], Vx
//Store registers V0 through Vx in memory starting at location I.
//The interpreter copies the values of registers V0 through Vx into memory, starting at the address in I.
void cpu::ld_regs_to_mem(uint8_t reg) {
  for (auto x = 0; x <= reg; x++) {
    _memory.write(static_cast<uint8_t>(i + x), vs[x]);
  }
}

void cpu::capture_keypress() {

}

void cpu::invalid_opcode(uint16_t opcode) {
  fprintf(stderr, "%s%04X", "Invalid opcode: ", opcode);
  exit(-1);
}

void cpu::loop() {
  //fetch
  uint16_t opcode = _memory.read(pc) << 8_u8 | _memory.read(pc + 1_u16);
  //decode


  uint8_t first_nibble = (uint8_t) ((opcode & 0xF000_u8) >> 6);
  uint8_t first_reg_index = (uint8_t) ((opcode & 0x0F00_u8) >> 4);
  uint8_t second_reg_index = (uint8_t) ((opcode & 0x00F0_u8) >> 2);
  auto imm8 = static_cast<uint8_t>(opcode);
  uint16_t addr = opcode & 0x0FFF_u8;
  uint8_t last_nibble = (uint8_t) opcode & 0x000F_u8;
  auto last_byte = static_cast<uint8_t>(opcode);
  uint8_t second_nibble = (uint8_t) ((opcode & 0x0F00_u8) >> 4);

  if (first_nibble == 0x0) {
    if (opcode == 0x00E0) {
      this->cls();
    } else if (opcode == 0x00EE) {
      this->ret();
    } else invalid_opcode(opcode);
  } else if (first_nibble == 0x1) {
    this->jp(addr);
  } else if (first_nibble == 0x2) {
    this->call(addr);
  } else if (first_nibble == 0x3) {
    this->se_imm8(first_reg_index, imm8);
  } else if (first_nibble == 0x4) {
    this->sne_imm8(first_reg_index, imm8);
  } else if (first_nibble == 0x5) {
    this->sne_reg(first_reg_index, second_reg_index);
  } else if (first_nibble == 0x6) {
    this->ld_imm8(first_reg_index, imm8);
  } else if (first_nibble == 0x7) {
    this->add_imm8(first_reg_index, imm8);
  } else if (first_nibble == 0x8) {
    if (last_nibble == 0x7) {
      this->subn(first_reg_index, second_reg_index);
    } else if (last_nibble == 0xE) {
      this->shl(first_reg_index);
    } else {
      this->invalid_opcode(opcode);
    }
  } else if (first_nibble == 0x9) {
    this->sne_reg(first_reg_index, second_reg_index);
  } else if (first_nibble == 0xA) {
    this->ld_i(addr);
  } else if (first_nibble == 0xB) {
    this->jp_v0(addr);
  } else if (first_nibble == 0xC) {
    this->rnd(first_reg_index, imm8);
  } else if (first_nibble == 0xD) {
    this->drw(first_reg_index, second_reg_index, last_nibble);
  } else if (first_nibble == 0xE) {
    if (last_byte == 0x9E) {
      this->skp(first_reg_index);
    } else if (last_byte == 0xA1) {
      this->sknp(first_reg_index);
    } else {
      this->invalid_opcode(opcode);
    }
  } else if (first_nibble == 0xF) {
    if (last_byte == 0x07) {
      this->dt_to_reg(first_reg_index);
    } else if (last_byte == 0x0A) {
      this->ld_key_press(first_reg_index);
    } else if (last_byte == 0x15) {
      this->reg_to_dt(first_reg_index);
    } else if (last_byte == 0x18) {
      this->reg_to_st(first_reg_index);
    } else if (last_byte == 0x1E) {
      this->add_i(first_reg_index);
    } else if (last_byte == 0x29) {
      this->ld_f(second_nibble);
    } else if (last_byte == 0x33) {
      this->ld_b(second_nibble);
    } else if (last_byte == 0x55) {
      this->ld_regs_to_mem(first_reg_index);
    } else if (last_byte == 0x65) {
      this->ld_mem_to_regs(first_reg_index);
    } else {
      this->invalid_opcode(opcode);
    }
  }
}

void cpu::ld_mem_to_regs(uint8_t reg) {
  for (uint16_t x = 0; x <= reg; x++) {
    vs[x] = _memory.read(i + x);
  }
}

void cpu::print_regs() {
  for (int i = 0; i < 16; ++i) {

    cout << "Reg " << i << ": " << vs[i] << endl;
  }
}

void cpu::print_stack() {
  _stack.print();
}

// void cpu::print_display() {
//  _display.print();
// }