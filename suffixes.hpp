#ifndef CHIP8EMU_SUFFIXES_HPP
#define CHIP8EMU_SUFFIXES_HPP

#include <cstdint>

inline constexpr uint8_t operator "" _u8(int arg) noexcept {
  return static_cast<uint8_t>(arg);
}

inline constexpr uint16_t operator "" _u16(int arg) noexcept {
  return static_cast<uint16_t>(arg);
}


#endif //CHIP8EMU_SUFFIXES_HPP
