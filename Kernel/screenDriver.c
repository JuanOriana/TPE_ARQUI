#include <graphicRenderer.h>
#include <screenDriver.h>
#include <fontConsts.h>

int cursorPosX=0;
int cursorPosY=0;
int maxX,maxY;

void initVideo(){
    initRenderer(0x0000000000005C00);
    //Determino los limites redondeados del posicionamiento de caracteres (para saber donde volver despues de un \b)
    maxX = (getWidth()/ABS_WIDTH)*ABS_WIDTH;
    maxY = (getHeight() / ABS_HEIGHT) * ABS_HEIGHT;
    cleanScreen();
}

int putChar(char c,unsigned int color){
    if (cursorPosX+ABS_WIDTH>maxX) //Me paso de ancho con esta insercion? Si es asi salto
        newLine();

    if (c=='\n'){ //newline
        newLine();
        return 1;
    }
    if (c=='\b') //backspace
    {
        backspace();
        return 1;
    }
    int res = renderChar(c,cursorPosX,cursorPosY,color);
    cursorPosX+=ABS_WIDTH;
    return res;
}

void newLine(){
    cursorPosX=0;
    cursorPosY += ABS_HEIGHT;
    if (cursorPosY>=maxY){
        scrollUp(ABS_HEIGHT);
        cursorPosY = maxY - ABS_HEIGHT;
    }

}

void cleanScreen(){
    clearAll();
    cursorPosX = 0;
    cursorPosY = 0;
}

void backspace(){
    if (cursorPosX==0){
        if (cursorPosY==0)
            return;
        cursorPosY-=ABS_HEIGHT;
        cursorPosX = maxX;
 
    }
    cursorPosX -= ABS_WIDTH;
    renderArea(cursorPosX, cursorPosY, 
        cursorPosX + ABS_WIDTH, cursorPosY + ABS_HEIGHT, 0x000000);
}
