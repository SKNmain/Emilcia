#pragma once

#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <map>
#include <string>
#include <SDL2/SDL.h>

using namespace std;


class Image {
	private:
		Image() {}
	public:
		SDL_Texture*	tex = nullptr;
		SDL_Rect		src;
		SDL_Rect		dst;
		bool 			visible;
		int 			id;

		Image(int width, int height, int objectCounter) {
			src.x = 0; src.y = 0; src.w = width; src.h = height;
			dst.x = 0; dst.y = 0; dst.w = width; dst.h = height;
			visible = true;
			id = objectCounter;
		};

		// ustawienie wycinka zrodlowej mapy

		void setClip(int x1, int y1, int x2, int y2) {
			src.x = x1;
			src.y = y1;
			dst.w = src.w = x2;
			dst.h = src.h = y2;
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


class Button {
	private:
		Button() {}

	public:
		int 		id;
		bool 		isPressed;
		SDL_Rect 	dst;
		string 		imageName;
		Image* 		imagePointer;


		Button(string imageNme, Image* imagePtr, int width, int height, int objectCounter) {			
			imagePointer = imagePtr;
			imageName = imageNme;
			dst.x = 0; dst.y = 0; dst.w = width; dst.h = height;
		}

		bool setImageHandler() {
			if(imagePointer == nullptr) {
				return false;
			}
			imagePointer->dst.x = dst.x;
			imagePointer->dst.y = dst.y;
			return true;
		}

		void setPos(int x, int y) {
			dst.x = x;
			dst.y = y;
		}

		~Button() {
			imagePointer = nullptr;
			imageName.clear();
		}
};

class SDL {

	private:
		SDL_Event					event;
		map<string, Image*>			gfx;
		map<string, Button*>		btn;
		unsigned short				fps;
		unsigned int				fpsTimer;
		int							objectCounter;

		SDL() {


			// wyzerowanie obiektow 

			objectCounter = 0;

			// Inicjalizacja SDL'a

			if (SDL_Init(SDL_INIT_EVERYTHING)) {
				isError = true;
				return;
			}

			// inicjalizacja okna

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

			// inicjalizacja renderera

			render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			if (render == nullptr) {
				isError = true;
				return;
			}

			// pobranie tickow

			fpsTimer = SDL_GetTicks();


		}

		~SDL() {
			for (auto it = gfx.begin(); it != gfx.end(); ++it) {
				delete it->second;
			}
			for (auto it = btn.begin(); it != btn.end(); ++it) {
				delete it->second;
			}
			gfx.clear();
			btn.clear();
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

		// odswiezanie

		void screenUpdate() {
			SDL_SetRenderDrawColor(render, 255, 0, 0, 255);

			if (SDL_GetTicks() - fpsTimer > fps) {
				SDL_RenderClear(render);

				// petla iterujaca po obrazach

				for (auto it = gfx.begin(); it != gfx.end(); ++it) {
					if (it->second->visible) {
						SDL_RenderCopy(render, it->second->tex, (const SDL_Rect*)&it->second->src, (const SDL_Rect*)&it->second->dst);
					}
					
				}	

				SDL_RenderPresent(render);
				fpsTimer = SDL_GetTicks();
			}
		}

		void setFPS(unsigned int newFPS) {
			fps =  1.0 / newFPS;
		}

		// wczytywanie map bitowych

		bool loadBMP(string fileName) {

			// sprawdzam czy juz istnieje

			if (gfx.find(fileName) != gfx.end()) {
				return true;
			}

			// zapisywanie do powierzchni

			SDL_Surface* newSurface = SDL_LoadBMP(fileName.c_str());
			if (newSurface == nullptr) {
				return false;
			}

			// zapisywanie do obiektu klasy image, do tekstury

			Image* newImage = new Image(newSurface->w, newSurface->h, objectCounter);
			newImage->tex = SDL_CreateTextureFromSurface(render, newSurface);
			if (newImage->tex == nullptr) {
				delete newImage;
				return false;
			}
			gfx[fileName] = newImage;
			objectCounter += 1;
			SDL_FreeSurface(newSurface);
			return true;
		}

		bool makeButton(string buttonName, Image* imagePtr) {
			if (btn.find(buttonName) != btn.end()) {
				return true;
			}
			Button* newBtn = new Button(imagePtr->)

			// DOKONCZYC ! ! !

		}

		// JEDYNY SPOSOB ZEBY DOSTAC SIE DO OBRAZOW ! ! !

		Image* accesImage(string imageName) {
			if (gfx.find(imageName) == gfx.end()) {
				return nullptr;
			} else {
				return gfx[imageName];
			}
		}

};
