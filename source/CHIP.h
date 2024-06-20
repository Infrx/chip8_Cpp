#ifndef CHIP_H
#define CHIP_H

#include <cstdint>
#include <iostream>
const unsigned int START_ADDRESS = 0x200;
const unsigned int FONTSET_SIZE = 80;

class chip8
{
public:
	//chip8();  // constructor may not be neccessary use member function instead
	void initialize();
	void emulateCycle();
	bool drawFlag{false};
	bool loadROM(const std::string& romPath);
	uint8_t delayTimer{};
	uint8_t soundTimer{};
	uint32_t gfx[64 * 32]{};  // 64 x 32 resolution 

private:
	// memory variables
	uint8_t memory[4096]{};   // 4kb RAM
	// 0x000 to 0x1FF contains fonts
	// 0x050 to 0x0A0 reserved
	// 0x200 to 0xFFF for program, 0x200 is start adress

	uint8_t V[16]{};  // V0 to VF , general purpose registers
	uint16_t I{};   // 1 Index register
	uint16_t pc{};  // program counter, 2 bytes due to instructions are also 2 bytes
	uint16_t stack[16]{};  // for subroutines
	uint8_t sp{}; // stack pointer
	uint8_t keypad[16]{};
	uint16_t opcode; // operand code
	
	

	
	// opcodes functions
	void opCode_00E0();// Clear Screen
	void opCode_1NNN();	// Jump
	void opCode_6XNN();	// Set register VX
	void opCode_7XNN();	// Add value to register VX
	void opCode_ANNN();	// Set index register I
	void opCode_DXYN();	// Display/draw

	//
	void updateTimers();

};

#endif