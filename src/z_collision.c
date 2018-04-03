#include <SDL.h>

Uint8 checkCollision(SDL_Rect a, SDL_Rect b) {
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;
	
	leftA = a.x;
	rightA = a.x + a.w;
	topA = a.y;
	bottomA = a.y + a.h;
	
	leftB = b.x;
	rightB = b.x + b.w;
	topB = b.y;
	bottomB = b.y + b.h;

	if (bottomA <= topB) {
		return 0;
	}
	if (topA >= bottomB) {
		return 0;
	}
	if (rightA <= leftB) {
		return 0;
	}
	if (rightA >= rightB) {
		return 0;
	}
	return 1;
}

