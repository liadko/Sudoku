#include <stdio.h>
#include <stdlib.h>

wchar_t *chars = L"0123456789!\"#$\%ABCDEFGHIJKLMNOPQRSTUVWXYZ&\'()*+,-./:;<=>?@[\\]^_`{|}~abcdefghijklmnopqrstuvwxyz";

void drawHorizontalLine(int isThick)
{
    wprintf(L"\t\t\t"); // left padding
    for (int i = 0; i < 7 * 9 + 10; i++)
    {
        if (i % (8 * 3) == 0)
            wprintf(L"╋");
        else if (i % 8 == 0)
            wprintf(L"┼");
        else if (isThick)
            wprintf(L"━");
        else
            wprintf(L"┄");
    }
    wprintf(L"\n");
}

void drawVerticalLine(int isThick)
{
    if (isThick)
        wprintf(L"┃");
    else
        wprintf(L"┆");
}

wchar_t letterToPrint(struct State *board, int tileIndex[], int indexWithinTile)
{
    int row = tileIndex[0], col = tileIndex[1];
    tileVal val = board->grid[row][col];

    int certain;
    if(isCertain(val, &certain)) //certain tile
    {
        if(indexWithinTile != 4)
            return L' ';
            
        return '0' + certain;
    }

    //uncertain tile
    if (couldBe(val, indexWithinTile + 1))
        return '0' + indexWithinTile + 1;
    else
        return L'·';//L'·';
}

void printBoxRow(struct State *board, int letterRowIndex)
{
    wprintf(L"\t\t\t"); // left padding

    int tileRowIndex = letterRowIndex / 3;

    // for each tile in row
    for (int tileColumnIndex = 0; tileColumnIndex < 9; tileColumnIndex++)
    {
        int tileIndex[2] = {tileRowIndex, tileColumnIndex};

        // vertical line
        drawVerticalLine(tileColumnIndex % 3 == 0);

        // print all 3 letters in the current tile row
        for (int letterInTileColumnIndex = 0; letterInTileColumnIndex < 3; letterInTileColumnIndex++)
        {
            // 0 - 8 index based on position in the tile
            int indexWithinTile = letterRowIndex % 3 * 3 + letterInTileColumnIndex;

            wprintf(L" %lc", letterToPrint(board, tileIndex, indexWithinTile));
        }
        wprintf(L" "); // space before next line
    }
    wprintf(L"┃\n"); // last line in the box row
}

void printState(struct State *board, wchar_t description[])
{
    wprintf(L"\n\t\t%s\n", description);
    for (int tileRowIndex = 0; tileRowIndex < 9; tileRowIndex++) // for every row of tiles
    {
        // Line on top of tile-row
        drawHorizontalLine(tileRowIndex % 3 == 0);

        // Entire Tile Row, one letter-row at a time
        for (int rowIndexWithinBoxRow = 0; rowIndexWithinBoxRow < 3; rowIndexWithinBoxRow++)
            printBoxRow(board, tileRowIndex * 3 + rowIndexWithinBoxRow);
    }

    drawHorizontalLine(1); // bottom line thick
    wprintf(L"\n\n");
}

void printStateString(struct State* board, wchar_t description[])
{
    wprintf(L"%-18s", description);
    for (int r = 0; r < 9; r++)
            for (int c = 0; c < 9; c++)
            {
                tileVal currentTile = board->grid[r][c];
                
                int certainVal;
                if (isCertain(currentTile, &certainVal))
                    wprintf(L"%lc", L'0' + certainVal);
                else
                    wprintf(L"·");
            }
    wprintf(L"\n");
}
