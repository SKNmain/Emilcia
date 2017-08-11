#include "includes.hpp"

//#include <SDL2/SDL_image.h>
//#include <SDL2/SDL_ttf.h>

using namespace std;


int main(int argc, char** argv) {
	SDL& sdl = SDL::init();
	sdl.setFPS(60);
	if (!sdl.loadBMP("test.bmp")) {
		sdl.showError();
	} else {
		sdl.accesImage("test.bmp")->setPos(256, 256);
	}

	if (!sdl.loadBMP("test2.bmp")) {
		sdl.showError();
	} else {
		sdl.accesImage("test2.bmp")->setClip(0, 0, 256, 256);
		sdl.accesImage("test2.bmp")->setPos(256 + 512, 256);
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
			default: {

				break;
			}
			
		}
	}
	return 0;
}
