#include "includes.hpp"

//#include <SDL2/SDL_ttf.h>

using namespace std;


int main(int argc, char** argv) {
	SDL& sdl = SDL::init();
	sdl.setFPS(60);

	sdl.addObject(new Button("images/minus.png", "images/minus.png", sdl.renderer));
	((Button*)sdl.getLastObject())->setPos(40, 200);
	((Button*)sdl.getLastObject())->bindFunction([&]() {
		SDL_Delay(160);
		sdl.setCurrentScene(1);
	});
	sdl.newScene()->addObject(sdl.getLastObject());

	sdl.addObject(new Button("images/loupe.png", "images/loupe.png", sdl.renderer));
	((Button*)sdl.getLastObject())->setPos(360, 200);
	((Button*)sdl.getLastObject())->bindFunction([&]() {
		SDL_Delay(160);
		sdl.setCurrentScene(1);
	});
	sdl.getSceneById(0)->addObject(sdl.getLastObject());

	sdl.addObject(new Button("images/plus.png", "images/plus.png", sdl.renderer));
	((Button*)sdl.getLastObject())->setPos(680, 200);
	((Button*)sdl.getLastObject())->bindFunction([&]() {
		SDL_Delay(160);
		sdl.setCurrentScene(1);
	});
	sdl.getSceneById(0)->addObject(sdl.getLastObject());

	sdl.addObject(new Button("images/noBarcode.png", "images/noBarcode.png", sdl.renderer));
	((Button*)sdl.getLastObject())->setPos(200, 200);
	((Button*)sdl.getLastObject())->bindFunction([&]() {
		SDL_Delay(160);
		sdl.setCurrentScene(0);
	});
	sdl.newScene()->addObject(sdl.getLastObject());

	sdl.addObject(new Button("images/typeBarcode.png", "images/typeBarcode.png", sdl.renderer));
	((Button*)sdl.getLastObject())->setPos(520, 200);
	((Button*)sdl.getLastObject())->bindFunction([&]() {
		SDL_Delay(160);
		sdl.setCurrentScene(0);
	});
	sdl.getSceneById(1)->addObject(sdl.getLastObject());

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
