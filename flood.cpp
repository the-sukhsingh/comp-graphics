#include <graphics.h>
#include <stack>
#include "animation_ui.h"

void floodFill(int startX, int startY, int replacementColor)
{
    const int targetColor = getpixel(startX, startY);

    if (targetColor == replacementColor)
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

        if (getpixel(x, y) != targetColor)
            continue;

        putpixel(x, y, replacementColor);
        processed++;
        if (processed % 150 == 0)
        {
            showFillCalculation("Flood fill", processed, x, y);
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

    char title[] = "Flood Fill Algorithm";
    char subtitle[] = "Four-connected region replacement with a live fill queue";
    drawUiHeader(title, subtitle);
    drawCalculationTable("Fill progress");
    setcolor(WHITE);
    rectangle(120, 150, 500, 450);
    floodFill(310, 300, LIGHTBLUE);
    showComplete("Flood fill complete");

    getch();
    closegraph();

    return 0;
}