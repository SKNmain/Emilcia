#pragma once

#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <map>
#include <vector>
#include <string>
#include <functional>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "object.hpp"
#include "image.hpp"

using namespace std;



class Button : public Object{
	private:
		SDL_Texture* loadBMP(SDL_Rect* src, string fileName, SDL_Renderer* renderer) {
			//zapisywanie do powierzchni
			SDL_Texture* tex		= nullptr;
			SDL_Surface* newSurface	= IMG_Load(fileName.c_str());
			if (newSurface == nullptr) {
				return nullptr;
			}

			src->w = newSurface->w;
			src->h = newSurface->h;

			//zapisywanie do tekstury
			tex = SDL_CreateTextureFromSurface(renderer, newSurface);
			SDL_FreeSurface(newSurface);
			return tex;
		}

	public:
		bool					isPressed;
		SDL_Rect				src_off;
		SDL_Rect				src_on;
		SDL_Texture*			tex_off;
		SDL_Texture*			tex_on;

		function<void(void)>			onPress;


		Button()
		: onPress(nullptr)
		{
			type = BUTTON;
		}

		Button(string fileNameOn, string fileNameOff, SDL_Renderer* renderer)
		: onPress(nullptr)
		{
			type	= BUTTON;
			tex_on	= loadBMP(&src_on, fileNameOn, renderer);
			tex_off	= loadBMP(&src_off, fileNameOff, renderer);
			dst.w	= src_on.w;
			dst.h	= src_on.h;
		}

		void setClip(SDL_Rect* src, int x1, int y1, int x2, int y2) {
			src->x = x1;
			src->y = y1;
			dst.w = src->w = x2;
			dst.h = src->h = y2;
		}

		void setPos(int x, int y) {
			dst.x = x;
			dst.y = y;
		}

		bool pressed(int x, int y) {
			if (x >= dst.x && x <= (dst.w + dst.x) && y >= dst.y && y <= (dst.h + dst.y)) {
				isPressed = true;
			} else {
				isPressed = false;
			}
			return isPressed;
		}

		void bindFunction(function<void(void)> func) {
			onPress		= func;
		}

		void exec() {
			if (onPress != nullptr)
				onPress();
			//--
		}

		void render(SDL_Renderer* renderer) const {
			if (tex_on == nullptr || tex_off == nullptr) {
				return;
			}
			SDL_RenderCopy(
				renderer,
				(isPressed? tex_on: tex_off),
				(isPressed? &src_on: &src_off),
				&dst
			);
		}

		~Button() {
			if (tex_on != nullptr) {
				SDL_DestroyTexture(tex_on);
			}
			if (tex_off != nullptr) {
				SDL_DestroyTexture(tex_off);
			}
		}
};