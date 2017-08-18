#pragma once

#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <map>
#include <string>
#include <SDL2/SDL.h>
#include "object.hpp"
#include "image.hpp"
using namespace std;

class Scene {
	private:
		Scene() {}
	public:

		vector<Object*> objects;
		SDL_Renderer* render = nullptr;

		Scene(SDL_Renderer* renderPtr) {
			render = renderPtr;
		}
		
		~Scene() {
			render = nullptr;
			for (int i = 0; i < objects.size(); ++i) {
				delete objects[i];
			}
		}

		Object* newObject() {
			Object* newObject = new Object();
			objects.push_back(newObject);
		}

		void render() {
			for (int i = 0; i < objects.size(); ++i) {
				objects[i].render(render);
			}
		}

		

};