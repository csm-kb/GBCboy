#include <stdio.h>

#include <SDL.h>
#include <renderer/GBCRenderer.h>

/*
 * This is the primary entry point into GBCboy.
 *
 * The system has an 8-bit microprocessor linked to an LCD driver (our SDL2 renderer), an audio
 * amplifier (through an external volume control), a 6-pin sub-connector, the operating keys,
 * some display memory (16 kB), and some working memory (32 kB).
 *
 * The CPU is the 8-bit SHARP LR35902, with architecture like so: https://www.pastraiser.com/cpu/gameboy/gameboy_opcodes.html
 * It runs at exactly 8.4 MHz, and is a hybrid of the Intel 8080 and Zilog Z80 (which are binary-compatible).
 *
 * It boots from a mask ROM program loaded from a game pak.
 */

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

		GBCRenderer_Render(renderer, delta);

	} while (renderer->running);

	// clean up renderer
	GBCRenderer_Quit(renderer);

	free(renderer);

	return 0;
}