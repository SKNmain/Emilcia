#pragma once

#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <map>
#include <vector>
#include <string>
#include <SDL2/SDL.h>

using namespace std;

enum ObjectType {
	NONE 	= 0,
	IMAGE 	= 1,
	TEXT 	= 2,
	BUTTON 	= 3
};

class Object {
	public:
		ObjectType type;
		bool enabled;
		union {
			struct {
				int x;
				int y;
				int w;
				int h;
			};
			SDL_Rect dst;
		};
		
		Object() {
			type = NONE;
			enabled = true;
		}
		~Object() {
			enabled = false;
			type = NONE;	
		};
		//virtual ~Object() const;
		virtual void render(SDL_Renderer* renderer) const = 0;


};
