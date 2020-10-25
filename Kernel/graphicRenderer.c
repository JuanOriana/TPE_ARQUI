#include <stdint.h>
#include <graphicRenderer.h>
#include <font.h>

const unsigned char font[96][6] = {
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, //
    {0x2e, 0x00, 0x00, 0x00, 0x00, 0x00}, // !
    {0x06, 0x00, 0x06, 0x00, 0x00, 0x00}, // "
    {0x14, 0x3e, 0x14, 0x3e, 0x14, 0x00}, // #
    {0x04, 0x2a, 0x3e, 0x2a, 0x10, 0x00}, // $
    {0x22, 0x10, 0x08, 0x04, 0x22, 0x00}, // %
    {0x14, 0x2a, 0x2a, 0x2c, 0x10, 0x28}, // &
    {0x06, 0x00, 0x00, 0x00, 0x00, 0x00}, // '
    {0x1c, 0x22, 0x00, 0x00, 0x00, 0x00}, // (
    {0x22, 0x1c, 0x00, 0x00, 0x00, 0x00}, // )
    {0x14, 0x08, 0x14, 0x00, 0x00, 0x00}, // *
    {0x08, 0x1c, 0x08, 0x00, 0x00, 0x00}, // +
    {0x60, 0x00, 0x00, 0x00, 0x00, 0x00}, // ,
    {0x08, 0x08, 0x08, 0x00, 0x00, 0x00}, // -
    {0x20, 0x00, 0x00, 0x00, 0x00, 0x00}, // .
    {0x30, 0x0c, 0x02, 0x00, 0x00, 0x00}, // /
    {0x1c, 0x22, 0x22, 0x22, 0x1e, 0x00}, // 0
    {0x02, 0x3e, 0x00, 0x00, 0x00, 0x00}, // 1
    {0x32, 0x2a, 0x2a, 0x24, 0x00, 0x00}, // 2
    {0x2a, 0x2a, 0x2a, 0x16, 0x00, 0x00}, // 3
    {0x0e, 0x10, 0x10, 0x3e, 0x10, 0x00}, // 4
    {0x2e, 0x2a, 0x2a, 0x12, 0x00, 0x00}, // 5
    {0x3c, 0x2a, 0x2a, 0x2a, 0x12, 0x00}, // 6
    {0x06, 0x02, 0x22, 0x12, 0x0e, 0x00}, // 7
    {0x14, 0x2a, 0x2a, 0x2a, 0x16, 0x00}, // 8
    {0x04, 0x2a, 0x2a, 0x2a, 0x1e, 0x00}, // 9
    {0x24, 0x00, 0x00, 0x00, 0x00, 0x00}, // :
    {0x64, 0x00, 0x00, 0x00, 0x00, 0x00}, // ;
    {0x08, 0x14, 0x22, 0x00, 0x00, 0x00}, // <
    {0x14, 0x14, 0x14, 0x00, 0x00, 0x00}, // =
    {0x22, 0x14, 0x08, 0x00, 0x00, 0x00}, // >
    {0x02, 0x2a, 0x0a, 0x04, 0x00, 0x00}, // ?
    {0x3c, 0x02, 0x1a, 0x2a, 0x22, 0x1e}, // @
    {0x3c, 0x12, 0x12, 0x12, 0x3e, 0x00}, // A
    {0x3c, 0x2a, 0x2a, 0x2e, 0x10, 0x00}, // B
    {0x1c, 0x22, 0x22, 0x22, 0x00, 0x00}, // C
    {0x3c, 0x22, 0x22, 0x22, 0x1c, 0x00}, // D
    {0x3c, 0x2a, 0x2a, 0x2a, 0x00, 0x00}, // E
    {0x3c, 0x12, 0x12, 0x12, 0x00, 0x00}, // F
    {0x3c, 0x22, 0x22, 0x2a, 0x1a, 0x00}, // G
    {0x3e, 0x08, 0x08, 0x3e, 0x00, 0x00}, // H
    {0x22, 0x3e, 0x22, 0x00, 0x00, 0x00}, // I
    {0x30, 0x22, 0x22, 0x1e, 0x00, 0x00}, // J
    {0x3e, 0x08, 0x0c, 0x32, 0x00, 0x00}, // K
    {0x3e, 0x20, 0x20, 0x20, 0x00, 0x00}, // L
    {0x3c, 0x02, 0x02, 0x3c, 0x02, 0x02}, // M
    {0x3c, 0x02, 0x02, 0x02, 0x3e, 0x00}, // N
    {0x1c, 0x22, 0x22, 0x22, 0x1e, 0x00}, // O
    {0x3c, 0x12, 0x12, 0x12, 0x0e, 0x00}, // P
    {0x1c, 0x22, 0x22, 0x62, 0x1e, 0x00}, // Q
    {0x3c, 0x12, 0x12, 0x32, 0x0e, 0x00}, // R
    {0x24, 0x2a, 0x2a, 0x12, 0x00, 0x00}, // S
    {0x02, 0x02, 0x3e, 0x02, 0x02, 0x00}, // T
    {0x1e, 0x20, 0x20, 0x20, 0x1e, 0x00}, // U
    {0x0e, 0x10, 0x20, 0x10, 0x0e, 0x00}, // V
    {0x3e, 0x20, 0x20, 0x1e, 0x20, 0x20}, // W
    {0x36, 0x08, 0x08, 0x36, 0x00, 0x00}, // X
    {0x26, 0x28, 0x28, 0x1e, 0x00, 0x00}, // Y
    {0x32, 0x2a, 0x2a, 0x26, 0x00, 0x00}, // Z
    {0x3e, 0x22, 0x00, 0x00, 0x00, 0x00}, // [
    {0x02, 0x0c, 0x30, 0x00, 0x00, 0x00}, // "\"
    {0x22, 0x3e, 0x00, 0x00, 0x00, 0x00}, // ]
    {0x04, 0x02, 0x04, 0x00, 0x00, 0x00}, // ^
    {0x20, 0x20, 0x20, 0x00, 0x00, 0x00}, // _
    {0x02, 0x04, 0x00, 0x00, 0x00, 0x00}, // `
    {0x3c, 0x12, 0x12, 0x12, 0x3e, 0x00}, // a
    {0x3c, 0x2a, 0x2a, 0x2e, 0x10, 0x00}, // b
    {0x1c, 0x22, 0x22, 0x22, 0x00, 0x00}, // c
    {0x3c, 0x22, 0x22, 0x22, 0x1c, 0x00}, // d
    {0x3c, 0x2a, 0x2a, 0x2a, 0x00, 0x00}, // e
    {0x3c, 0x12, 0x12, 0x12, 0x00, 0x00}, // f
    {0x3c, 0x22, 0x22, 0x2a, 0x1a, 0x00}, // g
    {0x3e, 0x08, 0x08, 0x3e, 0x00, 0x00}, // h
    {0x22, 0x3e, 0x22, 0x00, 0x00, 0x00}, // i
    {0x30, 0x22, 0x22, 0x1e, 0x00, 0x00}, // j
    {0x3e, 0x08, 0x0c, 0x32, 0x00, 0x00}, // k
    {0x3e, 0x20, 0x20, 0x20, 0x00, 0x00}, // l
    {0x3c, 0x02, 0x02, 0x3c, 0x02, 0x02}, // m
    {0x3c, 0x02, 0x02, 0x02, 0x3e, 0x00}, // n
    {0x1c, 0x22, 0x22, 0x22, 0x1e, 0x00}, // o
    {0x3c, 0x12, 0x12, 0x12, 0x0e, 0x00}, // p
    {0x1c, 0x22, 0x22, 0x62, 0x1e, 0x00}, // q
    {0x3c, 0x12, 0x12, 0x32, 0x0e, 0x00}, // r
    {0x24, 0x2a, 0x2a, 0x12, 0x00, 0x00}, // s
    {0x02, 0x02, 0x3e, 0x02, 0x02, 0x00}, // t
    {0x1e, 0x20, 0x20, 0x20, 0x1e, 0x00}, // u
    {0x0e, 0x10, 0x20, 0x10, 0x0e, 0x00}, // v
    {0x3e, 0x20, 0x20, 0x1e, 0x20, 0x20}, // w
    {0x36, 0x08, 0x08, 0x36, 0x00, 0x00}, // x
    {0x26, 0x28, 0x28, 0x1e, 0x00, 0x00}, // y
    {0x32, 0x2a, 0x2a, 0x26, 0x00, 0x00}, // z
    {0x08, 0x3e, 0x22, 0x00, 0x00, 0x00}, // {
    {0x3e, 0x00, 0x00, 0x00, 0x00, 0x00}, // |
    {0x22, 0x3e, 0x08, 0x00, 0x00, 0x00}, // }
    {0x04, 0x02, 0x02, 0x00, 0x00, 0x00}, // ~
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00}};

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

int width=0;
int height=0;

void initRenderer(long int infoLoc){
	screenData = (void *)infoLoc;
	width = screenData->width;
	height = screenData->height;

}


int getHeight(){
	return height;
}

int getWidth()
{
	return width;
}

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

void clearAll(){
	renderArea(0,0,width,height,BG_COLOR);
}