#include <display.cpp>
#include <chip.cpp>

display disp;
chip8 chip;

int main(int argc, char* args[]) {
    // Initialize SDL and setup window, renderer, and texture
    if (!disp.init()) {
        std::cerr << "Failed to initialize!" << std::endl;
        return -1;
    }

    // Main loop flag
    bool quit = false;
    
    
    
    // need to load ROM before emulation starts
    chip.initialize();


    // Main loop
    while (!quit) {
        // Handle events on queue
        while (SDL_PollEvent(&disp.event) != 0) {
            if (disp.event.type == SDL_QUIT) {
                quit = true;
            }
        }

        
        chip.emulateCycle();
        //
        // 
        
        if (chip.drawFlag) {            
            disp.drawGraphics(chip.gfx);
            chip.drawFlag = false;
        }

         
        // Delay to control frame rate
        SDL_Delay(1000 / 60);

      
    }
    disp.close();
    return 0;
}