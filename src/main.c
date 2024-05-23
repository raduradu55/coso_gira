
#include <stdio.h>
#include "include/SDL.h"
#include "constants.h"

struct state {
    SDL_Window* window;
    SDL_Renderer* renderer;
    int running;

    struct time {
        float delta;
        float last_frame;
        float last_second;
        int frames;
    } time;

} state;

int initialize_window(void) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        fprintf(stderr, "error in sdl init\n");
        return FALSE;
    }

    // creating window
    state.window = SDL_CreateWindow(
        "Coso gira",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        0
    );

    if(!state.window) {
        fprintf(stderr, "bad window\n");
        return FALSE;
    }

    // creating renderer
    state.renderer = SDL_CreateRenderer(
        state.window,
        -1,
        0
    );

    if(!state.renderer) {
        fprintf(stderr, "bad renderer");
        return FALSE;
    }

    return TRUE;
}

void process_input() {  
    SDL_Event event;
    SDL_PollEvent(&event);
    
    switch(event.type) {
        case SDL_QUIT:
            state.running = FALSE;
            break;

        case SDL_KEYDOWN:
            break;
        case SDL_KEYUP:
            break;
    }
}
void setup() {

}

void update() {
    
    // delta time (in seconds)
    int now = SDL_GetTicks(); 
    state.time.delta = (now - state.time.last_frame) / 1000.0f;
    state.time.last_frame = now;
    
    // calculates fps
    state.time.frames += 1;
    if(now - state.time.last_second > MS_PER_SEC) {
        state.time.last_second = now;
        printf("FPS: %d\n", state.time.frames);
        state.time.frames = 0;
    }
}

void render() {
    SDL_SetRenderDrawColor(state.renderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderClear(state.renderer);
    
    SDL_RenderPresent(state.renderer);
}

void destroy_window() {
    SDL_DestroyRenderer(state.renderer);
    SDL_DestroyWindow(state.window);

    SDL_Quit();
}

int main(int argc, char *argv[]) {
    // initializing sdl
    state.running = initialize_window();

    // setup envrioment, initialaze game
    setup();

    state.time.last_second = SDL_GetTicks();
    while(state.running) {
        process_input();
        update();
        render();
    }   

    // clean stuff
    destroy_window();

    return 0;
}       