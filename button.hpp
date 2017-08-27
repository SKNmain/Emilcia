#pragma once

#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <map>
#include <vector>
#include <string>
#include <SDL2/SDL.h>
#include "object.hpp"
#include "image.hpp"

using namespace std;



class Button : public Object{
	private:
	public:
		bool			isPressed;
		SDL_Rect		src_off;
		SDL_Rect		src_on;
		SDL_Texture*	tex_off;
		SDL_Texture*	tex_on;


		Button() {
			type = BUTTON;
		}
		/*
		void setPos(int x, int y) {
			dst.x = x;
			dst.y = y;
		}

		bool setPosLikeImage() {
			if (imagePointer == nullptr) {
				return false;
			}
			setPos(imagePointer->dst.x, imagePointer->dst.y);
			return true;
		}
		*/
		bool pressed(int x, int y) {
			if (x >= dst.x && x <= dst.w && y >= dst.y && y <= dst.h) {
				isPressed = true;
			} else {
				isPressed = false;
			}
			return isPressed;
		}

		void render(SDL_Renderer* renderer) {
			if (isPressed == true) {
				if (tex_on == nullptr) {
					return;
				}
				SDL_RenderCopy(
					renderer,
					tex_on,
					&src_on,
					&dst
				);
			} else {
				if (tex_off == nullptr) {
					return;
				}
				SDL_RenderCopy(
					renderer,
					tex_off,
					&src_off,
					&dst
				);
			}
		}

		~Button() {
		}
};