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

    std::string romPath = "C:\\Users\\mertc\\source\\4-flags.ch8";
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
    

    // need to load ROM before emulation starts // chip8.loadRom something

    // Main loop
    chip.initialize();

    while (!quit) {
        // Handle events on queue

        quit = disp.keyPresses(chip.hexpad);  // handle events, key presses
        /*
        while (SDL_PollEvent(&disp.event) != 0) {
            if (disp.event.type == SDL_QUIT) {
                quit = true;
            }
        }
        */
        // find dt by lasttime - currenttime
        auto currentTime = std::chrono::high_resolution_clock::now();
        float dt = std::chrono::duration<float, std::chrono::milliseconds::period>(currentTime - lastCycleTime).count();

        chip.updateTimers();

        if (dt > cycleDelay)
        {
            lastCycleTime = currentTime;

            chip.emulateCycle();
        }
        
        chip.emulateCycle();
        if (chip.drawFlag) 
        {            
            disp.drawGraphics(chip.gfx);
            chip.drawFlag = false;
        }
        
         
        // Delay to control frame rate
        //SDL_Delay(1000 / 6000);

      
    }
    disp.close();
    return 0;
}