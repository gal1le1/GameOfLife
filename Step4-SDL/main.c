#include "logic.h"


int main(int argc, char const *argv[]){
    
    // Initialise SDL
    SDL_Init(SDL_INIT_VIDEO);

    // Create window and renderer
    SDL_Window *window = createWindow("Game of Life");
    SDL_Renderer *renderer = createRenderer(window);

    // Setup event handling
    SDL_Event event;
    int mouseX, mouseY;
    bool mouse_left_down = false;
    bool mouse_right_down = false;
    int counter = 1;

    
    int cells[AREA_HEIGHT][AREA_WIDTH];

    // Set all cells to initial state of dead
    for(int i = 0; i < AREA_HEIGHT; i++){
        for(int j = 0; j < AREA_WIDTH; j++){
            cells[i][j] = DEAD;
        }
    }

    // game
    while(1){
      while(SDL_PollEvent(&event) != 0){
            switch(event.type){
                case SDL_QUIT:
                    return 1;
                case SDL_MOUSEBUTTONDOWN: case SDL_MOUSEBUTTONUP:
                    switch(event.button.button){
                        case SDL_BUTTON_LEFT: mouse_left_down = !mouse_left_down; break;
                        case SDL_BUTTON_RIGHT: mouse_right_down = !mouse_right_down; break;
                    }
                case SDL_KEYDOWN:
                    if(event.key.keysym.sym == SDLK_SPACE){ // when space is pressed
                        while(1){
                            circular_game_rule(cells);
                            sleep(1);

                            SDL_SetRenderDrawColor(renderer, 24, 147, 163, 0);
                            SDL_RenderClear(renderer);

                            drawGrid(renderer);
                            drawCells(renderer, cells);

                            SDL_RenderPresent(renderer);
                            if(counter == 100){ // stops when cells are updated 100 times
                                SDL_RenderClear(renderer);

                                drawGrid(renderer);
                                drawCells(renderer, cells);

                                SDL_RenderPresent(renderer);
                                break;
                            }
                            counter += 1;
                        }
                    }
                    counter = 1;
            }
        }

        SDL_GetMouseState(&mouseX, &mouseY);
	
	// cell becomes alive if left button of mouse clicked
        if(mouse_left_down == true){
            cells[mouseY/CELL_SIZE][mouseX/CELL_SIZE] = ALIVE;
        }else if(mouse_right_down == true){ // cell becomes dead if right button of mouse clicked
            cells[mouseY/CELL_SIZE][mouseX/CELL_SIZE] = DEAD;
        }
        
        // screen colour to blue
        SDL_SetRenderDrawColor(renderer, 24, 147, 163, 0);

        // Clear screen
        SDL_RenderClear(renderer);
	
        drawGrid(renderer);

        drawCells(renderer, cells);

        SDL_RenderPresent(renderer);
    }
    
    SDL_Quit();


    return 0;
}

