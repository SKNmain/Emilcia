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

enum Assigment {
	NONE	= 0,
	TAKE	= 1,
	LOUPE	= 2,
	ADD 	= 3
};



class Button : public Image{
	private:
		Assigment 	taskFlag;
	public:
		bool 		isPressed;
		


		Button() {
			type = BUTTON;
			taskFlag = NONE;
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

		void render() {

		}
		~Button() {
		}
};