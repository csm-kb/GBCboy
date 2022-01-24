#ifndef GBCRenderer_H
#define GBCRenderer_H

#include <SDL.h>

#define GBC_SCREEN_WIDTH  160
#define GBC_SCREEN_HEIGHT 144
#define GBC_SCREEN_DEPTH  16

/**
 * \brief Renderer object for the GBC emulator.
 */
struct GBCRenderer
{
	SDL_Window* window;
	SDL_Surface* surface;
	SDL_Surface* pixels;
	int running;
	Uint64 ticks;
};

/**
 * \brief Initializes a renderer object.
 */
int GBCRenderer_Init(struct GBCRenderer* renderer);
/**
 * \brief Tells the renderer to render this frame.
 */
int GBCRenderer_Render(struct GBCRenderer* renderer, double delta);
/**
 * \brief Tells the renderer to quit and clean up.
 */
void GBCRenderer_Quit(struct GBCRenderer* renderer);

#endif//GBCRenderer_H