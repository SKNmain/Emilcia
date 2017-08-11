#include "includes.hpp"

//#include <SDL2/SDL_image.h>
//#include <SDL2/SDL_ttf.h>

using namespace std;


int main(int argc, char** argv) {
	int margin = 16;
	SDL& sdl = SDL::init();
	sdl.setFPS(60);
	if (!sdl.loadBMP("minus.bmp")) {
		sdl.showError();
	} else {
		sdl.accesImage("minus.bmp")->setPos(margin, 224);
		sdl.makeNewButton("minus", "minus.bmp");
		sdl.accesButton("minus")->setPosLikeImage();
		sdl.accesButton("minus")->fitSizeToImage();
	}

	if (!sdl.loadBMP("lupa.bmp")) {
		sdl.showError();
	} else {
		sdl.accesImage("lupa.bmp")->setPos(margin + 320 + margin, 224);
		sdl.makeNewButton("lupa", "lupa.bmp");
		sdl.accesButton("lupa")->setPosLikeImage();
		sdl.accesButton("lupa")->fitSizeToImage();
	}

	if (!sdl.loadBMP("plus.bmp")) {
		sdl.showError();
	} else {
		sdl.accesImage("plus.bmp")->setPos(margin + 320 + margin + 320 + margin, 224);
		sdl.makeNewButton("plus", "plus.bmp");
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
