#pragma once

#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <map>
#include <string>
#include <SDL2/SDL.h>
#include "scene.hpp"
#include "object.hpp"
#include "image.hpp"
#include "button.hpp"
using namespace std;

class SDL {

	private:
		SDL_Event					event;
		map<string, Image*>			gfx;
		map<string, Button*>		btn;
		vector<Scene*>				scenes;
		unsigned short 				currentScene = 0;
		unsigned short				fps;
		unsigned int				fpsTimer;

		SDL() {

			// Inicjalizacja SDL'a

			if (SDL_Init(SDL_INIT_EVERYTHING)) {
				isError = true;
				return;
			}

			// inicjalizacja okna
			//-------------------------------------------------
			window = SDL_CreateWindow(
				"Emilcia",
				SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
				1024, 768,
				SDL_WINDOW_SHOWN | SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_MOUSE_FOCUS
			);
			//-------------------------------------------------

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
		void screenUpdate(SDL_Event* event) {
			SDL_SetRenderDrawColor(render, 255, 0, 0, 255);
			if (SDL_GetTicks() - fpsTimer > fps) {
				SDL_RenderClear(render);
				/*
				//Petla iterujaca po obrazach
				for (auto it = gfx.begin(); it != gfx.end(); ++it) {
					if (it->second->visible) {
						SDL_RenderCopy(
							render,
							it->second->tex,
							(const SDL_Rect*)&it->second->src,
							(const SDL_Rect*)&it->second->dst
						);
					}
				}

				//Petla iterujaca po przyciskach
				for (auto it = btn.begin(); it != btn.end(); ++it) {
					if (it->second) {
						SDL_RenderCopy(
							render,
							it->second->getImage()->tex,
							(const SDL_Rect*)&it->second->getImage()->src,
							(const SDL_Rect*)&it->second->dst
						);
						if (event->type == SDL_MOUSEBUTTONDOWN) {
							accesImage("images\\test.bmp")->visible = true;
						}
						if (event->type == SDL_MOUSEBUTTONUP) {
							accesImage("images\\test.bmp")->visible = false;
						}
						
					}
				}
				*/

				if (currentScene < scenes.size()) {
					scenes[currentScene].render();
				}
				SDL_RenderPresent(render);
				fpsTimer = SDL_GetTicks();
			}
		}

		void setFPS(unsigned int newFPS) {
			fps =  1.0 / newFPS;
		}

		// wczytywanie map bitowych
		// przeniesione do class Image
		/*
		bool loadBMP(string fileName) {

			// sprawdzam czy juz istnieje

			if (gfx.find(fileName) != gfx.end()) {
				return true;
			}

			

			SDL_Surface* newSurface = SDL_LoadBMP(fileName.c_str());
			if (newSurface == nullptr) {
				return false;
			}

			// zapisywanie do obiektu klasy image, do tekstury

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
		*/
		bool makeNewButton(string buttonName, string imgName) {

			// sprawdzam czy juz istnieje

			if (btn.find(buttonName) != btn.end()) {
				return false;
			}
			if (gfx.find(imgName) == gfx.end()) {
				return false;
			}
			Button* newBtn = new Button(gfx[imgName]);
			gfx[imgName]->visible = false;
			btn[buttonName] = newBtn;
			return true;
		}

		// JEDYNY SPOSOB ZEBY DOSTAC SIE DO OBRAZOW ! ! !

		Image* accesImage(string imageName) {
			if (gfx.find(imageName) == gfx.end()) {
				return nullptr;
			} else {
				return gfx[imageName];
			}
		}

		Button* accesButton(string btnName) {
			if (btn.find(btnName) == btn.end()) {
				return nullptr;
			} else {
				return btn[btnName];
			}
		}


};
