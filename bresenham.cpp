#include <graphics.h>
#include <iostream>
#include "animation_ui.h"
using namespace std;

void pixel(int x, int y, int color, int originX, int originY, int zoom)
{
    int screenX = originX + x * zoom;
    int screenY = originY - y * zoom;
    setfillstyle(SOLID_FILL, color);
    // draw a filled rectangle to represent the pixel in color
    bar(
        screenX - zoom/2,
        screenY - zoom/2,
        screenX + zoom/2 - 1,
        screenY + zoom/2 + 1);
}

void drawCoordinateSystem(int originX, int originY, int zoom)
{
    // X-axis
    line(0, originY, getmaxx(), originY);

    // Y-axis
    line(originX, 0, originX, getmaxy());

    // X-axis numbering
    for (int x = 0; originX + x * zoom < getmaxx(); x++)
    {
        int screenX = originX + x * zoom;

        // Tick
        line(screenX, originY - 3,
             screenX, originY + 3);

        char text[10];
        sprintf(text, "%d", x);

        outtextxy(screenX + 2, originY + 5, text);
    }

    // Negative X-axis
    for (int x = -1; originX + x * zoom >= 0; x--)
    {
        int screenX = originX + x * zoom;

        line(screenX, originY - 3,
             screenX, originY + 3);

        char text[10];
        sprintf(text, "%d", x);

        outtextxy(screenX - 8, originY + 5, text);
    }

    // Y-axis numbering
    for (int y = 1; originY - y * zoom >= 0; y++)
    {
        int screenY = originY - y * zoom;

        // Tick
        line(originX - 3, screenY,
             originX + 3, screenY);

        char text[10];
        sprintf(text, "%d", y);

        outtextxy(originX - 20, screenY - 5, text);
    }

    // Negative Y-axis
    for (int y = -1; originY - y * zoom < getmaxy(); y--)
    {
        int screenY = originY - y * zoom;

        line(originX - 3, screenY,
             originX + 3, screenY);

        char text[10];
        sprintf(text, "%d", y);

        outtextxy(originX - 25, screenY - 5, text);
    }

    // Origin label
    char originLabel[] = "0";
    outtextxy(originX + 5, originY + 5, originLabel);
}

void bresenhamLine(int x1, int y1, int x2, int y2, int color, int originX, int originY, int zoom){
    int x = x1;
    int y = y1;
    int dx = x2 - x1;
    int dy = y2 - y1;
    int p;
    int step = 1;
    if (abs(dx) > abs(dy)){
        p = 2 * abs(dy) - abs(dx);
        while (x <= x2){
            pixel(x, y, color, originX, originY, zoom);
            showCalculation("Bresenham line", step++, x, y, p);
            showTableRow(step - 1, x, y, p);
            x += 1;
            if (p < 0){
                p += 2 * abs(dy);
            }
            else{
                p += 2 * abs(dy) - 2 * abs(dx);
                y += 1;
            }
        }
    } else {
        p = 2 * abs(dx) - abs(dy);
        while (y <= y2){
            pixel(x, y, color, originX, originY, zoom);
            showCalculation("Bresenham line", step++, x, y, p);
            showTableRow(step - 1, x, y, p);
            y += 1;
            if (p < 0){
                p += 2 * abs(dx);
            }
            else{
                x += 1;
                p += 2 * abs(dx) - 2 * abs(dy);
            }
        }
    }

}

int main()
{
    int gd = DETECT, gm;

    // 800 x 600 window
    initwindow(800, 600, "Computer Graphics");

    setbkcolor(BLACK);
    cleardevice();

    // Coordinate system settings
    int originX = 100;
    int originY = 500;
    int zoom = 25;

    drawCoordinateSystem(originX, originY, zoom);
    char title[] = "Bresenham Line Algorithm";
    char subtitle[] = "Incremental rasterization with live decision parameter";
    drawUiHeader(title, subtitle);
    drawCalculationTable("Decision table");

    // Draw a straight line from 1,1 to 8,5

    bresenhamLine(1, 1, 8, 5, RED, originX, originY, zoom);
    showComplete("Bresenham line complete");

    getch();
    closegraph();

    return 0;
}