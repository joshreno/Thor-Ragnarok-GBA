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
#include "poster.h"
#include "characters.h"
#include "main.h"

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

// void startGame();
// void fight(enum ENEMYState enemy);
// void loseGame(enum ENEMYState enemy);
// void gameover();

enum GBAState state = START;
enum ENEMYState enemy = LOKI;

int reset = 0;
int hp_count = 1;
int hp = 5;

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

	enemyPointer->row = 80;
	enemyPointer->col = 80;
	enemyPointer->health = 1;
	enemyPointer->dx = 1;
	enemyPointer->dy = 1;
	enemyPointer->height = LOKI_HEIGHT;
	enemyPointer->width = LOKI_WIDTH;

	hp_count = 1;
}

void gameover()
{
	// delay(1000);
	//drawImage3(0, 0, 240, 160, gameOver);
	// drawImage3(0, 0, 240, 160, poster);
	// delay(40);
	drawImage3(0, 0, 240, 160, characters);
	enemy = LOKI;
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
	char cont[24] = "Press Select To Continue";
	drawString(100, 60, cont, WHITE);
	int reset = 0;
	while (!reset)
	{
		if (KEY_DOWN_NOW(BUTTON_SELECT))
		{
      		reset = 1;
    	}
	}
	enemy = LOKI;
	state = START;
}

