#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "myLib.h"

enum GBAState {
	START,
	LOKI
	HULK
	HELA
	LOSE
	GAMEOVER
}

int main(void) {
	REG_DISPCNT = MODE_3 | BG2_ENABLE;

	enum GBAState state = START;

	while (1)
	{
		waitForVBlank();
		switch(state)
		{
			case START:
				break;

			case LOKI:
				break;

			case HULK:
				break;

			case HELA:
				break;

			case LOSE:
				break;

			case GAMEOVER:
				break;
		}
	}

	return 0;
}