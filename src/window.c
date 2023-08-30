#include <stdio.h>
#include <SDL2/SDL.h>


#define FALSE 0
#define TRUE 1

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600


int window_is_running = FALSE;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;



int initialize_window(void){
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		fprintf(stderr, "Error initializing SDL.\n");
		return FALSE;
	}
	window = SDL_CreateWindow(
		NULL,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		WINDOW_WIDTH,
		WINDOW_HEIGHT,
		SDL_WINDOW_BORDERLESS
	);
	if(!window){
		fprintf(stderr, "Error creating SDL Window.\n");
		return FALSE;
	}
	renderer = SDL_CreateRenderer(window, -1, 0);
	if(!renderer){
		fprintf(stderr, "Error creating SDL Renderer.\n");
		return FALSE;
	}

	return TRUE;
}

void render(void) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); 
	SDL_RenderPresent(renderer);
}
void process_input(void){
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type){
		case SDL_QUIT: 
			window_is_running = FALSE;
			break;

		case SDL_KEYDOWN:
			if(event.key.keysym.sym == SDLK_ESCAPE)
				window_is_running = FALSE;
	}
}

void destroy_window(void){
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

int main(){
	window_is_running = initialize_window();

    render();

    while (window_is_running) {
        process_input();
    }

	return 0;
}
