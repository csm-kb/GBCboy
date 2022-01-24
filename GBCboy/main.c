#include <stdio.h>

#include <SDL.h>
#include <renderer/GBCRenderer.h>

int main(int argc, char* argv[])
{
	struct GBCRenderer* renderer = malloc(sizeof(struct GBCRenderer));

	// initialize renderer
	if (GBCRenderer_Init(renderer))
	{
		return 1;
	}

	// render until quit
	SDL_Event event;
	double delta = 0;
	double pos = 0;
	do
	{
		while (SDL_PollEvent(&event))
		{
			renderer->running = event.type != SDL_QUIT;
		}
		Uint64 tx = SDL_GetTicks64();
		delta = (tx - renderer->ticks) / 1000.0;
		renderer->ticks = tx;
		
		const SDL_PixelFormat* pfmt = renderer->pixels->format;

		// clear pixels
		SDL_FillRect(renderer->pixels, NULL, SDL_MapRGBA(pfmt, 0, 0, 0, 255));

		// write pixels
		SDL_LockSurface(renderer->pixels);
		{
			const int pitch = renderer->pixels->pitch;

			// move 144 px/s
			pos += delta * 144.0;
			pos = fmodf(pos, GBC_SCREEN_WIDTH);

			// draw red diagonal line
			for (int i = 0; i < GBC_SCREEN_HEIGHT; i++)
			{
				int y = i;
				int x = ((int)pos + i) % GBC_SCREEN_WIDTH;

				Uint16* row = (Uint16*)((char*)renderer->pixels->pixels + pitch * y);
				row[x] = 0xf00f; //0xRGBA
			}
		}
		SDL_UnlockSurface(renderer->pixels);

	} while (GBCRenderer_Render(renderer, delta));

	// clean up renderer
	GBCRenderer_Quit(renderer);

	free(renderer);

	return 0;
}