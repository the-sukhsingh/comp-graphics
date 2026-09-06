#include <graphics.h>
#include <stack>
#include "animation_ui.h"

void boundaryFill(int startX, int startY, int fillColor, int boundaryColor)
{
    if (getpixel(startX, startY) == boundaryColor ||
        getpixel(startX, startY) == fillColor)
        return;

    std::stack<std::pair<int, int>> pixels;
    pixels.push({startX, startY});
    int processed = 0;

    while (!pixels.empty())
    {
        const int x = pixels.top().first;
        const int y = pixels.top().second;
        pixels.pop();

        if (x < 0 || x > getmaxx() || y < 0 || y > getmaxy())
            continue;

        const int color = getpixel(x, y);
        if (color == boundaryColor || color == fillColor)
            continue;

        putpixel(x, y, fillColor);
        processed++;
        if (processed % 150 == 0)
        {
            showFillCalculation("Boundary fill", processed, x, y);
            showTableRow(processed / 150, x, y, processed);
        }
        pixels.push({x + 1, y});
        pixels.push({x - 1, y});
        pixels.push({x, y + 1});
        pixels.push({x, y - 1});
    }
}

int main()
{
    initwindow(800, 600, "Computer Graphics");
    setbkcolor(BLACK);
    cleardevice();

    char title[] = "Boundary Fill Algorithm";
    char subtitle[] = "Four-connected fill stopped by the white boundary";
    drawUiHeader(title, subtitle);
    drawCalculationTable("Fill progress");
    setcolor(WHITE);
    rectangle(120, 150, 500, 450);
    boundaryFill(310, 300, LIGHTGREEN, WHITE);
    showComplete("Boundary fill complete");

    getch();
    closegraph();
    return 0;
}