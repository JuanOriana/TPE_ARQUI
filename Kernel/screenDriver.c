#include <graphicRenderer.h>
#include <screenDriver.h>
#include <font.h>

int cursorPosX=0;
int cursorPosY=0;

void initVideo(){
    initRenderer(0x0000000000005C00);
    cleanScreen();
}

int putChar(char c,unsigned int color){
    if (cursorPosX+CHAR_WIDTH*FONT_SCALING>getWidth()) //Me paso de ancho con esta insercion? Si es asi salto
        newLine();

    int res = renderChar(c,cursorPosX,cursorPosY,color);
    cursorPosX+=FONT_SCALING*CHAR_WIDTH;
    return res;
}

void newLine(){
    cursorPosX=0;
    cursorPosY += FONT_SCALING * CHAR_HEIGHT;
    if (cursorPosY==getHeight()){
        //SCROLL UP
        cleanScreen();
    }

}

void cleanScreen(){
    clearAll();
    cursorPosX = 0;
    cursorPosY = 0;
}
