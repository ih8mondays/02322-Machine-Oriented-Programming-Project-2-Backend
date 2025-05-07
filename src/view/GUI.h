#ifndef YUKONBACKEND_GUI_H
#define YUKONBACKEND_GUI_H

int initSDL();
SDL_Texture* loadTexture(char path[]);
void closeSDL();
void render(float x, float y);
int createGUI();
int testGUI();
int drawBaseBoard();

#endif //YUKONBACKEND_GUI_H
