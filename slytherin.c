#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
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
// struct coordinate head;

struct Node
{
    int x;
    int y;
    struct Node *next;
    struct Node *prev;
    struct Node *head;
    // struct Node *tail;
};
struct Node *head; /* Global variable - pointer to head node */

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

void insertAtHead(int x, int y)
{
    struct Node *newNode = getNewNode(x, y);
    if (head == NULL)
    {
        // struct Node *newNode = getNewNode(5, 5);
        head = newNode;
        return;
    }
    head->prev = newNode;
    (*newNode).next = head;
    head = newNode;
    (*newNode).x = x;
    (*newNode).y = y;

    // struct Node temp = *newNode;
    // for (int i = 0; i < 30; i++)
    // {
    //     xs[i] = temp.x;
    //     ys[i] = temp.y;
    //     if (temp.next == NULL)
    //     {
    //         return;
    //     }
    //     temp = *temp.next;
    //     // temp.x += 1;
    // }
}

void print()
{
    struct Node *temp = head;
    // printf("Forward: ");
    while (temp != NULL)
    {
        printToCoordinates(temp->x, temp->y, "*");
        // printf("%d ", temp->x);
        temp = temp->next;
        usleep(200000);
    }
    // printf("\n");
}

int main()
{
    int length;
    system("clear"); /* Clears the terminal */
    length = 5;
    // head.x = 25;
    // head.y = 10;
    // int xs[30];
    // int ys[30];
    // printf("x: %d, y: %d\n\n", xs[0], ys[0]);
    // struct Node *newNode = getNewNode(10, 25);
    insertAtHead(11, 25);
    insertAtHead(12, 25);
    insertAtHead(13, 25);
    insertAtHead(14, 25);

    print();

    // struct Node temp = *newNode;
    // for (int i = 0; i < 30; i++)
    // {
    //     xs[i] = temp.x;
    //     ys[i] = temp.y;
    //     if (temp.next == NULL)
    //     {
    //         return;
    //     }
    //     temp = *temp.next;
    //     // temp.x += 1;
    // }
    // insertAtHead(11, 25, xs, ys);
    // insertAtHead(12, 25, xs, ys);
    // xs[0] = 10;
    // ys[0] = 25;
    // printf("x: %d, y: %d\n", xs[0], ys[0]);
    // xs[0] = 10;
    // ys[0] = 25;
    // printToCoordinates(xs[0], ys[0], "*");
    // printToCoordinates(xs[1], ys[1], "*");
    // printToCoordinates(xs[2], ys[2], "*");
    // printToCoordinates(xs[3], ys[3], "*");
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