#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
// #include <mem.h>

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
struct coordinate head;

struct Node
{
    int x;
    int y;
    struct Node *next;
    struct Node *prev;
    struct Node *head;
    // struct Node *tail;
};
struct Node *snake; /* Global variable - pointer to snake node */

struct Node *getNewNode(int x, int y)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    (*newNode).x = x;
    (*newNode).y = y;
    (*newNode).prev = NULL;
    (*newNode).next = NULL;
    (*newNode).head = NULL;
    // (*newNode).tail = NULL;
    return newNode;
}

void insertAtHead(int x, int y, char *xs, char *ys)
{
    struct Node *newNode = getNewNode(x, y);
    if ((*newNode).head == NULL)
    {
        // struct Node *newNode = getNewNode(5, 5);
        (*newNode).head = newNode;
        return;
    }
    (*newNode).head->prev = newNode;
    (*newNode).next = (*newNode).head;
    (*newNode).head = newNode;
    (*newNode).x = x;
    (*newNode).y = y;

    // char *xs = malloc(30);
    // char *ys = malloc(30);
    struct Node temp = *newNode;
    xs[0] = 10;
    ys[0] = 25;
    for (int i = 0; i < 30; i++)
    {
        // xs[i] = temp.x;
        // ys[i] = temp.y;
        if (temp.next == NULL)
        {
            return;
        }
        temp = *temp.next;
    }
}

int length;

/*  */
int main()
{
    system("clear"); /* Clears the terminal */
    length = 5;
    // head.x = 25;
    // head.y = 10;
    char xs[30];
    char ys[30];
    printf("%d\n", xs[0]);
    insertAtHead(25, 10, xs, ys);
    printf("%d\n ", xs[0]);
    // xs[0] = 10;
    // ys[0] = 25;
    printToCoordinates(xs[0], ys[0], "*");
    load(); /* Prints game board */
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