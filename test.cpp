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
    char title[] = "Pixel Plotting Demo";
    char subtitle[] = "Animated coordinate-to-pixel mapping";
    drawUiHeader(title, subtitle);
    drawCalculationTable("Pixel coordinates");

    // Draw a straight line from (0, 0) to (10, 10)
    for (int i = 0; i <= 10; ++i)
    {
        pixel(i, i, WHITE, originX, originY, zoom);
        showCalculation("Pixel plotting", i + 1, i, i, zoom);
        showTableRow(i + 1, i, i, zoom);
    }
    showComplete("Pixel plotting complete");

    getch();
    closegraph();

    return 0;
}