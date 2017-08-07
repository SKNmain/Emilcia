#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <map>
#include <string>
#include <SDL2/SDL.h>

//#include <SDL2/SDL_image.h>
//#include <SDL2/SDL_ttf.h>

using namespace std;

class Image {
    public:
        SDL_Texture*	tex = nullptr;
        SDL_Rect		src;
        SDL_Rect		dst;

        Image() {
            src.x = 0; src.y = 0; src.w = 0; src.h = 0;
            dst.x = 0; dst.y = 0; dst.w = 0; dst.h = 0;
        };
        
        ~Image() {
            SDL_DestroyTexture(tex);
        };
};

class SDL {

	private:
		SDL_Event					event;
		map<string, Image*>			gfx;
		unsigned short				fps;
		unsigned int				fpsTimer;

		SDL() {
			//Inicjalizacja SDL'a
			if (SDL_Init(SDL_INIT_EVERYTHING)) {
				isError = true;
				return;
			}

			//inicjalizacja okna
			window = SDL_CreateWindow(
				"Emilcia",
				SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
				1024, 768,
				SDL_WINDOW_SHOWN | SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_MOUSE_FOCUS
			);
			if (window == nullptr) {
				isError = true;
				return;
			}

			//inicjalizacja renderera
			render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			if (render == nullptr) {
				isError = true;
				return;
			}
		}

		~SDL() {
			SDL_DestroyRenderer(render);
			SDL_DestroyWindow(window);
			SDL_Quit();
		}

		



	public:
		static SDL& init() {
			static SDL sdl;
			return sdl;
		}

		bool			isError = false;
		SDL_Window*		window	= nullptr;
		SDL_Renderer*	render	= nullptr;

		void showError() {
			cout << "Error: " << SDL_GetError() << endl;
		}

		SDL_Event* eventUpdate() {
			SDL_PollEvent(&event);
			return &event;
		}

		void ScreenUpdate() {
			SDL_SetRenderDrawColor(render, 255, 0, 0, 255);

			fpsTimer = SDL_GetTicks();

			if (SDL_GetTicks() - fpsTimer > fps) {
				SDL_RenderClear(render);



				SDL_RenderPresent(render);
				fpsTimer = SDL_GetTicks();
			}
		}

		void setFPS(unsigned int newFPS) {
			fps =  1 / newFPS;
		}

};

int main(int argc, char** argv) {
	SDL& sdl = SDL::init();


	const Uint8* state;
	SDL_Rect srcrect;
	srcrect.x = 0;
	srcrect.y = 0;
	srcrect.w = 5;
	srcrect.h = 5;
	SDL_Rect dstrects[5];
	SDL_Rect srcrects[5];
	int i = 0;
	int j = 0;
	for(i = 0; i < 5; ++i) {
		dstrects[i].x = i * 100;
		dstrects[i].y = 0;
		dstrects[i].w = 100;
		dstrects[i].h = 100;
		srcrects[i].x = 0;
		srcrects[i].y = 0;
		srcrects[i].w = 5;
		srcrects[i].h = 5;
	}
	SDL_Rect dstrect;
	dstrect.x = 0;
	dstrect.y = 0;
	dstrect.w = 100;
	dstrect.h = 100;

	
	SDL_SetRenderDrawColor(sdl.render, 255, 0, 0, 255);

	SDL_Surface* surface = SDL_LoadBMP("test.bmp");
	if(surface == NULL) {
		printf("%s\n", SDL_GetError());
		return 1;
	}
	SDL_Texture* texture = SDL_CreateTextureFromSurface(sdl.render, surface);
	SDL_FreeSurface(surface);

	int	timer = SDL_GetTicks();
	
	for(SDL_Event* event = sdl.eventUpdate(); event->type != SDL_QUIT; sdl.eventUpdate()) {
		//Wyswietlanie ekranu w ~60fps
		if (SDL_GetTicks() - timer > 17) {
			SDL_RenderClear(sdl.render);
			for(i = 0; i < 5; ++i) {
				SDL_RenderCopy(sdl.render, texture, &srcrects[i], &dstrects[i]);
			}
			SDL_RenderPresent(sdl.render);
			timer = SDL_GetTicks();
			i = 0;
		}
		//Event handling
		switch(event->type) {
			case(SDL_MOUSEMOTION): {
				//event.motion.x
				//event.motion.y
				//SDL_SetRenderDrawColor(render,
				//	int((float(event.motion.x) / 640) * 255),
				//	int((float(event.motion.y) / 480) * 255),
				//	0,
				//	255
				//);
				break;
			}
			case(SDL_KEYDOWN): {
				if(event->key.keysym.scancode >= 4 && event->key.keysym.scancode <= 29) {
					if(event->key.keysym.scancode <= 18) {
						srcrects[j].x = ((event->key.keysym.scancode - 4) * 5) + 5;
						srcrects[j].y = 20;
					}
					if(event->key.keysym.scancode > 18) {
						srcrects[j].x = ((event->key.keysym.scancode - 4 - 18) * 5) + 15;
						srcrects[j].y = 25;
					}
					j++;
				}
				if(j >= 5) {
					j = 0;
				}
				break;
			}
			default: {

				break;
			}
			
		}
	}
	return 0;
}
