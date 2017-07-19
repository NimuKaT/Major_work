
#include "../Header/Main.h"



//Initialises SDL and its subsystems
bool init(SDL_Window* &window_ptr_ref, SDL_Renderer* &renderer_ptr_ref){
	bool init_flag = false;

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0){

	}
	else{
		window_ptr_ref = SDL_CreateWindow("A game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

		if (window_ptr_ref == NULL){
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		}
		else{
			renderer_ptr_ref = SDL_CreateRenderer(window_ptr_ref, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_TEXTUREACCESS_TARGET);

			if (renderer_ptr_ref == NULL){
				printf("Renderer could not be created. SDL Error: %s\n", SDL_GetError());
			}
			else{
				SDL_RenderSetLogicalSize(renderer_ptr_ref, 3840, 2160);
				SDL_SetRenderDrawColor( renderer_ptr_ref, 0xFF, 0xFF, 0xFF, 0xFF);
				int imgFlags = IMG_INIT_PNG;

				if (!(IMG_Init(imgFlags) & imgFlags)){
					printf( "SDL_image could not initialise. SDL_image Error: %s\n", IMG_GetError() );
				}
				else{
					if (TTF_Init() == -1){
						printf( "SDL_ttf could not initialise. Error: %s\n", TTF_GetError() );
					}
					else{
						init_flag = true;
					}
				}
			}
		}
	}
	return init_flag;
}

//Closes SDL and frees memory
void close(SDL_Window* window_ptr, SDL_Renderer* renderer_ptr){
//TODO add function to free all textures
	SDL_DestroyRenderer(renderer_ptr);
	SDL_DestroyWindow(window_ptr);
	renderer_ptr = NULL;
	window_ptr = NULL;

	IMG_Quit();
	SDL_Quit();
}

//Logs users inputs
void get_input(SDL_Event& event, std::shared_ptr<Input_event> &input_data, bool &quit){
	while (SDL_PollEvent(&event) != 0){
		switch (event.type){
			case SDL_QUIT:{
				quit = true;
				break;
			}
			case SDL_KEYDOWN:
			case SDL_KEYUP:{
				switch(event.key.keysym.sym){
					case SDLK_w:{
						input_data->key_pressed[KEY_PRESS_W] = event.key.state;
						break;
					}
					case SDLK_a:{
						input_data->key_pressed[KEY_PRESS_A] = event.key.state;
						break;
					}
					case SDLK_s:{
						input_data->key_pressed[KEY_PRESS_S] = event.key.state;
						break;
					}
					case SDLK_d:{
						input_data->key_pressed[KEY_PRESS_D] = event.key.state;
						break;
					}
					case SDLK_r:{
						input_data->key_pressed[KEY_PRESS_R] = event.key.state;
						break;
										}
					case SDLK_UP:{
						input_data->key_pressed[KEY_PRESS_UP] = event.key.state;
						break;
					}
					case SDLK_LEFT:{
						input_data->key_pressed[KEY_PRESS_LEFT] = event.key.state;
						break;
					}
					case SDLK_DOWN:{
						input_data->key_pressed[KEY_PRESS_DOWN] = event.key.state;
						break;
					}
					case SDLK_RIGHT:{
						input_data->key_pressed[KEY_PRESS_RIGHT] = event.key.state;
						break;
					}
				}
				break;
			}
			case SDL_MOUSEBUTTONUP:
			case SDL_MOUSEBUTTONDOWN:{
				switch (event.button.button){
					case SDL_BUTTON_LEFT:{
						input_data->key_pressed[KEY_PRESS_MB_1] = event.button.state;
					}
				}
				input_data->mouse_x = event.button.x;
				input_data->mouse_y = event.button.y;
				break;
			}
			case SDL_MOUSEMOTION:{
				input_data->mouse_x = event.button.x;
				input_data->mouse_y = event.button.y;
				break;
			}
		}
	}
}

//Main Loop
int main(int argc, char* args[]){

//TODO add vector for textures
	get_options();
	//The window that will be rendered to
	SDL_Window* window_ptr = NULL;
	//The window renderer
	SDL_Renderer* renderer_ptr = NULL;

	//Runs the main loop if the initilisation of the window and renderer succeeds
	if (init(window_ptr, renderer_ptr)){
//		Input event struct initialiser
		std::shared_ptr<Input_event> input_data = std::make_shared<Input_event>();
		input_data->key_pressed.fill(false);
		input_data->mouse_x = 0;
		input_data->mouse_y = 0;
//		Initialiser for the debug menu
		Debugger console;
		console.init(renderer_ptr, input_data);
		console.change_option("frame_rate", true);
		console.change_option("mouse_location", true);

//		pointer to int for current menu
		std::unique_ptr<int> menu_ptr(new int(INIT_MENU));

//		Vector of Menu objects
		std::vector<std::unique_ptr<MenuManager>> menus(DEFAULT_MENU);
		menus[MAIN_MENU] = std::unique_ptr<MenuManager>(new MainMenu(renderer_ptr, input_data));
		menus[TEST_MENU] = std::unique_ptr<MenuManager>(new Test_Menu(renderer_ptr, input_data));
		menus[GAME_MENU] = std::unique_ptr<MenuManager>(new GameMenu(renderer_ptr, input_data));

//		Frame capping (not working)
		Timer frame_rate_cap;
		frame_rate_cap.start();

//		Core variables for the main loop
		bool quit = false;
		SDL_Event event;

		while(!quit){
			/*if( TEMP_FRAME_RATE_CAP <= frame_rate_cap.get_time_elapsed()){
				SDL_Delay(TEMP_FRAME_RATE_CAP - frame_rate_cap.get_time_elapsed());
			}
			frame_rate_cap.reset();*/

			//Clear screen
			SDL_RenderClear(renderer_ptr);

			get_input(event, input_data, quit);

//			Logs user input
			menus[*menu_ptr]->update_logic();

//			Renders graphics according to logic
			menus[*menu_ptr]->render_texture();

			console.render();

			//Push to screen
			SDL_RenderPresent(renderer_ptr);


		}
	}

	close(window_ptr, renderer_ptr);

	return 0;
}
