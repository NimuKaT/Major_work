
#include "Main.h"

//Screen dimension constants
const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;

//Initialises SDL and its subsystems
bool init( SDL_Window* &targetWindow, SDL_Renderer* &targetRenderer ){
	bool initFlag = false;

	if ( SDL_Init( SDL_INIT_VIDEO|SDL_INIT_AUDIO ) < 0){

	}
	else{

		targetWindow = SDL_CreateWindow( "A game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );

		if( &targetWindow == NULL ){

			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );

		}
		else{

			targetRenderer = SDL_CreateRenderer( targetWindow, -1, SDL_RENDERER_ACCELERATED );

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

					initFlag = true;

				}
			}
		}
	}

	return initFlag;
}

SDL_Texture* loadTexture(SDL_Renderer* &targetRenderer, std::string path ){

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
void close(SDL_Window* &targetWindow, SDL_Renderer* &targetRenderer){

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

	//The window that will be rendered to
	SDL_Window* window = NULL;

	//The window renderer
	SDL_Renderer* mainRenderer = NULL;

	//The texture currently displayed
	SDL_Texture* mainTexture = NULL;


	if (init(window, mainRenderer) ){

		bool quit = false;
		SDL_Event event;

		while( !quit ){

			while( SDL_PollEvent( &event ) != 0 ){
				switch( event.type ){

					case SDL_QUIT:{
						quit = true;
						break;
					}

					default:{
						break;
					}
				}

			//Clear screen
			SDL_RenderClear(mainRenderer);

			//Render texture to screen
			SDL_RenderCopy( mainRenderer, mainTexture, NULL, NULL );

			//Push to screen
			SDL_RenderPresent( mainRenderer );

			}
		}
	}

	close( window, mainRenderer );

	return 0;
}
