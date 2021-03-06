#pragma once

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <cstdlib>
#include <map>
#include <vector>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "object.hpp"

using namespace std;



class Image : public Object {
	public:
		SDL_Texture*	tex = nullptr;
		SDL_Rect		src;

		Image() {
			src.x = 0; src.y = 0; src.w = 0; src.h = 0;
			dst.x = 0; dst.y = 0; dst.w = 0; dst.h = 0;
			type = IMAGE;
		}

		bool loadBMP(string fileName, SDL_Renderer* renderer) {
			// zapisywanie do powierzchni
			SDL_Surface* newSurface = IMG_Load(fileName.c_str());
			if (newSurface == nullptr) {
				return false;
			}
			dst.w = src.w = newSurface->w;
			dst.h = src.h = newSurface->h;
			// zapisywanie do tekstury

			tex = SDL_CreateTextureFromSurface(renderer, newSurface);
			if (tex == nullptr) {
				return false;
			}
			SDL_FreeSurface(newSurface);

			return true;
		}

		Image(string fileName, SDL_Renderer* renderer) {
			src.x = 0; src.y = 0; src.w = 0; src.h = 0;
			dst.x = 0; dst.y = 0; dst.w = 0; dst.h = 0;
			type = IMAGE;
			loadBMP(fileName, renderer);
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

		void render(SDL_Renderer* renderer) const {
			if (tex == nullptr) {
				return;
			}
			SDL_RenderCopy(
				renderer,
				tex,
				&src,
				&dst
			);
		}



		~Image() {
			if (tex != nullptr) {
				SDL_DestroyTexture(tex);
			}
		};
};