#include <display.h>
#include <chip.h>
#include <chrono>



int main(int argc, char* argv[]) {
    // Initialize SDL and setup window, renderer, and texture
    if (argc != 2) {
        std::cerr << "Usage:" << argv[0] << " <ROM>\n";
        return -1;
    }
    display disp;
    chip8 chip;

    disp.init();

    std::string romPath = "C:\\Users\\mertc\\source\\IBM_Logo.ch8";
    int cycleDelay = 1;
    // Main loop flag
    bool quit = false;
    auto lastCycleTime = std::chrono::high_resolution_clock::now();
    if (!chip.loadROM(romPath))
    {
        std::cerr << "Failed to load ROM\n";
        return EXIT_FAILURE;
    }
    //chip.loadROM(romFilename);
    chip.initialize();

    // need to load ROM before emulation starts // chip8.loadRom something

    // Main loop
    while (!quit) {
        // Handle events on queue
        while (SDL_PollEvent(&disp.event) != 0) {
            if (disp.event.type == SDL_QUIT) {
                quit = true;
            }
        }
        
        // find dt by lasttime - currenttime
        auto currentTime = std::chrono::high_resolution_clock::now();
        float dt = std::chrono::duration<float, std::chrono::milliseconds::period>(currentTime - lastCycleTime).count();

        if (chip.delayTimer > 0){--chip.delayTimer;}
        if (chip.soundTimer > 0){--chip.soundTimer;}

       
        bool timeFlag = false;
        if (dt > cycleDelay)
        {
            lastCycleTime = currentTime;

            chip.emulateCycle();
            timeFlag = true;
        }

        
        if (chip.drawFlag && timeFlag) 
        {            
            disp.drawGraphics(chip.gfx);
            chip.drawFlag = false;
            timeFlag = false;
        }
        
         
        // Delay to control frame rate
        SDL_Delay(1000 / 60);

      
    }
    disp.close();
    return 0;
}