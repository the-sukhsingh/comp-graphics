#include <graphics.h>
#include <iostream>
using namespace std;

void pixel(int x, int y, int color, int originX, int originY, int zoom)
{
    int screenX = originX + x * zoom;
    int screenY = originY - y * zoom;
    setfillstyle(SOLID_FILL, color);
    bar(
        screenX - zoom / 2,
        screenY - zoom / 2,
        screenX + zoom / 2 - 1,
        screenY + zoom / 2 + 1);
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
        // sprintf(text, "%d", x);

        // outtextxy(screenX + 2, originY + 5, text);
    }

    // Negative X-axis
    for (int x = -1; originX + x * zoom >= 0; x--)
    {
        int screenX = originX + x * zoom;

        line(screenX, originY - 3,
             screenX, originY + 3);

        char text[10];
        // sprintf(text, "%d", x);

        // outtextxy(screenX - 8, originY + 5, text);
    }

    // Y-axis numbering
    for (int y = 1; originY - y * zoom >= 0; y++)
    {
        int screenY = originY - y * zoom;

        // Tick
        line(originX - 3, screenY,
             originX + 3, screenY);

        char text[10];
        // sprintf(text, "%d", y);

        // outtextxy(originX - 20, screenY - 5, text);
    }

    // Negative Y-axis
    for (int y = -1; originY - y * zoom < getmaxy(); y--)
    {
        int screenY = originY - y * zoom;

        line(originX - 3, screenY,
             originX + 3, screenY);

        char text[10];
        // sprintf(text, "%d", y);

        // outtextxy(originX - 25, screenY - 5, text);
    }

    // Origin label
    outtextxy(originX + 5, originY + 5, "0");
}

void ellipsePlotPoints(int xc, int yc, int x, int y, int color, int originX, int originY, int zoom)
{
    pixel(xc + x, yc + y, color, originX, originY, zoom);
    pixel(xc - x, yc + y, color, originX, originY, zoom);
    pixel(xc + x, yc - y, color, originX, originY, zoom);
    pixel(xc - x, yc - y, color, originX, originY, zoom);
}

void midpointEllipse(int rx, int ry, int xc, int yc, int color, int originX, int originY, int zoom)
{

    int x = 0, y = ry;
    float p1 = ry * ry - rx * rx * ry + 0.25 * rx * rx;

    // Region 1
    while (2 * ry * ry * x < 2 * rx * rx * y)
    {
        ellipsePlotPoints(xc, yc, x, y, color, originX, originY, zoom);

        x++;
        if (p1 < 0)
        {
            p1 += 2 * ry * ry * x + ry * ry;
        }
        else
        {
            y--;
            p1 += 2 * ry * ry * x - 2 * rx * rx * y + ry * ry;
        }
    }

    // Region 2
    float p2 = ry * ry * (x + 0.5) * (x + 0.5) + rx * rx * (y - 1) * (y - 1) - rx * rx * ry * ry;

    while (y >= 0) {
        ellipsePlotPoints(xc, yc, x, y, color, originX, originY, zoom);

        y--;
        if (p2 > 0) {
            p2 += -2 * rx * rx * y + rx * rx;
        } else {
            x++;
            p2 += 2 * ry * ry * x - 2 * rx * rx * y + rx * rx;
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
    int zoom = 10;

    drawCoordinateSystem(originX, originY, zoom);

    // Draw an ellipse with rx = 8, ry = 6, centered at (0, 0)
    midpointEllipse(15, 25, 0, 0, BLUE, originX, originY, zoom);

    getch();
    closegraph();

    return 0;
}