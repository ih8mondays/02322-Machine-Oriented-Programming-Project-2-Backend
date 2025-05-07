#include <stdio.h>
#include <stdbool.h>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "GUI.h"

//The window we'll be rendering to
SDL_Window* window = NULL;

//The renderer itself, draws textures onto window
SDL_Renderer *renderer = NULL;

//Texture storage in VRAM until rendered
SDL_Texture* texture = NULL;

//Screen dimension constants
const int SCALE = 2;
const int SCREEN_WIDTH = 800 * SCALE;
const int SCREEN_HEIGHT = 600 * SCALE;
const int CARD_WIDTH = 64 * SCALE;
const int CARD_HEIGHT = 64 * SCALE;
const float COL_OFFSET = 96 * (float) SCALE;
const float STACK_OFFSET =  24 * (float) SCALE;
const float FOUND_OFFSET = 128 * (float) SCALE;
const float X_RESET = 32 * (float) SCALE;
const float Y_RESET = 32 * (float) SCALE;
const float X_FOUND = (float) SCREEN_WIDTH-96 * (float) SCALE;
const float Y_FOUND = 128 * (float) SCALE;

const char* assetHidden = "assets/card_back.png";
const char* assetEmpty = "assets/card_empty.png";
const char* assetSuit[] = {"assets/card_clubs_","assets/card_diamonds_","assets/card_hearts_","assets/card_spades_"};
const char* assetRank[] = {"A.png","02.png","03.png","04.png","05.png","06.png","07.png","08.png","09.png","10.png","J.png","Q.png","K.png"};

//Rendering target pixels
float xPos = (float) X_RESET;
float yPos = Y_RESET;




/** Initiates the core SDL features
 * @note must be accompanied by closeSDL() before program shutdown
 * @return -1 if failure, 1 if successful
 */
int initSDL() {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return -1;
    } else {
        return 1;
    }
}


/** Loads texture file from specified path (in the build folder) onto RAM, then transfers it to VRAM.
 *
 */
SDL_Texture* loadTexture( char path[] )
{
    //The final texture
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( path );
    if( loadedSurface == NULL )
    {
        SDL_Log( "Unable to load image %s! SDL_image Error: %s\n", path, SDL_GetError() );
    }
    else
    {
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
        if( newTexture == NULL )
        {
            SDL_Log( "Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError() );
        }

        //Get rid of old loaded surface
        SDL_DestroySurface( loadedSurface );
    }
    return newTexture;
}


/**Renders the currently loaded card texture on specified location, then clears texture off of VRAM.
 *
 * @param x leftmost pixel to render from
 * @param y topmost pixel to render from (downwards)
 */
void render(float x,float y) {
    SDL_FRect renderSpace = { x, y, (float) CARD_WIDTH, (float) CARD_HEIGHT};
    SDL_RenderTexture(renderer, texture, NULL, &renderSpace);
    SDL_DestroyTexture(texture);
}


/**Cleans up the remaining tools before closing SDL.
 *
 */
void closeSDL() {

    if (texture != NULL)
    {
        SDL_DestroyTexture(texture);
        texture = NULL;
    }

    if (renderer != NULL)
    {
        SDL_DestroyRenderer(renderer);
        renderer = NULL;
    }

    if (window != NULL)
    {
        SDL_DestroyWindow(window);
        window = NULL;
    }

    SDL_Quit();
}


int createGUI() {
    if (initSDL() == 1) {
        //Create window
        if (!SDL_CreateWindowAndRenderer("Yukon Solitaire", SCREEN_WIDTH, SCREEN_HEIGHT, 0, &window, &renderer)) {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            closeSDL();
            return -1;
        } else {
            return 1;
        }
    } else {
        printf("SDL not initiated!");
        return -1;
    }
}

int testGUI() {
    //Allocates string for card file loading
    char cardPath[50];

    //sets default/background color
    SDL_SetRenderDrawColor(renderer, 0x2F, 0xBF, 0x32, 0xFF);
    SDL_RenderClear(renderer);

    for (int i = 0; i < 7; ++i) {
        texture = loadTexture("assets/card_empty.png");
        if (texture == NULL) {
            printf("Failed to load texture!\n");
            closeSDL();
            return -1;
        }
        render(xPos, yPos);
        xPos += COL_OFFSET;
    }

    xPos = X_RESET;
    //Example loop, draws each suit in their own column.
    for (int j = 0; j < 4; ++j) {
        for (int i = 0; i < 13; ++i) {
            strcpy(cardPath, assetSuit[j]);
            strcat(cardPath, assetRank[i]);
            texture = loadTexture(cardPath);
            if (texture == NULL) {
                printf("Failed to load texture!\n");
                closeSDL();
                return -1;
            }
            render(xPos, yPos);
            yPos += STACK_OFFSET;
        }
        xPos += COL_OFFSET;
        yPos = Y_RESET;
    }

    //Draws foundation piles
    xPos = X_FOUND;
    yPos = Y_FOUND;
    strcpy(cardPath, assetEmpty);
    for (int j = 0; j < 4; ++j) {
        texture = loadTexture(cardPath);
        if (texture == NULL) {
            printf("Failed to load texture!\n");
            closeSDL();
            return -1;
        }
        render(xPos, yPos);
        yPos += FOUND_OFFSET;
    }

    SDL_RenderPresent(renderer);
    SDL_RenderClear(renderer);


    //Keeps the window up until the user presses close on it
    SDL_Event e;
    bool quit = false;
    while (quit == false) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) quit = true;
        }
    }
    closeSDL();
    return 0;
}

int drawBaseBoard() {
    if (window != NULL && renderer != NULL) {
        //Allocates string for card file loading
        char cardPath[50];

        //sets default/background color
        SDL_SetRenderDrawColor(renderer, 0x2F, 0xBF, 0x32, 0xFF);
        SDL_RenderClear(renderer);

        for (int i = 0; i < 7; ++i) {
            texture = loadTexture("assets/card_empty.png");
            if (texture == NULL) {
                printf("Failed to load texture!\n");
                closeSDL();
                return -1;
            }
            render(xPos, yPos);
            xPos += COL_OFFSET;
        }

        //Draws foundation piles
        xPos = X_FOUND;
        yPos = Y_FOUND;
        strcpy(cardPath, assetEmpty);
        for (int j = 0; j < 4; ++j) {
            texture = loadTexture(cardPath);
            if (texture == NULL) {
                printf("Failed to load texture!\n");
                closeSDL();
                return -1;
            }
            render(xPos, yPos);
            yPos += FOUND_OFFSET;
        }


        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);


        //Keeps the window up until the user presses close on it
        SDL_Event e;
        bool quit = false;
        while (quit == false) {
            while (SDL_PollEvent(&e)) {
                if (e.type == SDL_EVENT_QUIT) quit = true;
            }
        }
    }
    closeSDL();
    return 0;
}

