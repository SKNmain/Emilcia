#include "includes.hpp"

//#include <SDL2/SDL_image.h>
//#include <SDL2/SDL_ttf.h>

using namespace std;


int main(int argc, char** argv) {
	SDL& sdl = SDL::init();
	sdl.setFPS(60);

	sdl.addObject(new Button("images/minus.bmp", "images/lupa.bmp", sdl.renderer));
	((Button*)sdl.getLastObject())->bindFunction([&]() {
			sdl.setCurrentScene(1);
	});
	sdl.newScene()->addObject(sdl.getLastObject());

	sdl.addObject(new Button("images/minus.bmp", "images/plus.bmp", sdl.renderer));
	((Button*)sdl.getLastObject())->setPos(500, 500);
	((Button*)sdl.getLastObject())->bindFunction([&]() {
			sdl.setCurrentScene(0);
	});
	sdl.newScene()->addObject(sdl.getLastObject());

	sdl.setCurrentScene(0);
	for(SDL_Event* event = sdl.eventUpdate(); event->type != SDL_QUIT; sdl.eventUpdate()) {
		sdl.inputUpdate(event);
		sdl.screenUpdate(event);
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
