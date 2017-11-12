#include <string.h>
#include <stdlib.h>
#include <myLib.h>

void setPixel(int row, int col, unsigned short color)
{
  videoBuffer[OFFSET(row, col)] = color;
}

void waitForVblank() {
  while(*SCANLINECOUNTER >= 160);
  while(*SCANLINECOUNTER < 160);
}

void drawImage3(int x, int y, int width, int height, const unsigned short *image) { 
  for(int i = 0; i < height - 1; i++) {
    DMA[3].src = &image[OFFSET(i, width)];
    DMA[3].dst = &videoBuffer[OFFSET(x + i, y)];
    DMA[3].cnt = 240 | DMA_SOURCE_INCREMENT | DMA_DESTINATION_INCREMENT | DMA_ON;
  }
}

void drawRectangle(int row, int col, int width, int height, unsigned short color)
{
  for(int l = 0; l <= height/2; l++) {
    for(int i = 0; i < width; i++) {
      setPixel(row + l, col + i, color);
      setPixel(row + height - l, col + i, color);
    }
  }
}

