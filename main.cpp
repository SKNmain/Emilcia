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
	private:
		Image() {}
	public:
		SDL_Texture*	tex = nullptr;
		SDL_Rect		src;
		SDL_Rect		dst;

		Image(int width, int height) {
			src.x = 0; src.y = 0; src.w = width; src.h = height;
			dst.x = 0; dst.y = 0; dst.w = width; dst.h = height;
		};

		void setClip(SDL_Point clipPos, SDL_Point clipSize) {
			src.x = clipPos.x;
			src.y = clipPos.y;
			dst.w = src.w = clipSize.x;
			dst.h = src.h = clipSize.y;
		}

		void setPos(int x, int y) {
			dst.x = x;
			dst.y = y;
		}

		~Image() {
			if (tex != nullptr) {
				SDL_DestroyTexture(tex);
			}
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

			//pobranie tickow
			fpsTimer = SDL_GetTicks();

		}

		~SDL() {
			for (auto it = gfx.begin(); it != gfx.end(); ++it) {
				delete it->second;
			}
			gfx.clear();
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

		void screenUpdate() {
			SDL_SetRenderDrawColor(render, 255, 0, 0, 255);

			if (SDL_GetTicks() - fpsTimer > fps) {
				SDL_RenderClear(render);

				for (auto it = gfx.begin(); it != gfx.end(); ++it) {
					SDL_RenderCopy(render, it->second->tex, (const SDL_Rect*)&it->second->src, (const SDL_Rect*)&it->second->dst);
				}	

				SDL_RenderPresent(render);
				fpsTimer = SDL_GetTicks();
			}
		}

		void setFPS(unsigned int newFPS) {
			fps =  1.0 / newFPS;
		}

		bool loadBMP(string fileName) {
			if (gfx.find(fileName) != gfx.end()) {
				return true;
			}
			SDL_Surface* newSurface = SDL_LoadBMP(fileName.c_str());
			if (newSurface == nullptr) {
				return false;
			}
			Image* newImage = new Image(newSurface->w, newSurface->h);
			newImage->tex = SDL_CreateTextureFromSurface(render, newSurface);
			if (newImage->tex == nullptr) {
				delete newImage;
				return false;
			}
			gfx[fileName] = newImage;
			SDL_FreeSurface(newSurface);
			return true;
		}

		Image* accesImage(string imageName) {
			if (gfx.find(imageName) == gfx.end()) {
				return nullptr;
			} else {
				return gfx[imageName];
			}
		}

};

int main(int argc, char** argv) {
	SDL& sdl = SDL::init();
	sdl.setFPS(60);
	if (!sdl.loadBMP("test.bmp")) {
		sdl.showError();
	}
	if (!sdl.loadBMP("test2.bmp")) {
		sdl.showError();
	} else {
		sdl.accesImage("test2.bmp")->setPos(sdl.accesImage("test.bmp")->src.w, sdl.accesImage("test.bmp")->src.h);
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
