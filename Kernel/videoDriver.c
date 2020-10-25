#include <stdint.h>
#include <videoDriver.h>
#include <font.h>

#define FONT_SCALING 3

struct vbe_mode_info_structure
{
	uint16_t attributes;  // deprecated, only bit 7 should be of interest to you, and it indicates the mode supports a linear frame buffer.
	uint8_t window_a;	  // deprecated
	uint8_t window_b;	  // deprecated
	uint16_t granularity; // deprecated; used while calculating bank numbers
	uint16_t window_size;
	uint16_t segment_a;
	uint16_t segment_b;
	uint32_t win_func_ptr; // deprecated; used to switch banks from protected mode without returning to real mode
	uint16_t pitch;		   // number of bytes per horizontal line
	uint16_t width;		   // width in pixels
	uint16_t height;	   // height in pixels
	uint8_t w_char;		   // unused...
	uint8_t y_char;		   // ...
	uint8_t planes;
	uint8_t bpp;   // bits per pixel in this mode
	uint8_t banks; // deprecated; total number of banks in this mode
	uint8_t memory_model;
	uint8_t bank_size; // deprecated; size of a bank, almost always 64 KB but may be 16 KB...
	uint8_t image_pages;
	uint8_t reserved0;

	uint8_t red_mask;
	uint8_t red_position;
	uint8_t green_mask;
	uint8_t green_position;
	uint8_t blue_mask;
	uint8_t blue_position;
	uint8_t reserved_mask;
	uint8_t reserved_position;
	uint8_t direct_color_attributes;

	uint32_t framebuffer; // physical address of the linear frame buffer; write here to draw to the screen
	uint32_t off_screen_mem_off;
	uint16_t off_screen_mem_size; // size of memory in the framebuffer but not being displayed on the screen
	uint8_t reserved1[206];
} __attribute__((packed));

struct vbe_mode_info_structure *screenData;

int cursorPositionX;
int cursorPositionY;
int width;
int height;

void initVideo(long int infoLoc){
	screenData = (void *)infoLoc;
	cursorPositionX = cursorPositionY = 0;
	width = screenData->width;
	height = screenData->height;

}
//TODO: INICIALIZAR CONSTANTES EN LUGAR DE LLAMAR A SCREENDATA->


int renderPixel(unsigned int x, unsigned int y, unsigned int color)
{
	if (x < 0 || y < 0 || x > width || y > height)
		return -1;

	char *pos = (char *)((uint64_t)screenData->framebuffer + (x + y * width) * 3);
	*pos = (color & 0x0000FF);
	*(pos+1) = (color & 0x00FF00) >> 8;
	*(pos+2) = (color & 0xFF0000) >> 16;
	return 0;

}

int renderArea(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, unsigned int color){
	if (x2<x1 || y2<y1)
		return -1;
	if (x1 < 0 || y1 < 0 || x2 > width || y2 > height)
		return -2;
	for (int i=x1;i<=x2;i++){
		for (int j=y1;j<=y2;j++)
			renderPixel(i,j,color);
	}
	return 0;
}

	// segun https://jared.geek.nz/2014/jan/custom-fonts-for-microcontrollers
	int renderChar(unsigned char c, unsigned int x, unsigned int y, unsigned int color)
{
	if (x < 0 || y < 0 || x + (CHAR_WIDTH * FONT_SCALING) > width || y + (CHAR_HEIGHT * FONT_SCALING) > height)
		return -1;

	// Convert the character to an index
	c = c & 0x7F;
	if (c < ' ')
		c = 0;
	else
		c -= ' ';

	// 'font' es un arreglo multidimensional de [96][char_width]
	// que es un arreglo 1D de tamano 96*char_width.
	const uint8_t *chr = font[c];

	// Draw pixels
	for (int i = 0; i < CHAR_WIDTH; i++){
		for (int j = 0; j < CHAR_HEIGHT; j++){
			if (chr[i] & (1 << j)) //En esta posicion hay un bit encendido
				renderArea(x + i*FONT_SCALING,y+j*FONT_SCALING,
							x+(i+1)*FONT_SCALING, y + (j+1)*FONT_SCALING, color);
		}
	}
	return 0;
}