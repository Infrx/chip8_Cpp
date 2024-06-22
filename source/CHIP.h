#ifndef CHIP_H
#define CHIP_H

#include <cstdint>
#include <iostream>
#include <chrono>
#include <random>
#include <ctime>

const unsigned int FONT_START_ADDRESS = 0x50;
const unsigned int START_ADDRESS = 0x200;
const unsigned int FONTSET_SIZE = 80;
const double FRAME_DURATION = 20;



class chip8
{
public:
	chip8();
	void initialize();
	void emulateCycle();
	bool drawFlag{false};
	bool loadROM(const std::string& romPath);
	void updateTimers();
	void updateKeyStates();
	uint8_t delayTimer{};
	uint8_t soundTimer{};
	uint32_t gfx[64 * 32]{};  // 64 x 32 resolution 
	uint8_t hexpad[16]{};
	uint8_t tempHexpad[16];

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
	uint16_t opcode{}; // operand code
	
	std::default_random_engine randEngine;
	std::uniform_int_distribution<unsigned int> randDist;

	
	// opcodes functions
	//void opCode_0NNN(); ignore this 
	void opCode_00E0();// Clear Screen
	void opCode_00EE();
	void opCode_1NNN();	// Jump
	void opCode_2NNN(); // Execute subroutine starting at adress NNN
	void opCode_3XNN();
	void opCode_4XNN();
	void opCode_5XY0();
	void opCode_6XNN();	// Set register VX
	void opCode_7XNN();	// Add value to register VX
	void opCode_8XY0();
	void opCode_8XY1();
	void opCode_8XY2();
	void opCode_8XY3();
	void opCode_8XY4();
	void opCode_8XY5();
	void opCode_8XY6();
	void opCode_8XY7();
	void opCode_8XYE();
	void opCode_9XY0();
	void opCode_ANNN();	// Set index register I
	void opCode_BNNN();
	void opCode_CXNN();
	void opCode_DXYN();	// Display/draw
	void opCode_EX9E();
	void opCode_EXA1();
	void opCode_FX07();
	void opCode_FX0A();
	void opCode_FX15();
	void opCode_FX18();
	void opCode_FX1E();
	void opCode_FX29();
	void opCode_FX33();
	void opCode_FX55();
	void opCode_FX65();
	int compareKeyStates(uint8_t* tempKeys, uint8_t* currentKeys);
	
	//
	

};

#endif