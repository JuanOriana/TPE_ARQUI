#include <graphicRenderer.h>
#include <screenDriver.h>
#include <fontConsts.h>

#define ENTER_KEY 13

static int cursorPosX = 0;
static int cursorPosY = 0;
static int maxX, maxY;
static int figLine=0;

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

    if (c=='\n'||c==ENTER_KEY){ //newline
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

//Posiiconamiento de figuras del tamano del DOBLE de una letra
int putFig(int*fig, unsigned int color){
    if (cursorPosX + ABS_WIDTH*2 > maxX) //Me paso de ancho con esta insercion? Si es asi salto
        newLine();
    figLine=1;
    int res = renderFig(fig, cursorPosX, cursorPosY, color);
    cursorPosX += ABS_WIDTH*2;
    return res;
}

void newLine(){
    int scrollDist = ABS_HEIGHT;
    //Si puse una figura en este linea, debo saltar el doble!
    if (figLine)
        scrollDist*=2;
    figLine=0;
    cursorPosX=0;
    cursorPosY += scrollDist;
    if (cursorPosY>=maxY){
        scrollUp(scrollDist);
        cursorPosY = maxY - scrollDist;
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
