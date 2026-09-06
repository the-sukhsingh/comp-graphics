#ifndef ANIMATION_UI_H
#define ANIMATION_UI_H

#include <graphics.h>
#include <cstdio>

inline void drawUiHeader(const char *title, const char *subtitle)
{
    setfillstyle(SOLID_FILL, BLACK);
    bar(0, 0, getmaxx(), 74);
    setcolor(DARKGRAY);
    line(0, 73, getmaxx(), 73);

    setcolor(LIGHTCYAN);
    char titleText[80];
    std::snprintf(titleText, sizeof(titleText), "%s", title);
    outtextxy(18, 12, titleText);

    setcolor(LIGHTGRAY);
    char subtitleText[120];
    std::snprintf(subtitleText, sizeof(subtitleText), "%s", subtitle);
    outtextxy(18, 34, subtitleText);
}

inline void showCalculation(const char *algorithm, int step, int x, int y, int decision)
{
    setfillstyle(SOLID_FILL, BLACK);
    bar(0, 48, getmaxx(), 72);

    setcolor(YELLOW);
    char status[180];
    std::snprintf(status, sizeof(status), "%s   step: %d   x: %d   y: %d   decision: %d",
                  algorithm, step, x, y, decision);
    outtextxy(18, 54, status);
    delay(100);
}

inline int calculationTableLeft()
{
    return getmaxx() >= 700 ? getmaxx() - 245 : getmaxx() - 235;
}

inline void drawCalculationTable(const char *title)
{
    const int left = calculationTableLeft();
    const int right = getmaxx() - 12;

    setfillstyle(SOLID_FILL, BLACK);
    bar(left, 86, right, getmaxy() - 12);
    setcolor(DARKGRAY);
    rectangle(left, 86, right, getmaxy() - 12);
    setcolor(LIGHTCYAN);

    char tableTitle[60];
    std::snprintf(tableTitle, sizeof(tableTitle), "%s", title);
    outtextxy(left + 10, 96, tableTitle);

    setcolor(LIGHTGRAY);
    char headings[] = "Step     X       Y       Decision";
    outtextxy(left + 10, 116, headings);
    setcolor(DARKGRAY);
    line(left + 8, 132, right - 8, 132);
}

inline void showTableRow(int step, int x, int y, int decision)
{
    const int left = calculationTableLeft();
    const int right = getmaxx() - 12;
    const int visibleRows = (getmaxy() - 154) / 18;
    const int row = (step - 1) % visibleRows;
    const int rowTop = 137 + row * 18;

    if (row == 0)
    {
        setfillstyle(SOLID_FILL, BLACK);
        bar(left + 5, 134, right - 5, getmaxy() - 17);
    }

    char values[100];
    std::snprintf(values, sizeof(values), "%-8d%-8d%-8d%-8d", step, x, y, decision);
    setcolor(WHITE);
    outtextxy(left + 10, rowTop, values);
}

inline void showFillCalculation(const char *algorithm, int processed, int x, int y)
{
    setfillstyle(SOLID_FILL, BLACK);
    bar(0, 48, getmaxx(), 72);

    setcolor(YELLOW);
    char status[180];
    std::snprintf(status, sizeof(status), "%s   pixels filled: %d   current: (%d, %d)",
                  algorithm, processed, x, y);
    outtextxy(18, 54, status);
    delay(4);
}

inline void showComplete(const char *message)
{
    setfillstyle(SOLID_FILL, BLACK);
    bar(0, 48, getmaxx(), 72);

    setcolor(LIGHTGREEN);
    char status[120];
    std::snprintf(status, sizeof(status), "%s   |   Press any key to close", message);
    outtextxy(18, 54, status);
}

#endif
