typedef unsigned short int tileVal; //16 bits baby

struct State
{
    tileVal grid[9][9];
    int r, c, guessedVal;
};