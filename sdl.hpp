#pragma once

#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <map>
#include <vector>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "object.hpp"
#include "image.hpp"
#include "button.hpp"
#include "scene.hpp"

using namespace std;

class SDL {

	private:
		SDL_Event					event;
		vector<Scene*>				scenes;
		vector<Object*> 			objects;
		unsigned short 				currentScene = 0;
		unsigned short				fps;
		unsigned int				fpsTimer;

		SDL() {

			// Inicjalizacja SDL'a

			if (SDL_Init(SDL_INIT_EVERYTHING)) {
				isError = true;
				return;
			}

            if ( IMG_Init( ((IMG_INIT_JPG|IMG_INIT_PNG) & (IMG_INIT_JPG|IMG_INIT_PNG)) != (IMG_INIT_JPG|IMG_INIT_PNG) ) ) {
                isError = true;
                return;
            }

			// inicjalizacja okna
			//-------------------------------------------------
			window = SDL_CreateWindow(
				"Emilcia",
				SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
				windowWidth, windowHeight,
				SDL_WINDOW_SHOWN | SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_MOUSE_FOCUS
			);
			//-------------------------------------------------

			if (window == nullptr) {
				isError = true;
				return;
			}

			// inicjalizacja renderera

			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			if (renderer == nullptr) {
				isError = true;
				return;
			}

			// pobranie tickow

			fpsTimer = SDL_GetTicks();


		}

		~SDL() {
			for (unsigned int i = 0; i < scenes.size(); ++i) {
				delete scenes[i];
			}
			for (unsigned int i = 0; i < objects.size(); ++i) {
				switch (objects[i]->type) {
					case (IMAGE): {
						delete ((Image*)objects[i]);
						break;
					}
					case (TEXT): {
						//delete ((Text*)objects[i]);
						break;
					}
					case (BUTTON): {
						Button* temp = (Button*)objects[i];
						delete temp;
						//delete ((Button*)objects[i]);
						break;
					}
					default: {
						delete (objects[i]);
						break;
					}
				}
			}

			SDL_DestroyRenderer(renderer);
			SDL_DestroyWindow(window);
			IMG_Quit();
			SDL_Quit();
		}


	public:
		static SDL& init() {
			static SDL sdl;
			return sdl;
		}

		bool			isError 		= false;
		SDL_Window*		window			= nullptr;
		SDL_Renderer*	renderer 		= nullptr;
		int 			windowWidth 	= 1024;
		int 			windowHeight 	= 768;

		void showError() {
			cout << "Error: " << SDL_GetError() << endl;
		}

		SDL_Event* eventUpdate() {
			SDL_PollEvent(&event);
			return &event;
		}
		void inputUpdate(SDL_Event* e) {
			if (currentScene < scenes.size()) {
				scenes[currentScene]->update(e);
			}
		}
		// odswiezanie
		void screenUpdate(SDL_Event* event) {
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
			if (SDL_GetTicks() - fpsTimer > fps) {
				SDL_RenderClear(renderer);
				if (currentScene < scenes.size()) {
					scenes[currentScene]->render();
				}
				SDL_RenderPresent(renderer);
				fpsTimer = SDL_GetTicks();
			}
		}

		void setFPS(unsigned int newFPS) {
			fps =  1.0 / newFPS;
		}

		Scene* newScene(){
			Scene* newScene = new Scene(renderer);
			if (newScene == nullptr) {
				return nullptr;
			}
			scenes.push_back(newScene);
			return (Scene*)scenes.back();
		}

		Scene* getSceneById(unsigned int id) {
			if (currentScene < scenes.size()) {
				return scenes[id];
			} else {
				return nullptr;
			}
		}

		bool addElementToScene(Object* obj, unsigned int id) {
			Scene* scn = getSceneById(id);
			if (scn == nullptr) {
				return false;
			}
			scn->addObject(obj);
			return true;
		}

		bool addObject(Object* obj) {
			if (obj == nullptr) {
				return false;
			}
			objects.push_back(obj);
			return true;
		}

		Object* getLastObject() {
			if (objects.size() == 0) {
				return nullptr;
			} else {
				return (Object*)objects.back();
			}
		}

		Scene* setCurrentScene(unsigned int n) {
			if (n < scenes.size()) {
				currentScene = n;
				return scenes[n];
			}
			return nullptr;
		}
};
