#include <stdio.h>

#include <renderer/GBCRenderer.h>

int GBCRenderer_Init(struct GBCRenderer* renderer)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		fprintf(stderr, "SDL video init failed: %s\n", SDL_GetError());
		return 1;
	}

	renderer->window = SDL_CreateWindow("GBCboy",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		GBC_SCREEN_WIDTH * 4, GBC_SCREEN_HEIGHT * 4, SDL_WINDOW_SHOWN);
	if (!renderer->window)
	{
		fprintf(stderr, "Window could not be created: %s\n", SDL_GetError());
		return 1;
	}

	renderer->surface = SDL_GetWindowSurface(renderer->window);
	renderer->pixels = SDL_CreateRGBSurfaceWithFormat(0, GBC_SCREEN_WIDTH, GBC_SCREEN_HEIGHT, GBC_SCREEN_DEPTH, SDL_PIXELFORMAT_RGBA4444);

	renderer->ticks = SDL_GetTicks64();

	return 0;
}

int GBCRenderer_Render(struct GBCRenderer* renderer, double delta)
{
	// copy to window
	SDL_UpperBlitScaled(renderer->pixels, NULL, renderer->surface, NULL);
	SDL_UpdateWindowSurface(renderer->window);

	return renderer->running;
}

void GBCRenderer_Quit(struct GBCRenderer* renderer)
{
	SDL_DestroyWindow(renderer->window);

	SDL_Quit();
}