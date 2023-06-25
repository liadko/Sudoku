#include <stdio.h>
#include <stdlib.h>

//returns the option count of a tile
//puts a valid guess into *p_aValidOption
int optionCount(tileVal val, int* p_aValidOption)
{
    int options = 0;
    int pos = 1 << 4;
    for(int i = 0; i < 9; i++)
    {
        if((val & pos) != 0) //has 1 in position
        {
            options++;
            if(p_aValidOption != NULL) *p_aValidOption = (i+1);
        }
        pos <<= 1;
    }
    
    return options;
}

//returns if the tile is immidiately deducable
//0 - no possibilities, 1 - one possibility, 2 - more than 1 possibility
int isDeducable(tileVal val, int* p_onlyOptionValue)
{
    int options = 0;
    int pos = 1 << 4;
    for(int i = 0; i < 9; i++)
    {
        if((val & pos) != 0) //has 1 in position
        {
            options++;
            if(options > 1)
                return 2;
            if(p_onlyOptionValue != NULL) *p_onlyOptionValue = (i + 1);
        }
        pos <<= 1;
    }
    // if(possibles != 1)
    // {
    //     wprintf(L"Possible Count in this tile is not 1, something weird with the algorithm.");
    // }
    
    return options;
}

int couldBe(tileVal val, int option)
{
    short pos = 1 << (3+option);
    return (pos&val)>0;
}

int isCertain(tileVal val, int* p_certainVal)
{
    
    if((val & 0xF) > 0)
    {
        if(p_certainVal != NULL)
            *p_certainVal = val & 0xF;
        return 1;
    }
    return 0;
}

void printVal(tileVal val)
{
    //certain
    int certain;
    if(isCertain(val, &certain))
    {
        wprintf(L"The Tile Is Surely %d\n", certain);
        return;
    }

    //uncertain
    wprintf(L"The Tile Could Be: ");
    for(int i = 1; i <= 9; i++)
    {
        //is i possible
        short pos = 1 << (3+i);
        if((pos & val) > 0)
            wprintf(L"%d ", i);

    }

    wprintf(L"\n");

}

tileVal createEmptyTile()
{
    return (tileVal)0b0001111111110000;
}

//certain = [1 - 9]
tileVal createCertainTileWithVal(int certain)
{
    if(certain > 9 || certain < 0)
        wprintf(L"Can't get a certain tile of value %d.", certain);
    return (tileVal)certain;
}