void fight()
{
	if (thorPointer->health == 0) 
	{
		state = LOSE;
		return;
	}
	if (enemyPointer->health == 0) {
		enemyPointer->health = 1;
		updateHearts(3, enemyPointer->health, background);
	}
	const unsigned short *fighting;
	switch (enemy){
		case LOKI:
			fighting = loki;
			break;
		case HULK:
			fighting = hulk;
			break;
		case HELA:
			fighting = hela;
			break;
	}
	if (KEY_DOWN_NOW(BUTTON_DOWN))
	{
		if (thorPointer->row < (160-thorPointer->height)) {
			thorPointer->dy = 1;

			thorPointer->oldRow = thorPointer->row;
			thorPointer->oldCol = thorPointer->col;
			//drawImage3(thorPointer->oldRow, thorPointer->col, thorPointer->width, thorPointer->dy, background);


			thorPointer->row = thorPointer->row + thorPointer->dy;

			drawCopyImage(thorPointer->oldRow, thorPointer->oldCol, thorPointer->width, 1, background);
		}
		//drawCopyImage(thorPointer->oldRow, thorPointer->oldCol, thorPointer->width, thorPointer->height, background);
		//drawImage3(thorPointer->row, thorPointer->col, thorPointer->width, thorPointer->height, thor);
	} else if (KEY_DOWN_NOW(BUTTON_UP))
	{
		if (thorPointer->row >= 10) {
			thorPointer->dy = -1;
			thorPointer->oldRow = thorPointer->row;
			thorPointer->oldCol = thorPointer->col;
			thorPointer->row += thorPointer->dy;
			drawCopyImage(thorPointer->oldRow + thorPointer->height, thorPointer->oldCol, thorPointer->width, 1, background);
		}
		

		//drawCopyImage(thorPointer->oldRow, thorPointer->oldCol, thorPointer->width, thorPointer->height, background);

		
		//drawImage3(thorPointer->row, thorPointer->col, thorPointer->width, thorPointer->height, thor);
	} else if (KEY_DOWN_NOW(BUTTON_RIGHT))
	{
		if (thorPointer->col < (240-thorPointer->width)) {
			thorPointer->dx = 1;
			thorPointer->oldRow = thorPointer->row;
			thorPointer->oldCol = thorPointer->col;
			thorPointer->col += thorPointer->dx;
			drawCopyImage(thorPointer->oldRow, thorPointer->oldCol, 1, thorPointer->height, background);
		}
		//drawImage3(thorPointer->row, thorPointer->col, thorPointer->width, thorPointer->height, thor);
		//drawCopyImage(thorPointer->oldRow, thorPointer->oldCol, thorPointer->width, thorPointer->height, background);
	} else if (KEY_DOWN_NOW(BUTTON_LEFT))
	{
		if (thorPointer->col >= 1){
			thorPointer->dx = -1;
			thorPointer->oldRow = thorPointer->row;
			thorPointer->oldCol = thorPointer->col;
			thorPointer->col += thorPointer->dx;
			drawCopyImage(thorPointer->oldRow, thorPointer->oldCol + thorPointer->width, 1, thorPointer->height, background);
		}
		//drawImage3(thorPointer->row, thorPointer->col, thorPointer->width, thorPointer->height, thor);
		//drawCopyImage(thorPointer->oldRow, thorPointer->oldCol, thorPointer->width, thorPointer->height, background);
	} else {
		thorPointer->dx = 0;
		thorPointer->dy = 0;
	}
	drawImage3(thorPointer->row, thorPointer->col, thorPointer->width, thorPointer->height, thor);

	enemyPointer->oldCol = enemyPointer->col;
	enemyPointer->oldRow = enemyPointer->row;
	enemyPointer->row += enemyPointer->dy;
	enemyPointer->col += enemyPointer->dx;
	if (enemyPointer->row < 10)
	{
		enemyPointer->row = 11;
		enemyPointer->dy = enemyPointer->dy * -1;
		// drawCopyimage
	} else {
		drawCopyImage(enemyPointer->oldRow + enemyPointer->height, enemyPointer->oldCol, enemyPointer->width, 1, background);
	}
	if (enemyPointer->row + enemyPointer->height >= 159)
	{
		enemyPointer->row = 158 - enemyPointer->height;
		enemyPointer->dy = enemyPointer->dy * -1;
	} else {
		drawCopyImage(enemyPointer->oldRow, enemyPointer->oldCol, enemyPointer->width, 1, background);
	}
	if (enemyPointer->col < 1)
	{
		enemyPointer->col = 0;
		enemyPointer->dx = enemyPointer->dx * -1;
	} else {
		drawCopyImage(enemyPointer->oldRow, enemyPointer->oldCol + enemyPointer->width, 1, enemyPointer->height, background);
	}
	if (enemyPointer->col + enemyPointer->width >= 239)
	{
		enemyPointer->col = 238 - enemyPointer->width;
		enemyPointer->dx = enemyPointer->dx * -1;
	} else {
		drawCopyImage(enemyPointer->oldRow, enemyPointer->oldCol, 1, enemyPointer->height, background);
	}
	drawImage3(enemyPointer->row, enemyPointer->col, enemyPointer->width, enemyPointer->height, fighting);

	int thorRow0 = thorPointer->row;
	int thorRowMax = thorPointer->row + thorPointer->height;
	int thorCol0 = thorPointer->col;
	int thorColMax = thorPointer->col + thorPointer ->width;

	int enemyRow0 = enemyPointer->row;
	int enemyRowMax = enemyPointer->row + enemyPointer->height;
	int enemyCol0 = enemyPointer->col;
	int enemyColMax = enemyPointer->col + enemyPointer->width;

	int intersect1 = 1;
	int intersect2 = 1;

	if (thorCol0 > enemyColMax || enemyCol0 >thorColMax) {
		intersect1 = 0;
	}
	if (thorRow0 < enemyRowMax || enemyRow0 < thorRowMax) {
		intersect2 = 0;
	}
	if (intersect1 || intersect2) {
		enemyPointer->dy = enemyPointer->dy * -1;
		enemyPointer->dx = enemyPointer->dx * -1;


		if (thorPointer->dx == 0 && thorPointer->dy == 0) {
			thorPointer->health = thorPointer->health -1;
			hp_count += 1;
			updateHearts(4, hp_count, background);
		} else {
			enemyPointer->health = 0;
			if (enemy == HELA) {
			state = GAMEOVER;
			}
			if (enemy == HULK) {
				enemy = HELA;
			}
			if (enemy == LOKI) {
				enemy = HULK;
			}
		}
	}
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
	drawImage3(enemyPointer->row, enemyPointer->col, enemyPointer->width, enemyPointer->height, loki);
	updateHearts(2, enemyPointer->health, background);
	updateHearts(1, thorPointer->health, background);
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
				fight();
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



