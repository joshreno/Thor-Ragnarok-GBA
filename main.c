#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "myLib.h"
#include "background.h"
#include "gameOver.h"
#include "lose.h"
#include "start.h"
#include "hela.h"
#include "hulk.h"
#include "thor.h"
#include "loki.h"
#include "text.h"

enum GBAState {
	START,
	FIGHT,
	LOSE,
	GAMEOVER
};

enum ENEMYState {
	LOKI,
	HULK,
	HELA
};

void startGame();
void fight(enum ENEMYState enemy);
void loseGame(enum ENEMYState enemy);
void gameover();

enum GBAState state = START;
enum ENEMYState enemy = LOKI;

int reset = 0;
int hp_dir = -1;
int hp = 10;

objetcLocation thorE;
objetcLocation enemyE;
objetcLocation *thorPointer = &thorE;
objetcLocation *enemyPointer = &enemyE;

void setInitialVariables()
{
	thorPointer->row = 20;
	thorPointer->col = 20;
	thorPointer->health = hp;
	thorPointer->dx = 1;
	thorPointer->dy = 1;
	thorPointer->height = THOR_HEIGHT;
	thorPointer->width = THOR_WIDTH;

	enemyPointer->row = 100;
	enemyPointer->col = 100;
	enemyPointer->health = hp;
	enemyPointer->dx = (-1) *(rand() % 3);
	enemyPointer->dy = (-1) *(rand() % 3);
	enemyPointer->height = LOKI_HEIGHT;
	enemyPointer->width = LOKI_WIDTH;
}

int main(void) {
	REG_DISPCTL = MODE3 | BG2_ENABLE;
	while (1)
	{
		waitForVblank();
		if (KEY_DOWN_NOW(BUTTON_SELECT))
		{
			state = START;
		}
		switch(state)
		{
			case START:
				startGame();
				break;
			case FIGHT:
				fight(enemy);
				break;

			case LOSE:
				loseGame(enemy);
				break;

			case GAMEOVER:
				gameover();
				break;
		}
	}
	return 0;
}

void startGame()
{
	drawImage3(0, 0, 240, 160, start);
	char str[11] = "Press START";
	drawString(10, 90, str, BLUE);
	//int count = 0;
	while (1)
	{
		if (KEY_DOWN_NOW(BUTTON_START))
		{
			delay(10);
			break;
		}
	}
	state = FIGHT;
	drawImage3(0, 0, 240, 160, background);
	setInitialVariables();
	drawImage3(thorPointer->row, thorPointer->col, thorPointer->width, thorPointer->height, thor);
}

void fight(enum ENEMYState enemy)
{
	if (thorPointer->health == 0) 
	{
		state = LOSE;
		return;
	}
	if (enemy == HELA && enemyPointer->health == 0)
	{
		state = GAMEOVER;
	}
	
	delay(10);
	if (KEY_DOWN_NOW(BUTTON_DOWN))
	{
		thorPointer->dy = 1;

		thorPointer->oldRow = thorPointer->row;
		thorPointer->oldCol = thorPointer->col;
		//drawImage3(thorPointer->oldRow, thorPointer->col, thorPointer->width, thorPointer->dy, background);


		thorPointer->row = thorPointer->row + thorPointer->dy;

		drawCopyImage(thorPointer->oldRow, thorPointer->oldCol, thorPointer->width, 1, background);
		//drawCopyImage(thorPointer->oldRow, thorPointer->oldCol, thorPointer->width, thorPointer->height, background);
		//drawImage3(thorPointer->row, thorPointer->col, thorPointer->width, thorPointer->height, thor);
	} else if (KEY_DOWN_NOW(BUTTON_UP))
	{
		thorPointer->dy = -1;
		thorPointer->oldRow = thorPointer->row;
		thorPointer->oldCol = thorPointer->col;
		thorPointer->row += thorPointer->dy;

		//drawCopyImage(thorPointer->oldRow, thorPointer->oldCol, thorPointer->width, thorPointer->height, background);

		drawCopyImage(thorPointer->oldRow + thorPointer->height, thorPointer->oldCol, thorPointer->width, 1, background);
		//drawImage3(thorPointer->row, thorPointer->col, thorPointer->width, thorPointer->height, thor);
	} else if (KEY_DOWN_NOW(BUTTON_RIGHT))
	{
		thorPointer->dx = 1;
		thorPointer->oldRow = thorPointer->row;
		thorPointer->oldCol = thorPointer->col;
		thorPointer->col += thorPointer->dx;
		drawCopyImage(thorPointer->oldRow, thorPointer->oldCol, 1, thorPointer->height, background);
		//drawImage3(thorPointer->row, thorPointer->col, thorPointer->width, thorPointer->height, thor);
		//drawCopyImage(thorPointer->oldRow, thorPointer->oldCol, thorPointer->width, thorPointer->height, background);
	} else if (KEY_DOWN_NOW(BUTTON_LEFT))
	{
		thorPointer->dx = -1;
		thorPointer->oldRow = thorPointer->row;
		thorPointer->oldCol = thorPointer->col;
		thorPointer->col += thorPointer->dx;
		drawCopyImage(thorPointer->oldRow, thorPointer->oldCol + thorPointer->width, 1, thorPointer->height, background);
		//drawImage3(thorPointer->row, thorPointer->col, thorPointer->width, thorPointer->height, thor);
		//drawCopyImage(thorPointer->oldRow, thorPointer->oldCol, thorPointer->width, thorPointer->height, background);
	}
	drawImage3(thorPointer->row, thorPointer->col, thorPointer->width, thorPointer->height, thor);
	delay(5);

	// hela code
	// 


}

void loseGame(enum ENEMYState enemy)
{
	fillScreen3(BLACK);
	drawImage3(0, 0, 240, 160, lose);
	delay(100);
	char *textLoki = "Lost to Loki";
	char *textHulk = "Lost to Hulk";
	char *textHela = "Lost to Hela";

	switch (enemy)
	{
		case LOKI:
			drawString(10, 90, textLoki, YELLOW);
			break;
		case HULK:
			drawString(10, 90, textHulk, GREEN);
			break;
		case HELA:
			drawString(10, 90, textHela, GREEN);
			break;
	}
	delay(100);
	char cont[19] = "Press A To Continue";
	drawString(100, 60, cont, WHITE);
	int reset = 0;
	while (!reset)
	{
		if (KEY_DOWN_NOW(BUTTON_A))
		{
      		reset = 1;
    	}
	}
	enemy = LOKI;
	state = START;
}

void gameover()
{
	delay(100);
	fillScreen3(RED);
	delay(100);
	drawImage3(0, 0, 240, 160, gameOver);
	delay(100);
	char cont[19] = "Press A To Continue";
	drawString(100, 60, cont, WHITE);
	int reset = 0;
	while (!reset)
	{
		if (KEY_DOWN_NOW(BUTTON_A))
		{
      		reset = 1;
    	}
	}
	enemy = LOKI;
	state = START;
}