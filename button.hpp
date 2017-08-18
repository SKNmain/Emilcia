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





class Button : public Image{
	private:
		Button() {}
		/*
	   -1 - zabierz
		0 - nic
		1 - lupa
		2 - dodaj
		*/
		int 		taskFlag;
	public:
		bool 		isPressed;
		


		Button() {
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
			imagePointer = nullptr;
		}
};