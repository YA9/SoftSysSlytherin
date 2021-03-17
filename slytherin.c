#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include "conio/conio.h"

#define UP 0;
#define DOWN 1;
#define LEFT 2;
#define RIGHT 3;

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
struct coordinate snake;

struct Node
{
    int x;
    int y;
    struct Node *next;
    struct Node *prev;
    struct Node *head;
    struct Node *tail;
};
struct Node *head; /* Global variable - pointer to head node */
struct Node *tail; /* Global variable - pointer to tail node */

struct Node *getNewNode(int x, int y)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    (*newNode).x = x;
    (*newNode).y = y;
    (*newNode).prev = NULL;
    (*newNode).next = NULL;
    (*newNode).head = NULL;
    (*newNode).tail = NULL;
    return newNode;
}

void insertAtHead(int x, int y)
{
    struct Node *newNode = getNewNode(x, y);
    if (head == NULL && tail == NULL)
    {
        // struct Node *newNode = getNewNode(5, 5);
        head = newNode;
        tail = newNode;
        return;
    }
    // if (tail->next == head)
    // {

    //     tail->next = newNode;
    //     newNode->prev = tail;
    //     return;
    // }
    head->prev = newNode;
    // tail->next = newNode;
    (*newNode).next = head;
    head = newNode;
    (*newNode).x = x;
    (*newNode).y = y;

    struct Node *temp = head;
    while (temp->prev != NULL)
    {
        temp = temp->prev;
    }

    // tail = temp;
    tail->next = temp->next;
    // tail->prev = NULL;

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

void pop()
{
    // while (tempy->prev != NULL)
    // {
    //     tempy = tempy->prev;
    // }
    // // tail = tempy;
    // tempy->prev = NULL;
    // tempy = head;
    tail = tail->prev;
    // tail->prev = NULL;
}

void print()
{
    struct Node *temp = tail;
    // printf("Forward: ");
    while (temp != NULL)
    {
        printToCoordinates(temp->x, temp->y, "*");
        // printf("%d ", temp->x);
        temp = temp->prev;
        // usleep(200000);
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
    insertAtHead(10, 25);
    insertAtHead(10, 26);
    insertAtHead(10, 27);
    insertAtHead(10, 28);
    insertAtHead(10, 29);
    insertAtHead(10, 30);
    char c;
    int i = 1;
    while (1)
    {
        struct Node *temp = head;
        if (c_kbhit() != 0)
        {
            // printf("click: %c", c_getch());
            switch (c_getch())
            {
            case 'w':
                c = 'w';
                break;
            case 'a':
                c = 'a';
                break;
            case 's':
                c = 's';
                break;
            case 'd':
                c = 'd';
                break;
            }
        }
        // printf("THISCHAR: %c", c);
        switch (c)
        {
        case 'w':
            insertAtHead(temp->x - 1, temp->y);
            pop();
            break;
        case 'a':
            insertAtHead(temp->x, temp->y - 1);
            pop();
            break;
        case 's':
            insertAtHead(temp->x + 1, temp->y);
            pop();
            break;
        case 'd':
            insertAtHead(temp->x, temp->y + 1);
            pop();
            break;
        }
        i += 1;
        if (i == 100)
        {
            break;
        }
        system("clear");
        load();
        print();
        usleep(200000);
    }
    // int val;
    // scanf("input: %i", &val);
    // printf("\nYou inputted: %i", val);
    sleep(3);
    snake.direction = UP;
    // insertAtHead(11, 25);
    // insertAtHead(12, 25);
    // insertAtHead(13, 25);
    // insertAtHead(14, 25);

    // print();

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