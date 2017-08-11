#include "includes.hpp"

//#include <SDL2/SDL_image.h>
//#include <SDL2/SDL_ttf.h>

using namespace std;


int main(int argc, char** argv) {
	int margin = 16;
	SDL& sdl = SDL::init();
	sdl.setFPS(60);
	if (!sdl.loadBMP("images\\minus.bmp")) {
		sdl.showError();
	} else {
		sdl.accesImage("images\\minus.bmp")->setPos(margin, 224);
		sdl.makeNewButton("minus", "images\\minus.bmp");
		sdl.accesButton("minus")->setPosLikeImage();
		sdl.accesButton("minus")->fitSizeToImage();
	}

	if (!sdl.loadBMP("images\\lupa.bmp")) {
		sdl.showError();
	} else {
		sdl.accesImage("images\\lupa.bmp")->setPos(margin + 320 + margin, 224);
		sdl.makeNewButton("lupa", "images\\lupa.bmp");
		sdl.accesButton("lupa")->setPosLikeImage();
		sdl.accesButton("lupa")->fitSizeToImage();
	}

	if (!sdl.loadBMP("images\\plus.bmp")) {
		sdl.showError();
	} else {
		sdl.accesImage("images\\plus.bmp")->setPos(margin + 320 + margin + 320 + margin, 224);
		sdl.makeNewButton("plus", "images\\plus.bmp");
		sdl.accesButton("plus")->setPosLikeImage();
		sdl.accesButton("plus")->fitSizeToImage();
	}
	for(SDL_Event* event = sdl.eventUpdate(); event->type != SDL_QUIT; sdl.eventUpdate()) {
		sdl.screenUpdate();
		//Event handling
		switch(event->type) {
			case(SDL_MOUSEMOTION): {

				break;
			}
			case(SDL_KEYDOWN): {

				break;
			}
			case(SDL_MOUSEBUTTONDOWN): {

				break;
			}
			default: {

				break;
			}
			
		}
	}
	return 0;
}
