#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>

void printToCoordinates(int y, int x, char text[])
{
    printf("\033[%d;%dH%s\n", y, x, text);
}

struct coordinate
{
    int x;
    int y;
    int direction;
};

struct coordinate coordinate;

int length;

int main()
{
    system("clear");

    load();
    // printToCoordinates(5, 15, "hello");
}

void load()
{
    for (int i = 7; i < 75; i++)
    {
        printToCoordinates(2, i, "=");
    }
    for (int i = 3; i < 20; i++)
    {
        printToCoordinates(i, 74, "|");
    }
    for (int i = 3; i < 20; i++)
    {
        printToCoordinates(i, 7, "|");
    }
    for (int i = 7; i < 75; i++)
    {
        printToCoordinates(20, i, "=");
    }
    printf("\n");
}