#include <display.h>
#include <chip.h>
#include <chrono>
#include <audio.h>


int main(int argc, char* argv[]) {
    // Initialize SDL and setup window, renderer, and texture
    if (argc != 2) {
        std::cerr << "Usage:" << argv[0] << " <ROM>\n";
        return -1;
    }
    display disp;
    chip8 chip;
    Audio audio;
    disp.init();
    audio.init();

    std::string romPath = "C:\\Users\\mertc\\source\\brix.ch8";
    int cycleDelay = 10;
    // Main loop flag
    bool quit = false;
    
    if (!chip.loadROM(romPath))
    {
        std::cerr << "Failed to load ROM\n";
        return EXIT_FAILURE;
    }
    //chip.loadROM(romFilename);
    auto lastCycleTime = std::chrono::high_resolution_clock::now();

    // need to load ROM before emulation starts // chip8.loadRom something

    // Main loop
    chip.initialize();

    uint32_t frameStart, frameTime;

    while (!quit) {
        frameStart = SDL_GetTicks();

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

        

        //if (dt > cycleDelay)
        //{
            //lastCycleTime = currentTime;
            chip.emulateCycle();
            
        //}
        chip.updateTimers();
        if (chip.soundTimer > 0)
        {
            audio.playBeep();
        }
        else
            audio.stopBeep();
        
        if (chip.drawFlag) 
        {            
            disp.drawGraphics(chip.gfx);
            chip.drawFlag = false;
        }
        
        chip.updateKeyStates();
        // Delay to control frame rate
        // SDL_Delay(1000/400);
        frameTime = SDL_GetTicks() - frameStart;
        if (frameTime < FRAME_DURATION) {
            SDL_Delay(FRAME_DURATION - frameTime);
        }

        
    }
    disp.close();
    return 0;
}