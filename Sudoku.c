#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include <windows.h>
#include "Structs.h"
#include "Stack.h"
#include "Value.h"
#include "Graphics.h"
#include "Algorithm.h"



void printArr(int arr[], int len)
{
    printf("[");
    for (int i = 0; i < len; i++)
    {
        printf("%d", arr[i]);
        if (i < len - 1)
            printf(", ");
    }
    printf("]\n");
}

struct State *mainBoard;
// struct Node* p_head = NULL;

int main(int argc, char* argv[]) {
    
    _setmode(_fileno(stdout), 0x20000); //for wprintf, allowing unicode char printing

    // CMD arguments
    if(argc != 2)
    {
        wprintf(L"Expected One Argument, Got %d.\n", argc - 1);
        return -1;
    }


    
    //create board
    wprintf(L"Start.\n");
    mainBoard = emptyBoard();
    //printStateString(mainBoard, L"Empty Board:");
    setBoard(mainBoard, argv[1]);

    printState(mainBoard, L"Before:");
    
    //start timer
    LARGE_INTEGER freq, start, end;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&start);
    
    //----------------
    
    solve(&mainBoard);

    //----------------

    //stop timer
    QueryPerformanceCounter(&end);
    
    //printState(mainBoard, L"After:");
    printStateString(mainBoard, L"Current Board");
    printState(mainBoard, L"Final Board");

    double elapsedTime = (double)(end.QuadPart  - start.QuadPart ) / freq.QuadPart;

    wprintf(L"\nElapsed time: %.9lf seconds\n", elapsedTime);

    return 0;
}
