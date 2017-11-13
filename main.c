#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "myLib.h"
#include "Assets/background.h"
#include "Assets/gameOver.h"
#include "Assets/lose.h"
#include "Assets/start.h"

enum GBAState {
	START,
	FIGHT,
	LOSE,
	GAMEOVER
}

enum ENEMYState {
	LOKI,
	HULK,
	HELA
}

void start();
void fight(ENEMYState enemy);
void lose();
void gameOver();

GBAState state = START;
ENEMYState enemy = LOKI;
int reset = 0;

int health = 0;
int attack = 0;
int hp_dir = -1;
int hp = 10;

OBJLOCATION thor;
OBJLOCATION enemy;

void setInitialVariables()
{
	thor.row = 5;
	thor.col = 5;
	thor.health = hp;
	thor.dx = 0;
	thor.dy = 0;

	enemy.row = 100;
	enemy.col = 100;
	enemy.health = hp;
	enemy.dx = 0;
	enemy.dy = 0;

}

int main(void) {
	REG_DISPCNT = MODE3 | BG2_ENABLE | OBJ_ENABLE;
	setInitialVariables();
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
				start();
				break;

			case FIGHT:
				fight(enemy);
				break;

			case LOSE:
				lose(enemy);
				break;

			case GAMEOVER:
				gameOver();
				break;
		}
	}
	return 0;
}

void start()
{
	drawImage3(0, 0, 240, 160, start);
	char str[11] = "Press START";
	int count = 0;
	while (1)
	{
		if (KEY_DOWN_NOW(BUTTON_START))
		{
			break;
		}
		// waitForVblank(); do I call this
		count += 1;
		if (count > 30)
		{
			count = 0;
		} 
		else if (count > 20)
		{
			fillScreen3(BLUE);
			drawImage3(0, 0, 240, 160, start);
		}
		else
		{
			drawString(10, 90, str, BLUE);
		}
	}
	state = FIGHT;
}

void fight(ENEMYState enemy)
{
	if (thor.health == 0) 
	{
		state = LOSE;
		return;
	}
	// the rest
	drawImage3(0, 0, 240, 160, background);


}

void lose(ENEMYState enemy)
{
	fillScreen3(BLACK);
	drawImage3(0, 0, 240, 160, lose);
	delay(100);
	switch (enemy)
	{
		case LOKI:
			char txt[12] = "Lost to Loki";
			drawString(10, 90, txt, YELLOW);
			break;
		case HULK:
			char txt[12] = "Lost to Hulk";
			drawString(10, 90, txt, GREEN);
			break;
		case HELA:
			char txt[12] = "Lost to Hela";
			drawString(10, 90, txt, GREEN);
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

void gameOver()
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