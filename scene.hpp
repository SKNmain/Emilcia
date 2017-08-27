#pragma once

#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <map>
#include <string>
#include <SDL2/SDL.h>
//#include "object.hpp"
#include "image.hpp"

using namespace std;



class Scene {
	private:
		Scene() {}
	public:

		vector<Object*> 	objects;
		SDL_Renderer* 		renderer = nullptr;


		Scene(SDL_Renderer* renderPtr) {
			renderer = renderPtr;
		}
		
		~Scene() {
			renderer = nullptr;
			for (int i = 0; i < objects.size(); ++i) {
				delete objects[i];
			}
		}

		Object* newObject() {
			Object* newObject = new Object();
			objects.push_back(newObject);
			return newObject;
		}

		void render() {
			for (int i = 0; i < objects.size(); ++i) {
				objects[i].render(renderer);
			}
		}

		

};