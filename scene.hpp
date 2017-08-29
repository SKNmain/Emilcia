#pragma once

#include <iostream>
#include <stdio.h>
#include <fstream>
#include <cstdlib>
#include <map>
#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include "object.hpp"
#include "image.hpp"



using namespace std;



class Scene {
	private:
		Scene() {}
	public:
		ofstream dbg;
		vector<Object*> 	objects;
		SDL_Renderer* 		renderer = nullptr;



		Scene(SDL_Renderer* renderPtr)
		: dbg("error.txt", ios::trunc | ios::out)
		{
			renderer = renderPtr;
		}

		~Scene() {
			dbg.close();
			renderer = nullptr;
		}

		bool addObject(Object* obj) {
			if (obj == nullptr) {
				return false;
			}
			objects.push_back(obj);
			return true;
		}

		void update(SDL_Event* e) {
			if (e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP) {
				for (unsigned int i = 0; i < objects.size(); ++i) {
					if (e->type != SDL_MOUSEBUTTONUP && objects[i]->type == BUTTON) {
						if (((Button*)objects[i])->pressed(e->button.x,  e->button.y)) {
							((Button*)objects[i])->exec();
						}
					} else {
						((Button*)objects[i])->pressed(-1000, -1000);
					}
				}
			}

		}


		void render() {
			for (unsigned int i = 0; i < objects.size(); ++i) {
				objects[i]->render(renderer);
			}
		}



};
