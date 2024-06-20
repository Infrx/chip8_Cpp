#ifndef CHIP_CPP
#define CHIP_CPP
#include<fstream>

#include <CHIP.h>

uint8_t fontset[FONTSET_SIZE] =
{
	0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
	0x20, 0x60, 0x20, 0x20, 0x70, // 1
	0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
	0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
	0x90, 0x90, 0xF0, 0x10, 0x10, // 4
	0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
	0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
	0xF0, 0x10, 0x20, 0x40, 0x40, // 7
	0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
	0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
	0xF0, 0x90, 0xF0, 0x90, 0x90, // A
	0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
	0xF0, 0x80, 0x80, 0x80, 0xF0, // C
	0xE0, 0x90, 0x90, 0x90, 0xE0, // D
	0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
	0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};




void chip8::initialize()
{
	pc = START_ADDRESS;// Initialize registers and memory once
	for(int i = 0; i < 80; ++i)
		memory[i] = fontset[i];
}

void chip8::emulateCycle()
{
	// Fetch Opcode
	opcode = memory[pc] << 8 | memory[pc + 1]; // stores 2 subsequent memory adress
	pc += 2;
	//
	// Decode Opcode - Use Switch statements and dont forget to add break after each opcode is executed

	switch (opcode & 0xF000)	// Check first nibble
	{
		
		case 0x0000:// 0NNN or 00EE or 00E0
			//check fourth nibble
			switch (opcode & 0x0FF)
			{
				case 0x00E0://00E0
					opCode_00E0();
					break;
				case 0x00EE:// 00EE
					//call function
					break;
				default:// 0NNN
					//call function
					break;
			}
			break;
		case 0x1000:// 1NNN
			opCode_1NNN();
			break;
		case 0x2000:// 2NNN
			//call function
			break;
		case 0x3000:// 3XNN
			//call function
			break;
		case 0x4000:// 4XNN
			//call function
			break;
		case 0x5000:// 5XY0
			//call function
			break;
		case 0x6000:// 6XNN
			opCode_6XNN();
			break;
		case 0x7000:// 7XNN
			opCode_7XNN();
			break;
		case 0x9000:// 9XY0
			//call function
			break;
		case 0xA000:// ANNN
			opCode_ANNN();
			break;
		case 0xB000:// BNNN
			//call function
			break;
		case 0xC000:// ANNN
			//call function
			break;
		case 0xD000:// DXYN
			opCode_DXYN();
			break;
		case 0xE000:// EX9E or EXA1
			switch (opcode & 0x000F)
			{
				case 0x000E:// EX9E
					//call function
					break;
				case 0x0001:// EXA1
					//call function
					break;
			}
			break;
			//call function
			break;
		case 0x8000:// 8XY(0 to 7 and E)
			switch (opcode & 0x000F)
			{
				case 0x0000:// 8XY0
					//call function
					break;
				case 0x0001:// 8XY1
					//call function
					break;
				case 0x0002:// 8XY2
					//call function
					break;
				case 0x0003:// 8XY3
					//call function
					break;
				case 0x0004:// 8XY4
					//call function
					break;
				case 0x0005:// 8XY5
					//call function
					break;
				case 0x0006:// 8XY6
					//call function
					break;
				case 0x0007:// 8XY7
					//call function
					break;
				case 0x000E:// 8XYE
					//call function
					break;
			}
			break;
		case 0xF000:// FX
			switch(opcode & 0x00FF)
			{
				case 0x0007: // FX07
					//call function
					break;
				case 0x000A: // FX0A
					//call function
					break;
				case 0x0015: // FX15
					//call function
					break;
				case 0x0018: // FX18
					//call function
					break;
				case 0x001E: // FX1E
					//call function
					break;
				case 0x0029: // FX29
					//call function
					break;
				case 0x0033: // FX33
					//call function
					break;
				case 0x0055: // FX55
					//call function
					break;
				case 0x0065: // FX65
					//call function
					break;
			}
			break;
		//switch (opcode & ) // Check for ?

		
	}




	// Execute Opcode

	// Update timers
}

bool chip8::loadROM(const std::string& romPath) {
	std::ifstream rom(romPath, std::ios::binary | std::ios::ate);
	if (!rom.is_open()) {
		std::cerr << "Failed to open ROM: " << romPath << std::endl;
		return false;
	}

	std::streampos size = rom.tellg(); // Get the size of the ROM
	rom.seekg(0, std::ios::beg); // Seek to the beginning of the ROM

	// Check if ROM size fits in memory (0x200 to 0xFFF)
	if (size > (4096 - 512)) {
		std::cerr << "ROM size exceeds Chip-8 memory capacity." << std::endl;
		return false;
	}

	rom.read(reinterpret_cast<char*>(memory + 512), size); // Load ROM into memory starting at 0x200
	rom.close();

	std::cout << "Loaded ROM: " << romPath << " (" << size << " bytes)" << std::endl;
	return true;
}


void chip8::opCode_00E0()     // pass your own pixel to display instead of vice versa
{
	memset(gfx, 0, sizeof(gfx));
}

void chip8::opCode_1NNN()
{
	// jump to adress NNN
	pc = opcode & 0x0FFF;
}

void chip8::opCode_6XNN()
{
	// store in register VX
	uint8_t i{};
	i = (opcode & 0x0F00) >> 8;
	V[i] = (opcode & 0x00FF);
	
}

void chip8::opCode_7XNN()
{
	// add the value NN to register VX
	uint8_t i{};
	i = (opcode & 0x0F00) >> 8;
	V[i] = V[i] + (opcode & 0x00FF);
}

void chip8::opCode_ANNN()
{
	// Store memoory address NNN in register I
	I = opcode & 0x0FFF;
}

void chip8::opCode_DXYN()
{
	// Draw a sprite at position VX, VY with N bytes of sprite data starting at the address stored in I
	// Set VF to 01 if any set pixels are changed to unset, and 00 otherwise
	

	uint8_t iX{};
	uint8_t iY{};
	uint8_t height{}; // aka number of rows
	unsigned short pixel{};

	iX = (opcode & 0x0F00) >> 8;
	iY = (opcode & 0x00F0) >> 4;
	unsigned short x = V[iX];
	unsigned short y = V[iY];
	height = (opcode & 0x000F);
	V[0xF] == 0; // Reset VF
	

	V[0xF] = 0;
	for (int yline = 0; yline < height; yline++)
	{
		uint8_t pixel = memory[I + yline];
		for (int xline = 0; xline < 8; xline++)
		{
			if ((pixel & (0x80 >> xline)) != 0)
			{
				int pixelIndex = (x + xline + ((y + yline) * 64)) % (64 * 32);
				if (gfx[pixelIndex] == 0xFFFFFFFF)
					V[0xF] = 1;
				gfx[pixelIndex] ^= 0xFFFFFFFF;
				std::cout << "Drawing pixel at (" << x << ", " << y << ")\n";
				std::cout << "Pixel data at index: " << pixelIndex << " is now: " << gfx[pixelIndex] << std::endl;
			}
		}
	}
	drawFlag = true;

}

void chip8::updateTimers()
{

}

#endif