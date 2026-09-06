#include <graphics.h>
#include <iostream>
#include "animation_ui.h"
using namespace std;

void pixel(int x, int y, int color, int originX, int originY, int zoom)
{
    int screenX = originX + x * zoom;
    int screenY = originY - y * zoom;

    setfillstyle(SOLID_FILL, color);
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
    outtextxy(originX + 5, originY + 5, "0");
}

int round(float number)
{
    return static_cast<int>(number + 0.5f);
}

void dda(int x1, int y1, int x2, int y2, int originX, int originY, int zoom)
{
    
    int dx = x2 - x1;
    int dy = y2 - y1;
    int steps;
    if (abs(dx) > abs(dy))
    {
        steps = abs(dx);
    }
    else
    {
        steps = abs(dy);
    }

    float xIncrement = dx / (float)steps;
    float yIncrement = dy / (float)steps;
    float x = x1;
    float y = y1;

    for (int i = 0; i <= steps; i++)
    {
        pixel(round(x), round(y), WHITE, originX, originY, zoom);
        showCalculation("DDA line", i + 1, round(x), round(y), steps);
        showTableRow(i + 1, round(x), round(y), steps);
        x += xIncrement;
        y += yIncrement;
    }
}

int main()
{
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");
    // 600 x 400 window
    initwindow(600, 400, "Computer Graphics");

    setbkcolor(BLACK);
    cleardevice();

    // Coordinate system settings
    int originX = 100;
    int originY = 300;
    int zoom = 30;

    // Draw Coordinate System
    drawCoordinateSystem(originX, originY, zoom);
    char title[] = "DDA Line Algorithm";
    char subtitle[] = "Step-by-step interpolation with rounded pixels";
    drawUiHeader(title, subtitle);
    drawCalculationTable("Interpolation table");

    // DDA
    int x1 = 2;
    int y1 = 3;
    int x2 = 8;
    int y2 = 5;

    dda(x1, y1, x2, y2, originX, originY, zoom);
    showComplete("DDA line complete");

    getch();
    closegraph();

    return 0;
}
