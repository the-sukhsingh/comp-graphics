#include <graphics.h>
#include <iostream>
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

void midpointCircle(int centerX, int centerY, int radius, int color, int originX, int originY, int zoom)
{
    int x = 0;
    int y = radius;
    int p = 1 - radius;

    while (x <= y)
    {
        // Draw the eight octants
        pixel(centerX + x, centerY + y, color, originX, originY, zoom);
        pixel(centerX + y, centerY + x, color, originX, originY, zoom);
        pixel(centerX - y, centerY + x, color, originX, originY, zoom);
        pixel(centerX - x, centerY + y, color, originX, originY, zoom);
        pixel(centerX - x, centerY - y, color, originX, originY, zoom);
        pixel(centerX - y, centerY - x, color, originX, originY, zoom);
        pixel(centerX + y, centerY - x, color, originX, originY, zoom);
        pixel(centerX + x, centerY - y, color, originX, originY, zoom);

        x++;

        if (p <= 0)
        {
            p = p + 2 * x + 1;
        }
        else
        {
            y--;
            p = p + 2 * x - 2 * y + 1;
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
    int originX = 400;
    int originY = 300;
    int zoom = 25;

    drawCoordinateSystem(originX, originY, zoom);

    // Draw a Circle at (0,0) of radius 10
    midpointCircle(0, 0, 10, RED, originX, originY, zoom);
    

    getch();
    closegraph();

    return 0;
}