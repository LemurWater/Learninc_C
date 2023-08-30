#include <stdio.h>
#include <SDL2/SDL.h>


#define FALSE 0
#define TRUE 1

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#define FPS 60
#define FRAME_TARGET_TIME (1000 / FPS)

#define BALL_SPEED 5.5f


int game_is_running = FALSE;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

int last_frame_time = 0;

struct ball {
	float x;
	float y;
	float width;
	float height; 
} ball;


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

void process_input(void){
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type){
		case SDL_QUIT: 
			game_is_running = FALSE;
			break;

		case SDL_KEYDOWN:
			if(event.key.keysym.sym == SDLK_ESCAPE)
				game_is_running = FALSE;
			break;
	}
}

void setup(void) {
	ball.x = 20;
	ball.y = 20;
	ball.width = 15;
	ball.height = 15;
}

void update(void) {
	//Logic to keep a fixed timestep
	int time_to_wait = FRAME_TARGET_TIME - (SDL_GetTicks() - last_frame_time);

	if (time_to_wait > 0 && time_to_wait <= FRAME_TARGET_TIME) {
		SDL_Delay(time_to_wait);
	}


	//Get a delta time factor converted to sesconds to be used to update my objects
	float delta_time = (SDL_GetTicks() - last_frame_time) / 1000.0f;
	
	last_frame_time = SDL_GetTicks();


	
    int direction_x = 1;
    int direction_y = 1;
    if (ball.x >= WINDOW_WIDTH - ball.width) 
        ball.x += 80 * BALL_SPEED * delta_time * -1;//direction_x = -1;
    else
        ball.x += 80 * BALL_SPEED * delta_time * direction_x;//direction_x = 1;

    if (ball.y >= WINDOW_HEIGHT - ball.height - 1) 
        direction_y = -1;
    else direction_y = 1;


    ball.y += 40 * BALL_SPEED * delta_time * direction_y;
}

void render(void){
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); 
	SDL_RenderClear(renderer);

	SDL_Rect ball_rect = {
		(int)ball.x,
		(int)ball.y,
		(int)ball.width,
		(int)ball.height
	};

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(renderer, &ball_rect);

	SDL_RenderPresent(renderer);
}

void destroy_window(void){
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

int main(){
	game_is_running = initialize_window();

	setup();

	while (game_is_running){
		process_input();
		update();
		render();
	}

	destroy_window();

	return 0;
}
