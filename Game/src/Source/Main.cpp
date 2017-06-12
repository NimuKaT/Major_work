
#include "../Header/Main.h"



//Initialises SDL and its subsystems
bool init( SDL_Window* &targetWindow, SDL_Renderer* &targetRenderer ){
	bool initFlag = false;

	if ( SDL_Init( SDL_INIT_EVERYTHING ) < 0){

	}
	else{

		targetWindow = SDL_CreateWindow( "A game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );

		if( targetWindow == NULL ){

			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );

		}
		else{

			targetRenderer = SDL_CreateRenderer( targetWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_TEXTUREACCESS_TARGET);

			if ( targetRenderer == NULL ){

				printf( "Renderer could not be created. SDL Error: %s\n", SDL_GetError() );
			}
			else{

				SDL_SetRenderDrawColor( targetRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				int imgFlags = IMG_INIT_PNG;

				if( !( IMG_Init( imgFlags) & imgFlags ) ){

					printf( "SDL_image could not initialise. SDL_image Error: %s\n", IMG_GetError() );

				}
				else{

					if( TTF_Init() == -1){
						printf( "SDL_ttf could not initialise. Error: %s\n", TTF_GetError() );
					}
					else{
						initFlag = true;
					}
				}
			}
		}
	}

	return initFlag;
}

SDL_Texture* loadTexture(SDL_Renderer* targetRenderer, std::string path ){

	//Output as final texture
	SDL_Texture* ouputTexture = NULL;

	//Load image from specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );

	if( loadedSurface == NULL ){
		printf( "Unable to load image. SDL_image Error: %s\n", IMG_GetError() );
	}
	else{
		ouputTexture = SDL_CreateTextureFromSurface( targetRenderer, loadedSurface );

		if( loadedSurface == NULL ){
			printf( "Unable to create texture from surface. SDL Error: %s\n", SDL_GetError() );
		}

		SDL_FreeSurface(loadedSurface);

	}

	return ouputTexture;

}

//Closes SDL and frees memory
void close(SDL_Window* targetWindow, SDL_Renderer* targetRenderer){

//TODO add function to free all textures

	SDL_DestroyRenderer(targetRenderer);
	SDL_DestroyWindow( targetWindow) ;
	targetRenderer = NULL;
	targetWindow = NULL;

	IMG_Quit();
	SDL_Quit();
}

//Main Loop
int main( int argc, char* args[] ){

//TODO add vector for textures

//	Asset_path_loader image;


	//The window that will be rendered to
	SDL_Window* window = NULL;

	//The window renderer
	SDL_Renderer* mainRenderer = NULL;

	//The texture currently displayed
//	SDL_Texture* mainTexture = NULL;



	//Runs the main loop if the initilisation of the window and renderer succeeds
	if (init(window, mainRenderer) ){

		std::unique_ptr< int > menu_ptr( new int( TEST_MENU ) );

		std::vector< std::unique_ptr< MenuManager> > menus (DEFAULT_MENU);
		menus[MAIN_MENU] = std::unique_ptr< MenuManager >( new MainMenu( mainRenderer ) );
		menus[TEST_MENU] = std::unique_ptr< MenuManager >( new Test_Menu( mainRenderer ) );

		Timer frame_rate_cap;
		frame_rate_cap.start();

		bool quit = false;
		SDL_Event event;

		while( !quit ){

			menus[*menu_ptr.get()]->event_Handler(event, quit);

			/*if( TEMP_FRAME_RATE_CAP <= frame_rate_cap.get_time_elapsed()){
				SDL_Delay(TEMP_FRAME_RATE_CAP - frame_rate_cap.get_time_elapsed());
			}
			frame_rate_cap.reset();*/

			//Clear screen
			SDL_RenderClear( mainRenderer );


//			std::cout << loadTexture(mainRenderer, "Assets//Images//player.png") << std::endl;

//			SDL_RenderCopy( mainRenderer, mainTexture, NULL, NULL );

			//SDL_RenderCopy(mainRenderer, loadTexture(mainRenderer, "Assets//Images//player.png"), NULL, &a);

//			test_balls.render(2);

			menus[*menu_ptr.get()]->render_Texture();

			//Push to screen
			SDL_RenderPresent( mainRenderer );


		}
	}

	close( window, mainRenderer );

	return 0;
}
